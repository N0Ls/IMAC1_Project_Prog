#include <iostream>
#include <stdlib.h>
using namespace std;
#include "infantry.h"
#include "player.h"
#include "display.h"
#include "bonus.h"


#define X_DIMENSION 10
#define Y_DIMENSION 10
void initBonus(bonus *bonus){
  bonus -> isActive = false;
  bonus -> x = rand() % X_DIMENSION +1;
  bonus -> y = rand() % Y_DIMENSION +1;
  bonus -> boostType = 'r';
}
