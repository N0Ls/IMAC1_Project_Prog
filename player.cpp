#include <iostream>
#include <string>
using namespace std;
#include "infantry.h"
#include "player.h"
#include "display.h"
#include "bonus.h"
#define X_DIMENSION 10
#define Y_DIMENSION 10

//Initialisation des paramètres
void initPlayer(player *player, int id, int nb_unite_active)
{
  player->id = id;
  player->nb_unite_active = nb_unite_active;
  player->isAlive = true;
  for (int i = 0; i < nb_unite_active; i++)
  {
    initInfantry(player->infantry_list + i, id, 100, 1, 7);
  }
}

//Affichage des infos si besoin
void printPlayer(player playerToPrint)
{
  cout << "Id " << playerToPrint.id << endl;
  cout << "Nb d'unités " << playerToPrint.nb_unite_active << endl;
  cout << "Is player alive : " << playerToPrint.isAlive << endl;
  for (int i = 0; i < playerToPrint.nb_unite_active; i++)
  {
    printInfantryinfos(playerToPrint.infantry_list[i]);
  }
}

//Verification de l'état des infantry_list
void check_if_isAlive(player *playerToCheck)
{
  if (playerToCheck->nb_unite_active == 0)
  {
    playerToCheck->isAlive = false;
  }
}

void changeCoordinates(int *x, int *y)
{
  int temporaryX, temporaryY;
  string messageX = "Saisissez la coordonnée X : ", messageY = "Saisissez la coordonnée Y : ";
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
  int coordinates[player->nb_unite_active][2];

  for (int i = 0; i < player->nb_unite_active; i++)
  {
    coordinates[i][0] = -1;
    coordinates[i][1] = -1;
  }

  for (int i = 0; i < player->nb_unite_active; i++)
  {
    cout << "____________________________________________________" << endl;
    cout << "Joueur " << player->id << ", placez vos unités" << endl;
    cout << "Entrez les coordonnées initiales pour l'unité : " << i + 1 << endl;
    changeCoordinates(&(player->infantry_list[i].x), &(player->infantry_list[i].y));

    while (1)
    {
      if (tabGrid[player->infantry_list[i].y * X_DIMENSION + player->infantry_list[i].x] != 0)
      {
        cout << "Attention, la position est déjà occupée par une unité ennemie. Veuillez indiquer des coordonnées différentes." << endl;
        changeCoordinates(&(player->infantry_list[i].x), &(player->infantry_list[i].y));
      }
      if (!(tabGrid[player->infantry_list[i].y * X_DIMENSION + player->infantry_list[i].x] != 0))
        break;
    }

    for (int j = 0; j < player->nb_unite_active; j++)
    {
      if (j != i)
      {
        if (coordinates[j][0] == player->infantry_list[i].x && coordinates[j][1] == player->infantry_list[i].y)
        {
          j = -1;
          cout << "Attention, la position est déjà occupée par une de vos unités. Veuillez indiquer des coordonnées différentes." << endl;
          changeCoordinates(&(player->infantry_list[i].x), &(player->infantry_list[i].y));
        }
      }
    }

    coordinates[i][0] = player->infantry_list[i].x;
    coordinates[i][1] = player->infantry_list[i].y;
  }
}

//Fonction pour choisir l'unité à utiliser
infantry selectUnit(player *player)
{
  int unit = 0;
  string message = "Indiquez le numéro de l'unité que vous souhaitez utiliser : ", errorMessage = "Le numéro indiqué ne correspond à aucune unité.";
  cout << message;
  cin >> unit;
  while (1)
  {
    if (cin.fail() || unit > player->nb_unite_active || unit < 1)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << errorMessage << endl;
      cout << message;
      cin >> unit;
    }
    if (!(cin.fail() || unit > player->nb_unite_active || unit < 1))
      break;
  }
  return player->infantry_list[unit - 1];
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
  int currentX = infantry->x;
  int currentY = infantry->y;
  cout << " Calcul depl : " << abs(currentX - newX) + abs(currentY - newY) << endl;
  cout << " dexterity : " << infantry->dexterity << endl;
  if (abs(currentX - newX) + abs(currentY - newY) <= infantry->dexterity && tabGrid[newX * X_DIMENSION + newY] == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//Fonction pour vérifier si une unité ennemie est présente sur la position
bool verifyEnemy(int targetX, int targetY, int attacker_id, int tabGrid[])
{
  if (tabGrid[targetY * X_DIMENSION + targetX] != 0 && tabGrid[targetY * X_DIMENSION + targetX] != attacker_id)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//Fonction pour vérifier si des ennemies se trouvent dans la zone de tir, et si oui appliquer des dégâts
void applyDamageZone(int targetX, int targetY, int attacker_id, int nb_joueurs, int tabGrid[], player *tabPlayer)
{
  bool enemyProximity = false;
  int spots = 8;

  int enemies[spots][3];

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

  if (tabGrid[topLeftPosition] != 0 && tabGrid[topLeftPosition] != attacker_id)
  {
    enemyProximity = true;

    enemies[spots - 7][0] = tabGrid[topLeftPosition];
    enemies[spots - 7][1] = targetX - 1;
    enemies[spots - 7][2] = targetY - 1;
  }
  if (tabGrid[topPosition] != 0 && tabGrid[topPosition] != attacker_id)
  {
    enemyProximity = true;

    enemies[spots - 6][0] = tabGrid[topPosition];
    enemies[spots - 6][1] = targetX;
    enemies[spots - 6][2] = targetY - 1;
  }
  if (tabGrid[topRightPosition] != 0 && tabGrid[topRightPosition] != attacker_id)
  {
    enemyProximity = true;

    enemies[spots - 5][0] = tabGrid[topRightPosition];
    enemies[spots - 5][1] = targetX + 1;
    enemies[spots - 5][2] = targetY - 1;
  }
  if (tabGrid[rightPosition] != 0 && tabGrid[rightPosition] != attacker_id)
  {
    enemyProximity = true;

    enemies[spots - 4][0] = tabGrid[rightPosition];
    enemies[spots - 4][1] = targetX + 1;
    enemies[spots - 4][2] = targetY;
  }
  if (tabGrid[bottomRight] != 0 && tabGrid[bottomRight] != attacker_id)
  {
    enemyProximity = true;

    enemies[spots - 3][0] = tabGrid[bottomRight];
    enemies[spots - 3][1] = targetX + 1;
    enemies[spots - 3][2] = targetY + 1;
  }
  if (tabGrid[bottomPosition] != 0 && tabGrid[bottomPosition] != attacker_id)
  {
    enemyProximity = true;

    enemies[spots - 2][0] = tabGrid[bottomPosition];
    enemies[spots - 2][1] = targetX;
    enemies[spots - 2][2] = targetY + 1;
  }
  if (tabGrid[bottomLeftPosition] != 0 && tabGrid[bottomLeftPosition] != attacker_id)
  {
    enemyProximity = true;

    enemies[spots - 1][0] = tabGrid[bottomLeftPosition];
    enemies[spots - 1][1] = targetX - 1;
    enemies[spots - 1][2] = targetY + 1;
  }
  if (tabGrid[leftPosition] != 0 && tabGrid[leftPosition] != attacker_id)
  {
    enemyProximity = true;

    enemies[spots][0] = tabGrid[leftPosition];
    enemies[spots][1] = targetX - 1;
    enemies[spots][2] = targetY;
  }

  if (enemyProximity)
  {
    for (int i = 0; i < nb_joueurs; i++)
    {
      if (i + 1 != attacker_id)
      {
        int unites_active = tabPlayer[i].nb_unite_active;
        for (int j = 0; j < unites_active; j++)
        {
          for (int k = 0; k < spots; k++)
          {
            if (tabPlayer[i].id == enemies[k][0] && tabPlayer[i].infantry_list[j].x == enemies[k][1] && tabPlayer[i].infantry_list[j].y == enemies[k][2])
            {
              tabPlayer[i].infantry_list[j].pv = tabPlayer[i].infantry_list[j].pv - 5;
              cout << "L'unité du joueur " << tabPlayer[i].id << " positionnée en (" << tabPlayer[i].infantry_list[j].x << ", " << tabPlayer[i].infantry_list[j].y << ") a été affectée par les projectiles de l'attaque. ";
              if (tabPlayer[i].infantry_list[j].pv > 0)
              {
                cout << "PV de l'unité après l'attaque : " << tabPlayer[i].infantry_list[j].pv << "." << endl;
              }
              else
              {
                tabPlayer[i].infantry_list[j].isAlive = false;
                tabPlayer[i].nb_unite_active = tabPlayer[i].nb_unite_active - 1;
                cout << "L'unité a été détruite." << endl;
                check_if_isAlive(&tabPlayer[i]);
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

//Fonction pour calculer les dommages infligés
int calculDamage(infantry *attackerUnit, int targetX, int targetY)
{
  int currentX = attackerUnit->x;
  int currentY = attackerUnit->y;
  float attackCoefficient = (abs(currentX - targetX) + abs(currentY - targetY)) / 10.0;
  if (abs(currentX - targetX) + abs(currentY - targetY) <= attackerUnit->dexterity)
  {
    return (attackerUnit->force - attackCoefficient) * attackerUnit->pv;
  }
  else
  {
    return 0;
  }
}

//int calculAreaDamage(infantry *attackerUnit, int targetX, int targetY){}

void moveUnit(player *player, int unit_id, int tabGrid[])
{
  int newX, newY;
  string messageX = "Entrez la nouvelle coordonnée X : ", messageY = "Entrez la nouvelle coordonnée Y : ";
  string errorMessage = "La coordonnée doit être un entier compris entre 1 et 9.";

  cout << messageX;
  cin >> newX;
  checkPlayerCoordinatesEntry(&newX, messageX, errorMessage);

  cout << messageY;
  cin >> newY;
  checkPlayerCoordinatesEntry(&newY, messageY, errorMessage);

  if (verifyCoordinates(&(player->infantry_list[unit_id - 1]), newX, newY, tabGrid) == 1)
  {
    player->infantry_list[unit_id - 1].x = newX;
    player->infantry_list[unit_id - 1].y = newY;
  }
  else
  {
    cout << "Ce déplacement est impossible" << endl;
    moveUnit(player, unit_id, tabGrid);
  }
}

void attackEnemy(infantry *selectedUnit, player *tabPlayer, int nb_joueurs, int tabGrid[])
{
  int attacker_id = selectedUnit->owner_id;
  int targetX;
  int targetY;
  float damage;
  float updatePV;
  string messageX = "Entrez la coordonnée X : ", messageY = "Entrez la coordonnée Y : ";
  string errorMessage = "La coordonnée doit être un entier compris entre 1 et 9.";

  cout << "Quelle est votre cible ?" << endl;

  cout << messageX;
  cin >> targetX;
  checkPlayerCoordinatesEntry(&targetX, messageX, errorMessage);

  cout << messageY;
  cin >> targetY;
  checkPlayerCoordinatesEntry(&targetY, messageY, errorMessage);

  if (verifyEnemy(targetX, targetY, attacker_id, tabGrid) == 1)
  {
    damage = calculDamage(selectedUnit, targetX, targetY);
    if (damage > 0)
    {
      for (int k = 0; k < nb_joueurs; k++)
      {
        for (int i = 0; i < tabPlayer[k].nb_unite_active; i++)
        {
          if (tabPlayer[k].infantry_list[i].x == targetX && tabPlayer[k].infantry_list[i].y == targetY)
          {
            printPlayer(tabPlayer[k]);
            updatePV = tabPlayer[k].infantry_list[i].pv - damage;
            tabPlayer[k].infantry_list[i].pv = updatePV;
            if (updatePV > 0)
            {
              cout << "L'unité ennemie a été touchée." << endl;
              cout << "PV de l'unité ennemie après l'attaque : " << tabPlayer[k].infantry_list[i].pv << "." << endl;
            }
            else
            {
              tabPlayer[k].infantry_list[i].isAlive = false;
              tabPlayer[k].nb_unite_active = tabPlayer[k].nb_unite_active - 1;
              cout << "L'unité ennemie a été détruite." << endl;
              cout << "Nombre d'unités actives restantes : " << tabPlayer[k].nb_unite_active << "." << endl;
              check_if_isAlive(&tabPlayer[k]);
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
    applyDamageZone(targetX, targetY, attacker_id, nb_joueurs, tabGrid, tabPlayer);
  }
}
