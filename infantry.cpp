#include <iostream>
using namespace std;
#include "infantry.h"
#include "player.h"
#include "bonus.h"
#include "display.h"

//Initialisation des paramètres
void initInfantry(infantry *inf, int id,float pv,float force,float dexterity, int arrayIndex){
  inf -> ownerId = id;
  inf -> pv = pv;
  inf -> force = force;
  inf -> dexterity = dexterity;
  inf -> isAlive = true;
  inf -> arrayIndex = arrayIndex;
}

//Fonction permettant d'imprimer les infos si besoin
void printInfantryInfos(infantry inf){
  cout << "Appartient au joueur " << inf.ownerId << endl;
  cout << "PV :  " << inf.pv << endl;
  cout << "Force : " << inf.force << endl;
  cout << "Dextérité : " << inf.dexterity << endl;
  cout << "X : " << inf.x << endl;
  cout << "Y : " << inf.y << endl;
}

void printInfantryInline(infantry inf){
  cout << "(" << inf.x <<","<< inf.y << ") | " << "PV : "<< inf.pv << endl;
}
