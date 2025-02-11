# Lesson 02: Features_of_Linux

## I. Câu hỏi tự luận

### Bài 1: So sánh Monolithic Kernel và Microkernel

#### Monolithic Structure

Một ví dụ về cấu trúc hạn chế như vậy là hệ điều hành UNIX nguyên bản, bao gồm hai phần có thể tách rời: kernel và các chương trình hệ thống. Kernel được tách thành một loạt giao diện và trình điều khiển thiết bị, những thành phần này đã được bổ sung và mở rộng theo thời gian khi UNIX phát triển. Chúng ta có thể xem hệ điều hành UNIX truyền thống như được phân lớp ở một mức độ nào đó, như minh họa trong Hình 2.12. Mọi thứ bên dưới giao diện lời gọi hệ thống và bên trên phần cứng vật lý đều thuộc về kernel. Kernel cung cấp hệ thống tệp, lập lịch CPU, quản lý bộ nhớ và các chức năng hệ điều hành khác thông qua các lời gọi hệ thống. Khi xem xét tổng thể, đó là một lượng lớn chức năng được kết hợp vào một không gian địa chỉ duy nhất.

![Alt text](Linux_Kernel\images\Figure_2_12.png)

#### Trình bày sự khác biệt giữa Monolithic Kernel và Microkernel


| Đặc điểm              | Monolithic Kernel                                  | Microkernel                                      |
|----------------------|------------------------------------------------|------------------------------------------------|
| **Cấu trúc**        | Kernel chứa hầu hết các dịch vụ hệ điều hành trong một không gian địa chỉ duy nhất. | Kernel chỉ giữ các chức năng lõi, còn các dịch vụ khác chạy ở không gian người dùng. |
| **Hiệu suất**       | Cao hơn do các dịch vụ chạy trực tiếp trong kernel, không cần giao tiếp qua message passing. | Thấp hơn do các dịch vụ phải giao tiếp qua message passing, gây overhead. |
| **Bảo mật & Ổn định** | Kém hơn, vì lỗi trong một phần của kernel có thể làm sập toàn bộ hệ thống. | Cao hơn, vì lỗi trong một dịch vụ người dùng không ảnh hưởng đến kernel. |
| **Khả năng mở rộng** | Khó mở rộng, vì cần sửa đổi trực tiếp kernel và phải biên dịch lại. | Dễ mở rộng, vì có thể thêm dịch vụ mới mà không cần thay đổi kernel. |
| **Giao tiếp**       | Các thành phần gọi trực tiếp lẫn nhau trong kernel. | Các thành phần giao tiếp thông qua **message passing**, gây tốn tài nguyên hơn. |
| **Ví dụ HĐH**       | Linux, Windows, macOS                             | QNX, Minix, Mach (dùng trong macOS) |

### Tóm tắt:
- **Monolithic Kernel**: Hiệu suất cao, nhưng khó mở rộng và kém bảo mật.
- **Microkernel**: Linh hoạt và bảo mật hơn, nhưng có độ trễ cao do cơ chế message passing.

#### So sánh ưu nhược điểm của hai mô hình này về hiệu suất, bải trì, bảo mật