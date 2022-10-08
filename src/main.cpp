#include <iostream>
#include <experimental/random>
/* PSEUDO
 * 1. Generate a random number between 1-10
 * 2. Create a main instance loop
 * 3. Generate random number between 1-10
 * 4. Create guessing instance loop with 5 guesses. If no more guesses left, go to 9
 * 5. Ask for user input
 * 6. If lower than random, remove one guess and loop back to 5
 * 7. If higher than random, remove one guess and loop back to 5
 * 8. If guessed correctly, end the guessing instance loop, go to 10
 * 9. No more guesses left, end the guessing instance loop
 * 10. Prompt player with game restart
 * 11. If yes, go to 1
 * 12. If no, end main instance loop and program
 */
int main()
{
  int guess_number = 0;
  bool running = true;
  bool winCond = false;
  char retry = 'y';
  std::cout << "Welcome to the number guessing game. The random number is between 1 and 10\n";
  // creates a loop that is broken when the player successfully guesses the random number
  while (running)
  {
    // assigns a random number 1-10 to target_number
    // this is done in the while loop so a new number is generated per game instance
    int target_number = std::experimental::randint(1, 10);
    for (int guess = 5; guess > 0; guess--)
    {
      std::cout << "Guesses Left: " << guess << "\nGuess the random number:";
      std::cin >> guess_number;
      // if the player guesses the random number
      if (target_number == guess_number)
      {
        std::cout << "You guessed correct!";
        // guess is set to '0' to break the for loop and let the player win
        guess = 0;
        // win condition differentiates program endgame text since either win or loss results in 0 guesses
        winCond = true;
      }
      // if the player guessed too high
      if (target_number < guess_number)
      {
        std::cout << "Nope, your guess was too high.\n";
      }
      // if the player guessed too low
      if (target_number > guess_number)
      {
        std::cout << "Nope, your guess was too low.\n";
      }
    }
    // when win condition is true, display win endgame text
    if (winCond)
    {
      // win condition is set back to false in the event of the loop restarting
      winCond = false;
      std::cout << " You won!\nPlay again? (y/n):";
    }
    // when win condition is false, display game over endgame text
    else
    {
      std::cout << "You've run out of guesses! The number was " << target_number
                << ", Game Over!\nPlay again? (y/n):";
    }
    std::cin >> retry;
    // ends game if 'n'. otherwise, the loop restarts
    if (retry == 'n')
    {
        running = false;
    }
  }
  return 0;
}