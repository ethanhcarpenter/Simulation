#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

class FileHandler {
public:
    static void writeToFile(const std::string& filename, const std::string& data);
    static void clearDirectory(const std::string& directory);
};
