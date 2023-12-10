//
// Created by bapti on 06/12/2023.
//
#include "list.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

t_d_cell *CreateCell(int val, int level) {
    t_d_cell *new_cell = malloc(sizeof(t_d_cell));
    if (new_cell == NULL) {
        return NULL;
    }
    new_cell->value = val;
    new_cell->next = malloc(sizeof(t_d_cell *) * level);
    if (new_cell->next == NULL) {
        free(new_cell);
        return NULL;
    }
    for (int i = 0; i < level; i++) {
        new_cell->next[i] = NULL;
    }
    new_cell->nblevel = level;
    return new_cell;
}

t_d_list CreateEmptyList(int level) {
    t_d_list new_list;
    new_list.head = malloc(sizeof(t_d_list) * level);
    if (new_list.head == NULL) {
    }
    for (int i = 0; i < level; i++) {
        new_list.head[i] = NULL;
    }
    new_list.max_cell = level;
    return new_list;
}

void insertHead(t_d_list *list, int i, p_cell new_cell) {
    new_cell->next[i] = list->head[i];
    list->head[i] = new_cell;
}

void insertList(t_d_list *list, int val, int level) {
    p_cell new_cell = CreateCell(val, level);
    for (int i = 0; i < level; i++) {
        if (list->head[i] == NULL) { // insertion tete de liste
            insertHead(list, i, new_cell);
        } else if ((list->head[i] != NULL) && (list->head[i]->value >= val)) {
            insertHead(list, i, new_cell);
        } else if (list->head[i] != NULL) { // insertion milieu de liste
            p_cell temp = list->head[i];
            p_cell prev;
            while (temp != NULL && temp->value <= val) {
                prev = temp;
                temp = temp->next[i];
            }
            prev->next[i] = new_cell;
            new_cell->next[i] = temp;
        }
    }
    return;
}

int isEmptyList(t_d_list list, int level) {
    if (list.head[level] == NULL) {
        return 1;
    }
    return 0;
}

void displayList(t_d_list list, int level){
    for (int i = 0; i <= level; i++) {
        printf("[list head_%d @-]-->", i);
        if (isEmptyList(list, i) == 0) {
            p_cell p_cell_tmp = list.head[i];
            while (p_cell_tmp != NULL) {
                printf("[ %d|@-]-->", p_cell_tmp->value);
                p_cell_tmp = p_cell_tmp->next[i];
            }
        }
        printf("NULL\n\n");
    }
    return;
}

void DisplayAllList(t_d_list list, int level) {
    displayList(list, 0);
    for (int i = 1; i < level ; i++) {
        p_cell curr = list.head[0];
        p_cell curr_level = list.head[i];
        printf("[list head%d @-] ", i);
        while (curr != NULL) {
            if (curr_level != NULL && curr->value == curr_level->value) {
                printf("--> [ %d|@-] ", curr_level->value);
                curr_level = curr_level->next[i];
            }
            else {
                printf("------------");
            }
            curr = curr->next[0];
        }
        printf("--> NULL\n");
    }
    return;
}

int* createLevels(int nb_level, int max_cell) {
    int i, j = 0;
    int* levels = malloc(max_cell * sizeof(int));

    for (j = 0; j < nb_level; j++) {
        for (i = (pow(2, j) - 1); i < max_cell; i += (pow(2, j))) {
            levels[i] = j;
        }
    }
    return levels;
}

int isInList_list(int val, t_d_list list, int level){
    p_cell temp = list.head[level];
    while (temp != NULL && temp->value <= val) {
        if (temp->value == val) {
            return 1;
        }
        temp = temp->next[level];
    }
    return 0;
}


int recherche_dicho(t_d_list mylist, int levelmax, int val)
{
    p_cell temp, prev;
    int i=2;
    int j=1;
    temp = mylist.head[levelmax-1];
    while (temp!=NULL && i<=levelmax+1)
    {
        if (temp->value == val)
        {
            return 1;
        }
        else if (temp->value >val && temp == mylist.head[levelmax-j])
        {
            temp = mylist.head[levelmax-i];
            i++;
            j++;
        }
        else if (val > temp->value)
        {
            prev=temp;
            temp = temp->next[levelmax-i];
            i++;
        }
        else
        {
            temp=prev->next[levelmax-i];
            i++;
        }
    }
    return 0;
}