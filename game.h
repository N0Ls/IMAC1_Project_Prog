#ifndef GAME_H
#define GAME_H

void initGame(int *tabGrid, player *tabPlayers, int *nbPlayers, bool *playingCondition, bonus *bonusArray);
void play_tour(int *currentPlayerIndex, int moveNumber, player tabPlayers[], int nbPlayers, int *turnChoice, int tabGrid[], bonus bonusArray[]);
void verify_win(player *tabPlayers, int *nbPlayers, bool *playingCondition, int *winner);

#endif
