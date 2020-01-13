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
        cout << "\033[96m";
        cout << " 1";
        cout << "\033[37m";
        cout << " |";
      }
      if (tabGrid[X_DIMENSION * i + y] == 2)
      {
        cout << "\033[91m";
        cout << " 2";
        cout << "\033[37m";
        cout << " |";
      }
      if (tabGrid[X_DIMENSION * i + y] == 3)
      {
        cout << "\033[35m";
        cout << " 3";
        cout << "\033[37m";
        cout << " |";
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
      if (tabPlayer[k].infantry_list[i].isAlive == 1)
      {
        tabGrid[tabPlayer[k].infantry_list[i].y * X_DIMENSION + tabPlayer[k].infantry_list[i].x] = tabPlayer[k].id;
      }
    }
  }
}

//Fonction pour initialiser le jeu
void initGame(int *tabGrid, player *tabPlayer, int *nb_joueurs, bool *playCondition)
{
  //Demande le nombre de joueur
  do
  {
    if (*nb_joueurs == 1)
    {
      cout << "Vous ne pouvez pas jouer seul." << endl;
    }
    else if (*nb_joueurs > 3)
    {
      cout << "Le nombre maximum de joueurs autorisé est 3." << endl;
    }
    cout << "Entrez le nombre de joueurs (2 minimum et 3 maximum) : ";
    cin >> *nb_joueurs;
  } while (*nb_joueurs > 3 || *nb_joueurs < 2);

  //Demande le nombre d'unité par joueur
  int nb_unite;
  cout << "Entrez le nombre d'unités par joueur : ";
  cin >> nb_unite;

  //Initialisation des joueurs
  for (int i = 0; i < *nb_joueurs; i++)
  {
    if(i==0){
      initPlayer(tabPlayer + i, i + 1, nb_unite);
    }
    if(i==1){
      initPlayer(tabPlayer + i, i + 1, nb_unite);
    }
    if(i==2){
      initPlayer(tabPlayer + i, i + 1, nb_unite);
    }
  }
  //Initialisation de la grille
  initGrid(tabGrid);

  //Début du jeu
  *playCondition = true;

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

void menu_tour(int *tour_choice)
{
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

void play_tour(int *current_player_index, player tabPlayer[], int nb_joueurs, int *tour_choice, int tabGrid[])
{
  infantry selectedUnit;
  if (tabPlayer[*current_player_index].isAlive == 1)
  {
    cout << "----------" << endl;
    cout << "Joueur " << *current_player_index + 1 << " c'est votre tour !" << endl;
    for (int i = 0; i < tabPlayer[*current_player_index].nb_unite_active; i++)
    {
      cout << "Unité n°" << i + 1 << " ";
      printInfantryInline(tabPlayer[*current_player_index].infantry_list[i]);
    }
    selectedUnit = selectUnit(&(tabPlayer[*current_player_index]));
    cout << "Vous avez choisi l'unité positionnée en (" << selectedUnit.x << ", " << selectedUnit.y << "). Que souhaitez-vous faire ?" << endl;
    // Appel du menu du tour
    menu_tour(tour_choice);
    //Traitement du choix
    switch (*tour_choice)
    {
    case 1: //Déplacement
      moveUnit(&tabPlayer[*current_player_index], 1, tabGrid);
      break;
    case 2: //Attacque
      attackEnemy(&selectedUnit, tabPlayer, nb_joueurs, tabGrid);
      break;
    }

    updateGrid(tabGrid, nb_joueurs, tabPlayer);
    drawGrid(tabGrid);
  }

  if (*current_player_index >= nb_joueurs - 1)
  {
    *current_player_index = 0;
  }
  else
  {
    *current_player_index += 1;
  }
}

void verify_win(player *tabPlayer, int *nb_joueurs, bool *playCondition, int *winner)
{
  int compteur_players_alive = 0;
  for (int i = 0; i < *nb_joueurs; i++)
  {
    if (tabPlayer[i].isAlive == true)
    {
      *winner = tabPlayer[i].id;
      compteur_players_alive++;
    }
  }
  if (compteur_players_alive == 1)
  {
    *playCondition = false;
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
  int choice = 0;
  int choice_tour = 0;
  int nb_joueurs;
  bool isPlaying = false;
  player tabPlayer[10];
  int tableauGrid[X_DIMENSION * Y_DIMENSION];
  int current_player = 0;
  int winner;

  menu(&choice);
  switch (choice)
  {
  case 1:
    initGame(tableauGrid, tabPlayer, &nb_joueurs, &isPlaying);
    while (isPlaying)
    {
      play_tour(&current_player, tabPlayer, nb_joueurs, &choice_tour, tableauGrid);
      verify_win(tabPlayer, &nb_joueurs, &isPlaying, &winner);
    }
    cout << "Fin de la partie." << endl;
    cout << "Le gagnant est le joueur " << winner << " !" << endl;
    break;
  case 2:
    cout << "À bientôt !" << endl;
    exit(EXIT_FAILURE);
    break;
  }

  return 0;
}
