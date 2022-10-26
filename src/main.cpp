#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

// init global vars so values can be kept outside function loop
char choiceHistory[3];
int choiceIter = -1;

// TESTING FILE READING, IGNORE
int readFile()
{
  std::ifstream inFile("C://Users//o2-kaczmarski//OneDrive - UWE Bristol//cplusplus//console-games-22-23-os-kacz/RPS.txt");
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

bool numGame()
{
  int guess_number = 0;
  bool winCond = false;
  char retry = 'y';
  // assigns a random number 1-10 to target_number
  // this is done in the while loop so a new number is generated per game instance
  int target_number = std::rand() % 10 + 1;
  // sets maximum guesses which is 5, and while you have guesses it loops. every loop removes a guess
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
    return true;
  }
  else
  {
    return false;
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
      USR = 5;
      break;
    default:
      std::cout << "invalid input";
      break;
  }
  // keeps rps choice iteration between 0 and 2
  choiceIter++;
  if (choiceIter > 2)
  {
    choiceIter = 0;
  }
  // assign user rps choice to respective position in choice history
  choiceHistory[choiceIter] = USRraw;
  /* for every time the player wins, there is an incremental increase of 10% to
   * the chance of the cpu deciding to beat the player regardless of input.
   * a random number is generated from how many times the player won - 10 to get
   * the 10% chance. e.g. if the player has won 10 times, there is a 100% chance*/
  int diffi = std::rand() % (11 - x) + 1;
  // if it hits the chance, and the difficulty is more than 0, and if the user hasn't selected quit
  if (diffi == 1 && y > 0 && USR != 5)
  {
    std::cout << "The CPU beat you!\n"; // "!" punctuation signifies cpu cheating
    return -1;
  }
  // if the last 3 choices are the same, beat the player
  else if (choiceHistory[0] == choiceHistory[1] && choiceHistory[1] == choiceHistory[2])
  {
    std::cout << "The CPU beat you?\n"; // "?" punctuation signifies user choosing same input 3 times
    return -1;
  }
  else
  {
    // option to leave the game
    if (USR == 5)
    {
      std::cout << "You beat the CPU...for good.\n";
      return 2;
    }
    // tie between user and cpu
    else if (CPU == USR)
    {
      std::cout << "It's a tie! Neither of you got points.\n"; // "." punctuation signifies regular gameplay
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
        std::cout << "You beat the CPU.";
        return 1;
      }
      // otherwise, CPU chose paper and USR chose rock, CPU wins
      else
      {
        std::cout << "The CPU beat you.\n";
        return -1;
      }
    }
    /* now that earlier possibilities have been eliminated, the only options
       * that could have been chosen are now either rock and paper, or paper
       * and scissors. so from this point forward, larger number wins. so that
       * means only either paper beats rock, or rock beats scissors*/
    else if (CPU > USR)
    {
      std::cout << "The CPU beat you.\n";
      return -1;
    }
    else if (USR > CPU)
    {
      std::cout << "You beat the CPU.";
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
        // runs the random number game. if func returns true, quit the game. anything else, continue
        if (numGame())
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
        if (lstreak > 5 || wstreak > 10)
        {
          // reduce the win streak to reduce difficulty so player can score. decrements randomly between lstreak value minus 2 and 1.
          wstreak -= std::rand() % (lstreak - 2) + 1;
          std::cout << "Loser! Difficulty decreased\n";
          // then reset lost streak as difficulty has been tweaked
          lstreak = 0;
        }
        /* generate a random number between 1 and 3 and put that into the rpsGame
         * function. this runs the game, takes in the CPU's choice as a condition,
         * then will return an int value. takes in the difficulty-related vars
         * to change how difficult the cpu is */
        int rpsState = rpsGame(std::rand() % 3 + 1, wstreak, lstreak);
        // the returned int is put into cases to find who won during the game
        switch (rpsState)
        {
          case -1: // CPU wins, gains a point and contributes to decreasing difficulty
            CPUtally++;
            lstreak++;
            break;
          case 0: // it's a tie. no points are awarded
            break;
          case 1: // user wins, gains a point, difficulty is increased
            if (wstreak > 6) // if the difficulty is 8 or more, give more points
            {
              USRtally += wstreak - 6;
              std::cout << " (extra points!)\n";
            }
            else
            {
              USRtally++;
              std::cout << "\n";
            }
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