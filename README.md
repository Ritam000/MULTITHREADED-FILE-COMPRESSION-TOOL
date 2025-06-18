# MULTITHREADED-FILE-COMPRESSION-TOOL

*COMPANY NAME*: CODTECH IT SOLUTIONS

*NAME*: RITAM KUNDU

*INTERN ID*: CT04DN1212

*DOMAIN*: C++ Programming

*DURATION*: 4 WEEKS

*MENTOR*: Neela Santhosh


This C++ program is a multithreaded file compression tool that implements the Run-Length Encoding (RLE) algorithm and was developed using **Visual Studio Code (VS Code)** as the editor. The code is written entirely in standard C++ and utilizes several components from the C++ Standard Library including `<iostream>`, `<fstream>`, `<vector>`, `<thread>`, `<mutex>`, and `<chrono>`. The goal of the program is to read a file in binary mode, divide it into chunks, compress each chunk in parallel using multiple threads, and then write the compressed result to an output file. RLE is a lossless compression algorithm that works by replacing sequences of repeated characters or bytes with a count and the repeated value. For example, a sequence like “AAAAA” would be stored as “5A”, saving space in scenarios with high redundancy. The program calculates the optimal number of threads based on the system's hardware concurrency, divides the file accordingly, and uses `std::mutex` to ensure thread-safe access when reading from the file or writing output to the console. Each thread processes its assigned chunk independently, applies RLE, and stores the result. After all threads complete execution, the compressed chunks are written sequentially into a single output file along with metadata like the number of chunks and their sizes. This enables the file to be decompressed correctly later if needed.
The development was carried out in **Visual Studio Code**, which is a popular, open-source code editor by Microsoft. VS Code is highly extensible and supports C++ through the Microsoft C++ extension (`ms-vscode.cpptools`), offering features like IntelliSense, debugging, syntax highlighting, and terminal integration. It allows smooth compilation using g++, clang++, or MSVC via the integrated terminal or build tasks. VS Code is ideal for both beginners and professionals working on C++ projects due to its clean interface, customizable environment, and seamless Git integration. The program also uses `<chrono>` to measure how long the compression process takes, providing valuable performance metrics. This is particularly useful for benchmarking and comparing compression algorithms or optimizing performance on different hardware.
In terms of applicability, this code is well-suited for a wide range of use cases. In **embedded systems** and **IoT devices**, where processing power and memory are limited, RLE offers a lightweight and fast compression technique. Since it doesn’t require complex computation or large memory usage, it is easy to implement and execute in constrained environments. In **scientific and industrial applications**, where data logging generates large volumes of repetitive data, this program can significantly reduce file sizes before storage or transmission. It’s also applicable in text-heavy formats like `.txt`, `.log`, or `.csv` files, where patterns of repeated characters are common. Moreover, it serves as an excellent educational resource for learning multithreading, file handling, and performance measurement in C++. The use of modern C++ features, structured memory management with vectors, and thread synchronization via mutexes demonstrates best practices for concurrent programming. By combining the simplicity of RLE with the efficiency of multithreading, the program achieves faster compression times, especially on large files or systems with multiple cores. This makes it both a practical tool and a powerful learning example for real-world C++ programming.



OUTPUT:

![Image](https://github.com/user-attachments/assets/2054d92c-5933-46a7-a819-ff8c2144957d)
