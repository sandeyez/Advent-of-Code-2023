#include "day04.h"
#include<string>
#include<vector>
#include "../utils.h"
#include <map>

void awardWinningCards(int &number, int &amountOfCards, std::map<int, int> &winningNumbers, int &scratchCardsWon) {
    scratchCardsWon += amountOfCards;

    for (int i = 1; i <= amountOfCards; i++) {
        int nextNumber = number + i;
        int amountOfCardsWon = winningNumbers[nextNumber];

        if (amountOfCardsWon == 0) {
            continue;
        }

        awardWinningCards(nextNumber, amountOfCardsWon, winningNumbers, scratchCardsWon);
    }
}


void day04(std::vector<std::string> &lines) {
    // ---------------- Part 1 ----------------
    // Create a variable to hold the total score.
    int score = 0;

    // Loop through each of the lines in the input
    for (auto &line: lines) {
        std::vector<std::string> words;

        // Split the line on spaces.
        splitOnSpace(line, words);

        // Create a vector to store the winning numbers.
        std::vector<int> winningNumbers;

        int cardScore = 0;

        // Loop through each of the words in the line (start at index 2 to skip the 'Game' and game number).
        int i = 2;
        for (; i < words.size(); i++) {
            if (words[i] == "|") {
                i++;
                break;
            }

            // Create a variable to store the current word.
            std::string word = words[i];

            // Create a variable to store the current number.
            int number = std::stoi(word);

            // Add the number to the winning numbers vector.
            winningNumbers.push_back(number);
        }

        // Continue the loop to check if our numbers are winning numbers.
        for (; i < words.size(); i++) {
            // Create a variable to store the current word.
            std::string word = words[i];

            // Create a variable to store the current number.
            int number = std::stoi(word);

            // Check if the number is in the winning numbers vector.
            if (std::find(winningNumbers.begin(), winningNumbers.end(), number) != winningNumbers.end()) {
                // If this is the first winning number, set the score to 1, otherwise double the score.
                if (cardScore == 0) {
                    cardScore = 1;
                } else {
                    cardScore *= 2;
                }
            }
        }

        // Add the card score to the total score.
        score += cardScore;
    }

    // Print the score.
    printf("Part 1: %d\n", score);

    // ---------------- Part 2 ----------------
    int totalNumberOfScratchCards = lines.size();

    // Create a map to store the number of winning numbers a card with a certain number has.
    std::map<int, int> winningNumbersPerCard;

    // Loop through each of the lines in the input (backwards to ensure that the cards to be won have already been seen).
    for (int i = lines.size() - 1; i >= 0; i--) {
        std::string line = lines[i];

        std::vector<std::string> words;

        // Split the line on spaces.
        splitOnSpace(line, words);

        // Create a vector to store the winning numbers.
        std::vector<int> winningNumbers;

        int cardScore = 0;

        // Loop through each of the words in the line (start at index 2 to skip the 'Game' and game number).
        int j = 2;
        for (; j < words.size(); j++) {
            if (words[j] == "|") {
                j++;
                break;
            }

            // Create a variable to store the current word.
            std::string word = words[j];

            // Create a variable to store the current number.
            int number = std::stoi(word);

            // Add the number to the winning numbers vector.
            winningNumbers.push_back(number);
        }

        // Continue the loop to check if our numbers are winning numbers.
        for (; j < words.size(); j++) {
            // Create a variable to store the current word.
            std::string word = words[j];

            // Create a variable to store the current number.
            int number = std::stoi(word);

            // Check if the number is in the winning numbers vector.
            if (std::find(winningNumbers.begin(), winningNumbers.end(), number) != winningNumbers.end()) {
                // If this is the first winning number, set the score to 1, otherwise double the score.
                cardScore++;
            }

        }

        // Set the number of winning numbers for this card in the map.
        winningNumbersPerCard[i] = cardScore;

        // Award the winning cards.
        awardWinningCards(i, cardScore, winningNumbersPerCard, totalNumberOfScratchCards);
    }

    printf("Part 2: %d\n", totalNumberOfScratchCards);
}