#ifndef INFANTRY_H
#define INFANTRY_H

//Déclaration de la structure
typedef struct {
    int owner_id;
    float pv;
    bool isAlive;
    float force;
    int x;
    int y ;
    float dexterity;
} infantry;

//Déclaration des prototypes
void printInfantryinfos(infantry inf);
void initInfantry(infantry *inf, int id,float pv,float force,float dexterity);
void printInfantryInline(infantry inf);

#endif
