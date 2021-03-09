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


Livre *creer_livre_lc(int num, char *titre, char *auteur);
void liberer_livre_lc(Livre *livre);
void afficher_livre_lc(Livre *livre);

Biblio *creer_biblio_lc();
void liberer_biblio_lc(Biblio *biblio);
void inserer_en_tete_lc(Biblio *biblio, int num, char *titre, char *auteur);
void afficher_biblio_lc(Biblio *biblio);

Livre *rechercher_biblio_numero_lc(Biblio *biblio, int numero);
Livre *rechercher_biblio_titre_lc(Biblio *biblio, char *titre);
Biblio *rechercher_biblio_auteur_lc(Biblio *biblio, char *auteur);
int suppression_ouverage_lc(Biblio *biblio, int numero, char *titre, char *auteur);
void fusion_biblios_lc(Biblio *src, Biblio *dest);
Biblio *rechercher_exemplaires_lc(Biblio *biblio);
int existe_lc(Biblio *biblio, int numero, char *titre, char *auteur);

#endif