#include <iostream>
#include <string>
using namespace std;

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