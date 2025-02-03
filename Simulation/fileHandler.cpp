#include "fileHandler.h"

void FileHandler::writeToFile(const string& filename, const string& data) {
    ofstream file(filename, ios::out | ios::app);
    
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;  // Early exit if file cannot be opened
    }

    file << data;
    file.close();  // Explicitly close the file
}
