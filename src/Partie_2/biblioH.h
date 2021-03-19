#ifndef __BIBLIOH_H__
#define __BIBLIOH_H__

// La structure d'un livre
typedef struct livreh {
    int clef;
    int num;
    char *titre;
    char *auteur;
    struct livreh *suivant;
} LivreH;

// La table de hachage
typedef struct table {
    int nombresElems;
    int taille;
    LivreH **tab;
} BiblioH;

// La fonction qui retourne la clé à partir de l'auteur
int fonction_clef(char *auteur);

// La fonction de hachage
int fonction_hachage(int cle, int taille);

// Créer un livre à partir de son numéro, titre et auteur
LivreH *creer_livre_h(int num, char *titre, char *auteur);

// Libere la mémoire alloué à un livre
void liberer_livre_h(LivreH *livre);

// Crée un bibliothéque à partir de sa taille
BiblioH *creer_biblio_h(int taille);

// Libere toute la mémoire alloué à la bibliotheque
void liberer_biblio_h(BiblioH *biblio);

// Affiche un livres
void afficher_livre_h(LivreH *livre);

// Affiche la liste des livres
void afficher_livres_h(LivreH *livres);

// Libere la liste des livres
void liberer_livres_h(LivreH *livres);

// Permet d'inserer un livre à une bibliotheque
void inserer_h(BiblioH *biblio, int num, char *titre, char *auteur);

// Affiche une bibliotheque
void afficher_biblio_h(BiblioH *biblio);

// Recherche un livre par son numero et le retourne si il existe
LivreH *rechercher_biblio_numero_h(BiblioH *biblio, int numero);

// Recherhce un livre par son titre et le retourne si il existe
LivreH *rechercher_biblio_titre_h(BiblioH *biblio, char *titre);

// Recherhce tous les livres d'un auteur donné
LivreH *rechercher_biblio_auteur_h(BiblioH *biblio, char *auteur);

// Supprime un livre de la bibliotheque et retourne le resultat de la requette
int suppression_ouverage_h(BiblioH *biblio, int numero, char *titre, char *auteur);

// Permet de fussionner deux bibliotheques
void fusion_biblios_h(BiblioH *src, BiblioH *dest);

// Recherche tous les livres qui possédent plusieurs exemplaires dans la bibiotheque
LivreH *rechercher_exemplaires_h(BiblioH *biblio);

// Permet de savoir si un livre existe dans la bibiotheque
int existe_h(BiblioH *biblio, int numero, char *titre, char *auteur);

#endif