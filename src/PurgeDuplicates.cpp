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
#include "PurgeDuplicates.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include <utility>
#include <vector>
#include <openssl/evp.h>
#include <filesystem>
#include <stdexcept>
#include <sstream>

namespace fs = std::filesystem;

PurgeDuplicates::PurgeDuplicates(std::string  directory, bool showProgress, bool liveRun)
        : directoryPath(std::move(directory)), showProgress(showProgress), liveRun(liveRun) {}

std::string PurgeDuplicates::generateHash(const std::string& filePath) {
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr) {
        throw std::runtime_error("Failed to create EVP_MD_CTX.");
    }
    if (EVP_DigestInit_ex(context, EVP_blake2b512(), nullptr) != 1) {
        EVP_MD_CTX_free(context);
        throw std::runtime_error("Failed to initialize digest with Blake2.");
    }

    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        EVP_MD_CTX_free(context);
        throw std::ios_base::failure("Could not open file: " + filePath);
    }

    char buffer[4096];
    while (file.read(buffer, sizeof(buffer))) {
        if (EVP_DigestUpdate(context, buffer, file.gcount()) != 1) {
            EVP_MD_CTX_free(context);
            throw std::runtime_error("Failed to update Blake2 hash during file processing.");
        }
    }

    if (file.gcount() > 0) {
        if (EVP_DigestUpdate(context, buffer, file.gcount()) != 1) {
            EVP_MD_CTX_free(context);
            throw std::runtime_error("Failed to update Blake2 hash with final bytes.");
        }
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLength = 0;
    if (EVP_DigestFinal_ex(context, hash, &hashLength) != 1) {
        EVP_MD_CTX_free(context);
        throw std::runtime_error("Failed to finalize Blake2 hash.");
    }

    EVP_MD_CTX_free(context);

    std::ostringstream result;
    for (unsigned int i = 0; i < hashLength; i++) {
        result << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return result.str();
}

void PurgeDuplicates::displayProgress(size_t current, size_t total) {
    static const int barWidth = 50;
    float progress = static_cast<float>(current) / static_cast<float>(total);
    int pos = static_cast<int>(barWidth * progress);

    std::cout << "\r[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << "%";
    std::cout.flush();
}

void PurgeDuplicates::identifyAndRemoveDuplicates() {
    std::unordered_map<std::string, std::string> fileHashes;
    std::vector<std::string> duplicates;
    size_t totalFiles = 0;

    // Count total files for progress display
    if (showProgress) {
        for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                ++totalFiles;
            }
        }
        if (totalFiles == 0) {
            std::cout << "No files found in the directory." << std::endl;
            return;
        }
    }

    size_t processedFiles = 0;

    // Identify duplicates
    for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            const std::string filePath = entry.path().string();
            try {
                std::string fileHash = generateHash(filePath);

                if (fileHashes.count(fileHash)) {
                    duplicates.push_back(filePath);
                } else {
                    fileHashes[fileHash] = filePath;
                }
            } catch (const std::exception& e) {
                std::cerr << "Error processing file: " << filePath << " - " << e.what() << std::endl;
            }
        }

        ++processedFiles;

        if (showProgress) {
            displayProgress(processedFiles, totalFiles);
        }
    }

    std::cout << std::endl;

    // Handle duplicates based on --live-run flag
    if (liveRun) {
        for (const auto& duplicate : duplicates) {
            try {
                fs::remove(duplicate);
                std::cout << "Removed duplicate: " << duplicate << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error deleting file: " << duplicate << " - " << e.what() << std::endl;
            }
        }
        std::cout << "Duplicate removal complete. Processed " << fileHashes.size() << " unique files." << std::endl;
    } else {
        // Dry-run: List duplicate files without deletion
        std::cout << "Dry Run: The following files would be deleted:" << std::endl;
        for (const auto& duplicate : duplicates) {
            std::cout << "  " << duplicate << std::endl;
        }
        std::cout << "Dry run complete. No files were deleted." << std::endl;
        std::cout << "To perform the actual deletion, re-run the command with the --live-run flag." << std::endl;
    }
}

void PurgeDuplicates::execute() {
    identifyAndRemoveDuplicates();
}
