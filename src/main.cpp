#include <iostream>
#include <experimental/random>
/* PSEUDO
 * 1. Generate a random number between 1-10
 * 2. Ask the user to guess a number between 1-10
 * 3. If the guess matches the random number, display "congratulations"
 * 4. If the guess doesn't match the random number, display "game over"
 * 5. End program
 */
int main()
{

  int guess_number = 0;

  // assigns a random number 1-10 to target_number
  int target_number = std::experimental::randint(1,10);
  std::cout << "Guess the random number:";

  std::cin >> guess_number;

  // if the player guesses the random number
  if (target_number == guess_number){
    std::cout << "You guessed correct!";
  }
  // if the player guessed too high
  if (target_number < guess_number){
    std::cout << "Nope, your guess was too high.";
  }
  // if the player guessed too low
  else {
    std::cout << "Nope, your guess was too low.";
  }

  return 0;
}
