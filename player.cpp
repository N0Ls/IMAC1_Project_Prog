#include <iostream>
using namespace std;
#include "infantry.h"
#include "player.h"
void initPlayer(player *player, int id,int nb_unite_active){
  player -> id = id;
  //player -> user_name[10] = user_name;
  player -> nb_unite_active = nb_unite_active;
  for(int i=0; i <nb_unite_active;i++){
    initInfantry(player -> infantry_list+i,1,100,50,2);
  }
}

void printPlayer(player playerToPrint){
  cout << "Id " << playerToPrint.id << endl;
  cout << "Nb d'unités " << playerToPrint.nb_unite_active << endl;
  cout << " " <<playerToPrint.infantry_list[1].pv<< endl;
  for(int i=0; i <playerToPrint.nb_unite_active;i++){
    printInfantryinfos(playerToPrint.infantry_list[i]);
  }

}
void changeCoordinates(int *x, int *y){
  cout << "Saisissez la coordonnée X : " ;
  cin >> *x;
  cout << "Saisissez la coordonnée Y : ";
  cin >> *y;
}

void placeUnits(player *player){
  for(int i=0; i<player -> nb_unite_active;i++){
    cout << "Entrez les coordonnées initales pour l'unité : " << i+1 << endl;
    changeCoordinates(&(player -> infantry_list[i].x),&(player -> infantry_list[i].y));
  }
}

bool verifyCoordinates(infantry *infantry, int newX, int newY){
  int currentX = infantry -> x;
  int currentY = infantry -> y;

  if(abs(currentX-newX)+abs(currentY-newY) < infantry -> dexterity){
    return true;
  }
  else{
    return false;
  }
}

void moveUnit(player *player, int unit_id){
   // int currentX = player -> infantry_list[unit_id-1].x;
   // int currentY = player -> infantry_list[unit_id-1].y;
   int newX ;
   int newY ;

   cout << "Entrez la nouvelle coordonnée X : ";
   cin >> newX;
   cout << "Entrez la nouvelle coordonnée Y : ";
   cin >> newY;

   if(verifyCoordinates(&(player -> infantry_list[unit_id-1]),newX,newY)){
     player -> infantry_list[unit_id-1].x = newX;
     player -> infantry_list[unit_id-1].y = newY;
   }
   else{
     moveUnit(player,unit_id);
   }
}
