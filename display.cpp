#include <iostream>
#include <string>
using namespace std;
#include "infantry.h"
#include "player.h"
#define X_DIMENSION 10
#define Y_DIMENSION 10

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

void menu(int *c)
{
  cout << "\n";
  printLogo();
  cout << "1. Commencer une partie"
       << "\n";
  cout << "2. Quitter la partie"
       << "\n\n";
  cout << "Votre choix (1/2 ?) : ";
  cin >> *c;
  cout << endl;
}

void menu_tour(int *tour_choice)
{
  cout << "\n";
  cout << "1. Se déplacer"
       << "\n";
  cout << "2. Attaquer"
       << "\n\n";
  cout << "Votre choix (1/2 ?) : ";
  cin >> *tour_choice;
  while (1)
  {
    if (cin.fail() || *tour_choice > 2 || *tour_choice < 1)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << "Vous ne pouvez que vous déplacez (1) ou attaquer (2)." << endl;
      cout << "Votre choix (1/2 ?) : ";
      cin >> *tour_choice;
    }
    if (!(cin.fail() || *tour_choice > 2 || *tour_choice < 1))
      break;
  }
  cout << endl;
}

//Fonction d'affichage de la grille
//Pour l'instant elle est de taille fixe
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
        cout << "\033[37m";
        cout << " |";
      }
      if (tabGrid[X_DIMENSION * i + y] == 2)
      {
        cout << "\033[91m";
        cout << " 2";
        cout << "\033[37m";
        cout << " |";
      }
      if (tabGrid[X_DIMENSION * i + y] == 3)
      {
        cout << "\033[35m";
        cout << " 3";
        cout << "\033[37m";
        cout << " |";
      }
      if (tabGrid[X_DIMENSION * i + y] == -1)
      {
        cout << "\033[35m";
        cout << " ♥";
        cout << "\033[37m";
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
