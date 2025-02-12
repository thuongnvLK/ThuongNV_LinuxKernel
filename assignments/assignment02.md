# Lesson 02: Features_of_Linux

## I. Câu hỏi tự luận

### Bài 1: So sánh Monolithic Kernel và Microkernel

#### 1. Trình bày sự khác biệt giữa Monolithic Kernel và Microkernel

| Đặc điểm              | Monolithic Kernel                                  | Microkernel                                      |
|----------------------|------------------------------------------------|------------------------------------------------|
| **Cấu trúc**        | Kernel chứa hầu hết các dịch vụ hệ điều hành trong một không gian địa chỉ duy nhất. | Kernel chỉ giữ các chức năng lõi, còn các dịch vụ khác chạy ở không gian người dùng. |
| **Hiệu suất**       | Cao hơn do các dịch vụ chạy trực tiếp trong kernel, không cần giao tiếp qua message passing. | Thấp hơn do các dịch vụ phải giao tiếp qua message passing, gây overhead. |
| **Bảo mật & Ổn định** | Kém hơn, vì lỗi trong một phần của kernel có thể làm sập toàn bộ hệ thống. | Cao hơn, vì lỗi trong một dịch vụ người dùng không ảnh hưởng đến kernel. |
| **Khả năng mở rộng** | Khó mở rộng, vì cần sửa đổi trực tiếp kernel và phải biên dịch lại. | Dễ mở rộng, vì có thể thêm dịch vụ mới mà không cần thay đổi kernel. |
| **Giao tiếp**       | Các thành phần gọi trực tiếp lẫn nhau trong kernel. | Các thành phần giao tiếp thông qua **message passing**, gây tốn tài nguyên hơn. |
| **Ví dụ HĐH**       | Linux, Windows, macOS                             | QNX, Minix, Mach (dùng trong macOS) |

#### 2. So sánh ưu nhược điểm của hai mô hình này về hiệu suất, bải trì, bảo mật

| **Tiêu chí**            | **Monolithic Kernel** | **Microkernel** |
|------------------------|---------------------|----------------|
| **Hiệu suất (Performance)** | ✅ Hiệu suất cao, do tất cả các thành phần chạy trong không gian kernel, giúp giảm độ trễ và overhead khi giao tiếp giữa các thành phần. | ❌ Hiệu suất thấp hơn, do việc sử dụng message passing giữa các dịch vụ chạy trong không gian user và kernel, gây overhead. |
| **Bảo trì (Maintainability)** | ❌ Khó bảo trì, vì toàn bộ kernel là một khối lớn, việc thay đổi một phần có thể ảnh hưởng đến toàn hệ thống. | ✅ Dễ bảo trì, vì các thành phần được tách biệt, có thể thay đổi hoặc cập nhật từng phần mà không làm ảnh hưởng toàn bộ hệ thống. |
| **Bảo mật (Security)** | ❌ Ít bảo mật hơn, vì nếu một lỗi xảy ra trong kernel, nó có thể làm hỏng toàn bộ hệ thống do tất cả chạy trong cùng một không gian địa chỉ. | ✅ Bảo mật cao hơn, vì hầu hết các dịch vụ chạy trong không gian người dùng, nếu một dịch vụ bị lỗi hoặc bị tấn công, hệ thống vẫn có thể hoạt động bình thường. |
| **Mức độ linh hoạt** | ❌ Kém linh hoạt hơn, vì các tính năng mới phải được tích hợp trực tiếp vào kernel, yêu cầu biên dịch lại. | ✅ Linh hoạt hơn, vì có thể thêm hoặc thay đổi dịch vụ dễ dàng mà không cần chỉnh sửa kernel chính. |

**Tóm tắt**:
- **Monolithic Kernel**: Hiệu suất cao, nhưng khó mở rộng và kém bảo mật.
- **Microkernel**: Linh hoạt và bảo mật hơn, nhưng có độ trễ cao do cơ chế message passing.

#### 3. Giải thích tại sao Linux sử dụng Monolithic Kernel nhưng vẫn có tính linh hoạt cao.

- Sử dụng Loadable Kernel Modules (LKMs).
    - LKMs cho phép thêm hoặc gỡ bỏ các thành phần của kernel trong khi hệ thống đang chạy mà không cần biên dịch lại toàn bộ kernel.
    - Điều này giúp Linux có thể mở rộng hoặc thay đổi tính năng dễ dàng mà vẫn giữ hiệu suất cao của Monolithic Kernel.
- Tính Modular trong Kernel.
    - Linux kernel có kiến trúc modular, giúp các thành phần như trình điều khiển thiết bị (device drivers), hệ thống tập tin (file systems), giao thức mạng (network protocols) có thể được tải hoặc gỡ bỏ một cách linh hoạt.
    - Ví dụ: Khi cắm một thiết bị USB vào máy tính, Linux có thể tự động tải driver tương ứng mà không cần khởi động lại hệ thống.
- Hiệu suất cao và khả năng mở rộng.
    - Monolithic Kernel giúp Linux duy trì hiệu suất cao do tất cả các thành phần chạy trong cùng một không gian địa chỉ, tránh được overhead từ message passing như trong Microkernel.
    - Nhờ LKMs, Linux có thể mở rộng mà không làm giảm hiệu suất đáng kể.


----------------------------------
#### Monolithic Structure
Cấu trúc đơn giản nhất để tổ chức một hệ điều hành là không có cấu trúc nào cả. Nói cách khác, đặt toàn bộ chức năng của kernel vào một tệp nhị phân tĩnh duy nhất chạy trong một không gian địa chỉ duy nhất. Cách tiếp cận này—được gọi là cấu trúc monolithic (monolithic structure)—là một kỹ thuật phổ biến trong thiết kế hệ điều hành.
    
Một ví dụ về cấu trúc hạn chế như vậy là hệ điều hành UNIX nguyên bản, bao gồm hai phần có thể tách rời: kernel và các chương trình hệ thống. Kernel được tách thành một loạt giao diện và trình điều khiển thiết bị, những thành phần này đã được bổ sung và mở rộng theo thời gian khi UNIX phát triển. Chúng ta có thể xem hệ điều hành UNIX truyền thống như được phân lớp ở một mức độ nào đó, như minh họa trong Hình 2.12. Mọi thứ bên dưới giao diện lời gọi hệ thống và bên trên phần cứng vật lý đều thuộc về kernel. Kernel cung cấp hệ thống tệp, lập lịch CPU, quản lý bộ nhớ và các chức năng hệ điều hành khác thông qua các lời gọi hệ thống. Khi xem xét tổng thể, đó là một lượng lớn chức năng được kết hợp vào một không gian địa chỉ duy nhất.

![Alt text](../images/Figure_2_12.png)

Hệ điều hành Linux được xây dựng dựa trên UNIX và có cấu trúc tương tự, như minh họa trong Hình 2.13. Các ứng dụng thường sử dụng thư viện C chuẩn glibc khi giao tiếp với giao diện lời gọi hệ thống của kernel. Kernel của Linux có kiến trúc nguyên khối (monolithic), nghĩa là nó chạy hoàn toàn trong chế độ kernel trong một không gian địa chỉ duy nhất. Tuy nhiên, như chúng ta sẽ thấy trong Mục 2.8.4, nó có thiết kế mô-đun, cho phép kernel được sửa đổi trong thời gian chạy.

![Alt text](../images/Figure_2_13.png)

#### Microkernels

Chúng ta đã thấy rằng hệ thống UNIX nguyên bản có cấu trúc nguyên khối (monolithic). Khi UNIX mở rộng, kernel trở nên lớn và khó quản lý. Vào giữa những năm 1980, các nhà nghiên cứu tại Đại học Carnegie Mellon đã phát triển một hệ điều hành có tên Mach, sử dụng phương pháp vi nhân (microkernel) để mô-đun hóa kernel. Phương pháp này tổ chức hệ điều hành bằng cách loại bỏ tất cả các thành phần không thiết yếu khỏi kernel và triển khai chúng dưới dạng các chương trình cấp người dùng, chạy trong các không gian địa chỉ riêng biệt. Kết quả là một kernel nhỏ gọn hơn. Tuy nhiên, vẫn chưa có sự đồng thuận rõ ràng về việc dịch vụ nào nên được giữ lại trong kernel và dịch vụ nào nên triển khai trong không gian người dùng. Thông thường, vi nhân chỉ cung cấp quản lý tiến trình tối thiểu, quản lý bộ nhớ, và cơ chế giao tiếp giữa các thành phần. Hình 2.15 minh họa kiến trúc của một vi nhân điển hình.

![Alt text](../images/Figure_2_15.png)

Chức năng chính của vi nhân là cung cấp cơ chế giao tiếp giữa chương trình khách (client program) và các dịch vụ khác cũng đang chạy trong không gian người dùng. Giao tiếp được thực hiện thông qua truyền thông điệp (message passing), như đã mô tả trong Mục 2.3.3.5. Ví dụ, nếu chương trình khách muốn truy cập một tệp, nó phải tương tác với máy chủ tệp (file server). Tuy nhiên, chương trình khách và dịch vụ không tương tác trực tiếp mà giao tiếp gián tiếp bằng cách trao đổi thông điệp thông qua vi nhân.

Một lợi ích của phương pháp vi nhân là giúp mở rộng hệ điều hành dễ dàng hơn. Các dịch vụ mới được thêm vào không gian người dùng, do đó không cần sửa đổi kernel. Khi cần thay đổi kernel, số lượng chỉnh sửa thường ít hơn, vì vi nhân có kích thước nhỏ gọn hơn. Hệ điều hành có thể dễ dàng chuyển đổi từ thiết kế phần cứng này sang thiết kế phần cứng khác. Vi nhân cũng mang lại bảo mật và độ tin cậy cao hơn, vì hầu hết các dịch vụ chạy dưới dạng tiến trình người dùng thay vì tiến trình kernel. Nếu một dịch vụ gặp lỗi, phần còn lại của hệ điều hành vẫn hoạt động bình thường, không bị ảnh hưởng.

Có lẽ minh họa nổi tiếng nhất về hệ điều hành sử dụng microkernel là Darwin, thành phần kernel của các hệ điều hành macOS và iOS. Thực tế, Darwin bao gồm hai kernel, trong đó có Mach microkernel. Chúng ta sẽ tìm hiểu chi tiết hơn về hệ thống macOS và iOS trong Mục 2.8.5.1.

Một ví dụ khác là QNX, một hệ điều hành thời gian thực (real-time OS) dành cho các hệ thống nhúng. Microkernel QNX Neutrino cung cấp các dịch vụ như truyền thông bằng thông điệp (message passing) và lập lịch tiến trình (process scheduling). Nó cũng xử lý giao tiếp mạng cấp thấp (low-level network communication) và ngắt phần cứng (hardware interrupts). Tất cả các dịch vụ khác trong QNX được cung cấp bởi các tiến trình tiêu chuẩn chạy bên ngoài kernel ở chế độ người dùng (user mode).

Thật không may, hiệu suất của microkernel có thể bị ảnh hưởng do tăng chi phí hệ thống (system-function overhead).
Khi hai dịch vụ ở chế độ người dùng (user-level services) cần giao tiếp với nhau, các thông điệp phải được sao chép giữa các dịch vụ này, vì chúng nằm trong các không gian địa chỉ riêng biệt (separate address spaces). Ngoài ra, hệ điều hành có thể phải chuyển đổi tiến trình (process switching) để trao đổi thông điệp. Chi phí liên quan đến sao chép thông điệp (message copying) và chuyển đổi giữa các tiến trình (process switching) chính là trở ngại lớn nhất đối với sự phát triển của các hệ điều hành dựa trên microkernel. Hãy xem xét lịch sử của Windows NT: Phiên bản đầu tiên có một kiến trúc microkernel phân lớp (layered microkernel organization). Tuy nhiên, hiệu suất của phiên bản này thấp hơn so với Windows 95. Windows NT 4.0 đã phần nào khắc phục vấn đề hiệu suất bằng cách di chuyển một số lớp từ không gian người dùng (user space) sang không gian kernel (kernel space) và tích hợp chúng chặt chẽ hơn. Khi Windows XP ra đời, kiến trúc của Windows đã trở nên monolithic (nguyên khối) hơn so với microkernel. Mục 2.8.5.1 sẽ mô tả cách macOS giải quyết các vấn đề về hiệu suất của Mach microkernel.

### Modules

Có lẽ phương pháp thiết kế hệ điều hành tốt nhất hiện nay là sử dụng các mô-đun kernel có thể tải động (Loadable Kernel Modules - LKMs). Trong mô hình này, kernel có một tập hợp các thành phần lõi (core components) và có thể liên kết thêm các dịch vụ khác thông qua các mô-đun (modules),
có thể được tải vào khi khởi động hệ thống (boot time) hoặc trong quá trình chạy (run time). Loại thiết kế này rất phổ biến trong các hệ điều hành UNIX hiện đại, chẳng hạn như Linux, macOS và Solaris, cũng như trong Windows.

Ý tưởng của thiết kế này là kernel cung cấp các dịch vụ lõi (core services), trong khi các dịch vụ khác được triển khai một cách động (implemented dynamically) khi kernel đang chạy. Việc liên kết (linking) các dịch vụ một cách động tốt hơn so với việc thêm trực tiếp các tính năng mới vào kernel,
vì nếu làm vậy, ta sẽ phải biên dịch lại kernel (recompile the kernel) mỗi khi có sự thay đổi. Ví dụ, chúng ta có thể tích hợp trực tiếp các thuật toán lập lịch CPU (CPU scheduling) và quản lý bộ nhớ (memory management) vào kernel, sau đó thêm hỗ trợ cho các hệ thống tệp khác nhau (different file systems) bằng các mô-đun có thể tải động (loadable modules).

Kết quả tổng thể tương tự như một hệ thống phân lớp (layered system), vì mỗi phần trong kernel đều có giao diện được xác định và bảo vệ (defined, protected interfaces).
Tuy nhiên, nó linh hoạt hơn so với mô hình phân lớp, vì bất kỳ mô-đun nào cũng có thể gọi mô-đun khác (any module can call any other module). Cách tiếp cận này cũng giống với mô hình microkernel, vì mô-đun chính chỉ chứa các chức năng lõi (core functions) và có khả năng tải cũng như giao tiếp với các mô-đun khác (knowledge of how to load and communicate with other modules). Nhưng nó hiệu quả hơn so với microkernel, vì các mô-đun không cần sử dụng truyền thông qua thông điệp (message passing) để giao tiếp với nhau.

Linux sử dụng các mô-đun kernel có thể tải động (Loadable Kernel Modules - LKMs), chủ yếu để hỗ trợ trình điều khiển thiết bị (device drivers) và hệ thống tệp (file systems). LKMs có thể được chèn vào kernel ("inserted" into the kernel) khi hệ thống khởi động (booted) hoặc trong khi chạy (run time), chẳng hạn như khi một thiết bị USB được cắm vào máy đang hoạt động. Nếu kernel của Linux không có driver cần thiết, nó có thể được tải động (dynamically loaded).
LKMs cũng có thể được gỡ bỏ khỏi kernel trong thời gian chạy (removed from the kernel during run time). Đối với Linux, LKMs giúp kernel trở nên linh hoạt và có tính mô-đun (dynamic and modular kernel), trong khi vẫn duy trì hiệu suất cao của hệ thống monolithic (maintaining the performance benefits of a monolithic system). Chúng tôi sẽ hướng dẫn tạo LKMs trong Linux thông qua một số bài tập lập trình ở cuối chương này.