#include <iostream>
#include <string>
using namespace std;
#include "infantry.h"
#include "player.h"
#include "bonus.h"
#include "menu.h"
#include "grid.h"
#include "game.h"

/**
 *
 * Initialize the game.
 *
 * @param tabGrid The map.
 * @param tabPlayers The players currently playing.
 * @param nbPlayers The number of players currently playing.
 * @param playingCondition Tell if the game is in progress or not.
 * @param bonusArray Bonuses.
 *
 */
void initGame(int *tabGrid, player *tabPlayers, int *nbPlayers, bool *playingCondition, bonus *bonusArray)
{
  cout << "Entrez le nombre de joueurs (2 minimum et 3 maximum) : ";
  cin >> *nbPlayers;
  while (1)
  {
    if (cin.fail() || *nbPlayers < 2 || *nbPlayers > 3)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << "Vous ne pouvez pas joueur seul et le nombre maximum de joueurs autorisé est 3." << endl;
      cout << "Entrez le nombre de joueurs (2 minimum et 3 maximum) : ";
      cin >> *nbPlayers;
    }
    if (!(cin.fail() || *nbPlayers < 2 || *nbPlayers > 3))
      break;
  }

  int nbUnites, maxUnites = 0;
  if (*nbPlayers == 2)
  {
    maxUnites = 9;
  }
  else if (*nbPlayers == 3)
  {
    maxUnites = 6;
  }
  cout << "Entrez le nombre d'unités par joueur (" << maxUnites << " unités maximum) : ";
  cin >> nbUnites;
  while (1)
  {
    if (cin.fail() || nbUnites < 1 || nbUnites > maxUnites)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << "Veuillez respecter le nombre maximal d'unités autorisé par joueur." << endl;
      cout << "Entrez le nombre d'unités par joueur (" << maxUnites << " unités maximum) : ";
      cin >> nbUnites;
    }
    if (!(cin.fail() || nbUnites < 1 || nbUnites > maxUnites))
      break;
  }

  initGrid(tabGrid);

  for (int indexAB = 0; indexAB < 3; indexAB++)
  {
    initBonus(bonusArray + indexAB);
  }

  *playingCondition = true;

  for (int i = 0; i < *nbPlayers; i++)
  {
    initPlayer(tabPlayers + i, i + 1, nbUnites);
    placeUnits(tabGrid, tabPlayers + i);
    updateGrid(tabGrid, *nbPlayers, tabPlayers, bonusArray);
  }
}

/**
 *
 *  Play a turn.
 *
 * @param currentPlayerIndex The id of the player currently playing.
 * @param moveNumber The move number of the player turn.
 * @param tabPlayers The players currently playing.
 * @param nbPlayers The number of players currently playing.
 * @param turnChoice The turn choice made by the player.
 * @param tabGrid The map.
 * @param bonusArray Bonuses.
 *
 */
void play_tour(int *currentPlayerIndex, int moveNumber, player tabPlayers[], int nbPlayers, int *turnChoice, int tabGrid[], bonus bonusArray[])
{

  infantry selectedUnit;
  if (tabPlayers[*currentPlayerIndex].isAlive == 1)
  {
    for (int i = 0; i < moveNumber; i++)
    {
      drawGrid(tabGrid);
      cout << "\n" << endl;
      if (i > 0)
      {
        cout << tabPlayers[*currentPlayerIndex].color;
        cout << "Joueur " << *currentPlayerIndex + 1 << ", c'est de nouveau votre tour !" << endl;
        cout << "\033[39m" << endl;
      }
      else
      {
        cout << tabPlayers[*currentPlayerIndex].color;
        cout << "Joueur " << *currentPlayerIndex + 1 << ", c'est votre tour !" << endl;
        cout << "\033[39m" << endl;
      }
      for (int i = 0; i < tabPlayers[*currentPlayerIndex].nbActiveUnits; i++)
      {
        if (tabPlayers[*currentPlayerIndex].infantriesList[i].isAlive)
        {
          cout << "Unité n°" << i + 1 << " ";
          printInfantryInline(tabPlayers[*currentPlayerIndex].infantriesList[i]);
        }
      }
      selectedUnit = selectUnit(&(tabPlayers[*currentPlayerIndex]));
      cout << "Vous avez choisi l'unité positionnée en (" << selectedUnit.x << ", " << selectedUnit.y << "). Que souhaitez-vous faire ?" << endl;
      // Appel du menu du tour
      turnMenu(turnChoice);
      //Traitement du choix
      switch (*turnChoice)
      {
      case 1: //Déplacement
        moveUnit(&tabPlayers[*currentPlayerIndex], selectedUnit.arrayIndex, tabGrid, bonusArray);
        break;
      case 2: //Attacque
        attackEnemy(&selectedUnit, tabPlayers, nbPlayers, tabGrid);
        break;
      }
      cout << endl;
      updateGrid(tabGrid, nbPlayers, tabPlayers, bonusArray);
    }
  }

  if (*currentPlayerIndex >= nbPlayers - 1)
  {
    *currentPlayerIndex = 0;
  }
  else
  {
    *currentPlayerIndex += 1;
  }
}

/**
 *
 *  Check if a player wins the game.
 *
 * @param tabPlayers The players currently playing.
 * @param nbPlayers The number of players currently playing.
 * @param playingCondition Tell if the game is in progress or not.
 * @param winner The winner of the game (null if there is no winner yet).
 *
 */
void verify_win(player *tabPlayers, int *nbPlayers, bool *playingCondition, int *winner)
{
  int alivePlayers = 0;
  for (int i = 0; i < *nbPlayers; i++)
  {
    if (tabPlayers[i].isAlive == true)
    {
      *winner = tabPlayers[i].id;
      alivePlayers++;
    }
  }
  if (alivePlayers == 1)
  {
    *playingCondition = false;
  }
}
