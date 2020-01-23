#include <iostream>
#include <stdlib.h>
using namespace std;
#include "infantry.h"
#include "player.h"
#include "display.h"
#include "bonus.h"


#define X_DIMENSION 10
#define Y_DIMENSION 10
#define BONUS_MAX 3


float rand_cent(){
  return (rand()%101);
}

int rand_int_x(){
  return (rand()%X_DIMENSION);
}
int rand_int_y(){
  return (rand()%Y_DIMENSION);
}

void initBonus(bonus *bonus){
  bonus -> isActive = false;
  bonus -> x = rand_int_x();
  bonus -> y = rand_int_y();
  bonus -> boostType = 'h';
}

void probBonusArray(bonus *bonusArray, int *tabGrid){
  int tirage;
  for(int indexB = 0; indexB < 3 ; indexB++){
    tirage = rand_cent();
    if(tirage <= 5 && tabGrid[bonusArray[indexB].y * X_DIMENSION + bonusArray[indexB].x] == 0 ){
      bonusArray[indexB].isActive = true;
    }
  }
}

void bonusTreatment(infantry *infantry, bonus *bonus){
  if(infantry -> x == bonus -> x && infantry -> y == bonus -> y && bonus -> isActive == true){
    if(bonus -> boostType == 'h'){
        infantry -> pv += 20;
        bonus -> isActive = false;
        bonus -> x = rand_int_x();
        bonus -> y = rand_int_y();
    }
  }
}

void printBonusarray(bonus bonus[]){
  for(int index = 0; index < 3 ; index++){
    cout << bonus[index].x << endl;
    cout << bonus[index].y << endl;
  }
}
