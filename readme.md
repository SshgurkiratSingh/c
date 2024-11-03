# C and System Programming Repository

This comprehensive repository showcases a wide range of C, C++, and Python programs, demonstrating various concepts in system programming, data structures, algorithms, and more. It serves as an invaluable resource for both beginners and experienced developers looking to expand their knowledge in low-level programming and system development.

## Repository Structure

### 1. Basic C Code
A diverse collection of fundamental C and C++ programs covering a wide range of topics:

#### Matrix Operations
- 2x2 and 3x3 matrix addition and subtraction (`2x2MatrixSum.cpp`, `2x2MatrixSubtraction.cpp`, `3x3MatrixSum.cpp`, `3x3MatrixSubtraction.cpp`)
- Matrix multiplication (`matrixMultiplication.cpp`)

#### Array Manipulations
- Array reversal (`arrayInReverse.cpp`, `DisplayArrInRev.cpp`)
- Sorting algorithms (`arraySortInAscending.cpp`)
- Finding minimum and maximum values (`findMinAndMaxInArray.cpp`)
- Various array operations (`5xArr.cpp`)

#### String Processing
- Vowel/consonant counting (`countVowelAndconsonants.cpp`)
- Case conversion (`stringToLowercase.cpp`, `VoweltoUpperInString.cpp`)
- Palindrome checking using recursion (`recursivePalindromeString.c`)
- Character removal and repetition detection (`removeCfromString.cpp`, `repeatedCharInString.cpp`)
- String printing and sorting (`stringPrint.cpp`, `StringSort.c`)

#### Mathematical Operations
- Prime factor calculation (`primeFactor.cpp`)
- Fibonacci sequence generation (`FibonacciSequence.cpp`)
- Quadratic equation solving (`rootOfQuadraticEq.cpp`)
- Pascal's Triangle construction (`PascalTriangle.cpp`)
- Numerical operations: cube (`cubeOfNumber.cpp`), average (`averageOfnNumber.cpp`), sum of digits (`sumOfNdigitandPrinteach.cpp`)

#### Games and Puzzles
- Combined Tic-Tac-Toe and Riddle Guessing game (`combinedCode.c`)
  - 3x3 Tic-Tac-Toe with AI opponent
  - Riddle guessing game with 13 pre-defined riddles
  - Custom color output for enhanced UI (`cchalk.c`, `cchalk.h`)
- Standalone Riddle Guessing game (`RiddleGuess.c`)

#### Utilities and Advanced Concepts
- Age calculator (`ageCalculator.cpp`)
- Binary conversion (`convertDecimalToBinary.cpp`)
- Hexadecimal checking (`checkHexadecimal.cpp`)
- Recursive function implementations (`recursivePower.cpp`, `countNoOfDigitUsingRecursion.cpp`)
- Pointer operations (`pointer.c`)
- Custom color output library (`cchalk.c`, `cchalk.h`)
- Pattern generation (`cross.c`: generates a cross pattern)

### 2. CircularBuffer
Implementation of a circular buffer data structure in C:
- `circular_buffer.h`: Header file defining the circular buffer structure (max 10 entries) and function prototypes
- `circular_buffer.c`: Implementation of circular buffer operations
- `main.c`: Example usage of the circular buffer
- `circular_buffer_temp.c`: Alternative implementation of the circular buffer

### 3. CShell
A custom shell implementation in C (`main.c`), demonstrating:
- Command parsing and execution (`lshSplitLine`, `lshExecute`)
- Built-in commands: cd, help, exit
- External program execution using `fork` and `execvp`
- Input/output redirection
- Dynamic memory allocation for command handling

### 4. Modules
Various Linux kernel modules and device drivers:
- Hello World kernel module (`helloWorld/mymodule.c`, `mymodule.mod.c`)
  - Basic module with `hello_init` and `hello_exit` functions
- Character Device drivers (`CharacterDevice/` directory)
- Dynamic Memory allocation in kernel space (`DynamicMemoryKernel/` directory)
- Device and file system interactions (`DeviceAndFiles/` directory)

### 5. MQTT
Examples of working with the MQTT (Message Queuing Telemetry Transport) protocol:
- MQTT publisher implementation
- Connection setup, message publishing, and error handling

### 6. POSIX
Programs illustrating POSIX API usage:
- Mutex implementation for thread synchronization
- Examples of thread creation and race condition handling

### 7. Python
Python scripts demonstrating various programming concepts:
- `Into.py`: An introductory Python script

### 8. Socket
Network programming examples using the socket API:
- Simple server implementation
- Socket creation, binding, listening, and client request handling

### 9. Additional Components
- `timeLib/`: Time-related utilities for precise measurements in C programs
- `aichat.py`: AI chatbot functionality (root directory)

## Key Features

1. **Diverse Programming Concepts**: From basic algorithms to system-level programming
2. **Kernel Module Development**: Linux kernel module creation and management
3. **Data Structures**: Custom implementations (e.g., circular buffers)
4. **Network Programming**: Socket programming and MQTT protocol usage
5. **Multithreading**: POSIX thread manipulation examples
6. **Custom Shell**: Basic command-line interface implementation
7. **Game Development**: Simple interactive game implementations (Tic-Tac-Toe, Riddle Guessing)

## Detailed Component Descriptions

### Basic C Code
This directory contains a wide array of C and C++ programs demonstrating fundamental programming concepts:
- **Matrix Operations**: Programs for matrix addition, subtraction, and multiplication, showcasing 2D array manipulation.
- **Array Manipulations**: Examples of common array operations like reversal, sorting, and finding min/max values.
- **String Processing**: Various string manipulation techniques, including character counting, case conversion, and palindrome checking.
- **Mathematical Operations**: Implementation of mathematical concepts like prime factorization, Fibonacci sequence, and Pascal's Triangle.
- **Games and Puzzles**: Interactive programs including a combined Tic-Tac-Toe and Riddle game, demonstrating game logic and user interaction.
- **Utilities and Advanced Concepts**: Programs showcasing more advanced C/C++ concepts like recursion, pointers, and custom libraries (e.g., color output).

### CircularBuffer
A complete implementation of a circular buffer data structure, demonstrating:
- Efficient memory usage for fixed-size buffers
- Thread-safe operations for potential use in multi-threaded applications
- Example usage showcasing practical applications of the data structure

### CShell
A custom shell implementation showcasing:
- Command parsing and execution techniques
- Process creation and management using system calls
- Basic shell functionalities including built-in commands and external program execution

### Modules
This directory contains examples of Linux kernel module programming:
- Basic module creation and initialization
- Character device driver implementation
- Kernel-space memory management
- Interaction between kernel modules and the file system

### MQTT
Demonstrates the usage of the MQTT protocol for IoT and messaging applications:
- Publisher implementation for sending messages to an MQTT broker
- Handling of connection setup and error management in MQTT communications

### POSIX
Examples of POSIX API usage focusing on:
- Thread creation and management
- Synchronization mechanisms (mutexes) to handle race conditions
- Practical demonstrations of multi-threaded programming concepts

### Python
Introductory Python scripts to showcase basic Python programming concepts and syntax.

### Socket
Network programming examples using the socket API, demonstrating:
- Server-side socket programming
- Handling of network connections and data transfer

### Additional Components
- `timeLib/`: Utilities for precise time measurements, crucial for performance analysis and time-sensitive operations in C programs.
- `aichat.py`: An AI chatbot implementation, showcasing integration of AI concepts with Python programming.

## Languages and Technologies

- Primary Languages: C, C++
- Additional Language: Python
- Build System: Makefile
- Operating System Concepts: Linux Kernel Modules, POSIX

## Getting Started

1. Clone the repository:
   ```
   git clone [repository URL]
   ```
2. Navigate to the directory of interest:
   ```
   cd [directory name]
   ```
3. Compile C/C++ programs using gcc/g++:
   ```
   gcc -o program_name source_file.c
   ```
4. For kernel modules, install necessary headers and use `make`:
   ```
   sudo apt-get install linux-headers-$(uname -r)
   make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
   ```
5. Run Python scripts with a Python interpreter:
   ```
   python script_name.py
   ```

## Contributing

Contributions to this repository are welcome and encouraged. Here's how you can contribute:
1. Fork the repository
2. Create a new branch (`git checkout -b feature-branch`)
3. Make your changes and commit them (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin feature-branch`)
5. Create a new Pull Request

Please ensure your code adheres to the existing style and includes appropriate comments and documentation.

## License

[Include your license information here]

This repository offers a comprehensive learning experience for aspiring programmers and system developers, covering everything from basic algorithmic problems to advanced system-level programming. It provides hands-on examples in various areas of computer science and system programming, making it an excellent resource for both learning and reference.

## Acknowledgments

- Thanks to all contributors who have helped in building and maintaining this educational resource.
- Special thanks to the open-source community for providing tools and libraries that make this learning experience possible.

Explore the folders to find examples and detailed code for different functionalities.

## License

This project is licensed under the MIT License.

## Contributing

Contributions are welcome! Please submit pull requests for any improvements or additions.
