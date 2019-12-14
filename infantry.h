#ifndef INFANTRY_H
#define INFANTRY_H
typedef struct {
    int owner_id;
    float pv;
    bool isAlive;
    float force;
    int x;
    int y ;
    float dexterity;
} infantry;
void printInfantryinfos(infantry inf);
void initInfantry(infantry *inf, int id,float pv,float force,float dexterity);

#endif
