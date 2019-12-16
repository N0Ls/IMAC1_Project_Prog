#include <iostream>
using namespace std;
#include "infantry.h"
#include "player.h"
#define X_DIMENSION 10
#define Y_DIMENSION 10


//Fonction d'affichage de la grille
//Pour l'instant elle est de taille fixe et ne prends en compte que 2 joueurs
void drawGrid(int tabGrid[]){
  cout << "      X| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |" << endl;
    cout << "    Y  _________________________________________" << endl;
    for (int i = 0; i <X_DIMENSION; i++) {
      cout <<"|   " << i<<"  |";
      for (int y = 0; y < Y_DIMENSION; y++) {

        if(tabGrid[X_DIMENSION*i+y]== 1){
          cout << " 1 |";
        }
        if(tabGrid[X_DIMENSION*i+y]== 2){
          cout << " 2 |";
        }
        if(tabGrid[X_DIMENSION*i+y]== 0){
          cout << "   |";
        }
      }
      cout << endl;
      cout << "       _________________________________________" << endl;
    }

}

//Fonction qui initialise le tableau grille pour le début de la partie 
void initGrid(int *tabGrid){
  for (int i = 0; i <X_DIMENSION; i++) {
    for (int y = 0; y < Y_DIMENSION; y++) {
      tabGrid[X_DIMENSION*i+y]= 0;
    }
  }
}

//Fonction qui update le contenu de la grille en fonction du placement des unités du joueurs
void updateGrid(int *tabGrid,int nb_joueurs,player tabPlayer[]){
  //Reset grid
  for (int i = 0; i <X_DIMENSION; i++) {
    for (int y = 0; y < Y_DIMENSION; y++) {
      tabGrid[X_DIMENSION*i+y]= 0;
    }
  }
  //Update for each player
  for(int k=0; k< nb_joueurs ;k++ ){
    for(int i=0; i<tabPlayer[k].nb_unite_active ; i++){
      tabGrid[tabPlayer[k].infantry_list[i].x*X_DIMENSION+tabPlayer[k].infantry_list[i].y]=tabPlayer[k].id;
    }
  }


}

//Fonction pour initialiser le jeu
void initGame(int *tabGrid, player *tabPlayer, int *nb_joueurs, bool *playCondition){

  //Demande le nombre de joueur
  cout << "Entrez le nombre de joueurs : " ;
  cin >> *nb_joueurs;

  //Demande le nombre d'unité par joueur
  int nb_unite;
  cout << "Entrez le nombre d'unités par joueur : ";
  cin >> nb_unite;

  //Initialisation des joueurs
  for(int i=0; i<*nb_joueurs ; i++){
    initPlayer(tabPlayer+i, i+1,nb_unite);
  }

  //Initialisation de la grille
  initGrid(tabGrid);
}


int main(int argc, char const *argv[]) {
  //variables de jeu
  //--------------------------------------------------------
  bool isPlaying = false;

  player tabPlayer[10];

  int nb_joueurs;

  int tableauGrid[X_DIMENSION * Y_DIMENSION];
  //--------------------------------------------------------

  // ---ZONE DE TEST --- //
  initGame(tableauGrid,tabPlayer,&nb_joueurs,&isPlaying);
  for(int i=0; i<nb_joueurs ; i++){
    placeUnits(tabPlayer+i);
/*    tabPlayer[0].infantry_list[0].x=1;
    tabPlayer[0].infantry_list[0].y=1;*/
    updateGrid(tableauGrid,nb_joueurs,tabPlayer);
  }


  moveUnit(&tabPlayer[0],1,tableauGrid);

  // cout << verifyCoordinates(&(tabPlayer -> infantry_list[0]),0,0,tableauGrid) << endl;
  updateGrid(tableauGrid,nb_joueurs,tabPlayer);
  drawGrid(tableauGrid);
  return 0;
}
