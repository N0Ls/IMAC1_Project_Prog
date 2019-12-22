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
  //player -> user_name[10] = user_name;
  player->nb_unite_active = nb_unite_active;
  player->isAlive = true;
  for (int i = 0; i < nb_unite_active; i++)
  {
    initInfantry(player->infantry_list + i, id, 100, 0.5, 7);
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
  cout << "Saisissez la coordonnée X : ";
  cin >> *x;
  cout << "Saisissez la coordonnée Y : ";
  cin >> *y;
}

//Placement des unités au début de la game
void placeUnits(player *player)
{
  for (int i = 0; i < player->nb_unite_active; i++)
  {
    cout << "____________________________________________________" << endl;
    cout << "Joueur " << player->id << ", placez vos unités" << endl;
    cout << "Entrez les coordonnées initales pour l'unité : " << i + 1 << endl;
    changeCoordinates(&(player->infantry_list[i].x), &(player->infantry_list[i].y));
  }
}

//Fonction pour choisir l'unité à utiliser
infantry selectUnit(player *player)
{
  int unitX, unitY;
  cout << "Entrez la coordonnée X de l'unité à utiliser : ";
  cin >> unitX;
  cout << "Entrez la coordonnée Y de l'unité à utiliser : ";
  cin >> unitY;
  for (int i = 0; i < player->nb_unite_active; i++)
  {
    if (player->infantry_list[i].x == unitX && player->infantry_list[i].y == unitY)
    {
      return player->infantry_list[i];
    }
    else {
      cout << "Attention, aucune de vos unitées ne sont localisées ici.";
      selectUnit(player);
    }
  }
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
bool verifyEnemy(int targetX, int targetY, int target_id, int tabGrid[])
{
  if (tabGrid[targetX * X_DIMENSION + targetY] == target_id)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void moveUnit(player *player, int unit_id, int tabGrid[])
{
  // int currentX = player -> infantry_list[unit_id-1].x;
  // int currentY = player -> infantry_list[unit_id-1].y;
  int newX;
  int newY;

  cout << "Entrez la nouvelle coordonnée X : ";
  cin >> newX;
  cout << "Entrez la nouvelle coordonnée Y : ";
  cin >> newY;

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

void attackEnemy(player *attacker, player *target, int attacker_id, int target_id, int tabGrid[])
{
  int targetX;
  int targetY;
  float damage;
  float updatePV;

  cout << "Quelle est votre cible ?" << endl;
  cout << "Entrez la coordonnée X : ";
  cin >> targetX;
  cout << "Entrez la coordonnée Y : ";
  cin >> targetY;

  if (verifyEnemy(targetX, targetY, target_id, tabGrid) == 1)
  {
    for (int i = 0; i < target->nb_unite_active; i++)
    {
      if (target->infantry_list[i].x == targetX && target->infantry_list[i].y == targetY)
      {
        damage = attacker->infantry_list[attacker_id - 1].pv * attacker->infantry_list[attacker_id - 1].force;
        updatePV = target->infantry_list[i].pv - damage;
        target->infantry_list[i].pv = updatePV;
        if (updatePV > 0)
        {
          cout << "L'unité ennemie a été touchée." << endl;
          cout << "PV de l'unité ennemie après l'attaque : " << target->infantry_list[i].pv << endl;
        }
        else
        {
          target->infantry_list[i].isAlive = false;
          cout << "L'unité ennemie a été détruite." << endl;
          cout << target->infantry_list[i].isAlive << endl;
        }
      }
    }
  }
  else
  {
    cout << "Attaque impossible. Attention, vous devez cibler une position ennemie et ne pas attaquer vos propres unités. Essayez encore." << endl;
    attackEnemy(attacker, target, attacker_id, target_id, tabGrid);
  }
}
