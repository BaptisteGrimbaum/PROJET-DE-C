#include "list.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

t_d_cell *CreateCell(int val, int level) { // Création d'une nouvelle cellule avec une valeur et un niveau donnés
  p_cell new_cell = malloc(sizeof(t_d_cell)); // Allocation dynamique d'une nouvelle cellule
  if (new_cell == NULL) {
    return NULL; // Retourne NULL en cas d'échec de l'allocation
  }
  new_cell->value = val; // Initialise la valeur de la cellule
  new_cell->next = malloc(sizeof(t_d_cell *) * level); // Allocation dynamique des niveaux d'une nouvelle cellule
  if (new_cell->next == NULL) {
    free(new_cell); // Retourne NULL en cas d'échec de l'allocation des niveaux
    return NULL;
  }
  for (int i = 0; i < level; i++) {
    new_cell->next[i] = NULL; // Initialise chaque niveau suivant à NULL
  }
  new_cell->nblevel = level; // Initialise le nombre de niveaux de la cellule
  return new_cell;
}

t_d_list CreateEmptyList(int level) { // Création d'une liste vide à niveau
  t_d_list new_list;
  new_list.head = malloc(sizeof(t_d_list) * level); // Alloue dynamiquement les niveaux de la liste
  for (int i = 0; i < level; i++) {
    new_list.head[i] = NULL; // Initialise chaque tete de chaque niveau de la liste à NULL
  }
  return new_list;
}

void insertHead(t_d_list *list, int i, p_cell new_cell) { // Insertion d'une cellule par la tete dans une liste
  new_cell->next[i] = list->head[i];
  list->head[i] = new_cell;
}

void insertList(t_d_list *list, int val, int level) { // Insertion d'une cellule dans la liste en respectant l'odre croissant
  p_cell new_cell = CreateCell(val, level); // Création d'une nouvelle cellule
  for (int i = 0; i < level; i++) {
    if (isEmptyList(*list, i) == 1) { // insertion tete de liste
      insertHead(list, i, new_cell);
    } else if ((isEmptyList(*list, i) == 0) && (list->head[i]->value >= val)) {
      insertHead(list, i, new_cell);
    } else if (isEmptyList(*list, i) == 0) { // insertion milieu de liste
      p_cell temp = list->head[i];
      p_cell prev;
      while (temp != NULL && temp->value <= val) { // Parcourt de la liste jusqu'à trouver le bon emplacement
        prev = temp;
        temp = temp->next[i];
      }
      prev->next[i] = new_cell;
      new_cell->next[i] = temp;
    }
  }
  return;
}

int isEmptyList(t_d_list list, int level) { // Vérification pour savoir si la liste est vide ou non
  if (list.head[level] == NULL) {
    return 1;
  }
  return 0;
}

void displayList(t_d_list list, int level){ // Affichage de la liste au niveau 0
  for (int i = 0; i <= level; i++) {
    printf("[list head_%d @-] ---->", i);
    if (isEmptyList(list, i) == 0) {
      p_cell p_cell_tmp = list.head[i];
      while (p_cell_tmp != NULL) {
        printf("[ %d|@-]----->", p_cell_tmp->value);
        p_cell_tmp = p_cell_tmp->next[i];
      }
    }
    printf(" NULL\n");
  }
  return;
}

void DisplayAllList(t_d_list list, int level) { // Affichage de la liste à partir du niveau 1, cette fonction permet d'alligner correctement les valeurs de la liste sur les différents niveaux
  displayList(list, 0);
    for (int i = 1; i < level ; i++) {
      p_cell curr = list.head[0];
      p_cell curr_level = list.head[i];
      printf("[list head_%d @-] ", i);
      while (curr != NULL) {
        if (curr_level != NULL && curr->value == curr_level->value) {
          printf("---> [ %d|@-] ", curr_level->value);
          curr_level = curr_level->next[i];
        }
        else {
          printf("-------------");
        }
        curr = curr->next[0];
      }
            printf("----> NULL\n");
    }
  return;
}

int* createLevels(int nb_level, int max_cell) { // Création du tableau Levels stockant les niveaux auxquelles les valeurs doivent etre envoyées
  int i, j = 0;
  int* levels = malloc(max_cell * sizeof(int));

  for (j = 0; j < nb_level; j++) {
    for (i = (pow(2, j) - 1); i < max_cell; i += (pow(2, j))) { // Iniatialise i à l'indice de son niveau - 1 et l'incrémente de son niveau (sauf pour le niveau 0 où i commencera à l'indice i avec une incrémentation de 1)
      levels[i] = j;
    }
  }
  return levels;
}

int isInList(int val, t_d_list list, int level){ // Vérification pour savoir si une valeur se trouve dans un niveau de la liste
  p_cell temp = list.head[level];
  while (temp != NULL && temp->value <= val) {
    if (temp->value == val) {
      return 1;
    }
    temp = temp->next[level];
  }
  return 0;
}


int recherche_dicho(t_d_list mylist, int levelmax, int val) // Vérification pour savoir si une valeur se trouve dans la liste en utilisant la méthode dichotomique
{
    // Déclaration de variables temporaire de type pointeur de cellule
  p_cell temp, prev;

  // Déclaration de compteurs
  int i=2;
  int j=1;

  temp = mylist.head[levelmax-1];
  while (temp!=NULL && i<=levelmax+1) // La boucle ne s'arrete uniquement si la varibale temporaire sort de la liste et si le compteur i et supérieur au nombre de niveau - 1
    {
      if (temp->value == val)
      {
        return 1; // Retourne 1 si la valeur est trouvée
      }
      else if (temp->value >val && temp == mylist.head[levelmax-j]) // Sinon si la valeur recherché est plus faible que la valeur de la cellule actuelle et que la cellule actuelle soit égale à la tete du niveau inférieure
      {
        temp = mylist.head[levelmax-i];
        // La variable temporaire passe alors au niveau inférieur
        i++;
        j++;
        // Incrémentation des compteurs
      }
      else if (val > temp->value) // Sinon si la valeur recherchée est supérieure à la valeur de la cellule actuelle
      {
        prev=temp;
        temp = temp->next[levelmax-i];
        // Prev prend la cellule de temp et temp prend la cellule suivante du niveau inférieur
        i++;
        // Incrémentation du compteur i
      }
      else // Si aucune des autres conditions n'ont été remplies
      {
        temp=prev->next[levelmax-i];
        // temp prend la cellule du suivant de prev du niveau inférieur
        i++;
        // Incrémentation du compteur i
      }
    }
  return 0;
}