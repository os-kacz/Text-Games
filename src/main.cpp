#include <iostream>
#include <experimental/random>

int numgame()
{
  int guess_number = 0;
  bool winCond     = false;
  char retry       = 'y';
  // assigns a random number 1-10 to target_number
  // this is done in the while loop so a new number is generated per game instance
  int target_number = std::experimental::randint(1, 10);
  // sets maximum guesses which is 5, and while you have guesses it loops. every loop removes a guess
  for (int guess = 5; guess > 0; guess--)
  {
    std::cout << "Guesses Left: " << guess
              << "\nGuess the random number:";
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
    else if (target_number < guess_number)
    {
      std::cout << "Nope, your guess was too high.\n";
    }
    // if the player guessed too low
    else if (target_number > guess_number)
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
    std::cout << "You've run out of guesses! The number was "
              << target_number << ", Game Over!\nPlay again? (y/n):";
  }
  std::cin >> retry;
  // ends game if 'n'. otherwise, the loop restarts
  if (retry == 'n')
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int rpsgame(char USRraw)
{
    // init user's mathematical choice var for CPU's choice comparison
    int USR = 0;
    // generate a random number between 1 and 3
    int CPU = std::experimental::randint(1, 3);
    // convert alphabetical value into numerical value for maths calculations
    switch (USRraw)
    {
      case 'r':
        USR = 1;
        break;
      case 'p':
        USR = 2;
        break;
      case 's':
        USR = 3;
        break;
      case 'q':
        USR = 4;
        break;
      default:
        std::cout << "invalid input";
        break;
    }
    // option to leave the game
    if (USR == 4)
    {
      std::cout << "You beat the CPU...for good\n";
      return 2;
    }
    // tie between user and cpu
    else if (CPU == USR)
    {
      std::cout << "It's a tie! Neither of you got points\n";
      return 0;
    }
    /* compares difference between inputs of CPU and USR (user). if greater
     * than 1, it can only mean either rock or paper has been chosen */
    else if ((CPU - USR * 1) > 1)
    {
      /* if CPU's choice is greater than USR, it means that CPU chose rock
       * and USR chose paper. USR wins and gets a point*/
      if (CPU > USR)
      {
        std::cout << "You beat the CPU\n";
        return 1;
      }
      // otherwise, CPU chose paper and USR chose rock, CPU wins
      else
      {
        std::cout << "The CPU beat you\n";
        return -1;
      }
    }
    /* now that earlier possibilities have been eliminated, the only options
         * that could have been chosen are now either rock and paper, or paper
         * and scissors. so from this point forward, larger number wins. so that
         * means only either paper beats rock, or rock beats scissors*/
    else if (CPU > USR)
    {
      std::cout << "The CPU beat you\n";
      return -1;
    }
    else if (USR > CPU)
    {
      std::cout << "You beat the CPU\n";
      return 1;
    }
    // if nothing else, return 3
    return 3;
}

int main()
{
  bool runningMain = true;
  char menu = 'a';
  while (runningMain)
  {
    bool runningInstance = true;
    std::cout << "Welcome to Console Games\nPress 'g' to play the Random Number Guessing Game\nPress 'r' to play the Rock Paper Scissors Game\nPress 'q' to quit the program\n:";
    std::cin >> menu;

    // NUMBER GUESSING GAME ----------------------------------------------------
    if (menu == 'g')
    {
      std::cout << "Welcome to the number guessing game. The random number is between 1 and 10\n";
      // creates a loop that is broken when the player successfully guesses the random number
      while (runningInstance)
      {
        // runs the random number game. if func returns 0, quit the game. anything else, continue
        if (numgame() == 0)
        {
          runningInstance = false;
        }
      }
    }

    // ROCK PAPER SCISSORS GAME ------------------------------------------------
    else if (menu == 'r')
    {
      // init point tallies for the game
      int USRtally = 0;
      int CPUtally = 0;
      char usrinput = 'r';
      std::cout << "Welcome to the Rock Paper Scissors game\nPlease select:\n'r' for Rock\n'p' for Paper\n's' for Scissors\nOr 'q' for Quit\n";
      // start game loop after so points are kept
      while (runningInstance)
      {
        std::cin >> usrinput;
        int rpsState = rpsgame(usrinput);
        switch (rpsState)
        {
          case -1:
            CPUtally += 1;
            break;
          case 0:
            break;
          case 1:
            USRtally += 1;
            break;
          case 2:
            std::cout << "The final scores are:\nYou: " << USRtally << "\nCPU: " << CPUtally << std::endl;
            runningInstance = false;
            break;
          default:
            std::cout << "No valid output detected";
            break;
        }
      }
    }
    // QUIT PROGRAM ------------------------------------------------------------
    else
    {
      std::cout << "Exiting program";
      runningMain = false;
    }
  }
  return 0;
}