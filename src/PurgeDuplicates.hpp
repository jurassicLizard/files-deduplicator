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
 */
#ifndef PURGE_DUPLICATES_HPP
#define PURGE_DUPLICATES_HPP

#include <string>

class PurgeDuplicates {
public:
    /**
     * @brief Constructor to initialize the PurgeDuplicates object.
     * @param directory Path to the directory that will be processed.
     * @param showProgress Whether to display a progress bar or not.
     * @param liveRun Must be passed and set as true to force a real run
     */
    PurgeDuplicates(std::string  directory, bool showProgress, bool liveRun = false);
    /**
     * @brief Executes the logic for identifying and removing duplicates.
     */
    void execute();

/**
 * @brief Generates a cryptographic hash of a file's contents using Blake2 algorithm.
 * @param filePath The file to generate the hash for.
 * @return The hash as a hexadecimal string.
 * @details Platform-specific behavior:
 *   - On 64-bit architectures: Uses Blake2b512 for better performance
 *   - On 32-bit architectures: Uses Blake2s256 for memory efficiency
 *   - Can be forced to 32-bit algorithm with PDCPP_FORCE_32BIT_PATH define
 * @throws std::runtime_error If the hash generation fails.
 * @throws std::ios_base::failure If the file cannot be opened.
 */
    static std::string generateHash(const std::string& filePath);

/**
 * @brief Displays a progress bar in the console.
 * @param current The current progress count.
 * @param total The total number of files to process.
 */
void displayProgress(size_t current, size_t total);

private:
    std::string directoryPath; // The path to the target directory
    bool showProgress;         // Flag to indicate if a progress bar is displayed
    bool liveRun;              // Force a real deletion of files instead of a dry run

    /**
     * @brief Identifies and removes duplicate files in a directory.
     * This is the main logic for processing the directory.
     */
    void identifyAndRemoveDuplicates();
};

#endif // PURGE_DUPLICATES_HPP
