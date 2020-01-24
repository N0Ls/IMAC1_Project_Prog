#ifndef PLAYER_H
#define PLAYER_H

#include "bonus.h"

typedef struct {
    int id;
    int nbActiveUnits;
    infantry infantriesList[255];
    bool isAlive;
    char color[10];
} player;

void initPlayer(player *player, int id, int nbActiveUnits);
void printPlayer(player playerToPrint);
void changeCoordinates(int *x, int *y);
void placeUnits(int *tabGrid, player *player);
infantry selectUnit(player *player);
int checkPlayerCoordinatesEntry(int *entry, string message, string errorMessage);
bool verifyCoordinates(infantry *infantry, int newX, int newY, int tabGrid[]);
bool verifyEnemy(int targetX, int targetY, int attackerId, int tabGrid[]);
void applyDamageZone(int targetX, int targetY, int attackerId, int damage, int nbPlayers, int tabGrid[], player *tabPlayers);
int calculDamage(infantry *attackerUnit, int targetX, int targetY);
void moveUnit(player *player, int unitId, int tabGrid[], bonus *tabBonus);
void attackEnemy(infantry *selectedUnit, player *tabPlayers, int nbPlayers, int tabGrid[]);
void checkIfIsAlive(player *playerToCheck);
#endif
