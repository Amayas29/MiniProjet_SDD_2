#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../commun.h"
#include "biblioLC.h"
#include "entreeSortieLC.h"

Biblio *charger_n_entrees(char *nomfic, int nombre_lignes) {

    FILE *file = fopen(nomfic, "r");
    if(!file) {
        print_probleme("Erreur d'ouverture du fichier");
        return NULL;
    }

    Biblio *biblio = creer_biblio();
    if(!biblio) {
        fclose(file);
        return NULL;
    }

    char BUFFER[512];
    int numero;
    char titre[256];
    char auteur[256];

    for(int ligne = 0; ligne < nombre_lignes && fgets(BUFFER, 512, file); ligne++) {

        if(sscanf(BUFFER, "%d %s %s\n", &numero, titre, auteur) != 3) {
            print_probleme("Erreur de lecture depuis le fichiers");
            fclose(file);
            liberer_biblio(biblio);
            return NULL;
        }

        inserer_en_tete(biblio, numero, titre, auteur);
    }

    fclose(file);
    return biblio;
}

void enregister_biblio(Biblio *biblio, char *nomfic) {

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }

    FILE *file = fopen(nomfic, "w");
    if(!file) {
        print_probleme("Erreur d'ouverture du fichier");
        return;
    }

    for(Livre *livre = biblio->livres; livre; livre = livre->suiv)
        fprintf(file, "%d %s %s\n", livre->num, livre->titre, livre->auteur);
    
    fclose(file);
}