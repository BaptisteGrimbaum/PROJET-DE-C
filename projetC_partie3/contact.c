//
// Created by bapti on 06/12/2023.
//
#include "contact.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 100
#define MAX_NAMES 1000



RDV *CreateCell_Rdv() // créer une cellule rdv
{
    RDV *new_rdv = malloc(sizeof(RDV));
    new_rdv->next=NULL;
    return new_rdv;
}

char* scanString()// permet saisie d'une chaine de caractere
{
    char* mot=(char*)malloc(sizeof(mot));
    fgets(mot,80,stdin);
    mot[strlen(mot)-1]='\0';
    return mot;

}
LIST_RDV CreateEmptyListRdv() //créer une list de rdv vide
{
    LIST_RDV new_rdv_list;
    new_rdv_list.head = NULL;
    return new_rdv_list;
}

void InsertHeadRdv(LIST_RDV *mylist, RDV *new_rdv, p_agenda_cell myCell) // utiliser myCell pour insérer le RDV
{
    if (mylist->head == NULL) // cas liste vide
        {
        mylist->head = new_rdv;
    }
    else {// cas general
        RDV *tmp = mylist->head;
        new_rdv->next = tmp;
        mylist->head = new_rdv;
    }
}

CONTACT * CreateContact() // permet de créer un contact
{
    CONTACT *new_contact= malloc(sizeof(CONTACT));
    char *nom,*prenom;
    printf("Saisir un nom : ");
    new_contact->nom = scanString();// permet de saisir le champ nom
    return new_contact;
}

p_agenda_cell Create_Entree_Agenda(CONTACT contact_agenda)// créer une cellule de l'agenda
{
    LIST_RDV new_rdv;
    new_rdv = CreateEmptyListRdv();
    p_agenda_cell new_cell = malloc(sizeof(p_agenda_cell));
    new_cell->contact = contact_agenda;
    new_cell->rdv = new_rdv;
    return new_cell;
}

RDV * CreateRDV() // pemret de créer la celulle rdv
{
    RDV * new_rdv= malloc(sizeof(RDV));
    char* new_objet_rdv;
    TEMPS new_duree_rdv;
    TEMPS new_heure_rdv;
    DATE new_date_rdv;
    printf("Veillez a remplir les informations suivantes : ");

    printf("\n\nObjet de votre rendez-vous : ");
    new_objet_rdv = scanString();// permet de rentrer une chaine de cractère pour l'objet du rdv
    new_rdv->objet_rdv = new_objet_rdv;

    printf("\nDate de votre rendez (JJ/MM/AAAA) : ");
    while (1){// saisie sécurisé
        scanf("%d/%d/%d",&new_date_rdv.jour,&new_date_rdv.mois,&new_date_rdv.annee);
        clear_input_buffer();
        if ((new_date_rdv.jour>=0 && new_date_rdv.jour<=31)&&(new_date_rdv.mois>=0 && new_date_rdv.mois<=12)&&(new_date_rdv.annee>=2000 && new_date_rdv.annee<=3000))
        {
            break;
        }printf("\nValeur invalide, reessayer:");
    }
    new_rdv->date_rdv = new_date_rdv;

    printf("\nHeure de votre rendez-vous (Hhm) : ");
    while (1) {// saisié s"curisé
        scanf(" %dh%d", &new_heure_rdv.heure, &new_heure_rdv.minute);
        clear_input_buffer();
        if ((new_heure_rdv.heure >= 0 && new_heure_rdv.heure <= 23) &&
            (new_heure_rdv.minute >= 0 && new_heure_rdv.minute <= 59)) {
            break;
        }printf("\nValeur invalide, reessayer:");
    }
    new_rdv->heure_rdv = new_heure_rdv;

    printf("\nDuree de votre rendez-vous (Hhm) : ");
    while (1){// saisie sécurisé
        scanf("%dh%d",&new_duree_rdv.heure,&new_duree_rdv.minute);
        clear_input_buffer();
        if ((new_duree_rdv.heure>=0 && new_duree_rdv.heure<=23)&&(new_duree_rdv.minute>=0 && new_duree_rdv.minute<=59))
        {
            break;
        }
        printf("\nValeur invalide, reessayer:");
    }
    new_rdv->duree_rdv = new_duree_rdv;

    new_rdv->next = NULL;

    return new_rdv;
}

agenda_list CreateEmptyAgenda() // créer un agenda vide
{
    agenda_list new_agenda;
    new_agenda.head = malloc(sizeof(agenda_list) * 4);// création de 4 niveaux avec malloc
    for (int i = 0; i < 4; i++) {
        new_agenda.head[i] = NULL;// affectation de chaque niveau a NULL
    }
    return new_agenda;
}


p_agenda_cell trouver_contact(agenda_list list, char *nom_prenom) // trouver un contact à partir du nom fournis en parametre
{
    p_agenda_cell temp = list.head[0];

    while (temp != NULL) {
        if (strncmp(temp->contact.nom, nom_prenom, strlen(nom_prenom)) == 0) { // compare chaque lettre au parametre donne dans la fonction
            return temp;
        }
        temp = temp->next[0];
    }
    return NULL;}

void add_rdv_list(LIST_RDV *liste, RDV *rdv) // ajouter une cellule rdv à la liste rdv
{

    if (liste->head == NULL) {// cas liste vide
        liste->head = rdv;
    }
    else // cas general
    {
        RDV *current = liste->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = rdv;
    }
}

void add_listrdv_cell_agenda(p_agenda_cell cell_agenda, LIST_RDV mylist)// affecte la list RDv à un contact
{
    cell_agenda->rdv = mylist;
}

void displayRDV(p_agenda_cell cell, char*nom)// afficher les rdvs d'un contact
{
    RDV* temp;
    temp = cell->rdv.head;
    if (cell->rdv.head == NULL)
    {
        printf("Aucun rdv pour %s \n\n",nom);
    }
    else{
        while(temp!=NULL) {
            printf("%s a un rdv : %s, le %d/%d/%d, a %dh%d, pour une duree de %dh%d \n", nom, temp->objet_rdv,
                   temp->date_rdv.jour, temp->date_rdv.mois, temp->date_rdv.annee,temp->heure_rdv.heure,
                   temp->heure_rdv.minute,temp->duree_rdv, temp->duree_rdv.minute); // affiche chaque champ de la structure LIST_RDV
            temp=temp->next;
        }
    }


}

void deleteRDV_list(LIST_RDV *mylist) // permet de supprimer une cellule de la liste rdv
{
    RDV * temp;
    temp=mylist->head;

    if (temp->next == NULL)// cas d'une liste contenat un seul rdv
    {
        mylist->head = NULL;
        free(temp);
    }
    else // cas general
    {
        mylist->head=temp->next;
        free(temp);
    }
}

void deleteRDV_cell(p_agenda_cell cell)// supprimer le rdv d'un contact
{
    deleteRDV_list(&(cell->rdv));
}



void displayMyAgenda(agenda_list myAgenda, int level) // permet d'afficher l'agenda
{
    for (int i = 0; i <= level; i++) {
        printf("[list head_%d @-]-->", i);
        if (isEmptyList(myAgenda, i) == 0) {
            p_agenda_cell p_cell_tmp = myAgenda.head[i];
            while (p_cell_tmp != NULL) {
                printf("[ %s|@-]-->", p_cell_tmp->contact.nom);
                p_cell_tmp = p_cell_tmp->next[i];
            }
        }
        printf("NULL\n\n");
    }
    return;
}




void insertagenda(p_agenda_cell new_cell, agenda_list *agenda) // insertion d'un contact dans l'agenda
{

    p_agenda_cell temp = agenda->head[3];
    int i = 0;
    int j = 3;
    p_agenda_cell prev;

    if (agenda->head[0] == NULL) // cas d'une liste vide
    {
        new_cell->next = (p_agenda_cell *) malloc((j + 1) * sizeof(p_agenda_cell));
        for (int cpt = 0; cpt <= j; cpt++) {
            agenda->head[cpt] = new_cell;
            new_cell->next[cpt] = NULL;
        }
    } else {
        while (temp != NULL &&
               temp->contact.nom[i] <= new_cell->contact.nom[i])/// pou
        {
            prev = temp;
            while (temp->contact.nom[i] == new_cell->contact.nom[i] && j > 0) {
                j--;// incrémentation de j pour changer de niveaux
                i++;// incrémentation de i pour avancer à la lettre suivante
            }
            temp = temp->next[j];
        }
        if (temp == NULL) {
            temp = prev;
        }

        new_cell->next = (p_agenda_cell *) malloc(
                (j + 1) * sizeof(p_agenda_cell));// créer le nombre de next de la cellule à insérer
        for (int k = 0; k <= j; k++) {
            new_cell->next[k] = NULL;
        }
        for (int k = 0; k <= j; k++) {
            p_agenda_cell copy = temp;
            if (new_cell->contact.nom[i] < agenda->head[k]->contact.nom[i]) {
                new_cell->next[k] = agenda->head[k];
                agenda->head[k] = new_cell;
            } else {
                while (copy->next[k] != NULL) {
                    copy = copy->next[k];
                }

                copy->next[k] = new_cell;

            }
        }
    }

}

void clear_input_buffer() // pour regler un problème de saisie
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
