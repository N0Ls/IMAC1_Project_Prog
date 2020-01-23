#include <iostream>
#include <string>
using namespace std;
#include "infantry.h"
#include "player.h"
#include "bonus.h"
#include "display.h"
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
  //Reset grid
  for (int i = 0; i < X_DIMENSION; i++)
  {
    for (int y = 0; y < Y_DIMENSION; y++)
    {
      tabGrid[X_DIMENSION * i + y] = 0;
    }
  }
  //Update for each player
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
  //Bonus may be appearing
  probBonusArray(tabBonus, tabGrid);
  for(int v = 0; v < BONUS_MAX ; v++){
    if(tabBonus[v].isActive==true){
      tabGrid[tabBonus[v].y * X_DIMENSION + tabBonus[v].x ]=-1;
    }
  }
}



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
  //Demande le nombre de joueur
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
    if (!(cin.fail() || *nbPlayers < 2  || *nbPlayers > 3))
      break;
  }

  //Demande le nombre d'unité par joueur
  int nbUnites, maxUnites = 0;
  if (*nbPlayers == 2){
    maxUnites = 9;
  } else if (*nbPlayers == 3) {
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
    if (!(cin.fail() || nbUnites < 1  || nbUnites > maxUnites))
      break;
  }



  //Initialisation de la grille
  initGrid(tabGrid);

  //initialisation des bonus
  for(int indexAB = 0; indexAB < 3; indexAB++){
    initBonus(bonusArray + indexAB);
  }

  //Début du jeu
  *playingCondition = true;

  //Placement des troupes
  //Initialisation des joueurs
  for (int i = 0; i < *nbPlayers; i++)
  {
    initPlayer(tabPlayers + i, i + 1, nbUnites);
    placeUnits(tabGrid, tabPlayers + i);
    updateGrid(tabGrid, *nbPlayers, tabPlayers, bonusArray);
  }

  //Dessin après le placement
  drawGrid(tabGrid);
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
      cout << "----------" << endl;
      if (i > 0)
      {
        cout << "Joueur " << *currentPlayerIndex + 1 << ", c'est de nouveau votre tour !" << endl;
      }
      else
      {
        cout << "Joueur " << *currentPlayerIndex + 1 << ", c'est votre tour !" << endl;
      }
      for (int i = 0; i < tabPlayers[*currentPlayerIndex].nbActiveUnits; i++)
      {
        cout << "Unité n°" << i + 1 << " ";
        printInfantryInline(tabPlayers[*currentPlayerIndex].infantriesList[i]);
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

      updateGrid(tabGrid, nbPlayers, tabPlayers, bonusArray);
      drawGrid(tabGrid);
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
    cout << "Fin de la partie." << endl;
    cout << "Le gagnant est le joueur " << winner << " !" << endl;
    break;
  case 2:
    cout << "À bientôt !" << endl;
    exit(EXIT_FAILURE);
    break;
  }

  return 0;
}
