#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "biblioH.h"
#include "../commun.h"

int fonction_clef(char *auteur) {
    
    int hach = 0;

    for(int i = 0; auteur[ i ]; i++)
        hach += auteur[ i ];
    
    return hach;
}

int fonction_hachage(int cle, int taille) {

    float a = (sqrt(5) - 1) / 2;

    return (int) (taille * (cle * a - ( (int) (cle * a) )) );
}

LivreH* creer_livre(int num, char *titre, char *auteur) {

    if(!titre || !auteur) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    LivreH *livre = (LivreH *) malloc(sizeof(LivreH));

    if(!livre) {
        print_probleme("Probleme d'allocation");
        return NULL;
    }

    livre->clef = fonction_clef(auteur);
    livre->num = num;
    livre->titre = strup(titre);
    livre->auteur = strdup(auteur);
    livre->suivant = NULL;

    return livre;
}

void liberer_livre(LivreH *livre) {

    if(!livre)
        return;

    free(livre->auteur);
    free(livre->titre);
    free(livre);
}

BiblioH *creer_biblio(int taille) {

    BiblioH *biblio = (BiblioH * ) malloc(sizeof(BiblioH));

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    biblio->nombresElems = 0;
    biblio->taille = taille;

    biblio->tab = (LivreH **) malloc(sizeof(LivreH *) * taille);

    if(!biblio->tab) {
        free(biblio);
        print_probleme("Probleme d'allocation");
        return NULL;
    }

    return biblio;
}

void liberer_biblio(BiblioH *biblio) {

    if(!biblio)
        return;

    for(int i = 0; i < biblio->taille; i++) {

        LivreH *tmp = NULL;

        while(!biblio->tab[ i ]) {
            tmp = biblio->tab[ i ]->suivant;
            liberer_livre(biblio->tab[ i ]);
            biblio->tab[ i ] = tmp;
        }
    }

    free(biblio->tab);
    free(biblio);
}

void inserer(BiblioH *biblio, int num, char *titre, char *auteur) {

    if(!biblio || !biblio->tab) {
        print_probleme("Pointeur non valide");
        return;
    }

    LivreH *livre = creer_livre(num, titre, auteur);
    if(!livre)
        return;

    int indice = fonction_hachage(livre->clef, biblio->taille);

    livre->suivant = biblio->tab[indice];
    biblio->tab[indice] = livre;    
}
