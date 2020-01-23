#include <iostream>
using namespace std;
#include "infantry.h"
#include "player.h"
#include "display.h"
#include "bonus.h"
#define X_DIMENSION 10
#define Y_DIMENSION 10
#define BONUS_MAX 3


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
void updateGrid(int *tabGrid, int nb_joueurs, player tabPlayer[], bonus *tabBonus)
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
  //Bonus may be appearing
  probBonusArray(tabBonus, tabGrid);
  for(int v = 0; v < BONUS_MAX ; v++){
    if(tabBonus[v].isActive==true){
      tabGrid[tabBonus[v].y * X_DIMENSION + tabBonus[v].x ]=-1;
    }
  }
}

//Fonction pour initialiser le jeu
void initGame(int *tabGrid, player *tabPlayer, int *nb_joueurs, bool *playCondition, bonus *bonusArray)
{
  //Demande le nombre de joueur
  cout << "Entrez le nombre de joueurs (2 minimum et 3 maximum) : ";
  cin >> *nb_joueurs;
  while (1)
  {
    if (cin.fail() || *nb_joueurs < 2 || *nb_joueurs > 3)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << "Vous ne pouvez pas joueur seul et le nombre maximum de joueurs autorisé est 3." << endl;
      cout << "Entrez le nombre de joueurs (2 minimum et 3 maximum) : ";
      cin >> *nb_joueurs;
    }
    if (!(cin.fail() || *nb_joueurs < 2  || *nb_joueurs > 3))
      break;
  }

  //Demande le nombre d'unité par joueur
  int nb_unite, max_unites = 0;
  if (*nb_joueurs == 2){
    max_unites = 9;
  } else if (*nb_joueurs == 3) {
    max_unites = 6;
  }
  cout << "Entrez le nombre d'unités par joueur (" << max_unites << " unités maximum) : ";
  cin >> nb_unite;
  while (1)
  {
    if (cin.fail() || nb_unite < 1 || nb_unite > max_unites)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << "Veuillez respecter le nombre maximal d'unités autorisé par joueur." << endl;
      cout << "Entrez le nombre d'unités par joueur (" << max_unites << " unités maximum) : ";
      cin >> nb_unite;
    }
    if (!(cin.fail() || nb_unite < 1  || nb_unite > max_unites))
      break;
  }

  //Initialisation des joueurs
  for (int i = 0; i < *nb_joueurs; i++)
  {
    initPlayer(tabPlayer + i, i + 1, nb_unite);
  }

  //Initialisation de la grille
  initGrid(tabGrid);

  //initialisation des bonus
  for(int indexAB = 0; indexAB < 3; indexAB++){
    initBonus(bonusArray + indexAB);
  }

  //Début du jeu
  *playCondition = true;

  //Placement des troupes
  for (int i = 0; i < *nb_joueurs; i++)
  {
    placeUnits(tabGrid, tabPlayer + i);
    updateGrid(tabGrid, *nb_joueurs, tabPlayer, bonusArray);
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
  while (1)
  {
    if (cin.fail() || *tour_choice > 2 || *tour_choice < 1)
    {
      cin.clear();
      cin.ignore(123, '\n');
      cout << "Vous ne pouvez que vous déplacez (1) ou attaquer (2)." << endl;
      cout << "Votre choix (1/2 ?) : ";
      cin >> *tour_choice;
    }
    if (!(cin.fail() || *tour_choice > 2 || *tour_choice < 1))
      break;
  }
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

void play_tour(int *current_player_index, int move_number, player tabPlayer[], int nb_joueurs, int *tour_choice, int tabGrid[], bonus bonusArray[])
{
  printBonusarray(bonusArray);
  infantry selectedUnit;
  if (tabPlayer[*current_player_index].isAlive == 1)
  {
    for (int i = 0; i < move_number; i++)
    {
      cout << "----------" << endl;
      if (i > 0)
      {
        cout << "Joueur " << *current_player_index + 1 << ", c'est de nouveau votre tour !" << endl;
      }
      else
      {
        cout << "Joueur " << *current_player_index + 1 << ", c'est votre tour !" << endl;
      }
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
        moveUnit(&tabPlayer[*current_player_index], 1, tabGrid, bonusArray);
        break;
      case 2: //Attacque
        attackEnemy(&selectedUnit, tabPlayer, nb_joueurs, tabGrid);
        break;
      }

      updateGrid(tabGrid, nb_joueurs, tabPlayer, bonusArray);
      drawGrid(tabGrid);
    }
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


int main(int argc, char const *argv[])
{
  srand(time(NULL));

  int choice = 0;
  int choice_tour = 0;
  int move_number = 2;
  int nb_joueurs;
  bool isPlaying = false;
  player tabPlayer[10];
  int tableauGrid[X_DIMENSION * Y_DIMENSION];
  int current_player = 0;
  int winner;
  bonus tabBonus[BONUS_MAX];

  menu(&choice);
  switch (choice)
  {
  case 1:
    initGame(tableauGrid, tabPlayer, &nb_joueurs, &isPlaying, tabBonus);
    while (isPlaying)
    {
      play_tour(&current_player, move_number, tabPlayer, nb_joueurs, &choice_tour, tableauGrid, tabBonus);
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
