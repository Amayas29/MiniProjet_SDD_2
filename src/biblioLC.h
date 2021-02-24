#ifndef __BIBLIOLC_H__
#define __BIBLIOLC_H__

typedef struct livre {
    int num;
    char *titre;
    char *auteur;
    struct livre *suiv;
} Livre;

typedef struct {
    Livre *livres;
} Biblio;


Livre *creer_livre(int num, char *titre, char *auteur);
void liberer_livre(Livre *livre);
void afficher_livre(Livre *livre);

Biblio *creer_biblio();
void liberer_biblio(Biblio *biblio);
void inserer_en_tete(Biblio *biblio, int num, char *titre, char *auteur);
void afficher_biblio(Biblio *biblio);

Livre *rechercher_biblio_numero(Biblio *biblio, int numero);
Livre *rechercher_biblio_titre(Biblio *biblio, char *titre);
Biblio *rechercher_biblio_auteur(Biblio *biblio, char *auteur);
void suppression_ouverage(Biblio *biblio, int numero, char *titre, char *auteur);
void fusion_biblios(Biblio *src, Biblio *dest);
Biblio *rechercher_exemplaires(Biblio *biblio);
int existe(Biblio *biblio, int numero, char *titre, char *auteur);

#endif