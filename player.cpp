#include <iostream>
#include <string>
#include <string.h>
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
 * Initialize the parameters of a player at the start.
 *
 * @param player The player to initialize.
 * @param id The id to apply to the player.
 * @param nbActiveUnits The number of units that the player will have.
 *
 */
void initPlayer(player *player, int id, int nbActiveUnits)
{
  char all_colors[3][10] = {"\033[96m", "\033[91m", "\033[93m"};
  player->id = id;
  player->nbActiveUnits = nbActiveUnits;
  player->isAlive = true;
  strcpy(player->color, all_colors[id - 1]);

  cout << "\n____________________________________________________" << endl;
  cout << all_colors[id - 1];
  cout << "\nJoueur " << id << " veuillez choisir vos types d'unités" << endl;
  cout << "\nTANK = t / SNIPER = s / K9 = k" << endl;
  cout << '\n';
  cout << "\033[39m";

  char typeOfUnitChoice;
  for (int i = 0; i < nbActiveUnits; i++)
  {
    cout << "Type de l'unité " << i + 1 << " : ";
    cin >> typeOfUnitChoice;

    while (1) {
    if (cin.fail() || (typeOfUnitChoice != 't' &&  typeOfUnitChoice != 's' && typeOfUnitChoice != 'k'))
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << "Vous ne pouvez choisir qu'entre un tank (t), un sniper (s) et un k9 (k)." << endl;
      cout << "Type de l'unité " << i + 1 << " : ";
      cin >> typeOfUnitChoice;
    }
    if (!(cin.fail() || (typeOfUnitChoice != 't' &&  typeOfUnitChoice != 's' && typeOfUnitChoice != 'k')))
      break;
    }

    if (typeOfUnitChoice == 't')
    {
      initInfantry(player->infantriesList + i, id, 200, 1.5, 2, 5, i);
    }
    if (typeOfUnitChoice == 's')
    {
      initInfantry(player->infantriesList + i, id, 75, 0.8, 4, 7, i);
    }
    if (typeOfUnitChoice == 'k')
    {
      initInfantry(player->infantriesList + i, id, 100, 1.5, 7, 2, i);
    }
  }
}

/**
 *
 * Display player information..
 *
 * @param playerToPrint The player whose information has to be displayed.
 *
 */
void printPlayer(player playerToPrint)
{
  cout << "Id " << playerToPrint.id << endl;
  cout << "Nb d'unités " << playerToPrint.nbActiveUnits << endl;
  cout << "Is player alive : " << playerToPrint.isAlive << endl;
  for (int i = 0; i < playerToPrint.nbActiveUnits; i++)
  {
    printInfantryInfos(playerToPrint.infantriesList[i]);
  }
}

/**
 *
 * Check if a player units are still alive.
 *
 * @param playerToCheck The player whose units have to be checked.
 *
 */
void checkIfIsAlive(player *playerToCheck)
{
  if (playerToCheck->nbActiveUnits == 0)
  {
    playerToCheck->isAlive = false;
  }
}

/**
 *
 * Apply coordinates (x and y) to a specific unit.
 *
 * @param x x coordinate.
 * @param y y coordinate.
 *
 */
void changeCoordinates(int *x, int *y)
{
  int temporaryX,
      temporaryY;

  string messageX = "Saisissez la coordonnée X : ",
         messageY = "Saisissez la coordonnée Y : ";
  string errorMessage = "La coordonnée doit être un entier compris entre 1 et 9.";

  cout << messageX;
  cin >> temporaryX;
  checkPlayerCoordinatesEntry(&temporaryX, messageX, errorMessage);

  cout << messageY;
  cin >> temporaryY;
  checkPlayerCoordinatesEntry(&temporaryY, messageY, errorMessage);

  *x = temporaryX;
  *y = temporaryY;
}

/**
 *
 * Place every units at the start.
 *
 * @param tabGrid The map.
 * @param player The player for whom the units have to be placed.
 *
 */
void placeUnits(int *tabGrid, player *player)
{
  int coordinates[player->nbActiveUnits][2];

  for (int i = 0; i < player->nbActiveUnits; i++)
  {
    coordinates[i][0] = -1;
    coordinates[i][1] = -1;
  }

  for (int i = 0; i < player->nbActiveUnits; i++)
  {
    cout << "____________________________________________________" << endl;
    cout << player->color << endl;
    cout << "Joueur " << player->id << ", placez vos unités" << endl;
    cout << "\033[39m" << endl;
    cout << "Entrez les coordonnées initiales pour l'unité : " << i + 1 << endl;
    changeCoordinates(&(player->infantriesList[i].x), &(player->infantriesList[i].y));

    while (1)
    {
      if (tabGrid[player->infantriesList[i].y * X_DIMENSION + player->infantriesList[i].x] != 0)
      {
        cout << "Attention, la position est déjà occupée par une unité ennemie. Veuillez indiquer des coordonnées différentes." << endl;
        changeCoordinates(&(player->infantriesList[i].x), &(player->infantriesList[i].y));
      }
      if (!(tabGrid[player->infantriesList[i].y * X_DIMENSION + player->infantriesList[i].x] != 0))
        break;
    }

    for (int j = 0; j < player->nbActiveUnits; j++)
    {
      if (j != i)
      {
        if (coordinates[j][0] == player->infantriesList[i].x && coordinates[j][1] == player->infantriesList[i].y)
        {
          j = -1;
          cout << "Attention, la position est déjà occupée par une de vos unités. Veuillez indiquer des coordonnées différentes." << endl;
          changeCoordinates(&(player->infantriesList[i].x), &(player->infantriesList[i].y));
        }
      }
    }

    coordinates[i][0] = player->infantriesList[i].x;
    coordinates[i][1] = player->infantriesList[i].y;
  }
}

/**
 *
 * Place every units at the start.
 *
 * @param player The player who has to select one of his units.
 *
 * @return The unit selected.
 */
infantry selectUnit(player *player)
{
  int unit = 0;

  string message = "Indiquez le numéro de l'unité que vous souhaitez utiliser : ",
         errorMessage = "Le numéro indiqué ne correspond à aucune unité.";

  cout << message;
  cin >> unit;
  while (1)
  {
    if (cin.fail() || unit > player->nbActiveUnits || unit < 1 || player->infantriesList[unit - 1].isAlive == 0)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << errorMessage << endl;
      cout << message;
      cin >> unit;
    }
    if (!(cin.fail() || unit > player->nbActiveUnits || unit < 1 || player->infantriesList[unit - 1].isAlive == 0))
      break;
  }

  return player->infantriesList[unit - 1];
}

/**
 *
 * Check for a user coordinate entry.
 *
 * @param entry The initial user entry (which to be checked).
 * @param message The message which asks the user for a coordinate.
 * @param errorMessage The error message (which has to be displayed if the user makes a wrong entry).
 *
 * @return A correct coordinate entry.
 */
int checkPlayerCoordinatesEntry(int *entry, string message, string errorMessage)
{
  while (1)
  {
    if (cin.fail() || *entry >= X_DIMENSION || *entry < 0)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << errorMessage << endl;
      cout << message;
      cin >> *entry;
    }
    if (!(cin.fail() || *entry >= X_DIMENSION || *entry < 0))
      break;
  }
  return *entry;
}

/**
 *
 * Check if the displacement is possible.
 *
 * @param infantry The unit which has to be moved.
 * @param newX The x coordinate destination.
 * @param newY The y coordinate destination.
 * @param tabGrid The map.
 *
 * @return true (possible) or false (not possible).
 */
bool verifyCoordinates(infantry *infantry, int newX, int newY, int tabGrid[])
{
  int currentX = infantry->x,
      currentY = infantry->y;

  // cout << " Calcul du déplacement : " << abs(currentX - newX) + abs(currentY - newY) << endl;
  // cout << " Dextérité : " << infantry->dexterity << endl;

  if (abs(currentX - newX) + abs(currentY - newY) <= infantry->dexterity && (tabGrid[newY * X_DIMENSION + newX] == 0 || tabGrid[newY * X_DIMENSION + newX] == -1))
  {
    return true;
  }
  else
  {
    return false;
  }
}

/**
 *
 * Check if the attack targets an enemy.
 *
 * @param targetX The x coordinate target.
 * @param targetY The y coordinate target.
 * @param attackerId The id of the attacking unit.
 * @param tabGrid The map.
 *
 * @return true (it is an enemy) or false (it is not an ennemy).
 */
bool verifyEnemy(int targetX, int targetY, int attackerId, int tabGrid[])
{
  if (tabGrid[targetY * X_DIMENSION + targetX] != 0 && tabGrid[targetY * X_DIMENSION + targetX] != attackerId)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/**
 *
 * Apply damages to ennemies who are in the attack area.
 *
 * @param targetX The x coordinate target.
 * @param targetY The y coordinate target.
 * @param attackerId The id of the attacking unit.
 * @param damage The damage value to apply.
 * @param nbPlayers The number of players currently playing.
 * @param tabGrid The map.
 * @param tabPlayers The players currently playing.
 *
 */
void applyDamageZone(int targetX, int targetY, int attackerId, int damage, int nbPlayers, int tabGrid[], player *tabPlayers)
{
  bool enemyProximity = false;

  int spots = 8,
      enemies[spots][3];

  int topLeftPosition = (targetY - 1) * X_DIMENSION + (targetX - 1),
      topPosition = (targetY - 1) * X_DIMENSION + (targetX),
      topRightPosition = (targetY - 1) * X_DIMENSION + (targetX + 1),
      leftPosition = (targetY)*X_DIMENSION + (targetX - 1),
      rightPosition = (targetY)*X_DIMENSION + (targetX + 1),
      bottomLeftPosition = (targetY + 1) * X_DIMENSION + (targetX - 1),
      bottomPosition = (targetY + 1) * X_DIMENSION + (targetX),
      bottomRight = (targetY + 1) * X_DIMENSION + (targetX + 1);

  for (int i = 0; i < spots; i++)
  {
    enemies[i][0] = -1;
    enemies[i][1] = -1;
    enemies[i][2] = -1;
  }

  if (damage > 0)
  {
    if (tabGrid[topLeftPosition] != 0 && tabGrid[topLeftPosition] != attackerId)
    {
      enemyProximity = true;

      enemies[spots - 7][0] = tabGrid[topLeftPosition];
      enemies[spots - 7][1] = targetX - 1;
      enemies[spots - 7][2] = targetY - 1;
    }
    if (tabGrid[topPosition] != 0 && tabGrid[topPosition] != attackerId)
    {
      enemyProximity = true;

      enemies[spots - 6][0] = tabGrid[topPosition];
      enemies[spots - 6][1] = targetX;
      enemies[spots - 6][2] = targetY - 1;
    }
    if (tabGrid[topRightPosition] != 0 && tabGrid[topRightPosition] != attackerId)
    {
      enemyProximity = true;

      enemies[spots - 5][0] = tabGrid[topRightPosition];
      enemies[spots - 5][1] = targetX + 1;
      enemies[spots - 5][2] = targetY - 1;
    }
    if (tabGrid[rightPosition] != 0 && tabGrid[rightPosition] != attackerId)
    {
      enemyProximity = true;

      enemies[spots - 4][0] = tabGrid[rightPosition];
      enemies[spots - 4][1] = targetX + 1;
      enemies[spots - 4][2] = targetY;
    }
    if (tabGrid[bottomRight] != 0 && tabGrid[bottomRight] != attackerId)
    {
      enemyProximity = true;

      enemies[spots - 3][0] = tabGrid[bottomRight];
      enemies[spots - 3][1] = targetX + 1;
      enemies[spots - 3][2] = targetY + 1;
    }
    if (tabGrid[bottomPosition] != 0 && tabGrid[bottomPosition] != attackerId)
    {
      enemyProximity = true;

      enemies[spots - 2][0] = tabGrid[bottomPosition];
      enemies[spots - 2][1] = targetX;
      enemies[spots - 2][2] = targetY + 1;
    }
    if (tabGrid[bottomLeftPosition] != 0 && tabGrid[bottomLeftPosition] != attackerId)
    {
      enemyProximity = true;

      enemies[spots - 1][0] = tabGrid[bottomLeftPosition];
      enemies[spots - 1][1] = targetX - 1;
      enemies[spots - 1][2] = targetY + 1;
    }
    if (tabGrid[leftPosition] != 0 && tabGrid[leftPosition] != attackerId)
    {
      enemyProximity = true;

      enemies[spots][0] = tabGrid[leftPosition];
      enemies[spots][1] = targetX - 1;
      enemies[spots][2] = targetY;
    }

    if (enemyProximity)
    {
      for (int i = 0; i < nbPlayers; i++)
      {
        if (i + 1 != attackerId)
        {
          int unites_active = tabPlayers[i].nbActiveUnits;
          for (int j = 0; j < unites_active; j++)
          {
            for (int k = 0; k < spots; k++)
            {
              if (tabPlayers[i].id == enemies[k][0] && tabPlayers[i].infantriesList[j].x == enemies[k][1] && tabPlayers[i].infantriesList[j].y == enemies[k][2])
              {
                tabPlayers[i].infantriesList[j].pv = tabPlayers[i].infantriesList[j].pv - damage;
                cout << "L'unité du joueur " << tabPlayers[i].id << " positionnée en (" << tabPlayers[i].infantriesList[j].x << ", " << tabPlayers[i].infantriesList[j].y << ") a été affectée par les projectiles de l'attaque. ";
                if (tabPlayers[i].infantriesList[j].pv > 0)
                {
                  cout << "PV de l'unité après l'attaque : " << tabPlayers[i].infantriesList[j].pv << "." << endl;
                }
                else
                {
                  tabPlayers[i].infantriesList[j].isAlive = false;
                  cout << "L'unité a été détruite." << endl;
                  checkIfIsAlive(&tabPlayers[i]);
                }
              }
            }
          }
        }
      }
    }
    else
    {
      cout << "Pas d'ennemis dans la zone de tir. Votre attaque n'a eu aucun effet." << endl;
    }
  }
  else
  {
    cout << "Attaque impossible. La zone cible est trop éloignée." << endl;
  }
}

/**
 *
 * Calcul damages.
 *
 * @param attackerUnit The attacking unit.
 * @param targetX The x coordinate target.
 * @param targetY The y coordinate target.
 * @param enemy Specify if an enemy is targeted.
 *
 * @return The value representing the damage to apply (specific value or 0).
 *
 */
int calculDamage(infantry *attackerUnit, int targetX, int targetY, bool enemy)
{
  int currentX = attackerUnit->x,
      currentY = attackerUnit->y;

  float attackCoefficient = (abs(currentX - targetX) + abs(currentY - targetY)) / 10.0;

  if (abs(currentX - targetX) + abs(currentY - targetY) <= attackerUnit->fireRange)
  {
    if (enemy == 1)
    {
      return (attackerUnit->force - attackCoefficient) * attackerUnit->pv;
    }
    else
    {
      return ((attackerUnit->force - attackCoefficient) * attackerUnit->pv) / 6;
    }
  }
  else
  {
    return 0;
  }
}

/**
 *
 * Move a specific unit.
 *
 * @param player The player who wants to move his unit.
 * @param unitIndex The id of the unit to move.
 * @param tabGrid The map.
 * @param tabBonus Bonuses.
 *
 */
void moveUnit(player *player, int unitIndex, int tabGrid[], bonus *tabBonus)
{
  int newX,
      newY;

  string messageX = "Entrez la nouvelle coordonnée X : ",
         messageY = "Entrez la nouvelle coordonnée Y : ";

  string errorMessage = "La coordonnée doit être un entier compris entre 1 et 9.";

  cout << messageX;
  cin >> newX;
  checkPlayerCoordinatesEntry(&newX, messageX, errorMessage);

  cout << messageY;
  cin >> newY;
  checkPlayerCoordinatesEntry(&newY, messageY, errorMessage);

  if (verifyCoordinates(&(player->infantriesList[unitIndex]), newX, newY, tabGrid) == 1)
  {
    player->infantriesList[unitIndex].x = newX;
    player->infantriesList[unitIndex].y = newY;

    //Check if player is on a bonus
    for (int k = 0; k < BONUS_MAX; k++)
    {
      bonusTreatment(player->infantriesList + (unitIndex), tabBonus + k);
    }
  }
  else
  {
    cout << "Ce déplacement est impossible." << endl;
    moveUnit(player, unitIndex, tabGrid, tabBonus);
  }
}

/**
 *
 * Attack an enemy.
 *
 * @param selectedUnit The player who wants to move his unit.
 * @param tabPlayers The players currently playing.
 * @param nbPlayers The number of players currently playing.
 * @param tabGrid The map.
 *
 */
void attackEnemy(infantry *selectedUnit, player *tabPlayers, int nbPlayers, int tabGrid[])
{
  int attackerId = selectedUnit->ownerId,
      targetX,
      targetY;

  bool enemy;

  float damage,
      updatePV;

  string messageX = "Entrez la coordonnée X : ",
         messageY = "Entrez la coordonnée Y : ";

  string errorMessage = "La coordonnée doit être un entier compris entre 1 et 9.";

  cout << "Quelle est votre cible ?" << endl;

  cout << messageX;
  cin >> targetX;
  checkPlayerCoordinatesEntry(&targetX, messageX, errorMessage);

  cout << messageY;
  cin >> targetY;
  checkPlayerCoordinatesEntry(&targetY, messageY, errorMessage);

  enemy = verifyEnemy(targetX, targetY, attackerId, tabGrid);

  damage = calculDamage(selectedUnit, targetX, targetY, enemy);

  if (enemy == 1)
  {
    if (damage > 0)
    {
      for (int k = 0; k < nbPlayers; k++)
      {
        for (int i = 0; i < tabPlayers[k].nbActiveUnits; i++)
        {
          if (tabPlayers[k].infantriesList[i].x == targetX && tabPlayers[k].infantriesList[i].y == targetY)
          {
            printPlayer(tabPlayers[k]);
            updatePV = tabPlayers[k].infantriesList[i].pv - damage;
            tabPlayers[k].infantriesList[i].pv = updatePV;
            if (updatePV > 0)
            {
              cout << "L'unité ennemie a été touchée." << endl;
              cout << "PV de l'unité ennemie après l'attaque : " << tabPlayers[k].infantriesList[i].pv << "." << endl;
            }
            else
            {
              tabPlayers[k].infantriesList[i].isAlive = false;
              cout << "L'unité ennemie a été détruite." << endl;
              cout << "Nombre d'unités actives restantes : " << tabPlayers[k].nbActiveUnits << "." << endl;
              checkIfIsAlive(&tabPlayers[k]);
            }
          }
        }
      }
    }
    else
    {
      cout << "Attaque impossible. L'ennemie est trop loin et ne peut pas être touché." << endl;
    }
  }
  else
  {
    applyDamageZone(targetX, targetY, attackerId, damage, nbPlayers, tabGrid, tabPlayers);
  }
}
