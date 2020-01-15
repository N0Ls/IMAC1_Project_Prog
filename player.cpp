#include <iostream>
using namespace std;
#include "infantry.h"
#include "player.h"
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
  cout << "Saisissez la coordonnée X : ";
  cin >> temporaryX;
  while (1)
  {
    if (cin.fail() || temporaryX > X_DIMENSION || temporaryX < 1)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << "La coordonnée doit être un entier compris entre 1 et " << X_DIMENSION << "." << endl;
      cout << "Entrez la coordonnée X : ";
      cin >> temporaryX;
    }
    if (!(cin.fail() || temporaryX > X_DIMENSION || temporaryX < 1))
      break;
  }
  cout << "Saisissez la coordonnée Y : ";
  cin >> temporaryY;
  while (1)
  {
    if (cin.fail() || temporaryY > X_DIMENSION || temporaryY < 1)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << "La coordonnée doit être un entier compris entre 1 et " << Y_DIMENSION << "." << endl;
      cout << "Entrez la coordonnée Y : ";
      cin >> temporaryY;
    }
    if (!(cin.fail() || temporaryY > X_DIMENSION || temporaryY < 1))
      break;
  }
  *x = temporaryX;
  *y = temporaryY;
}

//Placement des unités au début de la game
void placeUnits(player *player)
{
  for (int i = 0; i < player->nb_unite_active; i++)
  {
    cout << "____________________________________________________" << endl;
    cout << "Joueur " << player->id << ", placez vos unités" << endl;
    cout << "Entrez les coordonnées initiales pour l'unité : " << i + 1 << endl;
    changeCoordinates(&(player->infantry_list[i].x), &(player->infantry_list[i].y));
  }
}

//Fonction pour choisir l'unité à utiliser
infantry selectUnit(player *player)
{
  int unit = 0;
  cout << "Indiquez le numéro de l'unité que vous souhaitez utiliser : ";
  cin >> unit;
  while (1)
  {
    if (cin.fail() || unit > player->nb_unite_active || unit < 1)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << "Le numéro indiqué ne correspond à aucune unité." << endl;
      cout << "Indiquez le numéro de l'unité que vous souhaitez utiliser : ";
      cin >> unit;
    }
    if (!(cin.fail() || unit > player->nb_unite_active || unit < 1))
      break;
  }
  return player->infantry_list[unit - 1];
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

void moveUnit(player *player, int unit_id, int tabGrid[])
{
  int newX;
  int newY;

  cout << "Entrez la nouvelle coordonnée X : ";
  cin >> newX;
  while (1)
  {
    if (cin.fail() || newX > X_DIMENSION || newX < 1)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << "La coordonnée doit être un entier compris entre 1 et " << X_DIMENSION << "." << endl;
      cout << "Entrez la nouvelle coordonnée X : ";
      cin >> newX;
    }
    if (!(cin.fail() || newX > X_DIMENSION || newX < 1))
      break;
  }
  cout << "Entrez la nouvelle coordonnée Y : ";
  cin >> newY;
  while (1)
  {
    if (cin.fail() || newY > Y_DIMENSION || newY < 1)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << "La coordonnée doit être un entier compris entre 1 et " << Y_DIMENSION << "." << endl;
      cout << "Entrez la nouvelle coordonnée Y : ";
      cin >> newY;
    }
    if (!(cin.fail() || newY > Y_DIMENSION || newY < 1))
      break;
  }

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

  cout << "Quelle est votre cible ?" << endl;
  cout << "Entrez la coordonnée X : ";
  cin >> targetX;
  while (1)
  {
    if (cin.fail() || targetX > X_DIMENSION || targetX < 1)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << "La coordonnée doit être un entier compris entre 1 et " << X_DIMENSION << "." << endl;
      cout << "Entrez la nouvelle coordonnée X : ";
      cin >> targetX;
    }
    if (!(cin.fail() || targetX > X_DIMENSION || targetX < 1))
      break;
  }
  cout << "Entrez la coordonnée Y : ";
  cin >> targetY;
  while (1)
  {
    if (cin.fail() || targetY > Y_DIMENSION || targetY < 1)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << "La coordonnée doit être un entier compris entre 1 et " << Y_DIMENSION << "." << endl;
      cout << "Entrez la nouvelle coordonnée X : ";
      cin >> targetY;
    }
    if (!(cin.fail() || targetY > Y_DIMENSION || targetY < 1))
      break;
  }
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
              cout << "PV de l'unité ennemie après l'attaque : " << tabPlayer[k].infantry_list[i].pv << endl;
            }
            else
            {
              tabPlayer[k].infantry_list[i].isAlive = false;
              tabPlayer[k].nb_unite_active = tabPlayer[k].nb_unite_active - 1;
              cout << "L'unité ennemie a été détruite." << endl;
              cout << "Nombre d'unités actives restantes : " << tabPlayer[k].nb_unite_active << endl;
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
    cout << "Attaque impossible. Attention, vous devez cibler une position ennemie." << endl;
    attackEnemy(selectedUnit, tabPlayer, nb_joueurs, tabGrid);
  }
}
