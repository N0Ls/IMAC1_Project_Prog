#include <iostream>
#include <string>
using namespace std;
#include "infantry.h"
#include "player.h"
#include "bonus.h"
#include "menu.h"
#include "grid.h"
#include "game.h"

#define X_DIMENSION 10
#define Y_DIMENSION 10
#define BONUS_MAX 3

/**
 *
 * Main function.
 *
 */
int main(int argc, char const *argv[])
{
  srand(time(NULL));

  int choice = 0,
      turnChoice = 0,
      moveNumber = 2,
      nbPlayers,
      tabGrid[X_DIMENSION * Y_DIMENSION],
      currentPlayer = 0,
      winner;

  bool isPlaying = false;

  player tabPlayers[10];
  bonus tabBonus[BONUS_MAX];

  menu(&choice);
  switch (choice)
  {
  case 1:
    initGame(tabGrid, tabPlayers, &nbPlayers, &isPlaying, tabBonus);
    while (isPlaying)
    {
      play_tour(&currentPlayer, moveNumber, tabPlayers, nbPlayers, &turnChoice, tabGrid, tabBonus);
      verify_win(tabPlayers, &nbPlayers, &isPlaying, &winner);
    }
    cout << "Fin de la partie.\n" << endl;
    cout << "Le gagnant est le joueur " << winner << " !\n" << endl;
    break;
  case 2:
    cout << "À bientôt !\n" << endl;
    exit(EXIT_FAILURE);
    break;
  }

  return 0;
}
