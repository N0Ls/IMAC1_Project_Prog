#include <iostream>
using namespace std;
#include <string.h>
#include "infantry.h"
#include "player.h"
#include "bonus.h"

/**
 *
 * Initialize infantry atttributes.
 *
 * @param inf The infantry to initialize.
 * @param id The id of the player that owns the infantry.
 * @param pv The number of health points of the infantry.
 * @param force The force of the infantry (its fire power).
 * @param dexterity The dexterity of the infantry (its mobility on the map).
 * @param fireRange The range of the attack of the infantry (its mobility on the map).
 * @param arrayIndex The index of the infantry inside the infantries array of the player.
 * @param type The name of the type of the infantry.
 *
 */
void initInfantry(infantry *inf, int id,float pv,float force,float dexterity, float fireRange, int arrayIndex){
  inf -> ownerId = id;
  inf -> pv = pv;
  inf -> force = force;
  inf -> dexterity = dexterity;
  inf -> fireRange = fireRange;
  inf -> isAlive = true;
  inf -> arrayIndex = arrayIndex;
}

/**
 *
 * Display infantry information.
 *
 * @param inf The infantry to display.
 *
 */
void printInfantryInfos(infantry inf){
  cout << "Appartient au joueur " << inf.ownerId << endl;
  cout << "PV :  " << inf.pv << endl;
  cout << "Force : " << inf.force << endl;
  cout << "Dextérité : " << inf.dexterity << endl;
  cout << "X : " << inf.x << endl;
  cout << "Y : " << inf.y << endl;
}

/**
 *
 * Display infantry information (in line).
 *
 * @param inf The infantry to display.
 *
 */
void printInfantryInline(infantry inf){
  cout << " (" << inf.x <<","<< inf.y << ") | " << "HP : "<< inf.pv << " | Dexterity : " << inf.dexterity <<" | Fire Range : "  << inf.fireRange << endl;
}
