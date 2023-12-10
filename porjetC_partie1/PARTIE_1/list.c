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


