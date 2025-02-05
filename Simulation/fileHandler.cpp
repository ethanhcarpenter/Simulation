#include "fileHandler.h"

void FileHandler::writeToFile(const std::string& filename, const std::string& data) {
    std::ofstream file(filename, std::ios::out | std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    file << data;
    file.close();
}

void FileHandler::clearDirectory(const std::string& directory) {
    try {
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            std::filesystem::remove(entry);
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error clearing directory: " << e.what() << std::endl;
    }
}
