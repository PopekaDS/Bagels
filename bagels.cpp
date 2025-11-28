// Original: The Big Book of Small Python Projects: 81 Easy Practice Programs by Al Sweigart
// #1 BAGELS
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include "bagels.h"

using namespace std;

BagelsGame::BagelsGame(int guesses) {
    NUM_DIGITS = 3;
    MAX_GUESSES = guesses;
}

string BagelsGame::generateSecretNumber() {
    int fNum = -1, sNum = -1, tNum = -1;

    while ((fNum == sNum) || (sNum == tNum) || (fNum == tNum)) {
        int randomNumber = rand();
        fNum = randomNumber % 10;
        randomNumber = rand();
        sNum = randomNumber % 10;
        randomNumber = rand();
        tNum = randomNumber % 10;
    }
    secretNum = to_string(fNum) + to_string(sNum) + to_string(tNum);

    return secretNum;
}

bool BagelsGame::isDecimal(const string& check) const {
    if (check.size() != NUM_DIGITS) {
        return false;
    }

    for (char c : check) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

string BagelsGame::getClues(const string& guess) const {
    // Returns a string with the pico, fermi, bagels clues for a guess
    // and secret number pair.
    if (guess == secretNum) {
        return "You got it!";
    }

    vector<string> clues;
    for (size_t i = 0; i < guess.size(); i++) {
        if (guess[i] == secretNum[i]) {
            // A correct digit is in the correct place
            clues.push_back("Fermi");
        }
        else {
            // A correct digit is in the incorrect place
            for (char c : secretNum) {
                if (guess[i] == c) {
                    clues.push_back("Pico");
                }
            }
        }
    }

    if (clues.empty()) {
        return "Bagels"; // There are no correct digits at all
    }
    else {
        // Sort the clues into alphabetical order so their original order
        // doesn't give information away
        sort(clues.begin(), clues.end());
        // Make a single string from the list of string clues
        string out = "";
        for (size_t i = 0; i < clues.size(); i++) {
            out += clues[i];
            if (i < clues.size() - 1) {
                out += " ";
            }
        }
        return out;
    }
}

void BagelsGame::displayInstructions() const {
    cout << "Bagels, a deductive logic game.\n\n";
    cout << "I am thinking of a " << NUM_DIGITS << "-digit number with no repeated digits.\n";
    cout << "Try to guess what it is. Here are some clues:\n";
    cout << "When I say:    That means:\n";
    cout << "  Pico         One digit is correct but in the wrong position.\n";
    cout << "  Fermi        One digit is correct and in the right position.\n";
    cout << "  Bagels       No digit is correct.\n";
    cout << "For example, if the secret number was 248 and your guess was 843, the\n";
    cout << "clues would be Fermi Pico.\n\n";
}

// Main game loop
void BagelsGame::playGame() {
    while (true) {
        srand(static_cast<unsigned int>(time(0)));
        // This stores the secret number the player needs to guess:
        secretNum = generateSecretNumber();

        int numGuesses = 1;
        while (numGuesses <= MAX_GUESSES) {
            string guess = "";

            // Keep looping until they enter a valid guess:
            while (!isDecimal(guess)) {
                cout << "Guess #" << numGuesses;
                cout << "\n> ";
                cin >> guess;

                if (!isDecimal(guess)) {
                    cout << "Please enter a " << NUM_DIGITS << "-digit number with no repeated digits.\n";
                }
            }

            string clues = getClues(guess);
            cout << clues << '\n';

            if (guess == secretNum) {
                cout << "Congratulations! You guessed the number in " << numGuesses << " tries!\n";
                // They're correct, so break out of this loop.
                break;
            }

            numGuesses++;

            if (numGuesses > MAX_GUESSES) {
                cout << "You ran out of guesses.\n";
                cout << "The answer was " << secretNum << '\n';
            }
        }

        // Ask player if they want to play again.
        if (!playAgain()) {
            break;
        }
    }

    cout << "Thanks for playing!\n";
}

bool BagelsGame::playAgain() const {
    cout << "Do you want to play again? (yes or no)\n";
    string response = "";
    cin >> ws;
    getline(cin, response);
    transform(response.begin(), response.end(), response.begin(), ::toupper);

    return (response == "YES" || response == "Y");
}