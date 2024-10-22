#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHIFT 3  // Shift value for Caesar Cipher

// Caesar Cipher Encryption function
char* encrypt(char* data, size_t length, int shift) {
    for (size_t i = 0; i < length; i++) {
        // Encrypt alphabetical characters
        if (data[i] >= 'A' && data[i] <= 'Z') {
            data[i] = 'A' + (data[i] - 'A' + shift) % 26;
        } else if (data[i] >= 'a' && data[i] <= 'z') {
            data[i] = 'a' + (data[i] - 'a' + shift) % 26;
        }
        // Encrypt numbers and dot (for IPs)
        else if (data[i] >= '0' && data[i] <= '9') {
            data[i] = '0' + (data[i] - '0' + shift) % 10;
        } else if (data[i] == '.') {
            data[i] = (data[i] == '.') ? '*' : '.'; // Just an example transformation for the dot
        }
    }
    return data;
}

// Caesar Cipher Decryption function
char* decrypt(char* data, size_t length, int shift) {
    for (size_t i = 0; i < length; i++) {
        // Decrypt alphabetical characters
        if (data[i] >= 'A' && data[i] <= 'Z') {
            data[i] = 'A' + (data[i] - 'A' - shift + 26) % 26;
        } else if (data[i] >= 'a' && data[i] <= 'z') {
            data[i] = 'a' + (data[i] - 'a' - shift + 26) % 26;
        }
        // Decrypt numbers and dot (for IPs)
        else if (data[i] >= '0' && data[i] <= '9') {
            data[i] = '0' + (data[i] - '0' - shift + 10) % 10;
        } else if (data[i] == '*') {
            data[i] = '.';
        }
    }
    return data;
}

// Function to resolve variable references in a value
char* resolve_variable_references(const char *value, const char **keys, const char **values, int count) {
    char *resolved_value = strdup(value);
    if (resolved_value == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    char *temp_value;

    do {
        temp_value = resolved_value;
        for (int i = 0; i < count; i++) {
            char *var_placeholder = strstr(resolved_value, "${");
            if (var_placeholder != NULL) {
                char *var_end = strchr(var_placeholder, '}');
                if (var_end) {
                    // Extract variable name
                    size_t var_name_length = var_end - (var_placeholder + 2);
                    char var_name[256];
                    strncpy(var_name, var_placeholder + 2, var_name_length);
                    var_name[var_name_length] = '\0';

                    // Find the variable value
                    const char *var_value = NULL;
                    for (int j = 0; j < count; j++) {
                        if (strcmp(var_name, keys[j]) == 0) {
                            var_value = values[j];
                            break;
                        }
                    }

                    // Replace the placeholder with the variable value if found
                    if (var_value) {
                        size_t new_length = (var_placeholder - resolved_value) + strlen(var_value) + strlen(var_end + 1) + 1;
                        char *new_resolved_value = malloc(new_length);
                        if (new_resolved_value == NULL) {
                            perror("Memory allocation failed");
                            exit(EXIT_FAILURE);
                        }
                        strncpy(new_resolved_value, resolved_value, var_placeholder - resolved_value);
                        strcpy(new_resolved_value + (var_placeholder - resolved_value), var_value);
                        strcat(new_resolved_value, var_end + 1);

                        free(resolved_value);
                        resolved_value = new_resolved_value;
                    }
                }
            }
        }
    } while (temp_value != resolved_value); // Loop until no more replacements are made

    return resolved_value;
}

// Function to write a new C program with the environment variables
void generate_new_program(const char **keys, const char **values, int count) {
    FILE *fp = fopen("env.c", "w");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write the environment variables as an array
    fprintf(fp, "#include <stdio.h>\n");
    fprintf(fp, "#include <stdlib.h>\n");
    fprintf(fp, "#include <string.h>\n\n");
    fprintf(fp, "#define SHIFT 3\n");

    // Caesar Cipher Decryption function in the new program
    fprintf(fp, "char* decrypt(char* data, size_t length, int shift) {\n");
    fprintf(fp, "    for (size_t i = 0; i < length; i++) {\n");
    fprintf(fp, "        if (data[i] >= 'A' && data[i] <= 'Z') {\n");
    fprintf(fp, "            data[i] = 'A' + (data[i] - 'A' - shift + 26) %% 26;\n");
    fprintf(fp, "        } else if (data[i] >= 'a' && data[i] <= 'z') {\n");
    fprintf(fp, "            data[i] = 'a' + (data[i] - 'a' - shift + 26) %% 26;\n");
    fprintf(fp, "        } else if (data[i] >= '0' && data[i] <= '9') {\n");
    fprintf(fp, "            data[i] = '0' + (data[i] - '0' - shift + 10) %% 10;\n");
    fprintf(fp, "        } else if (data[i] == '*') {\n");
    fprintf(fp, "            data[i] = '.';\n");
    fprintf(fp, "        }\n");
    fprintf(fp, "    }\n");
    fprintf(fp, "    return data;\n");
    fprintf(fp, "}\n\n");

    // Declare the array of environment variables
    fprintf(fp, "const char *env_vars[] = {\n");
    for (int i = 0; i < count; i++) {
        size_t length_key = strlen(keys[i]);
        size_t length_value = strlen(values[i]);

        // Replace double quotes in values with escaped double quotes
        char *escaped_value = malloc(length_value * 2 + 1); // Allocate enough space
        if (escaped_value == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        char *p = escaped_value;
        for (size_t j = 0; j < length_value; j++) {
            if (values[i][j] == '\"') {
                *p++ = '\\'; // Escape the double quote
            }
            *p++ = values[i][j];
        }
        *p = '\0'; // Null-terminate the escaped string

        // Encrypt the key-value pairs
        fprintf(fp, "    \"%s=%s\",\n", encrypt(strdup(keys[i]), length_key, SHIFT), encrypt(escaped_value, strlen(escaped_value), SHIFT));

        free(escaped_value); // Free the escaped string
    }
    fprintf(fp, "};\n\n");

    // Function to retrieve the decrypted value of a key
    fprintf(fp, "const char* get_env_value(const char *key) {\n");
    fprintf(fp, "    static char decrypted_key[256];\n");
    fprintf(fp, "    static char decrypted_value[256];\n");
    fprintf(fp, "    for (int i = 0; i < %d; i++) {\n", count);
    fprintf(fp, "        const char *env = env_vars[i];\n");
    fprintf(fp, "        const char *env_value = strchr(env, '=');\n");
    fprintf(fp, "        if (env_value == NULL) continue;\n");

    // Decrypt the key part
    fprintf(fp, "        strncpy(decrypted_key, env, env_value - env);\n");
    fprintf(fp, "        decrypted_key[env_value - env] = '\\0';\n");
    fprintf(fp, "        decrypt(decrypted_key, strlen(decrypted_key), SHIFT);\n");

    // Compare the decrypted key with the input key
    fprintf(fp, "        if (strcmp(decrypted_key, key) == 0) {\n");
    fprintf(fp, "            strncpy(decrypted_value, env_value + 1, sizeof(decrypted_value));\n");
    fprintf(fp, "            decrypt(decrypted_value, strlen(decrypted_value), SHIFT);\n");
    fprintf(fp, "            return decrypted_value;\n");
    fprintf(fp, "        }\n");
    fprintf(fp, "    }\n");
    fprintf(fp, "    return NULL; // Not found\n");
    fprintf(fp, "}\n");

    fclose(fp);
}

// Function to parse the .env file
void parse_env_file(const char *filename, const char ***keys, const char ***values, int *count) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening .env file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    *count = 0;

    // Count the number of valid lines (key-value pairs)
    while (fgets(line, sizeof(line), fp)) {
        if (line[0] != '#' && line[0] != '\n') {
            (*count)++;
        }
    }

    // Allocate memory for keys and values
    *keys = malloc(*count * sizeof(char*));
    *values = malloc(*count * sizeof(char*));
    if (*keys == NULL || *values == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    rewind(fp); // Reset file pointer to the beginning

    int index = 0;
    // Read key-value pairs
    while (fgets(line, sizeof(line), fp) && index < *count) {
        if (line[0] != '#' && line[0] != '\n') {
            char *key = strtok(line, "=");
            char *value = strtok(NULL, "\n");

            if (key == NULL || value == NULL) {
                fprintf(stderr, "Invalid line format: %s", line);
                continue; // Skip invalid lines
            }

            (*keys)[index] = strdup(key);
            (*values)[index] = strdup(value);
            if ((*keys)[index] == NULL || (*values)[index] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                fclose(fp);
                exit(EXIT_FAILURE);
            }
            index++;
        }
    }

    fclose(fp);
}

int main() {
    const char **keys;
    const char **values;
    int count;

    // Parse the .env file
    parse_env_file(".env", &keys, &values, &count);

    // Generate a new C program with the environment variables
    generate_new_program(keys, values, count);

    // Clean up allocated memory
    for (int i = 0; i < count; i++) {
        free((void*)keys[i]);
        free((void*)values[i]);
    }
    free(keys);
    free(values);

    return 0;
}
