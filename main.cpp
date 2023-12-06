#include "day-01/day01.h"
#include "day-02/day02.h"
#include "day-03/day03.h"
#include "day-04/day04.h"
#include "day-05/day05.h"
#include "day-06/day06.h"
#include <stdio.h>
#include <chrono>
using namespace std::chrono;

int main() {
    int day = 6;

    printf("Advent of Code 2023 - Day %d \n", day);
    printf("====================================\n");

    auto start = high_resolution_clock::now();
    switch (day) {
        case 1:
            day01();
            break;
        case 2:
            day02();
            break;
        case 3:
            day03();
            break;
        case 4:
            day04();
            break;
        case 5:
            day05();
            break;
        case 6:
            day06();
            break;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    printf("====================================\n");
    printf("Execution time: %d μs\n", duration.count());

    return 0;
}
