//
// Created by bapti on 06/12/2023.
//

#ifndef UNTITLED6_LIST_H
#define UNTITLED6_LIST_H
#ifndef UNTITLED_LIST_H
#define UNTITLED_LIST_H

typedef struct s_d_cell {
    int value;
    struct s_d_cell **next;
    int nblevel;
}t_d_cell, *p_cell;

typedef struct s_d_list {
    t_d_cell** head;
    int max_cell;
} t_d_list;

t_d_cell *CreateCell(int, int);

t_d_list CreateEmptyList(int);

void insertHead(t_d_list *, int, p_cell);

int isEmptyList_list_h(t_d_list, int);

void displayList(t_d_list, int);

void DisplayAllList(t_d_list, int);

void insertList_list_h(t_d_list *, int, int);

int *createLevels(int, int);

int isInList_list_h(int, t_d_list, int);

int recherche_dicho(t_d_list, int level, int val);

#endif
#endif //UNTITLED6_LIST_H