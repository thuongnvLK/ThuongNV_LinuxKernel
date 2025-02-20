#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  // Để sử dụng thời gian
#include "miniz.h"

void log_change(const char *username, const char *password, const char *access) {
    // Mở file config.txt để ghi lại sự thay đổi
    FILE *log_file = fopen("config.txt", "a");
    if (log_file == NULL) {
        printf("Lỗi: Không thể mở config.txt để ghi lại sự thay đổi!\n");
        return;
    }

    // Lấy thời gian hiện tại
    time_t current_time = time(NULL);
    char *time_str = ctime(&current_time); // Chuyển thời gian thành chuỗi
    time_str[strlen(time_str) - 1] = '\0';  // Xóa ký tự newline ở cuối chuỗi thời gian

    // Ghi lại thông tin vào file config.txt
    fprintf(log_file, "Thời gian: %s\n", time_str);
    fprintf(log_file, "Tên đăng nhập: %s, Mật khẩu: %s, Quyền truy cập: %s\n", username, password, access);
    fprintf(log_file, "--------------------------\n");

    fclose(log_file); // Đóng file sau khi ghi
}

void login(char *zip_filename) {
    // Mở file ZIP
    mz_zip_archive zip;
    memset(&zip, 0, sizeof(zip));

    // Mở file ZIP để đọc
    if (!mz_zip_reader_init_file(&zip, zip_filename, 0)) {
        printf("Lỗi: Không thể mở file ZIP.\n");
        return;
    }

    // Tìm file users.txt trong ZIP
    int file_index = mz_zip_reader_locate_file(&zip, "users.txt", NULL, 0);
    if (file_index < 0) {
        printf("Lỗi: Không tìm thấy file users.txt trong ZIP.\n");
        mz_zip_reader_end(&zip);
        return;
    }

    // Lấy thông tin file
    mz_zip_archive_file_stat file_stat;
    if (!mz_zip_reader_file_stat(&zip, file_index, &file_stat)) {
        printf("Lỗi: Không thể lấy thông tin file từ ZIP.\n");
        mz_zip_reader_end(&zip);
        return;
    }

    // Lấy kích thước của file
    size_t file_size = file_stat.m_uncomp_size;  // Sử dụng m_uncomp_size thay cho m_uncompressed_size
    char *buffer = malloc(file_size);
    if (!buffer) {
        printf("Lỗi: Không đủ bộ nhớ để đọc file.\n");
        mz_zip_reader_end(&zip);
        return;
    }

    // Giải nén file users.txt vào bộ nhớ
    mz_zip_reader_extract_to_mem(&zip, file_index, buffer, file_size, 0);
    mz_zip_reader_end(&zip);

    // Đọc và phân tích nội dung từ users.txt
    char username[100], password[100], access[10];
    sscanf(buffer, "%99[^|]|%99[^|]|%9s", username, password, access);
    free(buffer);  // Giải phóng bộ nhớ đã cấp phát

    // Lặp lại yêu cầu đăng nhập nếu sai
    while (1) {
        // Nhập tên đăng nhập và mật khẩu từ người dùng
        char input_username[100], input_password[100];
        printf("Nhập tên đăng nhập: ");
        scanf("%s", input_username);
        printf("Nhập mật khẩu: ");
        scanf("%s", input_password);

        // Kiểm tra thông tin đăng nhập
        if (strcmp(input_username, username) == 0 && strcmp(input_password, password) == 0) {
            printf("Đăng nhập thành công!\n");

            // Cập nhật quyền truy cập (access = 1)
            snprintf(access, sizeof(access), "1");

            // Cập nhật lại file users.txt với quyền truy cập đã thay đổi
            FILE *file = fopen("users.txt", "w");
            if (file == NULL) {
                printf("Lỗi: Không thể mở users.txt để ghi lại quyền truy cập!\n");
                return;
            }
            fprintf(file, "%s|%s|%s\n", username, password, access);
            fclose(file);

            // Ghi lại sự thay đổi vào config.txt
            log_change(username, password, access);

            // Cập nhật lại file vào kernel.zip
            system("zip -uj kernel.zip users.txt");

            // Giải nén và biên dịch kernel.c
            system("unzip -o kernel.zip kernel.c");
            // system("gcc kernel.c -o kernel");
            system("./kernel");

            printf("Quyền truy cập đã được cấp. Bạn có thể sử dụng kernel.\n");
            break;  // Thoát khỏi vòng lặp nếu đăng nhập thành công
        } else {
            printf("Sai tên đăng nhập hoặc mật khẩu! Vui lòng thử lại.\n");
        }
    }
}

int main() {
    login("kernel.zip");
    return 0;
}


// run ok
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
