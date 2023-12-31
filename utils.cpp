#include "utils.h"
#include<string>

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

void splitOnSpace(std::string& line, std::vector<std::string>& words) {
    // Create an accumulator to store the current word.
    std::string acc = "";

    // Loop through each character in the line.
    for (char c: line) {
        // If the character is a space, add the accumulator to the words vector and reset the accumulator.
        if (c == ' ') {
            if (acc.empty()) {
                continue;
            }
            words.push_back(acc);
            acc = "";
        }
        // If the character is not a space, add it to the accumulator.
        else {
            acc += c;
        }
    }

    // If the accumulator is not empty, add the final word to the words vector.
    if (!acc.empty()) {
        words.push_back(acc);
    }
}

int solveWithABCFormula(long a, long b, long c, long& x1, long& x2) {
    // Calculate the discriminant.
    long discriminant = b * b - 4 * a * c;

    // If the discriminant is negative, return 1 to indicate that the equation has no real solutions.
    if (discriminant < 0) {
        return 1;
    }

    // Calculate the two solutions.
    x1 = (-b + sqrt(discriminant)) / (2 * a);
    x2 = (-b - sqrt(discriminant)) / (2 * a);

    // Return 0 to indicate success.
    return 0;
}

int solveWithABCFormula(int a, int b, int c, int& x1, int& x2) {
    solveWithABCFormula((long) a, (long) b, (long) c, (long&) x1, (long&) x2);
}