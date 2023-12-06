#include "../utils.h"
#include "day02.h"
#include<string>
#include<map>

void splitStringOnSpace(std::string& s, std::vector<std::string>& result) {
    // Initialize a variable to store the index where the word starts.
    int wordStartIndex = 0;

    // Loop through each character in the string.
    for (int i = 0; i < s.length(); i++) {
        // If the character is a space, we need to get the substring from the last space to the current index.
        if (s[i] == ' ') {
            // Get the substring.
            std::string substring = s.substr(wordStartIndex, i - wordStartIndex);

            // Add the substring to the result vector.
            result.push_back(substring);

            // If there is a space at i, the next word starts at i + 1.
            wordStartIndex = i + 1;
        }
    }

    // Get the substring from the last space to the end of the string.
    std::string substring = s.substr(wordStartIndex, s.length() - wordStartIndex);

    // Add the substring to the result vector.
    result.push_back(substring);
}

void day02(std::vector<std::string> &lines) {
    // ---------------- Part 1 ----------------
    // Initialize a counter variable to store the number of possible game IDs.
    int counter = 0;

    // Create an object to store the number of cubes left in each box.
    const std::map<std::string, int> cubesLeft = {{"red", 12},{"green", 13},{"blue", 14}};

    // Loop through each line in the lines vector.
    for (int i = 0; i < lines.size(); i++) {
        std::vector<std::string> words;
        splitStringOnSpace(lines[i], words);

        // Set a variable to store whether the game is impossible.
        // If the game is impossible, the for-loop will break, but also need to break the outer loop.
        bool gameImpossible = false;

        // We skip the first two words ('game' and the number of the game).
        // Iteration happens in steps of 2 because we process two words at a time (the number of cubes and the color).
        // The end condition makes sure that there is at least one more word after the current one.
        for (int j = 2; j < words.size() - 1; j+= 2) {
            int number = std::stoi(words[j]);
            std::string color = words[j + 1];

            // If the color ends in , or ; we need to remove it.
            if (color[color.length() - 1] == ',' || color[color.length() - 1] == ';') {
                color = color.substr(0, color.length() - 1);
            }

            // If the number of the color is greater than the number of cubes left, the game is impossible.
            if (number > cubesLeft.at(color)) {
                gameImpossible = true;
                break;
            }
        }

        // If the game is impossible, we skip the rest of the loop.
        if (gameImpossible) {
            continue;
        }

        // If the game is possible, we increment the counter with the game ID.
        counter+= (i + 1);
    }

    // Print the result.
    printf("Result (Part 1): %d\n", counter);

    // ---------------- Part 2 ----------------
    int sumOfPowers = 0;

    // Loop through each line in the lines vector.
    for (int i = 0; i < lines.size(); i++) {
        std::vector<std::string> words;
        splitStringOnSpace(lines[i], words);

        // Store in an object the number of cubes required for that line, up until now.
        std::map<std::string, int> cubesRequired = {{"red", 0},{"green", 0},{"blue", 0}};

        // We skip the first two words ('game' and the number of the game).
        // Iteration happens in steps of 2 because we process two words at a time (the number of cubes and the color).
        // The end condition makes sure that there is at least one more word after the current one.
        for (int j = 2; j < words.size() - 1; j+= 2) {
            int number = std::stoi(words[j]);
            std::string color = words[j + 1];

            // If the color ends in , or ; we need to remove it.
            if (color[color.length() - 1] == ',' || color[color.length() - 1] == ';') {
                color = color.substr(0, color.length() - 1);
            }

            // See if the number of cubes required for the current color is greater than the number currently stored.
            // If it is, we update the number of cubes required.
            if (number > cubesRequired.at(color)) {
                cubesRequired[color] = number;
            }
        }

        // Calculate the sum of the powers.
        int powerForLine = 1;
        for (auto& [color, number] : cubesRequired) {
            powerForLine *= number;
        }

        // Add the sum of the powers for the current line to the total sum of powers.
        sumOfPowers += powerForLine;
    }

    // Print the result.
    printf("Result (Part 2): %d\n", sumOfPowers);
}
