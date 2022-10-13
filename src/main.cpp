#include <iostream>
#include <experimental/random>

int main()
{
  bool runningMain = true;
  char menu = 'a';
  while (runningMain)
  {
    std::cout << "Welcome to Console Games\nPress 'g' to play the Random Number Guessing Game\nPress 'r' to play the Rock Paper Scissors Game\nPress 'q' to quit the program\n:";
    std::cin >> menu;
    bool running = true;
    // NUMBER GUESSING GAME ------------------------------------------------------
    if (menu == 'g')
    {
      int guess_number = 0;
      bool winCond     = false;
      char retry       = 'y';
      std::cout << "Welcome to the number guessing game. The random number is between 1 and 10\n";
      // creates a loop that is broken when the player successfully guesses the random number
      while (running)
      {
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
          running = false;
        }
      }
    }
    // ROCK PAPER SCISSORS GAME --------------------------------------------------
    else if (menu == 'r')
    {
      // init point tallies for the game
      int USRtally = 0;
      int CPUtally = 0;
      std::cout << "Welcome to the Rock Paper Scissors game\nPlease select:\n'r' for Rock\n'p' for Paper\n's' for Scissors\nOr 'q' for Quit\n";
      // start game loop after so points are kept
      while (running)
      {
        // init user's choice var, default is rock
        char USRraw = 'r';
        // DEBUG CPU CHOICE BELOW
        char CPUraw = 'r';
        // ----------------------
        // init user's mathematical choice var for CPU's choice comparison
        int USR = 0;
        // generate a random number between 1 and 3
        int CPU = std::experimental::randint(1, 3);
        std::cout << "Your Points: " << USRtally
                  << "\nCPU's Points: " << CPUtally << "\n:";
        std::cin >> USRraw;
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
            break;
        }
        // DEBUG CPU CHOICE BELOW
        switch (CPU)
        {
          case 1:
            CPUraw = 'r';
            break;
          case 2:
            CPUraw = 'p';
            break;
          case 3:
            CPUraw = 's';
            break;
          default:
            break;
        }
        // -----------------------
        if (USR == 4)
        {
          std::cout << "You beat the CPU...for good\n";
          running = false;
        }
        else if (CPU == USR)
        {
          std::cout << "It's a tie! Neither of you got points\nCPU Chose: "
                    << CPUraw << "\n";
        }
        /* compares difference between inputs of CPU and USR (user). if greater
         * than 1, it can only mean either rock or paper has been chosen */
        else if ((CPU - USR * 1) > 1)
        {
          /* if CPU's choice is greater than USR, it means that CPU chose rock
           * and USR chose paper. USR wins and gets a point*/
          if (CPU > USR)
          {
            USRtally++;
            std::cout << "You beat the CPU\nCPU Chose: " << CPUraw << "\n";
          }
          // otherwise, CPU chose paper and USR chose rock, CPU wins
          else
          {
            CPUtally++;
            std::cout << "The CPU beat you\nCPU Chose: " << CPUraw << "\n";
          }
        }
        /* now that earlier possibilities have been eliminated, the only options
         * that could have been chosen are now either rock and paper, or paper
         * and scissors. so from this point forward, larger number wins. so that
         * means only either paper beats rock, or rock beats scissors*/
        else if (CPU > USR)
        {
          CPUtally++;
          std::cout << "The CPU beat you\nCPU Chose: " << CPUraw << "\n";
        }
        else if (USR > CPU)
        {
          USRtally++;
          std::cout << "You beat the CPU\nCPU Chose: " << CPUraw << "\n";
        }
        // secret fourth option to leave the game
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