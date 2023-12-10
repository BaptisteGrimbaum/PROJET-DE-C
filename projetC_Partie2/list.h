#ifndef PROJETC_PARTIE2_TIMER_H
#define PROJETC_PARTIE2_TIMER_H

// Déclaration des structures :


// Déclaration de la structure d'une cellule à plusieurs niveaux
typedef struct s_d_cell {
    int value; // Initialisation de la valeur que va stocker la cellule
    struct s_d_cell **next; // Initialisation d'un double pointeur next pour passer à la cellule suivante en fonction du niveau
    int nblevel; // Initialisation du nombre de niveau de la cellule
}t_d_cell, *p_cell;

// Déclaration de la structure d'une liste chainée simple à plusieurs niveaux
typedef struct s_d_list {
    t_d_cell** head; // Initialisation d'un double pointeur head pour parcourir à la tete de la liste en fonction du niveau
    int max_cell; // Initialisation du nombre de cellule max que la liste pourra stocker
} t_d_list;

t_d_cell *CreateCell(int, int);

t_d_list CreateEmptyList(int);

void insertHead(t_d_list *, int, p_cell);

int isEmptyList(t_d_list, int);

void displayList(t_d_list, int);

void DisplayAllList(t_d_list, int);

void insertList(t_d_list *, int, int);

int *createLevels(int, int);

int isInList(int, t_d_list, int);

int recherche_dicho(t_d_list, int level, int val);

#endif //PROJETC_PARTIE2_TIMER_H