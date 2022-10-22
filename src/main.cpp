#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

// TESTING FILE READING, IGNORE
int readFile()
{
  std::ifstream inFile("C://Users//semis//OneDrive - UWE Bristol//cplusplus//console-games-22-23-os-kacz/RPS.txt");
  if (inFile.is_open())
  {
    int choice[10];
    for (int & j : choice)
    {
      inFile >> j;
      std::cout << j << std::endl;
    }
    inFile.close();
  }
  else
  {
    std::cout << "Could not read file";
  }
  return 0;
}

int numGame()
{
  int guess_number = 0;
  bool winCond     = false;
  char retry       = 'y';
  // assigns a random number 1-10 to target_number
  // this is done in the while loop so a new number is generated per game instance
  int target_number = std::rand() % 10 + 1;
  std::cout << target_number;
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

int rpsGame(int CPU, int x, int y)
{
  // init user's mathematical choice var for CPU's choice comparison
  int USR = 0;
  // convert alphabetical value into numerical value for maths calculations
  char USRraw = 'r';
  std::cout << "\nDifficulty: " << x << "/10\nYour Choice:";
  std::cin >> USRraw;
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
  int diffi = std::rand() % (11 - x) + 1;
  if (diffi == 1 && y > 1 && USR != 4)
  {
    std::cout << "The CPU beat you\n";
    return -1;
  }
  else
  {
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
}

int main()
{
  // using time_t() because time() did not generate desired random numbers
  std::srand(std::time_t());
  bool runningMain = true;
  char menu = 'a';
  while (runningMain)
  {
    // MAIN MENU ---------------------------------------------------------------
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
        if (numGame() == 0)
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
      // init difficulty-related factors
      int wstreak = 0;
      int lstreak = 0;
      std::cout << "Welcome to the Rock Paper Scissors game\nPlease select:\n'r' for Rock\n'p' for Paper\n's' for Scissors\nOr 'q' for Quit\n";
      // start game loop after so points are kept
      while (runningInstance)
      {
        /* generate a random number between 1 and 3 and put that into the rpsGame
         * function. this runs the game, takes in the CPU's choice as a condition,
         * then will return an int value*/
        if (lstreak > 5)
        {
          wstreak -= std::rand() % (lstreak - 2) + 1;
          std::cout << "Loser! Difficulty decreased\n";
          lstreak = 0;
        }
        int rpsState = rpsGame(std::rand() % 3 + 1, wstreak, lstreak);
        // the returned int is put into cases to find who won during the game
        switch (rpsState)
        {
          case -1: // CPU wins, gains a point
            CPUtally++;
            lstreak++;
            break;
          case 0: // no one wins, it's a tie. no points are awarded
            break;
          case 1: // user wins, gains a point
            USRtally++;
            wstreak++;
            break;
          case 2: // user quits the game. outputs score then breaks loop
            std::cout << "The final scores are:\nYou: " << USRtally << "\nCPU: " << CPUtally << std::endl;
            runningInstance = false;
            break;
          default:
            std::cout << "No valid output detected";
            break;
        }
      }
    }
    // TESTING FILE READING, IGNORE
    else if (menu == 'f')
    {
      readFile();
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