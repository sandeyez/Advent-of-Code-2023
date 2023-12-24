#include "day-01/day01.h"
#include "day-02/day02.h"
#include "day-03/day03.h"
#include "day-04/day04.h"
#include "day-05/day05.h"
#include "day-06/day06.h"
#include "day-07/day07.h"
#include "day-08/day08.h"
#include "utils.h"
#include <stdio.h>
#include <vector>
#include <string>

#include <chrono>
using namespace std::chrono;

int main() {
    int day = 8;

    printf("Advent of Code 2023 - Day %d \n", day);
    printf("====================================\n");

    // Initialize a vector to store the file input and set the input file name.
    std::vector<std::string> lines;

    std::string dayFolder = std::string("../day-") + (day < 10 ? "0" : "") + std::to_string(day) + "/";
    std::string fileName = dayFolder + "input.txt";

    // Read the file and store the result in the lines vector.
    int res = readFile(fileName, lines);

    // If an error occurred during the file reading, print an error message.
    if (res != 0) {
        printf("Error reading the input file.");
    }

    auto start = high_resolution_clock::now();
    switch (day) {
        case 1:
            day01(lines);
            break;
        case 2:
            day02(lines);
            break;
        case 3:
            day03(lines);
            break;
        case 4:
            day04(lines);
            break;
        case 5:
            day05(lines);
            break;
        case 6:
            day06(lines);
            break;
        case 7:
            day07(lines);
            break;
        case 8:
            day08(lines);
            break;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    printf("====================================\n");
    printf("Execution time: %d μs\n", duration.count());

    return 0;
}
