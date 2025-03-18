# Files-Deduplicator

![GitHub release](https://img.shields.io/github/v/release/jurassiclizard/files-deduplicator)
![License](https://img.shields.io/github/license/jurassiclizard/files-deduplicator)

> 🔍 Fast & reliable duplicate file detection and removal tool using Blake2 cryptographic hashing

**Files-Deduplicator** is a powerful command-line tool that efficiently identifies and removes duplicate files from directories. Using cryptographic **Blake2** hashes, it ensures accurate and fast file comparison, making it an essential tool for data cleaning and file management. By default, the software runs in duplication detection mode and does not make any changes unless run with the `--live-run` flag.

---

## ⚡ Features

- **Recursive File Scanning**: Analyzes all files within a folder, including its subdirectories.
- **Cryptographic Precision**: Utilizes Blake2 to guarantee accurate and fast duplicate detection.
    - Uses Blake2b512 on 64-bit platforms
    - Uses Blake2s256 on 32-bit platforms for faster performance
- **Progress Display**: Optionally display progress during execution using a progress bar.
- **Cross-Platform**: Designed to work on **Linux**, **Windows**, and **macOS**.
- **Efficient and Lightweight**: Capable of processing large datasets effectively.
- **Safe by Default**: Runs in dry-run mode unless explicitly told to delete files.

> **DISCLAIMER**: This software is provided **"as is"** under the MIT License. Use the software **at your own risk**. The authors are not liable for any damage, loss, or issues that may arise as a result of using this tool. The software runs by default in duplication detection mode and does not make any changes unless run with the `--live-run` flag. Users must always ensure they have their own backups. The software is thoroughly tested to the best of the author's knowledge.

---

## 📋 Table of Contents

1. [Introduction](#introduction)
2. [Getting Started](#getting-started)
3. [Usage](#usage)
    - [Command-Line Arguments](#command-line-arguments)
4. [Building from Source](#building-from-source)
    - [Linux](#linux)
    - [Windows](#windows)
    - [Installing and Uninstalling the Software](#installing-and-uninstalling-the-software)
5. [Testing](#testing)
    - [Address Sanitization](#address-sanitization)
6. [License](#license)

---

## Introduction

Files-Deduplicator is designed to help users clean up their file systems by removing duplicate files. Whether you are managing a large dataset or simply tidying up your personal files, this tool provides a reliable and efficient solution for disk space optimization and file organization. The software also functions as a "duplicate detector," allowing you to safely identify duplicates before removing them.

## 🚀 Getting Started

Download the latest [release](https://github.com/jurassiclizard/files-deduplicator/releases) or build the software from source to get started. Refer to the [Usage](#usage) section for detailed instructions on how to use the tool.

---

## 📖 Usage

To use **Files-Deduplicator**, you can execute the compiled binary with the required arguments directly from the command line:

```bash
rmdup <directory_path> [--show-progress] [--live-run]
```

### Command-Line Arguments

- `<directory_path>` (required):
  The directory path to be scanned for duplicate files.

- `--show-progress` (optional):
  Displays a progress bar in the terminal to indicate file processing progress. Useful for large datasets.

- `--live-run` (optional):
  Performs the actual deletion of duplicate files. When this flag is **not** provided, the tool will execute in **dry-run mode** and only list the duplicate files that would be deleted without making any changes.

### Example 1: Dry-Run (Default)

**Scenario**: Find duplicate files in `/home/user/documents` and only list them (dry-run mode by default).

```bash
rmdup /home/user/documents
```

Output:
```plaintext
Dry Run: The following files would be deleted:
  /home/user/documents/file1.txt
  /home/user/documents/subdir/file2.txt
Dry run complete. No files were deleted.
To perform the actual deletion, re-run the command with the --live-run flag.
```

---

### Example 2: Live-Run (Deletes Duplicates)

**Scenario**: Remove duplicate files in `/home/user/documents` and show progress.

```bash
rmdup /home/user/documents --show-progress --live-run
```

Output:
```plaintext
[=========================>                ] 50% 
Removed duplicate: /home/user/documents/file1.txt
Removed duplicate: /home/user/documents/subdir/file2.txt
Duplicate removal complete. Processed 500 unique files.
```

> **NOTE**: Use the `--live-run` flag cautiously, as it will permanently delete files identified as duplicates. Always run the tool in **dry-run mode** first to verify the files to be deleted.

---

## 🔧 Building from Source

### Linux

To build the software on Linux:

1. Clone the repository:
   ```bash
   git clone https://github.com/jurassiclizard/files-deduplicator.git
   cd files-deduplicator
   ```

2. Build using CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

### Windows

To build the software on Windows:

1. Clone the repository
2. Open the project in Visual Studio or use CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

### Installing and Uninstalling the Software

After building, you can install the software system-wide on Linux:

```bash
sudo make install
```

To uninstall:

```bash
sudo make uninstall
```

## Testing

To ensure reliability, the software includes comprehensive tests. Tests must be enabled explicitly using the CMake option:

```bash
cmake .. -DPDCPP_ENABLE_TESTING=ON
```

To run the test suite:

```bash
cd build
make
ctest
```

### Address Sanitization

For GCC or Clang users, Address Sanitization (ASan) can be enabled to detect memory errors during testing:

```bash
cmake .. -DPDCPP_ENABLE_TESTING_WITH_ASAN=ON
make
ctest
```

This option automatically enables testing and configures AddressSanitizer for memory error detection.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

---

⭐️ If you find this tool useful, please consider starring the repository on GitHub!