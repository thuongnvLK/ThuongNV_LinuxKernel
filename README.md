#   **LINUX KERNEL**

![Build Status](https://img.shields.io/badge/build-in%20progress-yellow)            
![Language: C](https://img.shields.io/badge/Language-C-yellow?logo=c&style=flat-square)     
![Version](https://img.shields.io/badge/Version-1.0-green?style=flat-square)     

<!-- ##  **Table of Contents**
[Lesson 01: Setting Up Your First Keil µVision Project](#lesson-01-setting-up-your-first-keil-µvision-project) 
1. [Install Keil C ARM Package for STM32](#1-install-keil-c-arm-package-for-stm32)  
2. [µVision Software Packs Download and Install](#2-µvision-software-packs-download-and-install)  
3. [Create a New Project](#3-create-a-new-project)  
4. [Add Source Files](#4-add-source-files)  
5. [Configure Project Options](#5-configure-project-options)  
6. [Build the Project](#6-build-the-project)  
7. [Debug (Optional)](#7-debug-optional)  
8. [Download (Optional)](#8-download-optional)  

[Lesson 02: General-purpose I/Os (GPIO)](#lesson-02-general-purpose-ios-gpio)
1. [What is GPIO ?](#1-what-is-gpio)  
2. [What is the GPIO Port ?](#2-what-is-the-gpio-port)   
3. [GPIO Modes](#3-gpio-modes)  
  3.1. [GPIO Output](#31-gpio-output)    
  3.2. [GPIO Input](#32-gpio-input)   
  3.3. [GPIO Input Modes](#33-gpio-input-modes)               
    3.3.1. [High-impedance or Floating](#331-high-impedance-or-floating)    
    3.3.2. [Pull-up](#332-pull-up)  
    3.3.3. [Pull-down](#333-pull-down)  
  3.4. [GPIO Output Modes](#34-gpio-output-modes)  
    3.4.1. [Push-pull](#341-push-pull)  
    3.4.2. [Open-drain](#342-open-drain)  
  3.5. [Analog Mode](#35-analog-mode)  
  3.6. [Alternate Function Mode](#36-alternate-function-mode)  
4. [Blink LED PC13](#4-blink-led-pc13)
    4.1. [Địa chỉ các thanh ghi](#41-địa-chỉ-các-thanh-ghi)  
    4.2. [Enable the peripheral's clock](#42-enable-the-peripherals-clock)  
5. [STM32F10x Standard Peripherals Firmware Library](#5-stm32f10x-standard-peripherals-firmware-library)    
  5.1. [Cấu hình và sử dụng ngoại vi (GPIO)](#51-cấu-hình-và-sử-dụng-ngoại-vi-gpio)  
    5.1.1. 	[Cấp clock cho ngoại vi](#511-cấp-clock-cho-ngoại-vi)  
    5.1.2. [Cấu hình ngoại vi](#512-cấu-hình-ngoại-vi) 

[Lesson 03: Interrupt and Timer](#lesson-03-interrupt-and-timer)

[1. Interrupt](#1-interrupt)
1. [What is an Interrupt?](#11-what-is-an-interrupt)  
2. [How Interrupt Works](#12-how-interrupt-works)  
3. [Types of Interrupts](#13-types-of-interrupts)  
   - [1.3.1 Hardware Interrupts](#131-hardware-interrupts)  
   - [1.3.2 Software Interrupts](#132-software-interrupts)  
   - [1.3.3 Multiple Interrupts (Priority)](#133-multiple-interrupts-priority)  
   - [1.3.4 Interrupt Handler in STM Cortex-M](#134-interrupt-handler-in-stm-cortex-m)  
   - [1.3.5 Components of NVIC](#135-components-of-nvic)  
   - [1.3.6 Interrupt Request (IRQs) Table](#136-interrupt-request-irqs-table)  
   - [1.3.7 External Interrupt](#137-external-interrupt)  
   - [1.3.8 Timer Interrupt](#138-timer-interrupt)  
   - [1.3.9 Communication Interrupt](#139-communication-interrupt)  
4. [Priority](#14-priority)  

[2. Timer](#2-timer)
1. [What is a Timer?](#21-what-is-a-timer)  
2. [Timer Structure and Components](#22-timer-structure-and-components)  
3. [Timer Configuration Example](#23-timer-configuration-example)  
   - [3.1 RCC Configuration](#231-rcc-configuration)  
   - [3.2 GPIO Configuration](#232-gpio-configuration)  
   - [3.3 Timer Configuration](#233-timer-configuration)  
   - [3.4 Delay Function](#234-delay-function)  
4. [Code Example](#24-code-example)  
5. [Timer Operation](#25-timer-operation) 

[Lesson 04: Communication Protocols](#lesson-04-communication-protocols)
1. [Truyền nhận dữ liệu](#1-truyền-nhận-dữ-liệu)  
2. [SPI](#2-spi)  
3. [I2C](#3-i2c)  
4. [UART](#4-uart)  

[Lesson 05: SPI Software and Hardware](#lesson-05-spi-software-and-hardware)
1. [SPI software](#1-spi-software)  
2. [SPI hardware](#2-spi-hardware)  

[Lesson 06: I2C Software and Hardware](#lesson-06-i2c-software-and-hardware)
1. [I2C software](#1-i2c-software)  
2. [I2C hardware](#2-i2c-hardware)  

[Lesson 07: UART Software and Hardware](#lesson-07-uart-software-and-hardware)
1. [UART software](#1-uart-software)  
2. [UART hardware](#2-uart-hardware)  

[Lesson 08: Interrupt](#lesson-08-interrupt)
1. [External Interrupt](#1-external-interrupt)
2. [Timer Interrupt](#2-timer-interrupt) 
3. [Communication Interrupt](#3-communication-interrupt)

[Lesson 09: ADC](#lesson-09-adc)
1. [Định nghĩa](#1-định-nghĩa)  
2. [Sử dụng ADC trong STM32](#2-sử-dụng-adc-trong-stm32) 

[Lesson 10: DMA](#lesson-10-dma)
1. [Định nghĩa](#1-định-nghĩa)  
2. [Sử dụng ADC trong STM32](#2-dma-trong-stm32) 
3. [PWM](#3-pwm) 

[Lesson 11: Flash - Bootloader](#lesson-11-flash---bootloader)
1. [Flash](#1-flash)  
2. [Bootloader](#2-bootloader)  -->

# So sánh Monolithic Kernel và Microkernel

| Đặc điểm              | Monolithic Kernel                                  | Microkernel                                      |
|----------------------|------------------------------------------------|------------------------------------------------|
| **Cấu trúc**        | Kernel chứa hầu hết các dịch vụ hệ điều hành trong một không gian địa chỉ duy nhất. | Kernel chỉ giữ các chức năng lõi, còn các dịch vụ khác chạy ở không gian người dùng. |
| **Hiệu suất**       | Cao hơn do các dịch vụ chạy trực tiếp trong kernel, không cần giao tiếp qua message passing. | Thấp hơn do các dịch vụ phải giao tiếp qua message passing, gây overhead. |
| **Bảo mật & Ổn định** | Kém hơn, vì lỗi trong một phần của kernel có thể làm sập toàn bộ hệ thống. | Cao hơn, vì lỗi trong một dịch vụ người dùng không ảnh hưởng đến kernel. |
| **Khả năng mở rộng** | Khó mở rộng, vì cần sửa đổi trực tiếp kernel và phải biên dịch lại. | Dễ mở rộng, vì có thể thêm dịch vụ mới mà không cần thay đổi kernel. |
| **Giao tiếp**       | Các thành phần gọi trực tiếp lẫn nhau trong kernel. | Các thành phần giao tiếp thông qua **message passing**, gây tốn tài nguyên hơn. |
| **Ví dụ HĐH**       | Linux, Windows, macOS                             | QNX, Minix, Mach (dùng trong macOS) |

## Tóm tắt:
- **Monolithic Kernel**: Hiệu suất cao, nhưng khó mở rộng và kém bảo mật.
- **Microkernel**: Linh hoạt và bảo mật hơn, nhưng có độ trễ cao do cơ chế message passing.


## Contact
Email: individual.thuongnguyen@gmail.com    
GitHub: [github.com/thuongnvLK](https://github.com/thuongnvLK)