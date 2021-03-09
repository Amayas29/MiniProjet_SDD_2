#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../commun.h"
#include "biblioLC.h"
#include "entreeSortieLC.h"

Biblio *charger_n_entrees_lc(char *nomfic, int nombre_lignes) {

    //ouverture du fichier
    FILE *file = fopen(nomfic, "r");
    if(!file) {
        print_probleme("Erreur d'ouverture du fichier");
        return NULL;
    }

    //on cree une bibliotheque
    Biblio *biblio = creer_biblio_lc();
    if(!biblio) {
        fclose(file);
        return NULL;
    }

    char BUFFER[512];
    int numero;
    char titre[256];
    char auteur[256];
    /*
    on parcoure le fichier et on ajoute les nombre de ligne lu dans le fichier dans une bibliotheque 
    la boucle s'arrete si on a atteint le nombre de ligne demander ou la fin du fichier
    */
    for(int ligne = 0; ligne < nombre_lignes && fgets(BUFFER, 512, file); ligne++) {

        //on teste si on a bien lu 3 données sur une ligne, sionon on desaloue tout les structure allouer et on return null
        if(sscanf(BUFFER, "%d %s %s\n", &numero, titre, auteur) != 3) {
            print_probleme("Erreur de lecture depuis le fichiers");
            fclose(file);
            liberer_biblio_lc(biblio);
            return NULL;
        }
        /*
        si la lecture des données dans une ligne est bien passé on les insert dans la bibliotheque
        la fonction inserer cree un livre en utilisant les données lu
        */
        inserer_en_tete_lc(biblio, numero, titre, auteur);
    }

    fclose(file);
    return biblio;
}

void enregister_biblio_lc(Biblio *biblio, char *nomfic) {

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }
    // on ouvre e fichier en ecriture
    FILE *file = fopen(nomfic, "w");
    if(!file) {
        print_probleme("Erreur d'ouverture du fichier");
        return;
    }
    //on parcoure tout les livres de la bibliotheque et on les ajoute au fichier
    for(Livre *livre = biblio->livres; livre; livre = livre->suiv)
        fprintf(file, "%d %s %s\n", livre->num, livre->titre, livre->auteur);
    
    fclose(file);
}