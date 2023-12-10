//
// Created by bapti on 06/12/2023.
//

#ifndef UNTITLED6_CONTACT_H
#define UNTITLED6_CONTACT_H
typedef struct {
    int jour;
    int mois;
    int annee;
} DATE;

typedef struct {
    int heure;
    int minute;
} TEMPS;

typedef struct s_rdv{
    struct s_rdv *next;
    DATE date_rdv;
    TEMPS heure_rdv;
    TEMPS duree_rdv;
    char *objet_rdv;
}RDV;

typedef struct s_rdv_list {
    RDV *head;
} LIST_RDV;

typedef struct {
    char *prenom;
    char *nom;
} CONTACT;

typedef struct s_agenda_cell {
    CONTACT contact;
    LIST_RDV rdv;
    struct s_d_cell **next;
} agenda_cell, *p_agenda_cell; // ENTREE AGENDA

typedef struct s_agenda_list {
    agenda_cell **head;
    int max_cell;
} agenda_list; // AGENDA

char *scanString();


p_agenda_cell trouver_contact(agenda_list list, char *nom_prenom);//trouver un contact

void add_rdv_list(LIST_RDV *,RDV*);// ajouter rdv à la liste de RDV;

LIST_RDV CreateEmptyListRdv();// créer une liste de rdv vide

RDV * CreateRDV();// créer une cellule de RDV

void add_rdv_list(LIST_RDV *,RDV*);// ajouter rdv à la liste de RDV;

void add_listrdv_cell_agenda(p_agenda_cell, LIST_RDV);// ajouter cette liste de RDV a une cell de l'agenda

void displayRDV(p_agenda_cell, char*);// afficher les RDV d'une cellule

void deleteRDV_list(LIST_RDV*);// supprimer un rdv d'une liste

void deleteRDV_cell(p_agenda_cell); // Supprimer dans la liste d'une cellule de l'agenda

CONTACT * CreateContact();

p_agenda_cell Create_Entree_Agenda(CONTACT);

agenda_list CreateEmptyAgenda(); // 4 niveaux

void insertagenda(p_agenda_cell ,agenda_list* );

void clear_input_buffer() ;

int isEmptyList(agenda_list, int);




#endif //UNTITLED6_CONTACT_H
