#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

class FileHandler {
public:
    //write path to a txt file
    static void writeToFile(const std::string& filename, const std::string& data);
    //delete all previosly made paths
    static void clearDirectory(const std::string& directory);
};
