#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHIFT 3  

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
    fprintf(fp,"#define SHIFT 3\n");

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
        // Encrypt the key-value pairs
        fprintf(fp, "    \"%s=%s\",\n", caesar_encrypt(strdup(keys[i]), length_key, SHIFT), caesar_encrypt(strdup(values[i]), length_value, SHIFT));
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
                (*values)[i] = strdup(equal_sign + 1);
                i++;
            }
        }
    }

    fclose(fp);
}

int main() {
    const char **keys, **values;
    int count;

    // Step 1: Parse the .env file
    parse_env_file(".env", &keys, &values, &count);

    // Step 2: Generate the new C program
    generate_new_program(keys, values, count);

    // Step 3: Compile the new C program
    system("gcc  -shared  -o env.so env.c  -fPIC");


    // Free the allocated memory
    for (int i = 0; i < count; i++) {
        free((char *)keys[i]);
        free((char *)values[i]);
    }
    free(keys);
    free(values);

    return 0;
}
