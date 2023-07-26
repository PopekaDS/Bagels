#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

int NUM_DIGITS = 3;
int MAX_GUESSES = 10;

string getSecretNum() {
    // Returns a string made up of NUM_DIGITS unique random digits.
    string secretNum = "";
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < NUM_DIGITS; ++i) {
        int randomNumber = rand();
        int secretRandomNumber = randomNumber % 10; // [0; 9]
        secretNum += to_string(secretRandomNumber);
    }

    return secretNum;
}

bool isdecimal(string check) {
    for (char c : check) {
        if (c < '0' || c > '9') {
            return false;
        }
    }

    return true;
}

string getClues(string guess, string secretNum) {
    // Returns a string with the pico, fermi, bagels clues for a guess
    // and secret number pair.
    if (guess == secretNum) {
        return "You got it!";
    }

    vector <string> clues;
    for (size_t i = 0; i < guess.size(); i++) {
        if (guess[i] == secretNum[i]) {
            // A correct digit is in the correct place.
            clues.push_back("Fermi");
        } else {
            // A correct digit is in the incorrect place.
            for (char c : secretNum) {
                if (guess[i] == c) {
                    clues.push_back("Pico");
                }
            }
        }
    }

    if (clues.size() == 0) {
        return "Bagels"; // There are no correct digits at all.
    } else {
        // Sort the clues into alphabetical order so their original order
        // doesn't give information away.
        sort(clues.begin(), clues.end());
        // Make a single string from the list of string clues.
        string out = "";
        for (size_t i = 0; i < clues.size(); i++) {
            out += clues[i];
            out += " ";
        }
        return out;
    }
}

string playAgain() {
    cout << "Do you want to play again? (yes or no)\n";
    string response = "YES";
    cin >> ws;
    getline(cin, response);
    return response;
}

int main() {

    cout << "Bagels, a deductive logic game.\n\n";
    cout << "I am thinking of a " << NUM_DIGITS << "-digit number with no repeated digits.\n";
    cout << "Try to guess what it is. Here are some clues:\n";
    cout << "When I say:    That means:\n";
    cout << "  Pico         One digit is correct but in the wrong position.\n";
    cout << "  Fermi        One digit is correct and in the right position.\n";
    cout << "  Bagels       No digit is correct.\n";
    cout << "For example, if the secret number was 248 and your guess was 843, the\n";
    cout << "clues would be Fermi Pico.\n";
    while (true) { // Main game loop.
        // This stores the secret number the player needs to guess:
        string secretNum = getSecretNum();
        
        cout << "\n\n\n\nDELETED IT\n"<< "NUM_DIGITS = " << NUM_DIGITS << "\nsecretNum = " << secretNum << "\nDELETED IT\n\n\n\n";
        cout << "I have thought up a number.\n";
        cout << "You have " << MAX_GUESSES << " guesses to get it.\n";

        int numGuesses = 1;
        while (numGuesses <= MAX_GUESSES) {
            string guess = "";
            // Keep looping until they enter a valid guess:
            while (guess.size() != NUM_DIGITS || !(isdecimal(guess))) {
                cout << "Guess #" << numGuesses;
                cout << "\n> ";
                cin >> guess;
            }
            string clues = getClues(guess, secretNum);
            cout << clues << '\n';
            numGuesses++;

            if (guess == secretNum) {
                break; // They're correct, so break out of this loop.
            }
            if (numGuesses > MAX_GUESSES) {
                cout << "You ran out of guesses.\n";
                cout << "The answer was " << secretNum << '\n';
            }
        }
        // Ask player if they want to play again.
        string askPlayAgain = "YES";
        askPlayAgain = playAgain();
        transform(askPlayAgain.begin(), askPlayAgain.end(), askPlayAgain.begin(), ::toupper);

        if (!(askPlayAgain == "YES" || askPlayAgain == "Y")) {
            break;
        }
        
    }
    cout << "Thanks for playing!\n";

    return 0;
}

/*
    Изменить секретное число, чтобы в нем  не было повторяющих чисел
*/
