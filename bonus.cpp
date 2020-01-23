#include <iostream>
#include <stdlib.h>
using namespace std;
#include "infantry.h"
#include "player.h"


#define X_DIMENSION 10
#define Y_DIMENSION 10
#define BONUS_MAX 3

/*******************************************************************************/
/*Functions to pick random numbers*/
float rand_cent(){
  return (rand()%101);
}

int rand_int_x(){
  return (rand()%X_DIMENSION);
}
int rand_int_y(){
  return (rand()%Y_DIMENSION);
}

/*******************************************************************************/
/*
* Initialize bonus attributes
* @param bonus The bonus to initialize.
*/
void initBonus(bonus *bonus){

  /* different types of bonuses
  h=health ; f=force ; d=dexterity */
  char bonusTypes[3]={'h','f','d'};
  bonus -> isActive = false;
  bonus -> x = rand_int_x();
  bonus -> y = rand_int_y();
  bonus -> boostType = bonusTypes[rand()%3];
}

/*******************************************************************************/
/*
* Using the probabilities to make the bonus active
* @param bonusArray the array of bonuses.
* @param tabGrid the grid array.
*/
void probBonusArray(bonus *bonusArray, int *tabGrid){
  int tirage;
  for(int indexB = 0; indexB < 3 ; indexB++){
    tirage = rand_cent();
    if(tirage <= 5 && tabGrid[bonusArray[indexB].y * X_DIMENSION + bonusArray[indexB].x] == 0 ){
      bonusArray[indexB].isActive = true;
    }
  }
}

/*******************************************************************************/
void bonusTreatment(infantry *infantry, bonus *bonus){
  if(infantry -> x == bonus -> x && infantry -> y == bonus -> y && bonus -> isActive == true){
    if(bonus -> boostType == 'h'){
        infantry -> pv += 20;
        cout << " Vous venez d'obtenir un bonus de santé !" << endl;
    }
    if(bonus -> boostType == 'f'){
        infantry -> force += 20;
        cout << " Vous venez d'obtenir un bonus de force !" << endl;
    }
    if(bonus -> boostType == 'd'){
        infantry -> dexterity += 2;
        cout << " Vous venez d'obtenir un bonus de dextérité !" << endl;
    }
    bonus -> isActive = false;
    bonus -> x = rand_int_x();
    bonus -> y = rand_int_y();
  }
}

void printBonusarray(bonus bonus[]){
  for(int index = 0; index < 3 ; index++){
    cout << bonus[index].x << " ";
    cout << bonus[index].y << " ";
    cout << bonus[index].boostType << endl;
  }
}
