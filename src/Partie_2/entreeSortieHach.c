#include "entreeSortieHach.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../commun.h"

BiblioH *charger_n_entrees_h(char *nomfic, int nombre_lignes, int taille) {
    //on ouvre le fichier par lecture
    FILE *file = fopen(nomfic, "r");
    if (!file) {
        print_probleme("Erreur d'ouverture du fichier");
        return NULL;
    }
    //on cree une bibliotheque
    BiblioH *biblio = creer_biblio_h(taille);
    if (!biblio) {
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
    for (int ligne = 0; ligne < nombre_lignes && fgets(BUFFER, 512, file); ligne++) {
        //on teste si on a bien lu 3 données sur une ligne, sionon on desaloue tout les structure allouer et on return null
        if (sscanf(BUFFER, "%d %s %s\n", &numero, titre, auteur) != 3) {
            print_probleme("Erreur de lecture depuis le fichiers");
            fclose(file);
            liberer_biblio_h(biblio);
            return NULL;
        }
        /*
        si la lecture des données dans une ligne est bien passé on les insert dans la bibliotheque
        la fonction inserer cree un livre en utilisant les données lu
        */
        inserer_h(biblio, numero, titre, auteur);
    }

    fclose(file);
    return biblio;
}

void enregister_biblio_h(BiblioH *biblio, char *nomfic) {
    if (!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }

    // on ouvre e fichier en ecriture
    FILE *file = fopen(nomfic, "w");
    if (!file) {
        print_probleme("Erreur d'ouverture du fichier");
        return;
    }
    //on parcoure tout les livres de la bibliotheque et on les ajoute au fichier
    /*
    pour ca on parcoure toutes les cases du tableau et on insert tout les livres de toutes les cases
    */
    for (int i = 0; i < biblio->taille; i++)
        for (LivreH *livres = biblio->tab[i]; livres; livres = livres->suivant)
            fprintf(file, "%d %s %s\n", livres->num, livres->titre, livres->auteur);

    fclose(file);
}

void enregister_livres_h(LivreH *livres, char *nomfic) {
    if (!livres) {
        print_probleme("Pointeur non valide");
        return;
    }

    //on ouvre le fichier par lecture
    FILE *file = fopen(nomfic, "w");
    if (!file) {
        print_probleme("Erreur d'ouverture du fichier");
        return;
    }

    //on parcoure tout les livres et on les ajoute au fichier
    for (; livres; livres = livres->suivant)
        fprintf(file, "%d %s %s\n", livres->num, livres->titre, livres->auteur);

    fclose(file);
}