#include "list.h"
#include "timer.h"

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

  // Partie 2 :
  printf("----------------------- PARTIE 2 -----------------------");
  printf("\n\n");


  int nb_level, i = 0; // Initialisateur d'un entier et d'un compteur
  t_d_list list; // Initialisation d'une liste de type liste chainée simple
  int *levels; // Initialisation d'un pointeur d'entier

  printf("Choisissez le nombre de niveau : "); // Demande à l'utilisateur d'insérer le nombre de niveau souhaités
  scanf("%d", &nb_level);
  while (nb_level < 1) {
    printf("Le nombre de niveau doit etre superieur à 0 : "); // Saisie sécurisée
    scanf("%d", &nb_level);
  }
  list = CreateEmptyList(nb_level); // Création d'une liste vide avec le nombre de niveau choisis par l'utilisateur
  list.max_cell = (pow(2, nb_level) - 1); // Calcul du nombre de cellule max pour la liste

  levels = createLevels(nb_level, list.max_cell); // Création du tableau levels, ajoutant 1 une fois sur 2, puis 1 une fois sur 4, etc...

  for (i = 0; i < list.max_cell; i++) {
    insertList(&list, i + 1, levels[i] + 1); // Insértion des valeurs dans l'ordre croissant dans la liste aux niveaux indiquées par le tableau Levels
    }

  printf("\n");

    int afficherliste=-1;
    while(afficherliste != 0 && afficherliste != 1){ // Saisie sécurisée
        printf("Voulez-vous afficher votre liste ? (0 : non ; 1 : oui) : ");
        scanf("%d",&afficherliste);
        if(afficherliste==1){
            printf("\n");
            DisplayAllList(list, nb_level); // Affichage de la liste comme demandée
        }
    }

    printf("\n");

  int val;
  printf("Choisissez une valeur a rechercher : "); // Choix de la valeur à rechercher dans la liste
  scanf("%d", &val);

  // RECHERCHE AU NIVEAU 0 UNIQUEMENT :
  if (isInList(val, list, 0) == 1) {
    printf("\nLa valeur %d est dans la liste.\n", val);
  } else {
    printf("\nLa valeur %d n'est pas dans la liste.\n", val);
  }

  // RECHERCHE DICHOTOMIQUE :
  if(recherche_dicho(list, nb_level,val)==1)
    printf("\nLa valeur %d est dans la liste par recherche dichotomique.\n", val);
  else
    printf("\nLa valeur %d n'est pas dans la liste par recherche dichotomique.\n", val);

  printf("\n\n");

/// TIMER

    int rechercher = -1;
    while(rechercher != 0 && rechercher != 1){ // Saisie sécurisée
        printf("Voulez-vous ccomparer le temps de recherche pour 1000, 10 000 et 100 000 valeurs entre la recherche au niveau 0 et celle dichotomique ? (0 : non ; 1 : oui) ");
        scanf("%d",&rechercher); // Choix de l'utilisateur
        printf("\n\n");
    }
    if(rechercher == 1){
        srand(time); // Initialiser le seed du random
        printf("Temps de recherche pour la recherche au niveau 0 :\n\n");
        for(int n = 1000; n <= 100000; n *= 10){ // Boucle pour multiplier n de 10 pour vérifier 1000, 10 000 et 100 000 valeurs
            printf("-Pour %d valeurs : ", n);
            int random_nb; // Déclaration de la variable qui va stocker les valeurs aléatoire à rechercher dans la liste
            startTimer(); // Lancement du chronometre
            for(int k = 0; k < n; k++){
                random_nb = rand()%((int)pow(2,n)-1); // Choix aléatoire d'une valeur se situant dans la liste
                isInList(random_nb, list, 0); // Recherche de la valeur dans la liste par le niveau 0
            }
            stopTimer(); // Arret du chronometre
            displayTime(); // Affichage du temps mesuré
            printf("\n");
        }

        printf("------------------------------------------------------\n\n");

        printf("Temps de recherche pour la recherche dichotomique :\n\n");
        for(int n = 1000; n <= 100000; n *= 10){ // Boucle pour multiplier n de 10 pour vérifier 1000, 10 000 et 100 000 valeurs
            printf("-Pour %d valeurs : ", n);
            int random_nb; // Déclaration de la variable qui va stocker les valeurs aléatoire à rechercher dans la liste
            startTimer(); // Lancement du chronometre
            for(int k = 0; k < n; k++){
                random_nb = rand()%((int)pow(2,n)-1); // Choix aléatoire d'une valeur se situant dans la liste
                recherche_dicho(list, nb_level,random_nb); // Recherche de la valeur dans la liste par dichotomie
            }
            stopTimer(); // Arret du chronometre
            displayTime(); // Affichage du temps mesuré
            printf("\n");
        }
    }

  return 0;
}