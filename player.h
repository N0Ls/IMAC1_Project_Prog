#ifndef PLAYER_H
#define PLAYER_H
typedef struct {
    int id;
    //char user_name[10];
    int nb_unite_active;
    infantry infantry_list[255];
    bool isAlive;
} player;

//déclaration des prototypes
void initPlayer(player *player, int id,int nb_unite_active);
void printPlayer(player playerToPrint);
void changeCoordinates(int *x, int *y);
void placeUnits(player *player);
infantry selectUnit(player *player);
bool verifyCoordinates(infantry *infantry, int newX, int newY,int tabGrid[]);
//bool verifyEnemy(int targetX, int targetY, int target_id, int tabGrid[]);
bool verifyEnemy(int targetX, int targetY, int attacker_id, int target_id, int tabGrid[]);
void moveUnit(player *player, int unit_id, int tabGrid[]);
//void attackEnemy(player *attacker, player *target, int attacker_id,int target_id, int tabGrid[]);
void attackEnemy(infantry *selectedUnit, player *tabPlayer, int nb_joueurs, int tabGrid[]);
void check_if_isAlive(player *playerToCheck);
#endif
