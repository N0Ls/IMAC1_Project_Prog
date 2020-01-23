#ifndef INFANTRY_H
#define INFANTRY_H

//Declaration of the structure
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

//Declaration of prototypes
void printInfantryInfos(infantry inf);
void initInfantry(infantry *inf, int id,float pv,float force,float dexterity,int arrayIndex);
void printInfantryInline(infantry inf);

#endif
