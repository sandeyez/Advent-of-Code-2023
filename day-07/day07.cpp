#include "day07.h"
#include "../utils.h"
#include<vector>
#include<string>

// SCORES: High-card (1), One-pair (2), Two-pairs (3), Three-of-a-kind (4), Full-house (5), Four-of-a-kind (6), Five of a kind (7)
struct Hand {
    int bid;
    std::vector<int> cards;
    int score;
};

void getHandScore(std::vector<int> &cards, int &score) {
    std::vector<int> counts(15, 0);

    // Count the occurence of each card.
    for (int i = 0; i < cards.size(); i++) {
        counts[cards[i]]++;
    }

    // Find the card with the highest occurence ands store its index.
    int maxCount = 0;
    int maxCountIndex = 0;

    for (int i = 0; i < counts.size(); i++) {
        if (counts[i] > maxCount) {
            maxCount = counts[i];
            maxCountIndex = i;
        }
    }

    // If the maxCount is 5, the hand is a five-of-a-kind.
    if (maxCount == 5) {
        score = 7;
    }

    // If the maxCount is 4, the hand is a four-of-a-kind.
    else if (maxCount == 4) {
        score = 6;
    }

    // If the maxCount is 3, the hand is either a three-of-a-kind or a full-house.
    else if (maxCount == 3) {
        int secondMaxCount = 0;

        // Get the second highest occurence of a card. Make sure to ignore the card with the highest occurence.
        for (int i = 0; i < counts.size(); i++) {
            if (counts[i] > secondMaxCount && i != maxCountIndex) {
                secondMaxCount = counts[i];
            }
        }

        // If the second highest occurence is 2, the hand is a full-house.
        if (secondMaxCount == 2) {
            score = 5;
        }
        // Otherwise, the hand is a three-of-a-kind.
        else {
            score = 4;
        }
    }
    // If the maxCount is 2, the hand is either a two-pairs or a one-pair.
    else if (maxCount == 2) {
        int secondMaxCount = 0;

        // Get the second highest occurence of a card. Make sure to ignore the card with the highest occurence.
        for (int i = 0; i < counts.size(); i++) {
            if (counts[i] > secondMaxCount && i != maxCountIndex) {
                secondMaxCount = counts[i];
            }
        }

        // If there is another card with an occurence of 2, the hand is a two-pairs.
        if (secondMaxCount == 2) {
            score = 3;
        }

        // Otherwise, the hand is a one-pair.
        else {
            score = 2;
        }
    }
    // If the maxCount is 1, the hand is a high-card.
    else {
        score = 1;
    }
}

void getHandScoreWithJoker(std::vector<int> &cards, int &score) {
    std::vector<int> counts(15, 0);

    // Count the occurence of the jokers separately.
    int amountOfJokers = 0;

    // Count the occurence of each card.
    for (int i = 0; i < cards.size(); i++) {
        // If the card is a joker, ignore it.
        if (cards[i] == -1) {
            amountOfJokers++;
            continue;
        }

        counts[cards[i]]++;
    }


    // Find the card with the highest occurence ands store its index.
    int maxCount = 0;
    int maxCountIndex = 0;

    for (int i = 0; i < counts.size(); i++) {
        if (counts[i] > maxCount) {
            maxCount = counts[i];
            maxCountIndex = i;
        }
    }

    // We use a greedy strategy to always use all the jokers on the card with the highest occurence.
    maxCount += amountOfJokers;

    // If the maxCount is 5, the hand is a five-of-a-kind.
    if (maxCount == 5) {
        score = 7;
    }

        // If the maxCount is 4, the hand is a four-of-a-kind.
    else if (maxCount == 4) {
        score = 6;
    }

        // If the maxCount is 3, the hand is either a three-of-a-kind or a full-house.
    else if (maxCount == 3) {
        int secondMaxCount = 0;

        // Get the second highest occurence of a card. Make sure to ignore the card with the highest occurence.
        for (int i = 0; i < counts.size(); i++) {
            if (counts[i] > secondMaxCount && i != maxCountIndex) {
                if (i < 0) {
                    continue;
                }

                secondMaxCount = counts[i];
            }
        }

        // If the second highest occurence is 2, the hand is a full-house.
        if (secondMaxCount == 2) {
            score = 5;
        }
            // Otherwise, the hand is a three-of-a-kind.
        else {
            score = 4;
        }
    }
        // If the maxCount is 2, the hand is either a two-pairs or a one-pair.
    else if (maxCount == 2) {
        int secondMaxCount = 0;

        // Get the second highest occurence of a card. Make sure to ignore the card with the highest occurence.
        for (int i = 0; i < counts.size(); i++) {
            if (counts[i] > secondMaxCount && i != maxCountIndex) {
                if (i < 0) {
                    continue;
                }
                secondMaxCount = counts[i];
            }
        }

        // If there is another card with an occurence of 2, the hand is a two-pairs.
        if (secondMaxCount == 2) {
            score = 3;
        }

            // Otherwise, the hand is a one-pair.
        else {
            score = 2;
        }
    }
        // If the maxCount is 1, the hand is a high-card.
    else {
        score = 1;
    }
}


void day07(std::vector<std::string> &lines) {
    // ---------------- Part 1 ----------------
    // Initialize a vector to store the hands.
    std::vector<Hand> hands;

    for (auto &line : lines) {
        // Create a hand struct to store the hand.
        Hand hand;

        // Split the line on spaces.
        std::vector<std::string> words;

        splitOnSpace(line, words);

        // Store the bid (the second word) in the hand struct.
        hand.bid = std::stoi(words[1]);

        // For each card in the hand, store its value in the hand struct (converted to int for easier comparison).
        for (int i = 0; i < words[0].size(); i++) {
            char c = words[0][i];

            // Ace maps to 14.
            if (c == 'A') {
                hand.cards.push_back(14);
            }
            // King maps to 13.
            else if (c == 'K') {
                hand.cards.push_back(13);
            }
            // Queen maps to 12.
            else if (c == 'Q') {
                hand.cards.push_back(12);
            }
            // Jack maps to 11.
            else if (c == 'J') {
                hand.cards.push_back(11);
            }
            // Ten maps to 10.
            else if (c == 'T') {
                hand.cards.push_back(10);
            }
            // Otherwise, the card is a number between 2 and 9.
            else {
                hand.cards.push_back(c - '0');
            }
        }

        getHandScore(hand.cards, hand.score);

        // If the hands vector is empty, we can just add the hand.
        if (hands.empty()) {
            hands.push_back(hand);
            continue;
        }

        bool inserted = false;

        // Compare this hand to each of the previous ones. We first compare the score,
        // if those are equal we compare the cards from index 0 to 4. The first time we
        // find a hand that is worse than the current one, we insert the current hand.
        for (int i = 0; i < hands.size() && !inserted; i++) {
            if (hand.score > hands[i].score) {
                hands.insert(hands.begin() + i, hand);
                inserted = true;
                break;
            }
            else if (hand.score == hands[i].score) {
                for (int j = 0; j < 5; j++) {
                    if (hand.cards[j] > hands[i].cards[j]) {
                        hands.insert(hands.begin() + i, hand);
                        inserted = true;
                        break;
                    }
                    else if (hand.cards[j] < hands[i].cards[j]) {
                        break;
                    }
                }
            }
        }

        // If the hand was not inserted, we can just add it to the end of the vector.
        if (!inserted) {
            hands.push_back(hand);
        }
    }

    int sum = 0;

    // Loop through each of the hands and multiply their bid with their index + 1.
    for (int i = 0; i < hands.size(); i++) {
        sum += hands[i].bid * (hands.size() - i);
    }

    printf("Part 1: %d\n", sum);

    // ---------------- Part 2 ----------------
    // Initialize a vector to store the hands.
    hands.clear();

    for (auto &line : lines) {
        // Create a hand struct to store the hand.
        Hand hand;

        // Split the line on spaces.
        std::vector<std::string> words;

        splitOnSpace(line, words);

        // Store the bid (the second word) in the hand struct.
        hand.bid = std::stoi(words[1]);

        // For each card in the hand, store its value in the hand struct (converted to int for easier comparison).
        for (int i = 0; i < words[0].size(); i++) {
            char c = words[0][i];

            // Ace maps to 14.
            if (c == 'A') {
                hand.cards.push_back(14);
            }
            // King maps to 13.
            else if (c == 'K') {
                hand.cards.push_back(13);
            }
            // Queen maps to 12.
            else if (c == 'Q') {
                hand.cards.push_back(12);
            }
            // The joker maps to -1.
            else if (c == 'J') {
                hand.cards.push_back(-1);
            }
            // Ten maps to 10.
            else if (c == 'T') {
                hand.cards.push_back(10);
            }
            // Otherwise, the card is a number between 2 and 9.
            else {
                hand.cards.push_back(c - '0');
            }
        }

        getHandScoreWithJoker(hand.cards, hand.score);

        bool inserted = false;

        // Compare this hand to each of the previous ones. We first compare the score,
        // if those are equal we compare the cards from index 0 to 4. The first time we
        // find a hand that is worse than the current one, we insert the current hand.
        for (int i = 0; i < hands.size() && !inserted; i++) {
            if (hand.score > hands[i].score) {
                hands.insert(hands.begin() + i, hand);
                inserted = true;
                break;
            }
            else if (hand.score == hands[i].score) {
                for (int j = 0; j < 5; j++) {
                    if (hand.cards[j] > hands[i].cards[j]) {
                        hands.insert(hands.begin() + i, hand);
                        inserted = true;
                        break;
                    }
                    else if (hand.cards[j] < hands[i].cards[j]) {
                        break;
                    }
                }
            }
        }

        // If the hand was not inserted, we can just add it to the end of the vector.
        if (!inserted) {
            hands.push_back(hand);
        }
    }

    sum = 0;

    // Loop through each of the hands and multiply their bid with their index + 1.
    for (int i = 0; i < hands.size(); i++) {
        sum += hands[i].bid * (hands.size() - i);
    }

    printf("Part 2: %d\n", sum);
}
