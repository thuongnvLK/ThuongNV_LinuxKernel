
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miniz.h"

void login(char *zip_filename) {
    // Open the ZIP file
    mz_zip_archive zip;
    memset(&zip, 0, sizeof(zip));

    // Initialize the ZIP reader
    if (!mz_zip_reader_init_file(&zip, zip_filename, 0)) {
        printf("Error: Unable to open ZIP file.\n");
        return;
    }

    // Locate the users.txt file inside the ZIP archive
    int file_index = mz_zip_reader_locate_file(&zip, "users.txt", NULL, 0);
    if (file_index < 0) {
        printf("Error: users.txt not found in the ZIP file.\n");
        mz_zip_reader_end(&zip);
        return;
    }

    // Get file information
    mz_zip_archive_file_stat file_stat;
    if (!mz_zip_reader_file_stat(&zip, file_index, &file_stat)) {
        printf("Error: Unable to get file information from ZIP.\n");
        mz_zip_reader_end(&zip);
        return;
    }

    // Get the file size
    size_t file_size = file_stat.m_uncomp_size;  // Use m_uncomp_size instead of m_uncompressed_size
    char *buffer = malloc(file_size);
    if (!buffer) {
        printf("Error: Not enough memory to read the file.\n");
        mz_zip_reader_end(&zip);
        return;
    }

    // Extract users.txt to memory
    mz_zip_reader_extract_to_mem(&zip, file_index, buffer, file_size, 0);
    mz_zip_reader_end(&zip);

    // Read and parse the content of users.txt
    char username[100], password[100], access[10];
    sscanf(buffer, "%99[^|]|%99[^|]|%9s", username, password, access);
    free(buffer);  // Free the allocated memory

    // Repeat the login request if the input is wrong
    while (1) {
        // Prompt the user for username and password
        char input_username[100], input_password[100];
        printf("Enter username: ");
        scanf("%s", input_username);
        printf("Enter password: ");
        scanf("%s", input_password);

        // Check login credentials
        if (strcmp(input_username, username) == 0 && strcmp(input_password, password) == 0) {
            printf("Login successful!\n");

            // Update the access rights (access = 1)
            snprintf(access, sizeof(access), "1");

            // Update users.txt with the new access rights
            FILE *file = fopen("users.txt", "w");
            if (file == NULL) {
                printf("Error: Unable to open users.txt to update access rights!\n");
                return;
            }
            fprintf(file, "%s|%s|%s\n", username, password, access);
            fclose(file);

            // Update the kernel.zip with the modified users.txt
            system("zip -uj kernel.zip users.txt");

            // Extract and compile kernel.c
            system("unzip -o kernel.zip kernel.c");
            system("gcc kernel.c -o kernel");
            system("./kernel");

            printf("Access rights granted. You can now use the kernel.\n");
            break;  // Exit the loop if login is successful
        } else {
            printf("Incorrect username or password! Please try again.\n");
        }
    }
}

int main() {
    login("kernel.zip");
    return 0;
}
