#include <iostream>
using namespace std;
#include "infantry.h"
#include "player.h"

//Initialisation des paramètres
void initInfantry(infantry *inf, int id,float pv,float force,float dexterity){
  inf -> owner_id = id;
  inf -> pv = pv;
  inf -> force = force;
  inf -> dexterity = dexterity;
  inf -> isAlive = true;
}

//Fonction permettant d'imprimer les infos si besoin
void printInfantryinfos(infantry inf){
  cout << "Appartient à " << inf.owner_id << endl;
  cout << "PV :  " << inf.pv << endl;
  cout << "Force : " << inf.force << endl;
  cout << "Dextérité : " << inf.dexterity << endl;
  cout << "X : " << inf.x << endl;
  cout << "Y : " << inf.y << endl;
}

void printInfantryInline(infantry inf){
  cout << "(" << inf.x <<","<< inf.y << ") | " << "PV : "<< inf.pv << endl;
}
