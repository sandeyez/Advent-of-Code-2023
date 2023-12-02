#include "day-01/day01.h"
#include "day-02/day02.h"
#include <stdio.h>
#include <chrono>
using namespace std::chrono;

int main() {
    int day = 2;

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
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    printf("====================================\n");
    printf("Execution time: %lld ms\n", duration.count());


    return 0;
}
