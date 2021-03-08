#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../commun.h"
#include "entreeSortieHach.h"

BiblioH *charger_n_entrees(char *nomfic, int nombre_lignes) {

    FILE *file = fopen(nomfic, "r");
    if(!file) {
        print_probleme("Erreur d'ouverture du fichier");
        return NULL;
    }

    BiblioH *biblio = creer_biblio(nombre_lignes);
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

        inserer(biblio, numero, titre, auteur);
    }

    fclose(file);
    return biblio;
}

void enregister_biblio(BiblioH *biblio, char *nomfic) {

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }

    FILE *file = fopen(nomfic, "w");
    if(!file) {
        print_probleme("Erreur d'ouverture du fichier");
        return;
    }

    for(int i = 0; i < biblio->taille; i++)
        for(LivreH *livres = biblio->tab[ i ]; livres; livres = livres->suivant)
            fprintf(file, "%d %s %s\n", livres->num, livres->titre, livres->auteur);
    
    fclose(file);
}

void enregister_livres(LivreH *livres, char *nomfic) {
    
    if(!livres) {
        print_probleme("Pointeur non valide");
        return;
    }

    FILE *file = fopen(nomfic, "w");
    if(!file) {
        print_probleme("Erreur d'ouverture du fichier");
        return;
    }

    for(; livres; livres = livres->suivant)
        fprintf(file, "%d %s %s\n", livres->num, livres->titre, livres->auteur);
    
    fclose(file);
}