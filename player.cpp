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
  printInfantryinfos(playerToPrint.infantry_list[1]);

}
