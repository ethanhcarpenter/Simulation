#pragma once
#include <fstream>
#include <iostream>
using namespace std;

class FileHandler {
public:
    static void writeToFile(const string& filename, const string& data);
};
