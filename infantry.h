#ifndef INFANTRY_H
#define INFANTRY_H

//Déclaration de la structure
typedef struct {
    int ownerId;
    float pv;
    bool isAlive;
    float force;
    int x;
    int y ;
    float dexterity;
    int arrayIndex;
} infantry;

//Déclaration des prototypes
void printInfantryInfos(infantry inf);
void initInfantry(infantry *inf, int id,float pv,float force,float dexterity,int arrayIndex);
void printInfantryInline(infantry inf);

#endif
