#include "day05.h"
#include<string>
#include<vector>
#include "../utils.h"

struct Range {
    long start;
    long end;
};

struct RangeMapping {
    long start;
    long end;
    long mapping;
};

void day05(std::vector<std::string> &lines) {
    // ---------------- Part 1 ----------------
    std::string line = lines[0];

    std::vector<std::string> words;

    // Split the line on spaces.
    splitOnSpace(line, words);

    // The amount of input numbers we have is the amount of words minus 1 (the first word is 'seeds:').
    const int amountOfInputNumbers = words.size() - 1;

    // Create an array to store the input numbers.
    long input[amountOfInputNumbers];

    bool inputMapped[amountOfInputNumbers];

    // Fill the array with the input numbers.
    for (int i = 0; i < amountOfInputNumbers; i++) {
        input[i] = std::stol(words[i + 1]);
        inputMapped[i] = false;
    }

    for (int i = 2; i < lines.size(); i++) {
        while (i < lines.size() && !lines[i].empty()) {
            line = lines[i];

            // Split the line on spaces.
            splitOnSpace(line, words);

            // If the first word is a number, we want to process this line
            if (words[0][0] >= '0' && words[0][0] <= '9') {
                // Parse the numbers from the line.
                long destinationStart = std::stol(words[0]);
                long sourceStart = std::stol(words[1]);
                long rangeLength = std::stol(words[2]);

                // Loop through each of the input numbers.
                for (int j = 0; j < amountOfInputNumbers; j++) {
                    // If the number is already mapped, we can skip it.
                    if (inputMapped[j]) {
                        continue;
                    }

                    long value = input[j];

                    // Check if the current range applies to this value. If so, map it.
                    if (value >= sourceStart && value < sourceStart + rangeLength) {
                        input[j] = destinationStart + (value - sourceStart);
                        inputMapped[j] = true;
                    }
                }
            }

            i++;
            // When a line processed, we want to reset the state for the next round.
            // Words should be cleared.
            words.clear();
        }

        // After a full map has been done, the inputMapped array should contain only false values.
        for (int j = 0; j < amountOfInputNumbers; j++) {
            inputMapped[j] = false;
        }
    }

    // When all the mapping is finished, print the minimum value in the input array.
    long min = -1;

    for (int i = 0; i < amountOfInputNumbers; i++) {
        if (input[i] < min || min == -1) {
            min = input[i];
        }
    }

    printf("Part 1: %d\n", min);

    // ---------------- Part 2 ----------------
    line = lines[0];

    words.clear();

    // Split the line on spaces.
    splitOnSpace(line, words);

    // Create a vector to store the input ranges.
    std::vector<Range> inputRanges;

    // Fill the array with the input ranges.
    for (int i = 1; i < words.size() - 1; i+= 2) {
        long start = std::stol(words[i]);
        long length = std::stol(words[i + 1]);

        Range range = {start, start + length - 1};
        inputRanges.push_back(range);
    }

    for (int i = 2; i < lines.size(); i++) {
        std::vector<Range> rangesLeftToMap = inputRanges;

        // Create a vector to store the ranges that result from the mapping.
        std::vector<Range> mappingResults;

        while (i < lines.size() && !lines[i].empty()) {
            line = lines[i];

            // Split the line on spaces.
            splitOnSpace(line, words);

            // If the first word is a number, we want to process this line
            if (words[0][0] >= '0' && words[0][0] <= '9') {
                // Parse the numbers from the line.
                long destinationStart = std::stol(words[0]);
                long sourceStart = std::stol(words[1]);
                long rangeLength = std::stol(words[2]);

                // Store all the ranges that are left to map for this line (it is initially one, but can be split into multiple).
                std::vector<RangeMapping> lineRangesLeftToMap = {
                        {
                                sourceStart,
                                sourceStart + rangeLength - 1,
                                destinationStart - sourceStart,
                        }
                };


                // We loop through each of the ranges that we are using to map (from this line).
                for (auto mappingRange : lineRangesLeftToMap) {
                    // Store the start and end of the range we are using to map + the operation it does to the input range.
                    long mappingRangeStart = mappingRange.start;
                    long mappingRangeEnd = mappingRange.end;
                    long mapping = mappingRange.mapping;

                    // We loop through each of our input ranges to see if they are affected by this mapping.
                    for (auto rangeToMap = rangesLeftToMap.begin(); rangeToMap != rangesLeftToMap.end(); rangeToMap++) {
                        // Store the start and end of our input range.
                        long rangeStart = rangeToMap->start;
                        long rangeEnd = rangeToMap->end;

                        // If the two ranges are totally disjoint, we can skip this comparison.
                        if (rangeEnd < mappingRangeStart || rangeStart > mappingRangeEnd) {
                            continue;
                        }

                        // Create a variable to store the mapping result.
                        Range mappedRange{};

                        // If the input range starts within the mapping range, but ends outside.
                        // We need to split the input range into two ranges. The first one is affected by the mapping, the second one is not.
                        // Because the second one still needs to be processed, we alter the input range to only contain the second one.
                        // The mapping output of the first one is added to the mapping results.
                        if (rangeStart >= mappingRangeStart && rangeStart <= mappingRangeEnd && rangeEnd > mappingRangeEnd) {
                            rangeToMap->start = mappingRangeEnd + 1;

                            mappedRange.start = rangeStart + mapping;
                            mappedRange.end = mappingRangeEnd + mapping;
                        }
                        // If the range starts outside the mapping range, but ends within.
                        // We need to do a similar thing as above. The range is split into two, the first one is not affected by the mapping, the second one is.
                        // The input range is altered to only contain the first one. The mapping output of the second one is added to the mapping results.
                        else if (rangeStart < mappingRangeStart && rangeEnd >= mappingRangeStart && rangeEnd <= mappingRangeEnd) {
                            rangeToMap->end = mappingRangeStart - 1;

                            mappedRange.start = mappingRangeStart + mapping;
                            mappedRange.end = rangeEnd + mapping;
                        }
                        // If the range starts and ends within the mapping range (or if they are equal).
                        // In this case, there is no part of this range left to map, so we delete it from the rangesLeftToMap vector.
                        // We add the mapping output to the mapping results.
                        else if (rangeStart >= mappingRangeStart && rangeStart <= mappingRangeEnd && rangeEnd >= mappingRangeStart && rangeEnd <= mappingRangeEnd) {
                            rangesLeftToMap.erase(rangeToMap);
                            rangeToMap--;

                            mappedRange.start = rangeStart + mapping;
                            mappedRange.end = rangeEnd + mapping;
                        }
                        // If the range starts before and ends after the mapping range.
                        // In this case the range is split into three parts. The first and last one are not affected by the mapping, the middle one is.
                        // The original input range is removed, and the mapping output of the middle one is added to the mapping results.
                        // Finally, we re-add the first and last part of the range to the rangesLeftToMap vector.
                        else if (rangeStart < mappingRangeStart && rangeEnd > mappingRangeEnd) {
                            mappedRange.start = mappingRangeStart + mapping;
                            mappedRange.end = mappingRangeEnd + mapping;

                            rangesLeftToMap.erase(rangeToMap);
                            rangeToMap--;

                            lineRangesLeftToMap.push_back({
                                    rangeStart,
                                    mappingRangeStart - 1,
                                    mapping,
                            });
                            lineRangesLeftToMap.push_back({
                                    mappingRangeEnd + 1,
                                    rangeEnd,
                                    mapping
                            });
                        }

                        // Try to find an existing range that has a neighboring start or end to the mapped range.
                        // If we find one, we can merge the two ranges.
                        bool found = false;

                        for (auto existingRange = mappingResults.begin(); existingRange != mappingResults.end(); existingRange++) {
                            if (existingRange->start == mappedRange.end + 1) {
                                existingRange->start = mappedRange.start;
                                found = true;
                                break;
                            } else if (existingRange->end == mappedRange.start - 1) {
                                existingRange->end = mappedRange.end;
                                found = true;
                                break;
                            }
                        }

                        // If no existing range was found, we add the mapped range to the mapping results.
                        if (!found) {
                            mappingResults.push_back(mappedRange);
                        }
                    }
                }
            }
            i++;

            // When a line processed, we want to reset the state for the next round.
            // Words should be cleared.
            words.clear();
        }
        // All the ranges that were not affected by any of the mapping ranges are added to the mapping results as themselves.
        for (auto range : rangesLeftToMap) {
            mappingResults.push_back(range);
        }

        // We set the input for the next round to the output of this round.
        inputRanges = mappingResults;

        // The mappingResults vector should be cleared for the next round.
        mappingResults.clear();
    }

    // When all the mapping is finished, print the minimum value in the input array.
    // Because the values are now ranges, we need to find the minimum start value.
    long minStart = -1;

    for (auto range : inputRanges) {
        if (range.start < minStart || minStart == -1) {
            minStart = range.start;
        }
    }

    printf("Part 2: %d\n", minStart);
}
