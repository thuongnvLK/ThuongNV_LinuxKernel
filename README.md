#  **LINUX EMBEDDED**

![Build Status](https://img.shields.io/badge/build-in%20progress-yellow)         
![IDE](https://img.shields.io/badge/IDE-Linux%20based%20tools-blue?logo=linux&style=flat-square)     
![Platform](https://img.shields.io/badge/Platform-ARM%20based%20processor-blue?logo=arm&style=flat-square)     
![Language: C](https://img.shields.io/badge/Language-C-yellow?logo=c&style=flat-square)     
![Version](https://img.shields.io/badge/Version-1.0-green?style=flat-square)    
 

##  **Table of Contents**

## Lesson 00: Setting Up

### 1. Ubuntu Linux

#### 1.1 What is sudo and apt

- `sudo` stands for **Superuser Do**. It is a command in Linux and Unix system that allows a user to execute tasks requiring **administrative privileges** or **superuser (root) rights** .

- `apt` stands for **Advanced Package Tool**. It is a command-line utility used in Linux distributions based on Debian (such as Ubuntu) to manage software packages. It simplifies the process of installing, updating, and removing software by communicating with the system's package management system.

**Install vim using apt**

The procedure is as follows:
  1. Open terminal application. You can also press `CTRL + ALT + T` keyboard shortcut.
  2. Update package database by typing the `sudo apt update` command
  3. Search for viim package run: `sudo apt search vim`
  4. Install vim on Ubuntu Linux, `type: sudo apt install vim`
  5. Verify vim installation by typing the `vim --version` command

**Install gcc using apt**

`sudo apt install gcc`

**Install make using apt**

`sudo apt install make`

**Install git using apt**

`sudo apt install git`

---

## Lesson 01: General

### 1. Introduction to Makefile

- A Makefile is a special file used by the `make` utility to automate the build process of software projects. It contains a set of rules and instructions to compile and link programs, simplifying repetitive tasks and improving efficiency.
- A Makefile is a script that contains the following information:
  - The structure of a project (files and dependencies).
  - Command lines used to create or delete files.
- The make program will read the content of the Makefile and execute it.

**Structure of a Simple Rule in Makefile**

![Alt text](images/Linux0.png)

- **Prereuisites**: These are the files required to create the target.
- **Target**: This is **the file** generated after the `make` process is executed, or it can be **an action mane** such as `build`, `run`, etc.
- **Action**: This refers to the Compile command used to generate the target from the prerequisites, or to execute the target. The action must be indented by one `tab` relative to the target.

Example:
```
hellomake: hello.c main.c
  gcc -o hellomake hello.c main.c -I
```

**Phony Targets**

A phony target is one that is not really the name of a file; rather it is just a name for a recipe to be executed when you make an explicit request. There are two reasons to use a phony target: to avoid a conflict with a file of the same name, and to improve performance. 

**Why use a phony target?**

There are two main reasons:

1. **Avoid conflicts with files of the same name**
  - If you have a file in your directory with the same name as your target, `make` might think the target is `up to date` and skip running the commands.
  - By marking a target as phony, you tell `make` to ignore the file and always run the commands for the target.
2. **Improve performance**
  - `make` doesn't waste time checking whether the phony target exists as a file. It knows immediately that the target is not a file and executes the commands directly.
  - This especially helpful in large projects wiht many dependencies.

### 2. Compiling a C program

#### 2.1 Pre-processing 

  - Remove comments.
  - Expanding macros.
  - Expanding include files.
  - Compiling conditional statements.
  - The result obtained after this step is a ".i" file.

### 2.2 Compilation (The stage of translating high-level language to assembly)

- At this stage, the source code continues to be compiled from the ".i" file obtained in the previous step into a ".s" file (assembly).
### 2.3 Assembly (The stage of translating assembly code to machine code)

- The ".s" file from the previous stage continues to be used for this stage.
- Through the assembler, the output we obtain is a ".o" file. This file contains instructions in machine language.

### 2.4 Linking

- Each ".o" file obtained in the assembly stage is part of the program.
- In the linking stage, these files are combined to produce a complete executable file.

| Propertics | Static Library | Shared Library |
|----------|----------|----------|
| Linking time  | All modules in the library will be copied into the executable file at compile time. When the program is loaded into memory, the operating system only loads a single executable file that includes the source code and the library linked (static linking).  | Meanwhile, a shared library is used during the linking process, where both the executable file and the library file are loaded into memory at runtime. A shared library can be used by multiple programs. (Dynamic Lnking)  |
| Size  | Using a static library consumes more memmory than a shared linbrary  | Using a shared library comsumes less memmory because there is only a single copy in memory.  |
| External File changes  | The executable file must be recompiled whenever there are changes in the static library  | For a shared library, it is not necessary to recompile the executable file  |
| Time  | Value 8  | Value 9  |


### 2.4 Static Lib and Shared Lib

- A library is a collection of precompiled code segments that can be reused in a prgram.

- Is is divided into two types:
  - Static Lib (.a)
  - Shared Lib (.so on Linux or .dll on Window (Dynamic Link Libraries)).

![Alt text](images/Linux1.png)

![Alt text](images/Linux2.png)

![Alt text](images/Linux3.png)


## Lesson 02: File

### 1. Overview of File on Linux

- Linux manages everything as a file.

- Types of Files in Linux:
  - **Regular file**: These are standard files, such as text files or executable files.
  - **Directory file**: A file that contains a list of other files.
  - **Character Device file**: A file that represents devices without memory addressable storage.
  - **Block Device file**: A file that represents devices with addressable memory storage.
  - **Link file**: A file that represents another file. 
  - **Socket file**: A file that represents a socket.
  - **Pipe file**: A file that represents a pipe.

![Alt text](images/Linux4.png)


### 2. File Reading and Writing in Linux

- The kernel provides a basic system call to perform reading, writing, and operation on files, including:
  - open()
  - read()
  - write()
  - lseek()
  - close()

### 3. File Management in Linux

### 4. File Locking

- Lock file 

### 5. Asynchronous File Reading and Writing

## Lesson 03: Process

### 1. Introduction

- **Program** and **Processes** are two related terms. 
- It is necessary to distinguish between a program and a process. 
- Each process has a unique identifier called a Process ID (PID), which is a positive integer and unique to each process on the system.

**A Program** is a collection of intructions that performs a specific task, represented by executable files stored on a computer's hard drive.

**A Process** is a program that is being executed and using system resources. 

### 2. Command-line Arguments

- Each program starts executing form the main() function.

- When running a program, environment parameters (command-line arguments) are passed through two arguments in the main() function.

- **argc** and **argv[]**

## Lesson 05: Thread

### 1. 

## Contact
Email: individual.thuongnguyen@gmail.com    
GitHub: [github.com/thuongnvLK](https://github.com/thuongnvLK)#   T h u o n g N V _ L i n u x K e r n e l - 
 
 