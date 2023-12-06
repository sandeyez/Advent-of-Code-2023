#include "../utils.h"
#include "day01.h"
#include<string>

std::vector<std::string> digits = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

bool isDigit(std::string& line, int index, int* digit) {
    // First we check if the character at the specified index is a digit.
    bool charIsDigit = line[index] >= '0' && line[index] <= '9';

    // If the character is a digit, we set the digit variable and return true.
    if (charIsDigit) {
        *digit = line[index] - '0';
        return true;
    }

    // If the character is not a digit, we need to check if the line starts with a digit in text.
    // Because we don't know how long this digit is going to be, we need to get a substring from the index to the end.
    std::string substring = line.substr(index, line.length() - index);

    // We check if the substring starts with a digit in text.
    bool substringStartsWithDigit = false;

    // For each of the digits in text, check if the substring starts with it.
    for (int i = 0; i < digits.size(); i++) {
        // If it does, set the digit variable and substringStartsWithDigit to true.
        if (substring.find(digits[i]) == 0) {
            substringStartsWithDigit = true;
            *digit = i + 1;
            break;
        }
    }

    // Return the result of the check.
    return substringStartsWithDigit;
}

void day01(std::vector<std::string> &lines) {
    // Initialize a counter variable to store the sum.
    int counter = 0;

    // Loop through each line in the lines vector.
    for (auto & line : lines) {
        // Initialize two variables to store the first and last number.
        int firstNumber = 0;
        int lastNumber = 0;

        // Loop through each character in the line.
        for (int i = 0; i < line.length(); i++) {
            // Initialize a variable to store the digit.
            int digit = 0;

            // Check if the character at the current index is a digit.
            if (!isDigit(line, i, &digit)) {
                continue;
            }

            // If no digits have been found yet, set the first number to the digit.
            if (firstNumber == 0) {
                firstNumber = digit;
            }

            // Always set the last number to the digit.
            lastNumber = digit;
        }

        // Calculate the value of the current line and add it to the counter.
        int value = (firstNumber) * 10 + (lastNumber);

        counter += value;
    }

    // Print the result.
    printf("Result (Part 2): %d\n", counter);
}