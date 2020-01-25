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
 * Initialize the map.
 *
 * @param tabGrid The map.
 *
 */
void initGrid(int *tabGrid)
{
  for (int i = 0; i < X_DIMENSION; i++)
  {
    for (int y = 0; y < Y_DIMENSION; y++)
    {
      tabGrid[X_DIMENSION * i + y] = 0;
    }
  }
}

/**
 *
 * Update the map (to use after every unit placement).
 *
 * @param tabGrid The map.
 * @param nbPlayers The number of players currently playing.
 * @param tabPlayers The players currently playing.
 * @param tabBonus Bonuses.
 *
 */
void updateGrid(int *tabGrid, int nbPlayers, player tabPlayers[], bonus *tabBonus)
{
  for (int i = 0; i < X_DIMENSION; i++)
  {
    for (int y = 0; y < Y_DIMENSION; y++)
    {
      tabGrid[X_DIMENSION * i + y] = 0;
    }
  }

  for (int k = 0; k < nbPlayers; k++)
  {
    for (int i = 0; i < tabPlayers[k].nbActiveUnits; i++)
    {
      if (tabPlayers[k].infantriesList[i].isAlive == 1)
      {
        tabGrid[tabPlayers[k].infantriesList[i].y * X_DIMENSION + tabPlayers[k].infantriesList[i].x] = tabPlayers[k].id;
      }
    }
  }

  probBonusArray(tabBonus, tabGrid);
  for (int v = 0; v < BONUS_MAX; v++)
  {
    if (tabBonus[v].isActive == true)
    {
      tabGrid[tabBonus[v].y * X_DIMENSION + tabBonus[v].x] = -1;
    }
  }
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
