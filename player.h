#ifndef PLAYER_H
#define PLAYER_H
typedef struct {
    int id;
    //char user_name[10];
    int nb_unite_active;
    infantry infantry_list[255];
} player;
void initPlayer(player *player, int id,int nb_unite_active);
void printPlayer(player playerToPrint);
#endif
