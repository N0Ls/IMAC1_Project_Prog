#include <iostream>
#include <string>
using namespace std;
#include "infantry.h"
#include "player.h"
#define X_DIMENSION 10
#define Y_DIMENSION 10

/**
 *
 * Display the logo.
 *
 */
void printLogo(void)
{
  cout << "=========================================\n";
  cout << " ██╗███╗   ███╗ █████╗  ██████╗\n";
  cout << " ██║████╗ ████║██╔══██╗██╔════╝\n";
  cout << " ██║██╔████╔██║███████║██║\n";
  cout << " ██║██║╚██╔╝██║██╔══██║██║\n";
  cout << " ██║██║ ╚═╝ ██║██║  ██║╚██████╗\n";
  cout << " ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝ ╚═════╝\n\n";
  cout << "      ██╗    ██╗ █████╗ ██████╗ ███████╗\n";
  cout << "      ██║    ██║██╔══██╗██╔══██╗██╔════╝\n";
  cout << "      ██║ █╗ ██║███████║██████╔╝███████╗\n";
  cout << "      ██║███╗██║██╔══██║██╔══██╗╚════██║\n";
  cout << "      ╚███╔███╔╝██║  ██║██║  ██║███████║\n";
  cout << "       ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝\n";
  cout << "=========================================\n\n";
}

/**
 *
 * Display the menu.
 *
 * @param choice The choice made by the player.
 *
 */
void menu(int *choice)
{
  cout << "\n";
  printLogo();
  cout << "1. Commencer une partie"
       << "\n";
  cout << "2. Quitter la partie"
       << "\n\n";
  cout << "Votre choix (1/2 ?) : ";
  cin >> *choice;
  cout << endl;
}

/**
 *
 * Display the turn menu.
 *
 * @param turnChoice The choice made by the player.
 *
 */
void turnMenu(int *turnChoice)
{
  cout << "\n";
  cout << "1. Se déplacer"
       << "\n";
  cout << "2. Attaquer"
       << "\n\n";
  cout << "Votre choix (1/2 ?) : ";
  cin >> *turnChoice;
  while (1)
  {
    if (cin.fail() || *turnChoice > 2 || *turnChoice < 1)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << "Vous ne pouvez que vous déplacez (1) ou attaquer (2)." << endl;
      cout << "Votre choix (1/2 ?) : ";
      cin >> *turnChoice;
    }
    if (!(cin.fail() || *turnChoice > 2 || *turnChoice < 1))
      break;
  }
  cout << endl;
}

/**
 *
 * Display the map.
 *
 * @param tabGrid The map.
 *
 */
void drawGrid(int tabGrid[])
{
  cout << "      X| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |" << endl;
  cout << "    Y  _________________________________________" << endl;
  for (int i = 0; i < X_DIMENSION; i++)
  {
    cout << "|   " << i << "  |";
    for (int y = 0; y < Y_DIMENSION; y++)
    {

      if (tabGrid[X_DIMENSION * i + y] == 1)
      {
        cout << "\033[96m";
        cout << " 1";
        cout << "\033[39m";
        cout << " |";
      }
      if (tabGrid[X_DIMENSION * i + y] == 2)
      {
        cout << "\033[91m";
        cout << " 2";
        cout << "\033[39m";
        cout << " |";
      }
      if (tabGrid[X_DIMENSION * i + y] == 3)
      {
        cout << "\033[93m";
        cout << " 3";
        cout << "\033[39m";
        cout << " |";
      }
      if (tabGrid[X_DIMENSION * i + y] == -1)
      {
        cout << "\033[35m";
        cout << " ♥";
        cout << "\033[39m";
        cout << " |";
      }
      if (tabGrid[X_DIMENSION * i + y] == 0)
      {
        cout << "   |";
      }
    }
    cout << endl;
    cout << "       _________________________________________" << endl;
  }
}
