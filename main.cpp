#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

void createRandomFile(const std::string &filename, std::size_t size_in_mb) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error creating file " << filename << std::endl;
        return;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<char> buffer(1024 * 1024); // 1 MB buffer

    for (std::size_t i = 0; i < size_in_mb; ++i) {
        for (std::size_t j = 0; j < buffer.size(); ++j) {
            buffer[j] = std::rand() % 256;
        }
        file.write(buffer.data(), buffer.size());
    }

    std::cout << "Random file " << filename << " of size " << size_in_mb << " MB created."
              << std::endl;
}

void copyFileRepeatedly(const std::string &source, const std::string &destination_dir,
                        std::size_t limit_in_gb) {
    std::size_t file_count       = 0;
    std::size_t total_size       = 0;
    std::size_t size_limit_bytes = limit_in_gb * 1024 * 1024 * 1024;

    while (total_size < size_limit_bytes) {
        std::string dest_file = destination_dir + "/file_copy_" + std::to_string(file_count);
        fs::copy(source, dest_file);
        std::cout << "Copied " << source << " to " << dest_file << std::endl;

        total_size += fs::file_size(dest_file);
        ++file_count;
    }

    std::cout << "Filled " << total_size / (1024 * 1024 * 1024) << " GB with " << file_count
              << " copies." << std::endl;
}

int main() {
    std::string filename        = "0.bin";
    std::string destination_dir = ".";
    std::size_t size_in_mb      = 100; // Size of the random file in MB
    std::size_t limit_in_gb     = 5;   // Limit for the total size in GB

    // Create destination directory if it doesn't exist
    // if (!fs::exists(destination_dir)) {
    //    fs::create_directory(destination_dir);
    //}

    // Create a random file
    createRandomFile(filename, size_in_mb);

    // Copy the file repeatedly until the space limit is reached
    copyFileRepeatedly(filename, destination_dir, limit_in_gb);

    return 0;
}
