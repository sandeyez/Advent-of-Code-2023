#include "day06.h"
#include "../utils.h"
#include<vector>
#include<string>

void day06(std::vector<std::string> &lines) {
    // ---------------- Part 1 ----------------
    // Initialize two vectors to store the times and the distances.
    std::vector<int> times;
    std::vector<int> distances;

    // Read the first line and store the numbers in the times vector.
    std::string line = lines[0];

    std::vector<std::string> words;

    splitOnSpace(line, words);

    for (int i = 1; i < words.size(); i++) {
        times.push_back(std::stoi(words[i]));
    }

    words.clear();

    // Read the second line and store the numbers in the distances vector.
    line = lines[1];

    splitOnSpace(line, words);

    for (int i = 1; i < words.size(); i++) {
        distances.push_back(std::stoi(words[i]));
    }

    int product = 1;

    for (int i = 0; i < times.size(); i++) {
        long time = times[i];
        long distance = distances[i];

        long x1, x2;

        solveWithABCFormula(1, -time, distance, x1, x2);

        product *= abs(x2 - x1);
    }

    printf("Part 1: %d\n", product);

    // ---------------- Part 2 ----------------
    // Initialize a variable to store the time and distance.
    long time = 0;
    long distance = 0;

    // Read the first line and store the numbers in the time and distance variables.
    line = lines[0];
    words.clear();

    splitOnSpace(line, words);

    for (int i = 1; i < words.size(); i++) {
        std::string word = words[i];

        time = time * (pow(10, word.size())) + std::stol(words[i]);
    }

    words.clear();

    // Read the second line and store the numbers in the time and distance variables.
    line = lines[1];

    splitOnSpace(line, words);

    for (int i = 1; i < words.size(); i++) {
        std::string word = words[i];

        distance = distance * (pow(10, word.size())) + std::stol(words[i]);
    }

    long x1, x2;

    solveWithABCFormula(1, -time, distance, x1, x2);

    printf("Part 2: %ld\n", abs(x2 - x1));
}
