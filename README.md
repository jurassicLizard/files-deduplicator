# Files-Deduplicator

**Files-Deduplicator** is a powerful command-line tool that efficiently identifies and removes duplicate files from directories. Using cryptographic **Blake2** hashes, it ensures accurate and fast file comparison, making it an essential tool for data cleaning and file management. By default, the software runs in duplication detection mode and does not make any changes unless run with the `--live-run` flag.

---

## Features

- **Recursive File Scanning**: Analyzes all files within a folder, including its subdirectories.
- **Cryptographic Precision**: Utilizes Blake2 to guarantee accurate and fast duplicate detection.
    - Uses Blake2b512 on 64-bit platforms
    - Uses Blake2s256 on 32-bit platforms for faster performance
- **Progress Display**: Optionally display progress during execution using a progress bar.
- **Cross-Platform**: Designed to work on **Linux**, **Windows**, and **macOS**.
- **Efficient and Lightweight**: Capable of processing large datasets effectively.

> **DISCLAIMER**: This software is provided **"as is"** under the MIT License. Use the software **at your own risk**. The authors are not liable for any damage, loss, or issues that may arise as a result of using this tool. The software runs by default in duplication detection mode and does not make any changes unless run with the `--live-run` flag. Users must always ensure they have their own backups. The software is thoroughly tested to the best of the author's knowledge.

---

## Table of Contents

1. [Introduction](#introduction)
2. [Getting Started](#getting-started)
3. [Usage](#usage)
    - [Command-Line Arguments](#command-line-arguments)
4. [Building from Source](#building-from-source)
    - [Linux](#linux)
    - [Windows](#windows)
    - [Installing and Uninstalling the Software](#installing-and-uninstalling-the-software)
5. [Testing](#testing)
6. [License](#license)

---

## Introduction

Files-Deduplicator is designed to help users clean up their file systems by removing duplicate files. Whether you are managing a large dataset or simply tidying up your personal files, this tool provides a reliable and efficient solution. The software also functions as a "duplicate detector."

## Getting Started

Download the latest release or build the software from source to get started. Refer to the [Usage](#usage) section for detailed instructions on how to use the tool.

---

## Usage

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

### Example 3: Large Dataset (Dry-Run)

**Scenario**: Scan a folder containing a large dataset while displaying progress, but do not delete any files.

```bash
rmdup /large/dataset --show-progress
```

Output:
```plaintext
[=========================>                ] 75%
Dry Run: The following files would be deleted:
  /large/dataset/sample1.txt
  /large/dataset/subfolder/sample2.txt
  ...
Dry run complete. No files were deleted.
```

By default, the program ensures no files are damaged or unexpectedly removed during testing by executing in **safe dry-run mode** unless explicitly instructed otherwise using the `--live-run` flag.

---

## Building from Source

This project uses **CMake** for cross-platform builds. Ensure you have the prerequisites installed and follow the instructions for your platform.

### Linux

1. Install prerequisites:
    - **GCC** or **Clang** compiler supporting C++17.
    - CMake version >= 3.15.
    - OpenSSL library version >= 1.0.0.

2. Clone and build the project:
   ```bash
   git clone https://github.com/jurassicLizard/files-deduplicator.git
   cd files-deduplicator
   mkdir build
   cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   make
   ```

    - The `-DCMAKE_BUILD_TYPE=Release` flag ensures the project is built in optimized **Release mode**.

3. The compiled binary will be located in the `build/bin/` folder.

4. (Optional) To install the binary system-wide:
   ```bash
   sudo cmake --install . --prefix /usr/local
   ```
    - By default, the binary will be installed to `/usr/local/bin`.

---

### Windows

The project is compatible with **Windows**, but preparation is required due to external dependencies (e.g., OpenSSL). These instructions use Visual Studio and a prebuilt OpenSSL binary.

1. Install prerequisites:
    - Visual Studio 2017 or newer with C++ tools.
    - Prebuilt [OpenSSL for Windows](https://slproweb.com/products/Win32OpenSSL.html) or compile OpenSSL manually.
    - CMake version >= 3.15.

2. Add OpenSSL to the system environment:
    - Set the `CMAKE_PREFIX_PATH` environment variable:
      ```powershell
      $env:CMAKE_PREFIX_PATH = "C:/path/to/openssl"
      ```

3. Clone and build the project:
   ```powershell
   git clone https://github.com/jurassicLizard/files-deduplicator.git
   cd files-deduplicator
   mkdir build
   cd build
   cmake .. -G "Visual Studio 17 2022" -DCMAKE_PREFIX_PATH="C:/path/to/openssl"
   cmake --build . --config Release
   ```

4. The compiled binary can be found in the `build/bin/` folder.

---

### Installing and Uninstalling the Software

#### Installing the Software

The project includes an **install target** to simplify deployment. The `cmake --install` command ensures that the binary and associated files are installed in system-appropriate directories (e.g., `/usr/local/bin` for Linux).

1. Install the binary:
   ```bash
   cmake --install . --prefix /custom/install/path
   ```

2. Run the installed binary from anywhere:
   ```bash
   rmdup /path/to/folder --show-progress
   ```

#### Uninstalling the Software

To uninstall, delete the installed files manually, e.g.:
```bash
sudo rm -f /usr/local/bin/rmdup
sudo rm -rf /usr/local/include/files-deduplicator/
```

---

## Testing

The project includes comprehensive testing to ensure reliability across different platforms:

- **Unit Tests**: Cover core functionality including file hashing, duplicate detection, and file operations.
- **Integration Tests**: Verify the end-to-end workflow with real file operations (creating and deleting) in a controlled test directory.
- **Platform-Specific Testing**: Both 64-bit and 32-bit hash implementation paths are tested.
    - For development purposes, the 32-bit algorithm path can be forced on 64-bit systems by defining `PDCPP_FORCE_32BIT_PATH` during compilation.
    - This ensures both code paths are fully tested even when developing on 64-bit systems only.

To run tests:

1. Run CMake with Testing enabled during build
   ```bash
   cmake .. -DPDCPP_ENABLE_TESTING=ON
   ```
   Or with GCC/CLANG you can activate address sanitization for memory specific error detection
   ```bash
   cmake .. -DPDCPP_ENABLE_TESTING_WITH_ASAN=ON
   ```
2. build
   ```bash
   make
   ```
3.Run tests:
   ```bash
   ctest --output-on-failure
   ```

## License

This project is licensed under the MIT License. See [LICENSE.md](LICENSE.md) for more details.
