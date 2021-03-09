#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../commun.h"
#include "entreeSortieLC.h"
#include "UIfonctions.h"

int main(int argc, char **argv) {

    //on teste si le nombre d'argument donnée en parametre est bien 3
    if(argc != 3) {
        fprintf(stderr, "Manque d'arguments. \nUsage %s <nom fichier> <nombre lignes>\n", argv[0]);
        return 1;
    }

    //on ignore le nom du l'executable du tableau 
    argc --;
    argv ++;

    //on cast la chaine de caractere en entier
    int lignes = atoi(argv[1]);
    //on alloue la bibioteque 
    Biblio *biblio = charger_n_entrees_lc(argv[0], lignes);

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return 1;
    }

    printf("\n\t ** Bienvenu : \n\n");

    int choix;

    while(1) {

        printf("\t\t==================================================\n\n");

        menu();
        choix = get_choix(0, 7);

        if(choix == 0)
            break;

        switch (choix) {
            case 1: {
                afficher_biblio_lc(biblio);
                printf("\n");
                break;
            }
            case 2: rechercher(biblio); break;

            case 3: supprimer(biblio); break;

            case 4: ajouter(biblio); break;

            case 5: fusionner(biblio); break;

            case 6: enregistrer(biblio); break;
        }
    }

    //on libere la biblioteque
    liberer_biblio_lc(biblio);
    printf("\n\t ** Merci au revoir\n");
    return 0;
}