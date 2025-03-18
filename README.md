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
2. [Getting Started](#-getting-started)
3. [Usage](#-usage)
    - [Command-Line Arguments](#command-line-arguments)
4. [Prerequisites](#prerequisites)
    - [Linux](#prerequisites-linux)
    - [Windows](#prerequisites-windows)
    - [macOS](#prerequisites-macos)
5. [Building from Source](#building-from-source)
    - [Linux](#linux)
    - [Windows](#windows)
    - [macOS](#macos)
    - [Installing and Uninstalling the Software](#installing-and-uninstalling-the-software)
6. [Testing](#testing)
    - [Address Sanitization](#address-sanitization)
7. [License](#license)

---

## Introduction

Files-Deduplicator is designed to help users clean up their file systems by removing duplicate files. Whether you are managing a large dataset or simply tidying up your personal files, this tool provides a reliable and efficient solution for disk space optimization and file organization. The software also functions as a "duplicate detector," allowing you to safely identify duplicates before removing them.

## 🚀 Getting Started

Download the latest [release](https://github.com/jurassiclizard/files-deduplicator/releases) or build the software from source to get started. Refer to the [Usage](#-usage) section for detailed instructions on how to use the tool.

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
```

## Prerequisites

### Prerequisites: Linux

- **CMake** (version 3.21 or higher)
- **C++ Compiler** with C++20 support (GCC 10+ or Clang 10+)
- **Git** (for obtaining the source code)
- **vcpkg** (optional, for dependency management)

To install prerequisites on Ubuntu/Debian:
```bash
sudo apt update
sudo apt install cmake build-essential git
```

### Prerequisites: Windows

- **CMake** (version 3.21 or higher)
- **Visual Studio 2019** or newer with C++ desktop development workload
- **Git** (for obtaining the source code)
- **vcpkg** (for dependency management)

You can install these tools through:
- [Visual Studio](https://visualstudio.microsoft.com/downloads/)
- [CMake](https://cmake.org/download/)
- [Git](https://git-scm.com/download/win)
- [vcpkg](https://github.com/microsoft/vcpkg)

#### Setting up vcpkg

1. Clone and bootstrap vcpkg:
    ```bash
    git clone https://github.com/microsoft/vcpkg
    cd vcpkg
    .\bootstrap-vcpkg.bat
    ```

2. Set the VCPKG_ROOT environment variable:
    ```bash
    # In PowerShell
    $env:VCPKG_ROOT = "path\to\vcpkg"
    
    # Or permanently (Windows)
    [Environment]::SetEnvironmentVariable("VCPKG_ROOT", "path\to\vcpkg", "User")
    ```

Note: The project includes a vcpkg.json manifest file that will automatically download and build the OpenSSL dependency when you configure the project with CMake.

### Prerequisites: macOS

- **CMake** (version 3.21 or higher)
- **Xcode** or **Command Line Tools**
- **Git** (for obtaining the source code)
- **vcpkg** (for dependency management)

To install prerequisites using Homebrew:
    ```bash
    brew install cmake git
    xcode-select --install
    ```

#### Setting up vcpkg

1. Clone and bootstrap vcpkg:
    ```bash
    git clone https://github.com/microsoft/vcpkg
    cd vcpkg
    ./bootstrap-vcpkg.sh
    ```
2. Set the VCPKG_ROOT environment variable:
    ```bash
    # For current session
    export VCPKG_ROOT=path/to/vcpkg
    
    # Add to ~/.zshrc or ~/.bash_profile for persistence
    echo 'export VCPKG_ROOT=path/to/vcpkg' >> ~/.zshrc
    source ~/.zshrc
    ```

Note: The project includes a vcpkg.json manifest file that will automatically download and build the OpenSSL dependency when you configure the project with CMake.

## Building from Source

The project uses CMake presets to simplify the build configuration. You'll find predefined configurations in `CMakePresets.json`, which you can extend with your own settings.

### CMakeUserPresets.json Setup

The repository includes a template file `CMakeUserPresets.json.template` that you can use to create your own custom build configurations.

1. Copy the template file to create your user presets:
    ```bash
    cp CMakeUserPresets.json.template CMakeUserPresets.json
    ```

2. Edit `CMakeUserPresets.json` to customize build settings, paths, or add your own presets.

3. This file is git-ignored, so your custom settings won't be committed to the repository.

Note: The template includes settings for vcpkg integration. If you're using vcpkg for dependency management, ensure the `VCPKG_ROOT` environment variable is set or update the `CMAKE_TOOLCHAIN_FILE` path in your user presets.


### Linux

Using CMake presets:

```bash
# Clone the repository
git clone https://github.com/jurassiclizard/files-deduplicator.git
cd files-deduplicator

# Configure using preset
cmake --preset linux-debug

# Build
cmake --build --preset linux-debug

# Run tests
ctest --preset linux-debug
```

For release build:
```bash
cmake --preset linux-release
cmake --build --preset linux-release
```

### Windows

Using CMake presets:

```bash
# Clone the repository
git clone https://github.com/jurassiclizard/files-deduplicator.git
cd files-deduplicator

# Configure using preset
cmake --preset non-linux-debug

# Build
cmake --build --preset non-linux-debug

# Run tests
ctest --preset non-linux-debug
```

For release build:
```bash
cmake --preset non-linux-release
cmake --build --preset non-linux-release
```

### macOS

Using CMake presets:

```bash
# Clone the repository
git clone https://github.com/jurassiclizard/files-deduplicator.git
cd files-deduplicator

# Configure using preset
cmake --preset non-linux-debug

# Build
cmake --build --preset non-linux-debug

# Run tests
ctest --preset non-linux-debug
```

For release build:
```bash
cmake --preset non-linux-release
cmake --build --preset non-linux-release
```

### Installing and Uninstalling the Software

#### Install

After building, you can install the software system-wide:

```bash
# For Linux/macOS
sudo cmake --install build

# For Windows (run as Administrator)
cmake --install build
```

#### Uninstall

To uninstall:

```bash
# For Linux/macOS
sudo xargs rm < build/install_manifest.txt

# For Windows
type build\install_manifest.txt | xargs -r rm
```

## Testing

The project includes a comprehensive test suite to ensure correctness and reliability. You can run the tests using CMake presets.

### Running Tests with Presets

Tests can be easily executed using the predefined CMake test presets (We have no threading thus tests are by default generated only in the debug preset):

```bash
# Run tests using Linux debug preset
ctest --preset linux-debug

# Run tests using non-Linux debug preset (Windows/macOS)
ctest --preset non-linux-debug
```

You can also define your own test configurations in the `CMakeUserPresets.json` file for custom test environments.

### Address Sanitization

Address Sanitization is enabled in debug builds with the ASAN option (GCC and CLANG only):

```bash
# Already enabled in debug presets
cmake --preset linux-debug
cmake --build --preset linux-debug
```

This helps detect memory-related issues like leaks, use-after-free, and out-of-bounds access during testing.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.