#include <iostream>
using namespace std;
#include "infantry.h

#DEFINE X_DIMENSION = 10;
#DEFINE Y_DIMENSION = 10;


void drawGrid(){
  cout << "       | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |" << endl;
  for(int i =0;i<10;i++){
    cout << "       _________________________________________" << endl;
    cout <<"  |" << i<<"|  " << "|   |   |   |   |   |   |   |   |   |   |" << endl;
  }
}


int main(int argc, char const *argv[]) {
  infantry first_unit;
  initInfantry(&first_unit,1,100,50,2);
  printInfantryinfos(first_unit);
  drawGrid();
  return 0;
}
