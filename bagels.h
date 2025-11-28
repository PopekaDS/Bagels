#ifndef BAGELS_H
#define BAGELS_H

#include <string>

class BagelsGame {
private:
    int NUM_DIGITS;
    int MAX_GUESSES;
    std::string secretNum; // Returns a string made up of NUM_DIGITS unique random digits.

    std::string generateSecretNumber();
    bool isDecimal(const std::string& check) const;
    std::string getClues(const std::string& guess) const;

public:
    BagelsGame(int guesses = 10);

    void displayInstructions() const;
    void playGame();
    bool playAgain() const;
};

#endif