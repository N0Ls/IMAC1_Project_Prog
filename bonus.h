#ifndef BONUS_H
#define BONUS_H

//Déclaration de la structure
typedef struct {
    bool isActive;
    int x;
    int y;
    char boostType;
} bonus;

void initBonus(bonus *bonus);
float rand_cent();
void probBonusArray(bonus *bonusArray, int *tabGrid);
void printBonusarray(bonus bonus[]);
void bonusTreatment(infantry *infantry, bonus *bonus);
#endif
