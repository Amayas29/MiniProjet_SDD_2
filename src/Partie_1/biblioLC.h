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

//permet de cree et retourner un livre
Livre *creer_livre_lc(int num, char *titre, char *auteur);

//permet de liberer la memoire
void liberer_livre_lc(Livre *livre);

//permet d'afficher un livre
void afficher_livre_lc(Livre *livre);

//permet de cree une bibliotheque
Biblio *creer_biblio_lc();

//permet de liberer une bibliotheque
void liberer_biblio_lc(Biblio *biblio);

//permet d'inserer un livre a la bibliotheque
void inserer_en_tete_lc(Biblio *biblio, int num, char *titre, char *auteur);

//permet dafficher tout les livres d'une bibliotheque
void afficher_biblio_lc(Biblio *biblio);

//permet de rechercher un livre dans une bibliotheque selon son nom
Livre *rechercher_biblio_numero_lc(Biblio *biblio, int numero);

//permet de rechercher un livre dans une bibliotheque selon son titre
Livre *rechercher_biblio_titre_lc(Biblio *biblio, char *titre);

//permet de rechercher tout les livres d'un auteur dans une bibliotheque
Biblio *rechercher_biblio_auteur_lc(Biblio *biblio, char *auteur);

//permet de supprimer un ouvrage dans une bibliotheque
int suppression_ouverage_lc(Biblio *biblio, int numero, char *titre, char *auteur);

//permet de fusionner deux bblioteque 
void fusion_biblios_lc(Biblio *src, Biblio *dest);

//permet de trouver tout les livres qui ont des exemplaire dans une bibliotheque
Biblio *rechercher_exemplaires_lc(Biblio *biblio);

//permet de retourner si un livre est present dans une bibliotheque
int existe_lc(Biblio *biblio, int numero, char *titre, char *auteur);

#endif