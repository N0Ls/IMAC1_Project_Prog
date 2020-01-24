#ifndef BONUS_H
#define BONUS_H

typedef struct {
    bool isActive;
    int x;
    int y;
    char boostType;
} bonus;

void initBonus(bonus *bonus);
float randCent();
int randIntX();
int randIntY();
void probBonusArray(bonus *bonusArray, int *tabGrid);
void printBonusArray(bonus bonus[]);
void bonusTreatment(infantry *infantry, bonus *bonus);
#endif
