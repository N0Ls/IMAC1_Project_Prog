#include <iostream>
#include <string>
#include <string.h>
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
 * Initialize the parameters of a player at the start.
 *
 * @param player The player to initialize.
 * @param id The id to apply to the player.
 * @param nbActiveUnits The number of units that the player will have.
 *
 */
void initPlayer(player *player, int id, int nbActiveUnits)
{
  char all_colors[3][10] = {"\033[96m","\033[91m","\033[35m"};
  player->id = id;
  player->nbActiveUnits = nbActiveUnits;
  player->isAlive = true;
  strcpy(player -> color , all_colors[id-1]);

  cout << all_colors[id-1];
  cout << "Joueur " << id << " veuillez choisir votre type d'unités" << endl;
  cout << "TANK = t / SNIPER = s / K9 = k" << endl;
  cout << "\033[39m";

  char typeOfUnitChoice;
  for (int i = 0; i < nbActiveUnits; i++)
  {
    cin >> typeOfUnitChoice;
    if(typeOfUnitChoice == 't'){
      initInfantry(player->infantriesList + i, id, 200, 1.5, 2, i);
    }
    if(typeOfUnitChoice == 's'){
      initInfantry(player->infantriesList + i, id, 75, 0.8, 4, i);
    }
    if(typeOfUnitChoice == 'k'){
      initInfantry(player->infantriesList + i, id, 100, 1.5, 7, i);
    }
  }
}

/**
 * Display player information.
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

//Verification de l'état des infantry_list
void checkIfIsAlive(player *playerToCheck)
{
  if (playerToCheck->nbActiveUnits == 0)
  {
    playerToCheck->isAlive = false;
  }
}

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

//Placement des unités au début de la game
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
    cout << "Joueur " << player->id << ", placez vos unités" << endl;
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

//Fonction pour choisir l'unité à utiliser
infantry selectUnit(player *player)
{
  int unit = 0;

  string message = "Indiquez le numéro de l'unité que vous souhaitez utiliser : ",
         errorMessage = "Le numéro indiqué ne correspond à aucune unité.";

  cout << message;
  cin >> unit;

  while (1)
  {
    if (cin.fail() || unit > player->nbActiveUnits || unit < 1)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << errorMessage << endl;
      cout << message;
      cin >> unit;
    }
    if (!(cin.fail() || unit > player->nbActiveUnits || unit < 1))
      break;
  }
  return player->infantriesList[unit - 1];
}

//Fonction pour vérifier les entrées utilisateurs
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

//Fonction pour vérifier si le déplacement est valide
bool verifyCoordinates(infantry *infantry, int newX, int newY, int tabGrid[])
{
  int currentX = infantry->x,
      currentY = infantry->y;

  cout << " Calcul du déplacement : " << abs(currentX - newX) + abs(currentY - newY) << endl;
  cout << " Dextérité : " << infantry->dexterity << endl;

  if (abs(currentX - newX) + abs(currentY - newY) <= infantry->dexterity && (tabGrid[newY * X_DIMENSION + newX] == 0 || tabGrid[newY * X_DIMENSION + newX] == -1))
  {
    return true;
  }
  else
  {
    return false;
  }
}

//Fonction pour vérifier si une unité ennemie est présente sur la position
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

//Fonction pour vérifier si des ennemies se trouvent dans la zone de tir, et si oui appliquer des dégâts
void applyDamageZone(int targetX, int targetY, int attackerId, int damage, int nbPlayers, int tabGrid[], player *tabPlayer)
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
          int unites_active = tabPlayer[i].nbActiveUnits;
          for (int j = 0; j < unites_active; j++)
          {
            for (int k = 0; k < spots; k++)
            {
              if (tabPlayer[i].id == enemies[k][0] && tabPlayer[i].infantriesList[j].x == enemies[k][1] && tabPlayer[i].infantriesList[j].y == enemies[k][2])
              {
                tabPlayer[i].infantriesList[j].pv = tabPlayer[i].infantriesList[j].pv - damage;
                cout << "L'unité du joueur " << tabPlayer[i].id << " positionnée en (" << tabPlayer[i].infantriesList[j].x << ", " << tabPlayer[i].infantriesList[j].y << ") a été affectée par les projectiles de l'attaque. ";
                if (tabPlayer[i].infantriesList[j].pv > 0)
                {
                  cout << "PV de l'unité après l'attaque : " << tabPlayer[i].infantriesList[j].pv << "." << endl;
                }
                else
                {
                  tabPlayer[i].infantriesList[j].isAlive = false;
                  tabPlayer[i].nbActiveUnits = tabPlayer[i].nbActiveUnits - 1;
                  cout << "L'unité a été détruite." << endl;
                  checkIfIsAlive(&tabPlayer[i]);
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

//Fonction pour calculer les dommages infligés
int calculDamage(infantry *attackerUnit, int targetX, int targetY, bool enemy)
{
  int currentX = attackerUnit->x,
      currentY = attackerUnit->y;

  float attackCoefficient = (abs(currentX - targetX) + abs(currentY - targetY)) / 10.0;

  if (abs(currentX - targetX) + abs(currentY - targetY) <= attackerUnit->dexterity)
  {
    if(enemy == 1){
      return (attackerUnit->force - attackCoefficient) * attackerUnit->pv;
    } else {
      return ((attackerUnit->force - attackCoefficient) * attackerUnit->pv)/6;
    }
  }
  else
  {
    return 0;
  }
}

//int calculAreaDamage(infantry *attackerUnit, int targetX, int targetY){}

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

void attackEnemy(infantry *selectedUnit, player *tabPlayer, int nbPlayers, int tabGrid[])
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
        for (int i = 0; i < tabPlayer[k].nbActiveUnits; i++)
        {
          if (tabPlayer[k].infantriesList[i].x == targetX && tabPlayer[k].infantriesList[i].y == targetY)
          {
            printPlayer(tabPlayer[k]);
            updatePV = tabPlayer[k].infantriesList[i].pv - damage;
            tabPlayer[k].infantriesList[i].pv = updatePV;
            if (updatePV > 0)
            {
              cout << "L'unité ennemie a été touchée." << endl;
              cout << "PV de l'unité ennemie après l'attaque : " << tabPlayer[k].infantriesList[i].pv << "." << endl;
            }
            else
            {
              tabPlayer[k].infantriesList[i].isAlive = false;
              tabPlayer[k].nbActiveUnits = tabPlayer[k].nbActiveUnits - 1;
              cout << "L'unité ennemie a été détruite." << endl;
              cout << "Nombre d'unités actives restantes : " << tabPlayer[k].nbActiveUnits << "." << endl;
              checkIfIsAlive(&tabPlayer[k]);
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
    applyDamageZone(targetX, targetY, attackerId, damage, nbPlayers, tabGrid, tabPlayer);
  }
}
