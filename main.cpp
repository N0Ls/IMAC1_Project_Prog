#include <iostream>
using namespace std;
#include "infantry.h"
#include "player.h"
#define X_DIMENSION 10
#define Y_DIMENSION 10



void drawGrid(){
  cout << "       | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |" << endl;
  for(int i =0;i<10;i++){
    cout << "       _________________________________________" << endl;
    cout <<"  |" << i<<"|  " << "|   |   |   |   |   |   |   |   |   |   |" << endl;
  }
}

void initGrid(int *tabGrid){
  for (int i = 0; i <X_DIMENSION; i++) {
    for (int y = 0; y < Y_DIMENSION; y++) {
      tabGrid[X_DIMENSION*i+y]= 0;
    }
  }
}
// void updateGrid(int *tabGrid,){
//   for()
// }


int main(int argc, char const *argv[]) {
  int tableauGrid[X_DIMENSION * Y_DIMENSION];
  player playerTest;

  initPlayer(&playerTest,1,3);
  printPlayer(playerTest);

  initGrid(tableauGrid);
  drawGrid();
  return 0;
}
