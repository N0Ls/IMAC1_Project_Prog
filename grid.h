#ifndef DISPLAY_H
#define DISPLAY_H

void initGrid(int *tabGrid);
void updateGrid(int *tabGrid, int nbPlayers, player tabPlayers[], bonus *tabBonus);
void drawGrid(int tabGrid[]);

#endif
