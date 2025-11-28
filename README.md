# Bagels
A deductive logic game where you try to guess a secret 3-digit number based on clever clues.

## Game Rules
The game generates a secret 3-digit number with no repeated digits. You have 10 attempts to guess it. After each guess, you'll receive one of three clues:

* Pico - One digit is correct but in the wrong position
* Fermi - One digit is correct and in the right position
* Bagels - No digits are correct

For example, if the secret number is 248 and you guess 843, you'd get "Fermi Pico" because:

4 is correct and in right position (Fermi)

8 is correct but in wrong position (Pico)

## Usage example
```cpp
#include <iostream>
#include "bagels.h"

int main() {
    BagelsGame game;

    std::cout << "=== BAGELS GAME ===\n";
    game.displayInstructions();
    game.playGame();

    return 0;
}
```
