# Lesson 02: Features_of_Linux

## I. Câu hỏi tự luận

### Bài 1: So sánh Monolithic Kernel và Microkernel

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