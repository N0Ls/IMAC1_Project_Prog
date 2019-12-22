#include <iostream>
using namespace std;
#include "infantry.h"
#include "player.h"
#define X_DIMENSION 10
#define Y_DIMENSION 10

//Fonction d'affichage de la grille
//Pour l'instant elle est de taille fixe et ne prends en compte que 2 joueurs
void drawGrid(int tabGrid[])
{
  cout << "      X| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |" << endl;
  cout << "    Y  _________________________________________" << endl;
  for (int i = 0; i < X_DIMENSION; i++)
  {
    cout << "|   " << i << "  |";
    for (int y = 0; y < Y_DIMENSION; y++)
    {

      if (tabGrid[X_DIMENSION * i + y] == 1)
      {
        cout << " 1 |";
      }
      if (tabGrid[X_DIMENSION * i + y] == 2)
      {
        cout << " 2 |";
      }
      if (tabGrid[X_DIMENSION * i + y] == 0)
      {
        cout << "   |";
      }
    }
    cout << endl;
    cout << "       _________________________________________" << endl;
  }
}

//Fonction qui initialise le tableau grille pour le début de la partie
void initGrid(int *tabGrid)
{
  for (int i = 0; i < X_DIMENSION; i++)
  {
    for (int y = 0; y < Y_DIMENSION; y++)
    {
      tabGrid[X_DIMENSION * i + y] = 0;
    }
  }
}

//Fonction qui update le contenu de la grille en fonction du placement des unités du joueurs
void updateGrid(int *tabGrid, int nb_joueurs, player tabPlayer[])
{
  //Reset grid
  for (int i = 0; i < X_DIMENSION; i++)
  {
    for (int y = 0; y < Y_DIMENSION; y++)
    {
      tabGrid[X_DIMENSION * i + y] = 0;
    }
  }
  //Update for each player
  for (int k = 0; k < nb_joueurs; k++)
  {
    for (int i = 0; i < tabPlayer[k].nb_unite_active; i++)
    {
      if(tabPlayer[k].infantry_list[i].isAlive == 1) {
        tabGrid[tabPlayer[k].infantry_list[i].x * X_DIMENSION + tabPlayer[k].infantry_list[i].y] = tabPlayer[k].id;
      }
    }
  }
}

//Fonction pour initialiser le jeu
void initGame(int *tabGrid, player *tabPlayer, int *nb_joueurs, bool *playCondition)
{

  //Demande le nombre de joueur
  cout << "Entrez le nombre de joueurs : ";
  cin >> *nb_joueurs;

  //Demande le nombre d'unité par joueur
  int nb_unite;
  cout << "Entrez le nombre d'unités par joueur : ";
  cin >> nb_unite;

  //Initialisation des joueurs
  for (int i = 0; i < *nb_joueurs; i++)
  {
    initPlayer(tabPlayer + i, i + 1, nb_unite);
  }
  //Initialisation de la grille
  initGrid(tabGrid);

  //Début du jeu
  *playCondition=true;

  //Dessin de la grille
  drawGrid(tabGrid);

  //Placement des troupes
  for (int i = 0; i < *nb_joueurs; i++)
  {
    placeUnits(tabPlayer + i);
    updateGrid(tabGrid, *nb_joueurs, tabPlayer);
  }

  //Dessin après le placement
  drawGrid(tabGrid);
}

void menu_tour(int *tour_choice){
  cout << "\n";
  cout << "1. Se déplacer"
       << "\n";
  cout << "2. Attaquer"
       << "\n\n";
  cout << "Votre choix (1/2 ?) : ";
  cin >> *tour_choice;
  cout << endl;
}

//Possiblement inutile
// void printing_all_infantries(player tabPlayer[],int nb_joueurs){
//   for (int i = 0; i < nb_joueurs ; i++) {
//     for (int y = 0; y < tabPlayer[i].nb_unite_active; y++) {
//       printInfantryInline(tabPlayer[i].infantry_list[y]);
//     }
//   }
// }

void play_tour(int *current_player_index , player tabPlayer[], int nb_joueurs, int *tour_choice){
  cout << "----------" << endl;
  cout << "Joueur " << *current_player_index+1 << " c'est votre tour !" << endl;
  for (int i = 0; i < tabPlayer[*current_player_index].nb_unite_active; i++) {
    cout << "Unité n°" << i ;
    printInfantryInline(tabPlayer[*current_player_index].infantry_list[i]);
  }
  //appel du menu du tour
  menu_tour(tour_choice);
  //traitement du choix
  //déplacement
  if(*tour_choice==1){
    //ajouter le menu de selection de l'unité à déplacer
    //moveUnit(&tabPlayer[*current_player_index], 1, tableauGrid);
  }
  if(*tour_choice==2){

  }

  if(*current_player_index >= nb_joueurs ){
    *current_player_index=0;
  }
  else{*current_player_index+=1;}
}


void verify_win(player *tabPlayer, int *nb_joueurs,bool *playCondition){
  int compteur_players_alive = 0;
  for(int i= 0 ; i < *nb_joueurs ; i++){
    if (tabPlayer[i].isAlive == true) {
      compteur_players_alive++;
    }
  }
  if(compteur_players_alive >1){
    *playCondition=false;
  }
  else{
    *playCondition=true;
  }
}

void printLogo(void)
{
  cout << "=========================================\n";
  cout << " ██╗███╗   ███╗ █████╗  ██████╗\n";
  cout << " ██║████╗ ████║██╔══██╗██╔════╝\n";
  cout << " ██║██╔████╔██║███████║██║\n";
  cout << " ██║██║╚██╔╝██║██╔══██║██║\n";
  cout << " ██║██║ ╚═╝ ██║██║  ██║╚██████╗\n";
  cout << " ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝ ╚═════╝\n\n";
  cout << "      ██╗    ██╗ █████╗ ██████╗ ███████╗\n";
  cout << "      ██║    ██║██╔══██╗██╔══██╗██╔════╝\n";
  cout << "      ██║ █╗ ██║███████║██████╔╝███████╗\n";
  cout << "      ██║███╗██║██╔══██║██╔══██╗╚════██║\n";
  cout << "      ╚███╔███╔╝██║  ██║██║  ██║███████║\n";
  cout << "       ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝\n";
  cout << "=========================================\n\n";
}

void menu(int *c)
{
  cout << "\n";
  printLogo();
  cout << "1. Commencer une partie"
       << "\n";
  cout << "2. Quitter la partie"
       << "\n\n";
  cout << "Votre choix (1/2 ?) : ";
  cin >> *c;
  cout << endl;
}

int main(int argc, char const *argv[])
{
  //--------------------------------------------------------
  int choice = 0;
  int choice_tour = 0 ;
  //variables de jeu
  //--------------------------------------------------------
  bool isPlaying = false;

  player tabPlayer[10];

  int nb_joueurs;

  int tableauGrid[X_DIMENSION * Y_DIMENSION];

  int current_player = 0;
  //--------------------------------------------------------

  menu(&choice);
    switch (choice)
    {
    case 1:
      // --- INITIALISATION DU JEU --- //
      initGame(tableauGrid, tabPlayer, &nb_joueurs, &isPlaying);

      // ---ZONE DE TEST --- //


      //moveUnit(&tabPlayer[0], 1, tableauGrid);

      attackEnemy(&tabPlayer[0], &tabPlayer[1], 1, 2, tableauGrid);

      //cout << verifyCoordinates(&(tabPlayer -> infantry_list[0]),0,0,tableauGrid) << endl;
      updateGrid(tableauGrid, nb_joueurs, tabPlayer);
      drawGrid(tableauGrid);
      break;
    case 2:
      cout << "À bientôt !" << endl;
      exit(EXIT_FAILURE);
      break;
    }


  return 0;
}
