#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Bạn đã được cap quyen truy cập kernel thành công!\n");

    // Giai nén file users.txt từ kernel.zip
    system("unzip -o kernel.zip users.txt");

    // Ghi đè trạng thái access = 0 vào users.txt
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
	printf("Loi: Không the mo users.txt đe reset quyen truy cập!\n");
        return 1;
    }
    fprintf(file, "admin|1234|0\n");  // Reset quyền truy cập
    fclose(file);

    // Cập nhật lại file users.txt vào kernel.zip
    system("zip -uj kernel.zip users.txt");

    printf("Quyen truy cập đã được reset. Bạn can đăng nhập lại lan sau!\n");
    
    return 0;
}

