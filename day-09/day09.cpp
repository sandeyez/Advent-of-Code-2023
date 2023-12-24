#include "day09.h"
#include "../utils.h"

void day09(std::vector<std::string> &lines) {
    int result = 0;

    // ---------------- Part 1 ----------------
    for (auto &line: lines) {
        std::vector<std::vector<int>> sequences;

        std::vector<std::string> words;

        splitOnSpace(line, words);

        std::vector<int> sequence;

        for (auto &word: words) {
            sequence.push_back(std::stoi(word));
        }

        sequences.push_back(sequence);

        while (!std::all_of(sequence.begin(), sequence.end(), [](int i) { return i==0; })) {
            std::vector<int> newSequence;

            for (int i = 0; i < sequence.size() - 1; i++) {
                int first = sequence[i];
                int second = sequence[i + 1];

                newSequence.push_back(second - first);
            }

            sequence = newSequence;

            sequences.push_back(sequence);
        }

        std::vector<int> prevSequence;

        for (int i = sequences.size() -1; i >= 0; i--) {
            sequence = sequences[i];

            int lastValue = sequence[sequence.size() - 1];
            int newValue;

            if (i == sequences.size() -1) {
                newValue = 0;
            } else {
                newValue = lastValue + prevSequence[prevSequence.size() - 1];
            }

            if (i == 0) {
                result += newValue;
            }

            sequence.push_back(newValue);

            prevSequence = sequence;
        }
    }

    printf("Part 1: %d\n", result);

    // ---------------- Part 2 ----------------
    result = 0;

    for (auto &line: lines) {
        std::vector<std::vector<int>> sequences;

        std::vector<std::string> words;

        splitOnSpace(line, words);

        std::vector<int> sequence;

        for (int i = words.size() -1; i >= 0; i--) {
            std::string word = words[i];
            sequence.push_back(std::stoi(word));
        }

        sequences.push_back(sequence);

        while (!std::all_of(sequence.begin(), sequence.end(), [](int i) { return i==0; })) {
            std::vector<int> newSequence;

            for (int i = 0; i < sequence.size() - 1; i++) {
                int first = sequence[i];
                int second = sequence[i + 1];

                newSequence.push_back(second - first);
            }

            sequence = newSequence;

            sequences.push_back(sequence);
        }

        std::vector<int> prevSequence;

        for (int i = sequences.size() -1; i >= 0; i--) {
            sequence = sequences[i];

            int lastValue = sequence[sequence.size() - 1];
            int newValue;

            if (i == sequences.size() -1) {
                newValue = 0;
            } else {
                newValue = lastValue + prevSequence[prevSequence.size() - 1];
            }

            if (i == 0) {
                result += newValue;
            }

            sequence.push_back(newValue);

            prevSequence = sequence;
        }
    }

    printf("Part 2: %d\n", result);
}