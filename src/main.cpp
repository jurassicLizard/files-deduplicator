/*
 * MIT License
 *
 * Copyright (c) 2024 Salem Bouraoui
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * ---
 *
 */

#include "version.hpp"
#include "PurgeDuplicates.hpp"
#include <iostream>
#include <string>
#include <sstream>

#define PDCPP_ARG_SHOWPROGRESS "--show-progress"
#define PDCPP_ARG_LIVERUN "--live-run"
/**
 * @brief prints version information to standard output
 */
void print_version_info() {
    std::cout << "purge-duplicates v" << pdcpp::VERSION << std::endl;
}

/**
 * @brief Prints program usage information
 * @param isError If true, prints to stderr; otherwise, prints to stdout
 * @param appName Name of the application to display in usage information
 */
void print_usage_info(const bool isError = false,const char* appName = "purge-duplicates") {
    std::stringstream ss;
    ss << "purge-duplicates v" << pdcpp::VERSION << std::endl;
    ss << "Usage: " << appName << " <directory_path> [--show-progress] [--live-run]" << std::endl;
    ss << std::endl;
    ss << "Arguments:" << std::endl;
    ss << "  <directory_path>   Required: Path to directory to scan for duplicates" << std::endl;
    ss << "  --show-progress    Optional: Display progress during scanning" << std::endl;
    ss << "  --live-run         Optional: Actually delete duplicates (without this, runs in dry-run mode)" << std::endl;

    if (isError) {
        std::cerr << ss.str();
    } else {
        std::cout << ss.str();
    }
}
/**
 * @brief prints an error message for an unimplemented argument
 * @param arg argument to print
 */
void print_unknown_arg_err(const char* arg) {
    std::stringstream ss;
    ss << "Error: '" << arg << "' is an unknown command-line argument." << std::endl;
    ss << "Run the program with no arguments to see usage information." << std::endl;

    std::cerr << ss.str();

    // Optionally, you could also call print_usage_info here
    print_usage_info(true);
}

int main(int argc, char* argv[]) {
// First check if we have enough arguments
    if (argc < 2) {
        print_usage_info(true, argv[0]);
        return EXIT_FAILURE;
    }

// Check if first argument is a special flag (like --version)
    std::string firstArg = argv[1];
    if (!firstArg.empty() && firstArg.at(0) == '-') {
        if (firstArg == "-v" || firstArg == "--version") {
            print_version_info();
            return EXIT_SUCCESS;
        } else {
            std::cerr << std::endl << "A path to a directory is expected as the first argument" << std::endl << std::endl;
            print_usage_info(true, argv[0]);
            return EXIT_FAILURE;
        }
    }

// First argument is the directory path
    const std::string directory = argv[1];
    bool showProgress = false;
    bool liveRun = false;

// Process remaining arguments (flags)
    for (int i = 2; i < argc; ++i) {
        std::string argument = argv[i];
        if (!argument.empty() && argument.at(0) == '-') {
            if (argument == PDCPP_ARG_SHOWPROGRESS) {
                showProgress = true;
            } else if (argument == PDCPP_ARG_LIVERUN) {
                liveRun = true;
            } else {
                // Unknown argument
                print_unknown_arg_err(argument.c_str());
                return EXIT_FAILURE;
            }
        } else {
            // Non-flag argument after the directory path
            std::cerr << "Unexpected argument: " << argument << std::endl;
            print_usage_info(true, argv[0]);
            return EXIT_FAILURE;
        }
    }


    try {
        // Pass the new flag to PurgeDuplicates
        PurgeDuplicates purgeDuplicates(directory, showProgress, liveRun);
        purgeDuplicates.execute(); // Begin execution
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
