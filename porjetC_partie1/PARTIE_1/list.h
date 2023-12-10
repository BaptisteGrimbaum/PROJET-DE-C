#ifndef UNTITLED_LIST_H
#define UNTITLED_LIST_H


//cellule
typedef struct s_d_cell {
    int value;
    struct s_d_cell **next; //tableau de suivant
    int nblevel;
}t_d_cell, *p_cell;


//liste a niveau
typedef struct s_d_list {
    t_d_cell** head; //liste de head
    int max_cell;
} t_d_list;

t_d_cell *CreateCell(int, int);

t_d_list CreateEmptyList(int);

void insertHead(t_d_list *, int, p_cell);

int isEmptyList(t_d_list, int);

void displayList(t_d_list, int);

void insertList(t_d_list *, int, int);


#endif