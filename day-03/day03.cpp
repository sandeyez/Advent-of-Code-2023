#include "../utils.h"
#include "day03.h"
#include<string>

struct Symbol {
    int x;
    int y;
};

int day03() {
    // Initialize a vector to store the file input and set the input file name.
    std::vector<std::string> lines;
    std::string fileName = "../day-03/input.txt";

    // Read the file and store the result in the lines vector.
    int res = readFile(fileName, lines);

    // If an error occurred during the file reading, print an error message.
    if (res != 0) {
        printf("Error reading the input file.");
    }

    size_t lineLength = lines[0].length();
    size_t lineCount = lines.size();

    // ---------------- Part 1 ----------------
    // Create a grid to store the numbers in the lines.
    int grid[lineCount][lineLength];

    // Create a vector to contain the positions of the symbols
    std::vector<Symbol> symbols;

    // Number will store the number we are currently reading.
    int number = 0;

    // Store the x-coordinates of the parts of the number we are currently reading.
    std::vector<int> numberCoordinates;

    for (int i = 0; i < lineCount; i++) {
        for (int j = 0; j < lineLength; j++) {
            char c = lines[i][j];

            if (c >= '0' && c <= '9') {
                int value = c - '0';

                // Add the value to the number.
                number = number * 10 + value;

                // Add the x-coordinate to the numberCoordinates vector.
                numberCoordinates.push_back(j);
            } else {
                grid[i][j] = 0;

                // If the character is not a digit, or a point, it is a symbol.
                if (c != '.') {
                    // Create a symbol object and set its x and y coordinates.
                    Symbol symbol{};
                    symbol.x = j;
                    symbol.y = i;

                    // Add the symbol to the symbols vector.
                    symbols.push_back(symbol);
                }
                if (number != 0) {
                    // If the number is not 0, we have finished reading a number.
                    // We have to put this number in the grid for each of the coordinates.
                    for (int k = 0; k < numberCoordinates.size(); k++) {
                        grid[i][numberCoordinates[k]] = number;
                    }

                    // Clear the numberCoordinates vector.
                    numberCoordinates.clear();

                    // Set the number to 0.
                    number = 0;
                }
            }
        }

        for (int k = 0; k < numberCoordinates.size(); k++) {
            grid[i][numberCoordinates[k]] = number;
        }
    }

    for (int k = 0; k < numberCoordinates.size(); k++) {
        grid[lineCount-1][numberCoordinates[k]] = number;
    }

    int sum = 0;

    // Now, for each of the symbols, check if there is a number on the grid that is adjacent to the symbol.
    for (auto symbol : symbols) {
        // Get the symbol.
        // Get the x and y coordinates of the symbol.
        int x = symbol.x;
        int y = symbol.y;

        // Loop through each of the neighbors horizontally, vertically and diagonally.
        // If there is a number, add it to the sum and set the value in the grid to 0.
        for (int deltaX = -1; deltaX <= 1; deltaX++) {
            for (int deltaY = -1; deltaY <= 1; deltaY++) {
                if (deltaX == 0 && deltaY == 0) {
                    continue;
                }

                // Check if the coordinates are valid.
                if (x + deltaX >= 0 && x + deltaX < lineLength && y + deltaY >= 0 && y + deltaY < lineCount) {
                    int value = grid[y + deltaY][x + deltaX];

                    if (value == 0) {
                        continue;
                    }

                    int foundY = y + deltaY;
                    int foundX = x + deltaX;

                    // Add the number to the sum.
                    sum += value;

                    // Set the value in the grid to 0.
                    grid[y + deltaY][x + deltaX] = 0;

                    int coordinateLeft = foundX - 1;
                    int coordinateRight = foundX + 1;

                    // We need to remove the number from the grid to prevent it from being counted twice.
                    for (int i = 0; i < lineCount; i++) {
                        // Check if the left neighbor is the same number.
                        if (coordinateLeft >= 0 && grid[foundY][coordinateLeft] == value) {
                            grid[foundY][coordinateLeft] = 0;
                            coordinateLeft--;
                        }

                        // Check if the right neighbor is the same number.
                        if (coordinateRight < lineLength && grid[foundY][coordinateRight] == value) {

                            grid[foundY][coordinateRight] = 0;
                            coordinateRight++;
                        }

                        // If both neighbors are not the same number, we can stop the loop.
                        if (grid[foundY][coordinateLeft] != value && grid[foundY][coordinateRight] != value) {
                            break;
                        }
                    }
                }
            }
        }
    }

    printf("Part 1: %d\n", sum);

    // ---------------- Part 2 ----------------
    std::vector<Symbol> gears;

    for (int i = 0; i < lineCount; i++) {
        for (int j = 0; j < lineLength; j++) {
            char c = lines[i][j];

            if (c >= '0' && c <= '9') {
                int value = c - '0';

                // Add the value to the number.
                number = number * 10 + value;

                // Add the x-coordinate to the numberCoordinates vector.
                numberCoordinates.push_back(j);
            } else {
                grid[i][j] = 0;

                // If the character is not a digit, or a point, it is a symbol.
                if (c == '*') {
                    // Create a symbol object and set its x and y coordinates.
                    Symbol gear{};
                    gear.x = j;
                    gear.y = i;

                    // Add the symbol to the symbols vector.
                    gears.push_back(gear);
                }

                if (number != 0) {
                    // If the number is not 0, we have finished reading a number.
                    // We have to put this number in the grid for each of the coordinates.
                    for (int k = 0; k < numberCoordinates.size(); k++) {
                        grid[i][numberCoordinates[k]] = number;
                    }

                    // Clear the numberCoordinates vector.
                    numberCoordinates.clear();

                    // Set the number to 0.
                    number = 0;
                }
            }
        }

        for (int k = 0; k < numberCoordinates.size(); k++) {
            grid[i][numberCoordinates[k]] = number;
        }
    }

    int gearRatioSum = 0;

    // Loop through each of the gears.
    for (auto &gear : gears) {
        int x = gear.x;
        int y = gear.y;

        int adjacentNumbers = 0;
        int gearRatio = 1;

        // Loop through each of the neighbors horizontally, vertically and diagonally.
        // If there is a number, add it to the gear ratio and increment the adjacent numbers.
        for (int deltaX = -1; deltaX <= 1; deltaX++) {
            for (int deltaY = -1; deltaY <= 1; deltaY++) {
                if (deltaX == 0 && deltaY == 0) {
                    continue;
                }

                if (adjacentNumbers > 2) {
                    break;
                }

                // Check if the coordinates are valid.
                if (x + deltaX >= 0 && x + deltaX < lineLength && y + deltaY >= 0 && y + deltaY < lineCount) {
                    int value = grid[y + deltaY][x + deltaX];

                    if (value == 0) {
                        continue;
                    }

                    int foundY = y + deltaY;
                    int foundX = x + deltaX;

                    adjacentNumbers++;
                    gearRatio *= value;

                    // Set the value in the grid to 0.
                    grid[y + deltaY][x + deltaX] = 0;

                    int coordinateLeft = foundX - 1;
                    int coordinateRight = foundX + 1;

                    // We need to remove the number from the grid to prevent it from being counted twice.
                    for (int i = 0; i < lineCount; i++) {
                        // Check if the left neighbor is the same number.
                        if (coordinateLeft >= 0 && grid[foundY][coordinateLeft] == value) {
                            grid[foundY][coordinateLeft] = 0;
                            coordinateLeft--;
                        }

                        // Check if the right neighbor is the same number.
                        if (coordinateRight < lineLength && grid[foundY][coordinateRight] == value) {

                            grid[foundY][coordinateRight] = 0;
                            coordinateRight++;
                        }

                        // If both neighbors are not the same number, we can stop the loop.
                        if (grid[foundY][coordinateLeft] != value && grid[foundY][coordinateRight] != value) {
                            break;
                        }
                    }
                }
            }
        }

        // If there are exactly 2 adjacent numbers, add the gear ratio to the sum.
        if (adjacentNumbers == 2) {
            gearRatioSum += gearRatio;
        }
    }

    printf("Part 2: %d\n", gearRatioSum);
}