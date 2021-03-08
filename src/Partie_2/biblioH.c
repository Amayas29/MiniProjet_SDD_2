#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    livre->titre = strdup(titre);
    livre->auteur = strdup(auteur);
    livre->suivant = NULL;

    return livre;
}

void afficher_livre(LivreH *livre) {

    if(!livre) {
        print_probleme("Pointeur non valide");
        return;
    }
    
    printf("\t >> %d %s %s\n", livre->num, livre->titre, livre->auteur);
}

void afficher_livres(LivreH *livres) {

    if(!livres)
        return;
    
    for(; livres; livres = livres->suivant)
        afficher_livre(livres);

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

    for(int i = 0; i < taille; i++)
        biblio->tab[ i ] = NULL;

    return biblio;
}

void afficher_biblio(BiblioH *biblio) {
    
    if(!biblio || !biblio->tab) {
        print_probleme("Pointeur non valide");
        return;
    }

    for(int i = 0; i < biblio->taille; i++)
        afficher_livres(biblio->tab[ i ]);

}
void liberer_livres(LivreH *livres) {

    LivreH *tmp = NULL;

    while(livres) {
        tmp = livres->suivant;
        liberer_livre(livres);
        livres = tmp;
    }
}
void liberer_biblio(BiblioH *biblio) {

    if(!biblio || !biblio->tab)
        return;

    for(int i = 0; i < biblio->taille; i++)
        liberer_livres(biblio->tab[ i ]);

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
    biblio->nombresElems ++;
}

LivreH *rechercher_biblio_numero(BiblioH *biblio, int numero) {

    if(!biblio || !biblio->tab) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    for(int i = 0; i < biblio->taille; i++)
        for(LivreH *livre = biblio->tab[ i ]; livre; livre = livre->suivant)
            if(livre->num == numero)
                return livre;

    return NULL;
}

LivreH *rechercher_biblio_titre(BiblioH *biblio, char *titre) {

    if(!biblio || !biblio->tab) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    for(int i = 0; i < biblio->taille; i++)
        for(LivreH *livre = biblio->tab[ i ]; livre; livre = livre->suivant)
            if(strcmp(livre->titre, titre) == 0)
                return livre;

    return NULL;
}

LivreH *rechercher_biblio_auteur(BiblioH *biblio, char *auteur) {

    if(!biblio || !biblio->tab) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    int indice = fonction_hachage(fonction_clef(auteur), biblio->taille);

    LivreH *livres = biblio->tab[indice];
    LivreH *liste = NULL;

    LivreH *tmp = NULL;
    for(; livres; livres = livres->suivant) {
        if(strcmp(livres->auteur, auteur) != 0)
            continue;

        tmp = creer_livre(livres->num, livres->titre, livres->auteur);
        tmp->suivant = liste;
        liste = tmp;
    }

    return liste;
}
static int compare_livres(LivreH *livre, int numero, char *titre) {
    return livre && livre->num == numero && strcmp(livre->titre, titre) == 0;
}

int suppression_ouverage(BiblioH *biblio, int numero, char *titre, char *auteur) {
    
    if(!biblio || !biblio->tab) {
        print_probleme("Pointeur non valide");
        return 0;
    }

    int indice = fonction_hachage(fonction_clef(auteur), biblio->taille);

    LivreH *livres = biblio->tab[indice];

    if(!livres)
        return 0;
  
    if(livres->num == numero && strcmp(livres->titre, titre) == 0) {
        biblio->tab[indice] = biblio->tab[indice]->suivant;
        liberer_livre(livres);
        return 1;
    }

    for(; livres && !compare_livres(livres->suivant, numero, titre); livres = livres->suivant);

    LivreH *sup = NULL;
    if(livres) {
        sup = livres->suivant;
        livres->suivant = sup->suivant;
        liberer_livre(sup);
        return 1;
    }

    return 0;
}

void fusion_biblios(BiblioH *dest, BiblioH *src) {

    if(!src || !dest || !src->tab || !dest->tab) {
        print_probleme("Pointeur non valide");
        return;
    }

    for(int i = 0; i < src->taille; i++)
        for(LivreH *livres = src->tab[i]; livres; livres = livres->suivant)
            if(existe(dest, livres->num, livres->titre, livres->auteur) == 0)
                inserer(dest, livres->num, livres->titre, livres->auteur);

    liberer_biblio(src);
}

LivreH *rechercher_exemplaires(BiblioH *biblio) {

    if(!biblio || !biblio->tab) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    LivreH *liste = NULL;

    for(int i = 0; i < biblio->taille; i++) {

        for(LivreH *livre = biblio->tab[ i ]; livre; livre = livre->suivant) {
            for(LivreH *suivant = biblio->tab[ i ]; suivant; suivant = suivant->suivant) {
                
                if(suivant == livre)
                    continue;

                if(strcmp(livre->titre, suivant->titre) == 0 && strcmp(livre->auteur, suivant->auteur) == 0 ) {
                    
                    LivreH *new = creer_livre(livre->num, livre->titre, livre->auteur);
                    if(!new)
                        continue;
                    
                    new->suivant = liste;
                    liste = new;

                    break;
                }
            }
        }
    }

    return liste;
}

int existe(BiblioH *biblio, int numero, char *titre, char *auteur) {

    if(!biblio || !biblio->tab)
        return 0;

    int indice = fonction_hachage(fonction_clef(auteur), biblio->taille);
    for(LivreH *livres = biblio->tab[indice]; livres; livres = livres->suivant)
        if(compare_livres(livres, numero, titre))
            return 1;

    return 0;
}
