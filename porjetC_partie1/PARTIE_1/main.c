#include <math.h>
#include <stdio.h>
#include "list.h"


int main() {
    int nb_level;
    t_d_list list;

    //initialisation de la liste
    printf("Choisissez le nombre de niveau de la liste : ");
    scanf("%d", &nb_level);
    printf("\n");

    //saisi scuriser
    while (nb_level < 1) {
        printf("Le nombre de niveau doit être supérieur à 0 : ");
        scanf("%d", &nb_level);
    }

    //creation liste vide
    list = CreateEmptyList(nb_level);
    list.max_cell = (pow(2, nb_level) - 1);
    printf("\n");

    displayList(list, nb_level - 1); //affichage de liste vide

    //insertion val
    char i;
    printf("Voulez-vous inserez une valeur (o/n) : ");
    scanf(" %c", &i);
    printf("\n");
    int val;
    int lev;
    while(i == 'o'){
        printf("Choisissez une valeur à inserer et le nombre de niveau : ");
        scanf("%d %d", &val, &lev);
        printf("\n");
        insertList(&list, val, lev);
        printf("Voulez-vous inserez une autre valeur (o/n) : ");
        scanf(" %c", &i);
        printf("\n");
    }

    //affichage de la liste final
    displayList(list, nb_level-1);


    return 0;
}