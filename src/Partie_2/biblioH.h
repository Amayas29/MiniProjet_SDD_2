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

LivreH* creer_livre_h(int num, char *titre, char *auteur);
void afficher_livre_h(LivreH *livre);
void afficher_livres_h(LivreH *livres);
void liberer_livre_h(LivreH *livre);
BiblioH *creer_biblio_h(int taille);
void liberer_biblio_h(BiblioH *biblio);
void inserer_h(BiblioH *biblio, int num, char *titre, char *auteur);
void liberer_livres_h(LivreH *livres);
void afficher_biblio_h(BiblioH *biblio);

LivreH *rechercher_biblio_numero_h(BiblioH *biblio, int numero);
LivreH *rechercher_biblio_titre_h(BiblioH *biblio, char *titre);
LivreH *rechercher_biblio_auteur_h(BiblioH *biblio, char *auteur);
int suppression_ouverage_h(BiblioH *biblio, int numero, char *titre, char *auteur);
void fusion_biblios_h(BiblioH *src, BiblioH *dest);
LivreH *rechercher_exemplaires_h(BiblioH *biblio);
int existe_h(BiblioH *biblio, int numero, char *titre, char *auteur);

#endif