#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHIFT 3  // Shift value for Caesar Cipher

// Caesar Cipher Encryption function
char* caesar_encrypt(char* data, size_t length, int shift) {
    for (size_t i = 0; i < length; i++) {
        // Encrypt only alphabetical characters
        if (data[i] >= 'A' && data[i] <= 'Z') {
            data[i] = 'A' + (data[i] - 'A' + shift) % 26;
        } else if (data[i] >= 'a' && data[i] <= 'z') {
            data[i] = 'a' + (data[i] - 'a' + shift) % 26;
        }
    }
    return data;
}

// Caesar Cipher Decryption function
char* caesar_decrypt(char* data, size_t length, int shift) {
    for (size_t i = 0; i < length; i++) {
        // Decrypt only alphabetical characters
        if (data[i] >= 'A' && data[i] <= 'Z') {
            data[i] = 'A' + (data[i] - 'A' - shift + 26) % 26;
        } else if (data[i] >= 'a' && data[i] <= 'z') {
            data[i] = 'a' + (data[i] - 'a' - shift + 26) % 26;
        }
    }
    return data;
}

// Function to resolve variable references in a value
char* resolve_variable_references(const char *value, const char **keys, const char **values, int count) {
    char *resolved_value = strdup(value);
    char *temp_value = NULL;

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
    fprintf(fp, "char* caesar_decrypt(char* data, size_t length, int shift) {\n");
    fprintf(fp, "    for (size_t i = 0; i < length; i++) {\n");
    fprintf(fp, "        if (data[i] >= 'A' && data[i] <= 'Z') {\n");
    fprintf(fp, "            data[i] = 'A' + (data[i] - 'A' - shift + 26) %% 26;\n");
    fprintf(fp, "        } else if (data[i] >= 'a' && data[i] <= 'z') {\n");
    fprintf(fp, "            data[i] = 'a' + (data[i] - 'a' - shift + 26) %% 26;\n");
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
        char *p = escaped_value;
        for (size_t j = 0; j < length_value; j++) {
            if (values[i][j] == '\"') {
                *p++ = '\\'; // Escape the double quote
            }
            *p++ = values[i][j];
        }
        *p = '\0'; // Null-terminate the escaped string

        // Encrypt the key-value pairs
        fprintf(fp, "    \"%s=%s\",\n", caesar_encrypt(strdup(keys[i]), length_key, SHIFT), caesar_encrypt(escaped_value, strlen(escaped_value), SHIFT));

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
    fprintf(fp, "        caesar_decrypt(decrypted_key, strlen(decrypted_key), SHIFT);\n");

    // Compare the decrypted key with the input key
    fprintf(fp, "        if (strcmp(decrypted_key, key) == 0) {\n");
    fprintf(fp, "            strncpy(decrypted_value, env_value + 1, sizeof(decrypted_value));\n");
    fprintf(fp, "            caesar_decrypt(decrypted_value, strlen(decrypted_value), SHIFT);\n");
    fprintf(fp, "            return decrypted_value;\n");
    fprintf(fp, "        }\n");
    fprintf(fp, "    }\n");
    fprintf(fp, "    return NULL;\n");
    fprintf(fp, "}\n\n");

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

    // First, count the number of lines (key-value pairs)
    while (fgets(line, sizeof(line), fp)) {
        if (strchr(line, '=') != NULL) {
            (*count)++;
        }
    }

    // Allocate memory for the keys and values arrays
    *keys = malloc(*count * sizeof(char *));
    *values = malloc(*count * sizeof(char *));

    rewind(fp); // Reset file pointer to the beginning

    int i = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strchr(line, '=') != NULL) {
            line[strcspn(line, "\n")] = 0; // Remove newline character

            // Split the line into key and value
            char *equal_sign = strchr(line, '=');
            if (equal_sign != NULL) {
                size_t key_len = equal_sign - line;
                (*keys)[i] = strndup(line, key_len);

                // Value is the part after '='
                char *value = strdup(equal_sign + 1);
                (*values)[i] = resolve_variable_references(value, *keys, *values, *count);

                free(value); // Free the original value string
                i++;
            }
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

    // Generate the new C program with encrypted values
    generate_new_program(keys, values, count);

    // Free allocated memory
    for (int i = 0; i < count; i++) {
        free((char *)keys[i]);
        free((char *)values[i]);
    }
    free(keys);
    free(values);

    return 0;
}
