#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "list.h"



int main() {


    agenda_list myagenda; // création de l'agenda
    myagenda = CreateEmptyAgenda();
    for(int i=0;i<2;i++)// insertion dans l'agenda des noms souhaités
    {
        CONTACT * mycontact;
        p_agenda_cell new;

        mycontact = CreateContact();

        new = Create_Entree_Agenda(*mycontact);
        insertagenda(new, &myagenda);
    }
    char nom[100];
    int choix;
    p_agenda_cell contact_trouve;
    CONTACT * mycontact;
    p_agenda_cell new;
    LIST_RDV mylist;
    mylist = CreateEmptyListRdv();

    do{
        printf("\n------ MENU AGENDA ------\n ");
        printf("0: Rechercher un contact\n");
        printf("1: Ajouter un Contact\n");
        printf("2: Afficher les rendez-vous d'un contact\n");
        printf("3: Ajouter un rdv a un contact \n");
        printf("4: Supprimer un rdv \n");
        printf("5: Quitter \n");
        printf("Votre choix : ");
        scanf(" %d", &choix);
        clear_input_buffer();

        switch (choix) {

            case 0: // chercher un contact

                printf("Quel contact voulez vous rechercher ?\n");
                fgets(nom, 100, stdin);
                nom[strcspn(nom, "\n")] = 0;// saisie du nom
                contact_trouve = trouver_contact(myagenda, nom);
                if (contact_trouve!=NULL)
                {
                    printf("%s est bien dans l'agenda.\n\n", nom);
                }
                else
                {
                    printf(" %s n'est pas dans l'agenda\n\n",nom);
                }
                break;


            case 1:

                mycontact = CreateContact();
                new = Create_Entree_Agenda(*mycontact);
                insertagenda(new, &myagenda);
                printf("Le Contact a bien ete ajoute a l'agenda \n\n");
                break;

            case 2:

                printf("Quel contact ?\n");
                fgets(nom, 100, stdin);
                nom[strcspn(nom, "\n")] = 0; // saisie du nom
                contact_trouve = trouver_contact(myagenda, nom);// appel fonction pour chercher un contact
                displayRDV(contact_trouve, nom);
                break;
            case 3:

                printf("A qui voulez vous rajouter un rdv ? ");
                fgets(nom, 100, stdin);
                nom[strcspn(nom, "\n")] = 0;// saisie du nom
                contact_trouve = trouver_contact(myagenda, nom);
                if (contact_trouve == NULL)
                {
                    printf(" Le contact n'est pas dans l'agenda \n");
                }
                else{
                    RDV *new_rdv;
                    new_rdv = CreateRDV();
                    add_rdv_list(&mylist,new_rdv);
                    add_listrdv_cell_agenda(contact_trouve,mylist);// affecte la liste de rdv a un contact
                    printf("Le rdv pour %s a bien ete ajoute\n", nom);
                    displayRDV(contact_trouve,nom);
                }
                break;


          case 4:
                printf("A qui voulez vous supprimer un rdv ?");
                fgets(nom, 100, stdin);
                nom[strcspn(nom, "\n")] = 0;// saisie du nom
                contact_trouve = trouver_contact(myagenda, nom);// appel de la fonction pour rechercher le contact
                deleteRDV_cell(contact_trouve);// appel fonction pour suppimer le rdv
                printf("RDV supprime: \n");
                displayRDV(contact_trouve,nom);

            case 5:
                printf(" Fin du programme ");
                break;

            default:
                printf("Choix invalide");

        }

    }while (choix !=5);




    return 0;
}
