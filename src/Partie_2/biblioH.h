#ifndef __BIBLIOH_H__
#define __BIBLIOH_H__

typedef struct livreh {
    int clef;
    int num;
    char *titre;
    char *auteur;
    struct livreh *suivant;
} LivreH;

typedef struct table {
    int nombresElems;
    int taille;
    LivreH **tab;
} BiblioH;

int fonction_clef(char *auteur);
int fonction_hachage(int cle, int taille);

LivreH* creer_livre(int num, char *titre, char *auteur);
void liberer_livre(LivreH *livre);
BiblioH *creer_biblio(int taille);
void liberer_biblio(BiblioH *biblio);
void inserer(BiblioH *biblio, int num, char *titre, char *auteur);

#endif