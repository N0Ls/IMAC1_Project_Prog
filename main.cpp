#include <iostream>
using namespace std;
#include "infantry.h"
#include "player.h"
#define X_DIMENSION 10
#define Y_DIMENSION 10



void drawGrid(int tabGrid[]){
  cout << "      Y| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |" << endl;
    cout << "    X  _________________________________________" << endl;
    for (int i = 0; i <X_DIMENSION; i++) {
      cout <<"|   " << i<<"  |";
      for (int y = 0; y < Y_DIMENSION; y++) {

        if(tabGrid[X_DIMENSION*i+y]== 1){
          cout << " 1 |";
        }
        if(tabGrid[X_DIMENSION*i+y]== 2){
          cout << " 2 |";
        }
        if(tabGrid[X_DIMENSION*i+y]== 0){
          cout << "   |";
        }
      }
      cout << endl;
      cout << "       _________________________________________" << endl;
    }

}

void initGrid(int *tabGrid){
  for (int i = 0; i <X_DIMENSION; i++) {
    for (int y = 0; y < Y_DIMENSION; y++) {
      tabGrid[X_DIMENSION*i+y]= 0;
    }
  }
}
void updateGrid(int *tabGrid,player player){
  for(int i=0; i<player.nb_unite_active ; i++){
    tabGrid[player.infantry_list[i].x*X_DIMENSION+player.infantry_list[i].y]=player.id;
  }
}


int main(int argc, char const *argv[]) {
  int tableauGrid[X_DIMENSION * Y_DIMENSION];
  player playerTest;
  initPlayer(&playerTest,1,3);
  //changeCoordinates(&playerTest.infantry_list[0].x,&playerTest.infantry_list[0].y);
  placeUnits(&playerTest);
  printPlayer(playerTest);
  initGrid(tableauGrid);
  updateGrid(tableauGrid,playerTest);
  drawGrid(tableauGrid);
  return 0;
}
