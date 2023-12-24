#include<string>
#include<vector>
#include<map>
#include<tuple>
#include<numeric>
#include "../utils.h"

// Source: https://www.geeksforgeeks.org/program-to-find-lcm-of-two-numbers/.
// Recursive function to return gcd of a and b
long long gcd(long long int a, long long int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to return LCM of two numbers
long long lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}

void day08(std::vector<std::string> &lines) {
    // Create a map that will map node names to their struct.
    std::map<std::string, std::tuple<std::string, std::string>> nodes;

    std::string instructions = lines[0];

    // ---------------- Part 1 ----------------
    std::string startingNodeName = "AAA";
    std::string endingNodeName = "ZZZ";

    for (int i = 2; i < lines.size(); i++) {
        std::string line = lines[i];

        std::vector<std::string> words;

        splitOnSpace(line, words);

        std::string nodeName = words[0];

        std::string leftNodeName = words[2].substr(1, words[2].length() - 2);
        std::string rightNodeName = words[3].substr(0, words[3].length() - 1);

        std::tuple<std::string, std::string> node = std::make_tuple(leftNodeName, rightNodeName);

        nodes[nodeName] = node;
    }

    int stepCount = 0;
    std::string activeNodeName = startingNodeName;

    while (activeNodeName != endingNodeName) {
        int i = stepCount % instructions.size();

        char instruction = instructions[i];

        if (instruction == 'L') {
            activeNodeName = std::get<0>(nodes[activeNodeName]);
        } else if (instruction == 'R') {
            activeNodeName = std::get<1>(nodes[activeNodeName]);
        }

        stepCount++;
    }

    printf("Part 1: %d\n", stepCount);

    // ---------------- Part 2 ----------------
    // Create a vector that will store all of the starting positions.
    std::vector<std::string> startingPositions;

    for (int i = 2; i < lines.size(); i++) {
        std::string line = lines[i];

        std::vector<std::string> words;

        splitOnSpace(line, words);

        std::string nodeName = words[0];

        std::string leftNodeName = words[2].substr(1, words[2].length() - 2);
        std::string rightNodeName = words[3].substr(0, words[3].length() - 1);

        std::tuple<std::string, std::string> node = std::make_tuple(leftNodeName, rightNodeName);

        nodes[nodeName] = node;

        // If the node name ends in A, it is an active node.
        if (nodeName[2] == 'A') {
            startingPositions.push_back(nodeName);
        }
    }

    // We store the lengths of the cycles for each of the ghosts in a vector.
    std::vector<int> cycleLengths;

    for(auto &startingPosition : startingPositions) {
        activeNodeName = startingPosition;

        stepCount = 0;

        while (activeNodeName[2] != 'Z') {
            int i = stepCount % instructions.size();

            char instruction = instructions[i];

            if (instruction == 'L') {
                activeNodeName = std::get<0>(nodes[activeNodeName]);
            } else if (instruction == 'R') {
                activeNodeName = std::get<1>(nodes[activeNodeName]);
            }

            stepCount++;
        }

        cycleLengths.push_back(stepCount);
    }

    // Find the least common multiple of all the numbers in the list.
    // This is when each of the cycles will be finished at the same time.
    int result = std::accumulate(cycleLengths.begin(), cycleLengths.end(), 1, lcm);

    printf("Part 2: %d\n", result);
}