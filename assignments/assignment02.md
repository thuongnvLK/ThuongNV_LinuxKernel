# Lesson 02: Features_of_the_Linux_Kernel

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

### Bài 2: Mô hình "Everything as a File" trong Linux

#### 1. Giải thích mô hình "Everything as a File"

- Mô hình "Everything as a File" (Mọi thứ đều là File) là một quyết định thiết kế quan trọng trong hệ điều hành UNIX và Linux, theo đó hầu hết các đối tượng hệ thống được biểu diễn dưới dạng file. Điều này cho phép các ứng dụng thao tác với tất cả các đối tượng hệ thống bằng API file thông thường (ví dụ: open, read, write, close).

![Alt text](../images/setup4.png)

- Dưới đây là những điểm chính của mô hình này:
    - Thiết bị được biểu diễn như file: Để các ứng dụng có thể tương tác với các thiết bị phần cứng, chúng được biểu diễn thông qua các file đặc biệt gọi là device file. Các file này liên kết một tên file mà người dùng có thể thấy với một thiết bị tương ứng.

    - API thống nhất: Việc sử dụng API file tiêu chuẩn giúp đơn giản hóa quá trình tương tác với các đối tượng hệ thống khác nhau. Các ứng dụng không cần phải sử dụng các lệnh hoặc thư viện đặc biệt cho từng loại đối tượng.

    - Tính trừu tượng: Mô hình này cung cấp một lớp trừu tượng giúp ẩn đi các chi tiết triển khai phức tạp của các thiết bị và tài nguyên hệ thống. Các ứng dụng chỉ cần tương tác với các file, không cần quan tâm đến cách dữ liệu được lưu trữ hoặc thiết bị được điều khiển.

    - Tính nhất quán: Bằng cách đối xử với mọi thứ như file, hệ thống trở nên nhất quán hơn, dễ hiểu và dễ quản lý.

    - File ảo: Mô hình này không giới hạn ở file vật lý trên đĩa. Các file ảo (pseudo-file) như /proc và /sys cũng được sử dụng để thể hiện các cấu trúc dữ liệu của kernel và cung cấp thông tin hệ thống.

        -   /proc và /sys là các pseudo filesystem, thể hiện các cấu trúc dữ liệu kernel dưới dạng một hệ thống phân cấp thư mục và file.

- Cách mô hình "Everything as a File" hoạt động:
    - File system: Các file được tổ chức trong một hệ thống file phân cấp, bắt đầu từ thư mục gốc /.
    - Virtual File System (VFS): Một lớp trừu tượng trong kernel, cung cấp một giao diện thống nhất cho các hệ thống file khác nhau.
        - VFS định nghĩa các đối tượng chính như:
            - Superblock object: Đại diện cho một hệ thống file đã được mount.
            - Inode object: Đại diện cho một file hoặc thư mục.
            - Dentry object: Đại diện cho một thành phần trong đường dẫn.
            - File object: Đại diện cho một file đang mở.
    - Device driver: Mỗi thiết bị có một device driver tương ứng, cung cấp các thao tác chuẩn như open, read, write, và close. Khi một ứng dụng tương tác với một device file, kernel sẽ gọi các hàm tương ứng trong device driver.
#### 2. Nêu các đối tượng trong Linux hoạt động như file (ví dụ: thiết bị, tiến trình).

![Alt text](../images/setup5.png)

- Các loại file đặc biệt:
    - File thiết bị (device file): Đại diện cho các thiết bị phần cứng như ổ đĩa, máy in, hoặc cổng giao tiếp. Có hai loại chính:
        - File thiết bị ký tự (character device file): Thường được sử dụng cho các thiết bị truyền dữ liệu theo luồng như bàn phím hoặc cổng nối tiếp.
        - File thiết bị khối (block device file): Thường được sử dụng cho các thiết bị lưu trữ như ổ cứng hoặc ổ đĩa flash.
    - File đặc biệt khác:
        - FIFO (pipe): Được sử dụng cho giao tiếp giữa các tiến trình.
        - Socket file: Được sử dụng cho giao tiếp mạng.

- Lấy ví dụ về file /dev, /proc, socket, process descriptor.
    - File trong /dev (Device Files)
        - Chức năng: Các file trong thư mục /dev là device files, đại diện cho các thiết bị phần cứng hoặc thiết bị ảo. Chúng cung cấp giao diện cho các ứng dụng để tương tác với các thiết bị này.
        - Phân loại: Có hai loại chính:
            - Character device file: (ví dụ: /dev/ttyS0, /dev/null, /dev/random) dùng để giao tiếp với các thiết bị theo luồng byte như cổng serial, bàn phím, chuột, và các thiết bị khác.
            - Block device file: (ví dụ: /dev/sda, /dev/sda1, /dev/hda) dùng để giao tiếp với các thiết bị lưu trữ theo khối dữ liệu như ổ cứng, ổ flash.
        - Ví dụ cụ thể:
            - /dev/sda, /dev/sda1, /dev/sda2: Đại diện cho ổ cứng và các phân vùng của ổ cứng.
            - /dev/ttyS0: Đại diện cho cổng serial.
            - /dev/null: Một thiết bị ảo, mọi dữ liệu ghi vào đây đều bị bỏ qua.
            - /dev/zero: Một thiết bị ảo, khi đọc sẽ trả về các byte 0.
            - /dev/console: Đại diện cho console của hệ thống.
        - Cơ chế hoạt động: Khi một ứng dụng mở một device file, kernel sẽ gọi tới driver thiết bị tương ứng. Driver này sẽ thực hiện các thao tác I/O trên thiết bị thật sự. Các thao tác như open, read, write, close trên device file sẽ được chuyển đến driver thông qua VFS.
        - Tạo device file: Các device file có thể được tạo bằng lệnh mknod hoặc thông qua các trình quản lý thiết bị như udev, mdev.
    - File trong /proc (Process Filesystem)
        - Chức năng: /proc là một pseudo filesystem, không thực sự lưu trữ dữ liệu trên đĩa mà cung cấp một giao diện để xem thông tin về kernel và các tiến trình đang chạy. Các file và thư mục trong /proc được tạo động bởi kernel.
        - Cấu trúc:
            - /proc chứa các thư mục con tương ứng với mỗi tiến trình đang chạy trên hệ thống. Tên của các thư mục này là PID (Process ID) của tiến trình. Ví dụ: /proc/1234 chứa thông tin về tiến trình có PID là 1234.
            - Ngoài ra còn có các file khác trong /proc cung cấp thông tin chung về hệ thống, ví dụ: /proc/cpuinfo, /proc/meminfo, /proc/mounts.
        - Ví dụ cụ thể:
            - /proc/PID/status: Cung cấp thông tin chi tiết về trạng thái của một tiến trình.
            - /proc/PID/fd: Chứa các symbolic link đến các file descriptor mà tiến trình đó đang mở.
            - /proc/mounts: Danh sách các filesystem đã được mount.
            - /proc/devices: Liệt kê các thiết bị (block và character) và số major của chúng.
        - Cơ chế hoạt động: Khi một ứng dụng đọc một file trong /proc, kernel sẽ tạo dữ liệu tương ứng theo yêu cầu của ứng dụng, dữ liệu này có thể là các thông số của hệ thống hoặc thông tin của tiến trình. Các file trong /proc thường là dạng text để các ứng dụng dễ dàng xử lý. Một số file trong /proc có thể được ghi vào để thay đổi các tham số hệ thống.
        - Ứng dụng: Các công cụ hệ thống như ps, top, free sử dụng /proc để lấy thông tin.
    - Socket File
        - Chức năng: Socket file là một loại file đặc biệt được dùng cho giao tiếp mạng (network communication) hoặc giao tiếp giữa các tiến trình trên cùng một máy (IPC - inter-process communication). Chúng không phải là file vật lý trên đĩa.
        - Đặc điểm:
            - Socket file được tạo và quản lý thông qua API socket (ví dụ: BSD socket API).
            - Chúng cho phép các ứng dụng gửi và nhận dữ liệu qua mạng hoặc giữa các tiến trình.
            - Socket file có thể được sử dụng cho cả giao thức TCP và UDP.
            - Không giống như các device file, socket file không có node trong /dev, chúng được truy cập thông qua API socket.
        - Ví dụ: Các ứng dụng web server, client, chat đều sử dụng socket để giao tiếp.
    - Process Descriptor
        - Chức năng: Process descriptor (cấu trúc task_struct trong kernel Linux) là một cấu trúc dữ liệu quan trọng mà kernel sử dụng để lưu trữ thông tin về một tiến trình. Nó không phải là file mà là một cấu trúc trong bộ nhớ kernel.
        - Nội dung: Process descriptor chứa rất nhiều thông tin, bao gồm:
            - PID (Process ID): Số định danh duy nhất của tiến trình.
            - Trạng thái của tiến trình: (ví dụ: running, sleeping, zombie).
            - Thông tin về bộ nhớ: (ví dụ: địa chỉ bộ nhớ, các vùng nhớ đã được cấp phát).
            - Thông tin về file: (ví dụ: danh sách các file descriptor đang mở).
            - Thông tin về tín hiệu: (ví dụ: các tín hiệu đang chờ xử lý).
            - Thông tin về người dùng: (ví dụ: UID, GID).
            - Con trỏ đến các cấu trúc dữ liệu khác: ví dụ, files (con trỏ đến cấu trúc files_struct để quản lý các file đang mở), mm (con trỏ đến cấu trúc mm_struct để quản lý bộ nhớ), ....
        - Liên quan đến file: Cấu trúc task_struct có trường files, trỏ đến cấu trúc files_struct, chứa danh sách các file descriptor (mảng các con trỏ đến các file object) mà tiến trình đang mở. Mỗi file descriptor là một số nguyên nhỏ không âm, là index của mảng này.
        - Mối quan hệ: Khi một tiến trình mở một file, kernel sẽ tạo một file object và một file descriptor, sau đó lưu trữ thông tin về file này trong process descriptor của tiến trình đó.
        - Truy cập: Thông tin trong process descriptor có thể được truy cập (một phần) qua các file trong /proc/PID, ví dụ: /proc/PID/status.

#### 3. Chạy lệnh kiểm tra và phân tích đầu ra để chứng minh rằng Linux áp dụng mô hình này.


### Bài 3: Cách Linux thực hiện Preemptive Multitasking

#### 1. Giải thích Preemptive Multitasking là gì.

 - Preemptive Multitasking là một phương pháp quản lý đa nhiệm trong hệ điều hành, trong đó hệ điều hành (thông qua bộ điều phối - scheduler) có quyền quyết định khi nào một tiến trình đang chạy sẽ bị tạm dừng (preempted) và chuyển quyền sử dụng CPU cho một tiến trình khác.

- Preemptive Multitasking dựa vào hỗ trợ phần cứng, đặc biệt thông qua một bộ định thời tạo ra các ngắt ở các khoảng thời gian nhất định. Khi CPU đang xử lý mã chế độ người dùng và một ngắt phần cứng xảy ra, nó chuyển sang chế độ nhân để xử lý ngắt, với trình xử lý tick bộ định thời thực thi để tính toán thời gian sử dụng CPU của quá trình hiện tại. Điều này cho phép quản lý hiệu quả việc thực thi quá trình và phân bổ tài nguyên.

- Cơ chế hoạt động:
    - Bộ điều phối (scheduler) đóng vai trò trung tâm trong việc quyết định tiến trình nào sẽ chạy.
    - Preemption là hành động tạm dừng một tiến trình đang chạy, thường dựa trên các yếu tố như thời gian chạy hoặc mức độ ưu tiên.
    - Các hệ thống preemptive multitasking thường sử dụng timeslice, là khoảng thời gian mà một tiến trình được phép chạy. Tuy nhiên, Linux sử dụng cơ chế khác cho các tiến trình thông thường.
    - Hệ điều hành theo dõi thời gian sử dụng CPU của từng tiến trình để đưa ra quyết định lập lịch.
    - Preemption có thể xảy ra khi:
        - Một tiến trình đã sử dụng hết timeslice được cấp.
        - Một tiến trình có độ ưu tiên cao hơn chuyển sang trạng thái sẵn sàng (ready).
        - Một tiến trình thực hiện thao tác I/O hoặc một sự kiện block khác.
        - Một ngắt phần cứng hoặc phần mềm xảy ra.

- Cooperative Multitasking: Các tiến trình tự quyết định khi nào chúng sẽ nhường CPU cho tiến trình khác. Điều này có nghĩa là, một tiến trình có thể chiếm giữ CPU vô thời hạn, nếu nó không tự nguyện nhường lại.

#### 2. Mô tả vai trò của Linux Scheduler trong việc quản lý tiến trình.

- Vai trò của Linux Scheduler
    - Quản lý tiến trình: Linux Scheduler quyết định tiến trình nào được chạy trên CPU và khi nào.
    - Điều phối tiến trình: Scheduler quản lý các tiến trình đang ở trạng thái sẵn sàng và chọn tiến trình tiếp theo để chạy dựa trên chính sách và thuật toán.
    - Thực hiện Preemption: Scheduler có quyền tạm dừng tiến trình đang chạy và chuyển CPU cho tiến trình khác khi cần.
    - Các loại Scheduling: Linux hỗ trợ các loại scheduling khác nhau, bao gồm:
        - Timeshare: Dành cho các tiến trình thông thường, đảm bảo công bằng.
        - Real-time: Dành cho các ứng dụng thời gian thực, ưu tiên độ trễ thấp và tính quyết định

- Mô tả thuật toán Completely Fair Scheduler (CFS)
    - Mục tiêu: CFS được thiết kế để đảm bảo tính công bằng trong việc phân chia thời gian CPU giữa các tiến trình đang chạy. 
    - Mô hình hóa: CFS mô hình hóa việc lập lịch tiến trình như thể hệ thống có một bộ xử lý đa nhiệm hoàn hảo, nơi mỗi tiến trình sẽ nhận được 1/n thời gian của bộ xử lý, với n là số lượng tiến trình đang chạy.
    - Không sử dụng timeslice cố định: Khác với các bộ lập lịch truyền thống, CFS không sử dụng timeslice cố định cho các tiến trình. Thay vào đó, nó tính toán thời gian mà mỗi tiến trình nên chạy dựa trên tổng số tiến trình đang chạy và độ ưu tiên của chúng.
    - Cơ chế chính của CFS:
        - vruntime (thời gian chạy ảo):
            - CFS sử dụng một biến vruntime (virtual runtime) để theo dõi thời gian mà một tiến trình đã chạy. vruntime không phải là thời gian thực tế mà tiến trình đã sử dụng CPU, mà là một giá trị được điều chỉnh dựa trên độ ưu tiên của tiến trình.
            - vruntime được tính bằng cách cộng dồn thời gian thực tế mà tiến trình đã chạy, được "chuẩn hóa" (normalized) hoặc "cân bằng" (weighted) bởi số lượng tiến trình có thể chạy (runnable processes).
            - Tiến trình có nice value thấp hơn (ưu tiên cao hơn) sẽ có tốc độ tăng vruntime chậm hơn, cho phép nó chạy lâu hơn so với tiến trình có nice value cao hơn.
            - Đơn vị của vruntime là nanosecond, do đó nó không bị ràng buộc vào timer tick.
        - Cây đỏ-đen (red-black tree):
            - Các tiến trình đang chạy được lưu trữ trong một cây đỏ-đen, một loại cây tìm kiếm nhị phân tự cân bằng.
            - Cây này được sắp xếp dựa trên giá trị vruntime, với tiến trình có vruntime nhỏ nhất nằm ở nút bên trái nhất của cây.
            - Khi cần chọn tiến trình tiếp theo để chạy, CFS chỉ cần lấy nút bên trái nhất của cây, đây chính là tiến trình có vruntime nhỏ nhất.
            - Việc sử dụng cây đỏ-đen đảm bảo rằng việc tìm kiếm tiến trình tiếp theo có thể thực hiện trong thời gian O(log N), với N là số lượng tiến trình đang chạy. Tuy nhiên, Linux scheduler còn cache lại nút bên trái nhất, giúp việc tìm kiếm tiến trình kế tiếp có thể thực hiện trong thời gian O(1).
        - Nice value:
            - Nice value là một giá trị nguyên (từ -20 đến +19) được gán cho mỗi tiến trình, thể hiện độ ưu tiên của tiến trình đó.
            - Nice value thấp hơn tương ứng với độ ưu tiên cao hơn và ngược lại.
            - CFS sử dụng nice value để điều chỉnh tỷ lệ CPU mà mỗi tiến trình nhận được. Tiến trình có nice value thấp hơn sẽ nhận được phần CPU lớn hơn, trong khi tiến trình có nice value cao hơn sẽ nhận được phần CPU nhỏ hơn.
        -   Tính toán thời gian chạy:
            - Thay vì timeslice cố định, CFS tính toán thời gian chạy của mỗi tiến trình dựa trên tỷ lệ giữa trọng số (weight) của tiến trình và tổng trọng số của tất cả các tiến trình đang chạy.
            - Trọng số của tiến trình được điều chỉnh bởi nice value của nó.
            - CFS xác định một targeted latency (độ trễ mục tiêu), là khoảng thời gian mà mỗi tiến trình chạy ít nhất một lần. Thời gian chạy của từng tiến trình sẽ được điều chỉnh sao cho đạt được mục tiêu này.
            - Ngoài ra, CFS còn có một giá trị gọi là minimum granularity (độ chi tiết tối thiểu), là thời gian chạy tối thiểu của một tiến trình, nhằm tránh overhead do context switch quá thường xuyên.

## II. Bài tập thực hành.

### Yêu cầu: Thực hiện trên môi trường Linux, kiểm tra đầu ra của từng bước.

#### Làm việc với Kernel Module

- Kiểm tra các module kernel đang chạy.
    - Lệnh: `lsmod`