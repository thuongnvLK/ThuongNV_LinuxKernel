# TÀI LIỆU HƯỚNG DẪN BÀI TẬP TRÊN LINUX  
## XÂY DỰNG HỆ THỐNG XÁC THỰC NGƯỜI DÙNG VÀ QUẢN LÝ QUYỀN TRUY CẬP KERNEL  

## 1. Giới thiệu  
Bài tập này hướng dẫn bạn xây dựng một hệ thống quản lý quyền truy cập kernel dựa trên xác thực người dùng.  
Hệ thống sẽ sử dụng một file ZIP để lưu trữ thông tin người dùng và chương trình kernel.  
Mỗi lần người dùng đăng nhập đúng, họ sẽ được cấp quyền truy cập vào kernel.  
Sau khi kernel chạy xong, hệ thống sẽ tự động reset quyền truy cập, yêu cầu người dùng đăng nhập lại.  

### **Quy trình hoạt động:**  
1. Giải nén file `users.txt` từ `kernel.zip`.  
2. Xác thực tài khoản bằng cách đối chiếu với `users.txt`.  
3. Nếu xác thực thành công, cập nhật quyền truy cập trong `users.txt`.  
4. Giải nén, biên dịch và chạy `kernel.c`.  
5. Sau khi `kernel.c` chạy xong, hệ thống sẽ reset quyền truy cập (đặt `access = 0`).  

---

## 2. Mục tiêu  
Sau khi hoàn thành bài tập này, bạn sẽ có thể:  
✅ Làm việc với file ZIP trong C để lưu trữ dữ liệu và chương trình.  
✅ Xây dựng hệ thống xác thực người dùng bằng file `users.txt`.  
✅ Quản lý quyền truy cập kernel bằng cách cập nhật trạng thái `access` trong `users.txt`.  
✅ Tự động reset quyền truy cập sau mỗi lần chạy kernel.  
✅ Giải nén, biên dịch và thực thi chương trình kernel trên Linux.  

---

## 3. Yêu cầu hệ thống  
### **Phần mềm cần thiết**  
Trước khi bắt đầu, bạn cần cài đặt các công cụ sau:  

🔹 **GCC (biên dịch C)**  
```sh
sudo apt update && sudo apt install gcc -y
```
🔹 Make (tạo Makefile tự động hóa biên dịch)
```sh
sudo apt install make -y
```
🔹 ZIP & UNZIP (nén và giải nén file ZIP)
```sh
sudo apt install zip unzip -y
```
🔹 Thư viện hỗ trợ ZIP (Miniz)
```sh
wget https://github.com/richgel999/miniz

./amalgamate.sh
```
## 4. Cấu trúc thư mục

Dự án được tổ chức như sau:
```
kernel_project/
│── src/                  # Thư mục chứa mã nguồn
│   ├── hala.c            # Chương trình xác thực và cấp quyền kernel
│   ├── miniz.c, miniz.h  # Thư viện hỗ trợ đọc file ZIP
│── kernel.zip            # File ZIP chứa dữ liệu
```
Bên trong file kernel.zip:
```
kernel.zip
├── users.txt   (Chứa thông tin đăng nhập: username|password|access)
├── kernel.c    (Chương trình kernel chỉ chạy sau khi xác thực thành công)
├── kernel.out
```

## 5. Các bước thực hiện

### 5.1. Tạo nội dung file users.txt

Tạo file users.txt để lưu thông tin đăng nhập:
```sh
echo "admin|1234|0" > users.txt
```
📌 Giải thích:

- admin: Tên đăng nhập
- 1234: Mật khẩu
- 0: Trạng thái truy cập (0 = chưa cấp quyền, 1 = đã có quyền)

### 5.2. Viết chương trình Kernel (kernel.c)

Tạo file kernel.c với nội dung sau:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Bạn đã được cấp quyền truy cập kernel thành công!\n");

    // Giải nén file users.txt từ kernel.zip
    system("unzip -o kernel.zip users.txt");

    // Ghi đè trạng thái access = 0 vào users.txt
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Lỗi: Không thể mở users.txt để reset quyền truy cập!\n");
        return 1;
    }
    fprintf(file, "admin|1234|0\n");  // Reset quyền truy cập
    fclose(file);

    // Cập nhật lại file users.txt vào kernel.zip
    system("zip -uj kernel.zip users.txt");

    printf("Quyền truy cập đã được reset. Bạn cần đăng nhập lại lần sau!\n");
    
    return 0;
}
```

### 5.3. Tạo file ZIP chứa dữ liệu

Gói users.txt và kernel.c vào kernel.zip:
```sh
zip -r kernel.zip users.txt kernel.c
```
Sau khi tạo xong, kernel.zip sẽ chứa:
```sh
users.txt
kernel.c
```
### 5.4. Viết chương trình hala.c

📌 Chương trình hala.c sẽ:
✅ Mở file ZIP và đọc users.txt.
✅ Yêu cầu nhập tài khoản và mật khẩu.
✅ Nếu đăng nhập đúng, cập nhật quyền truy cập (access = 1).
✅ Giải nén, biên dịch và chạy kernel.c.

### 5.5. Biên dịch và Chạy

✅ Biên dịch chương trình hala.c
```sh
mkdir bin
gcc -wall -g src/hala.c src/miniz.c -o bin/hala
```
✅ Chạy chương trình
```sh
./bin/hala kernel.zip
```
## 6. Kịch bản chạy chương trình
### 6.1. Trường hợp nhập đúng tài khoản & mật khẩu
```
Nhập tên đăng nhập: admin
Nhập mật khẩu: 1234
Đăng nhập thành công!
Giải nén kernel...
Biên dịch kernel...
Chạy kernel...
Bạn đã được cấp quyền truy cập kernel thành công!
Quyền truy cập đã được reset. Bạn cần đăng nhập lại lần sau!
```

6.2. Trường hợp nhập sai mật khẩu
```Nhập tên đăng nhập: admin
Nhập mật khẩu: 4321
Sai tên đăng nhập hoặc mật khẩu!
```

## 7. Các tính năng chính của Miniz

## Miniz cung cấp nhiều API để thao tác với ZIP.

| **Chức năng**          | **Hàm trong Miniz**                  |
|------------------------|-------------------------------------|
| Mở file ZIP           | `mz_zip_reader_init_file()`        |
| Đọc số lượng file     | `mz_zip_reader_get_num_files()`    |
| Đọc thông tin file    | `mz_zip_reader_file_stat()`        |
| Giải nén file         | `mz_zip_reader_extract_file_to_heap()` |
| Đóng file ZIP         | `mz_zip_reader_end()`              |
| Tạo file ZIP mới      | `mz_zip_writer_init_file()`        |
| Thêm file vào ZIP     | `mz_zip_writer_add_file()`         |
| Kết thúc & đóng ZIP   | `mz_zip_writer_finalize_archive()` |
