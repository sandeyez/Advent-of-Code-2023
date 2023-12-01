#include "utils.h"

// Utility function to read a file and store each line in a vector.
int readFile(std::string& fileName, std::vector<std::string>& lines) {
    // Attempt to open the file.
    std::ifstream file(fileName);

    // If the file could not be opened, print an error message and return 1.
    if (!file) {
        printf("Error opening file %s\n", fileName.c_str());
        return 1;
    }

    // Read each line in the file and store it in the lines vector.
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    // Close the file
    file.close();

    // Return 0 to indicate success.
    return 0;
}

