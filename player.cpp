#include <iostream>
using namespace std;
#include "infantry.h"
#include "player.h"
#define X_DIMENSION 10
#define Y_DIMENSION 10

//Initialisation des paramètres
void initPlayer(player *player, int id,int nb_unite_active){
  player -> id = id;
  //player -> user_name[10] = user_name;
  player -> nb_unite_active = nb_unite_active;
  player -> isAlive = true;
  for(int i=0; i <nb_unite_active;i++){
    initInfantry(player -> infantry_list+i,id,100,50,7);
  }
}

//Affichage des infos si besoin
void printPlayer(player playerToPrint){
  cout << "Id " << playerToPrint.id << endl;
  cout << "Nb d'unités " << playerToPrint.nb_unite_active << endl;
  cout << "Is player alive : " << playerToPrint.isAlive << endl;
  for(int i=0; i <playerToPrint.nb_unite_active;i++){
    printInfantryinfos(playerToPrint.infantry_list[i]);
  }

}

//Verification de l'état des infantry_list
void check_if_isAlive(player *playerToCheck){
  if(playerToCheck -> nb_unite_active == 0 ){
    playerToCheck -> isAlive=false;
  }
}

void changeCoordinates(int *x, int *y){
  cout << "Saisissez la coordonnée X : " ;
  cin >> *x;
  cout << "Saisissez la coordonnée Y : ";
  cin >> *y;
}

//Placement des unités au début de la game
void placeUnits(player *player){
  for(int i=0; i<player -> nb_unite_active;i++){
    cout << "____________________________________________________" << endl;
    cout << "Joueur " << player -> id << ",placez vos unités" << endl;
    cout << "Entrez les coordonnées initales pour l'unité : " << i+1 << endl;
    changeCoordinates(&(player -> infantry_list[i].x),&(player -> infantry_list[i].y));
  }
}

//Fonction pour vérifier si le déplacement est valide
bool verifyCoordinates(infantry *infantry, int newX, int newY,int tabGrid[]){
  int currentX = infantry -> x;
  int currentY = infantry -> y;
  cout << " Calcul depl : " << abs(currentX-newX)+abs(currentY-newY) << endl;
  cout << " dexterity : " << infantry -> dexterity<< endl;
  if(abs(currentX-newX)+abs(currentY-newY) <= infantry -> dexterity && tabGrid[newX*X_DIMENSION+newY]==0){
    return true;
  }
  else{
    return false;
  }
}

void moveUnit(player *player, int unit_id, int tabGrid[]){
   // int currentX = player -> infantry_list[unit_id-1].x;
   // int currentY = player -> infantry_list[unit_id-1].y;
   int newX ;
   int newY ;

   cout << "Entrez la nouvelle coordonnée X : ";
   cin >> newX;
   cout << "Entrez la nouvelle coordonnée Y : ";
   cin >> newY;

   if(verifyCoordinates(&(player -> infantry_list[unit_id-1]),newX,newY,tabGrid)==1){
     player -> infantry_list[unit_id-1].x = newX;
     player -> infantry_list[unit_id-1].y = newY;

  }
   else{
    cout << "Ce déplacement est impossible" << endl;
     moveUnit(player,unit_id, tabGrid);
   }
}
