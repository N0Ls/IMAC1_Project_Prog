#include <iostream>
using namespace std;
#include "infantry.h"

void initInfantry(infantry *inf, int id,float pv,float force,float dexterity){
  inf -> owner_id = id;
  inf -> pv = pv;
  inf -> force = force;
  inf -> dexterity = dexterity;
  inf -> isAlive = true;
}

void printInfantryinfos(infantry inf){
  cout << "Appartient à " << inf.owner_id << endl;
  cout << "PV :  " << inf.pv << endl;
  cout << "Force : " << inf.force << endl;
  cout << "Dextérité : " << inf.dexterity << endl;

}
