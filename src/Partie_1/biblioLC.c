#include <stdlib.h>
#include <string.h>
#include "../commun.h"
#include "biblioLC.h"

Livre *creer_livre_lc(int num, char *titre, char *auteur) {

    if(!titre || !auteur) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    Livre *livre = (Livre *) malloc(sizeof(Livre));
    if(!livre) {
        print_probleme("Erreur d'allocation");
        return NULL;
    }

    livre->num = num;
    livre->titre = strdup(titre);
    livre->auteur = strdup(auteur);

    return livre;
}

void liberer_livre_lc(Livre *livre) {

    if(!livre)
        return;
    
    free(livre->titre);
    free(livre->auteur);
    free(livre);
}

void afficher_livre_lc(Livre *livre) {

      if(!livre) {
        print_probleme("Pointeur non valide");
        return;
    }
    
    printf("\t >> %d %s %s\n", livre->num, livre->titre, livre->auteur);
}

Biblio *creer_biblio_lc() {
    Biblio *biblio = (Biblio *) malloc(sizeof(Biblio));

    if(!biblio) {
        print_probleme("Erreur d'allocation");
        return NULL;
    }

    biblio->livres = NULL;
    return biblio;
}

void liberer_biblio_lc(Biblio *biblio) {

    if(!biblio)
        return;

    Livre *tmp = NULL; 

    while(biblio->livres) {
        tmp = biblio->livres->suiv;
        liberer_livre_lc(biblio->livres);
        biblio->livres = tmp;
    }
    
    free(biblio);
}

void inserer_en_tete_lc(Biblio *biblio, int num, char *titre, char *auteur) {
    
    if(!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }

    Livre *livre = creer_livre_lc(num, titre, auteur);
    if(!livre)
        return;
    
    livre->suiv = biblio->livres;
    biblio->livres = livre;
}

void afficher_biblio_lc(Biblio *biblio) {
    
    if(!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }

    for(Livre *livre = biblio->livres; livre; livre = livre->suiv)
        afficher_livre_lc(livre);
}

Livre *rechercher_biblio_numero_lc(Biblio *biblio, int numero) {
    
    if(!biblio) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    Livre *livre = biblio->livres;
    for(; livre && livre->num != numero; livre = livre->suiv);

    return livre;
}

Livre *rechercher_biblio_titre_lc(Biblio *biblio, char *titre) {

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    Livre *livre = biblio->livres;
    for(; livre && strcmp(livre->titre, titre) != 0; livre = livre->suiv);

    return livre;
}

Biblio *rechercher_biblio_auteur_lc(Biblio *biblio, char *auteur) {

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    Biblio *new = creer_biblio_lc();
    if(!new)
        return NULL;
    
    for(Livre *livre = biblio->livres; livre; livre = livre->suiv) {
        if(strcmp(livre->auteur, auteur) == 0)
            inserer_en_tete_lc(new, livre->num, livre->titre, livre->auteur);
    }

    return new;
}

static int compare_livres_lc(Livre *livre, int numero, char *titre, char *auteur) {
    return livre && livre->num == numero && strcmp(livre->titre, titre) == 0 && strcmp(livre->auteur, auteur) == 0; 
}

int suppression_ouverage_lc(Biblio *biblio, int numero, char *titre, char *auteur) {
    
    if(!biblio) {
        print_probleme("Pointeur non valide");
        return 0;
    }

    Livre *curr = biblio->livres;

    if(compare_livres_lc(biblio->livres, numero, titre, auteur)) {
        biblio->livres = curr->suiv;
        liberer_livre_lc(curr);
        return 1;
    }

    for(; curr && !compare_livres_lc(curr->suiv, numero, titre, auteur); curr = curr->suiv);

    Livre *sup = NULL;
    if(curr) {
        sup = curr->suiv;
        curr->suiv = sup->suiv;
        liberer_livre_lc(sup);
        return 1;
    }

    return 0;
}

void fusion_biblios_lc(Biblio *dest, Biblio *src) {
    
    if(!dest || !src) {
        print_probleme("Pointeur non valide");
        return;
    }

    int add;
    for(Livre *livre = src->livres; livre; livre = livre->suiv) {
        add = 1;
        for(Livre *tete = dest->livres; tete; tete = tete->suiv) {
            if(compare_livres_lc(livre, tete->num, tete->titre, tete->auteur)) {
                add = 0;
                break;
            }
        }
        if(add)
            inserer_en_tete_lc(dest, livre->num, livre->titre, livre->auteur);
    }
    liberer_biblio_lc(src);
}

Biblio *rechercher_exemplaires_lc(Biblio *biblio) {

    Biblio *new_biblio = creer_biblio_lc();

    if(!new_biblio)
        return NULL;

    for(Livre *livre = biblio->livres; livre; livre = livre->suiv) {
        for(Livre *suivant = biblio->livres; suivant; suivant = suivant->suiv) {
            
            if(suivant == livre)
                continue;
            
            if(strcmp(livre->titre, suivant->titre) == 0 && strcmp(livre->auteur, suivant->auteur) == 0) {
                inserer_en_tete_lc(new_biblio, livre->num, livre->titre, livre->auteur);
                break;
            }
        }
    }

    return new_biblio;
}

int existe_lc(Biblio *biblio, int numero, char *titre, char *auteur) {
    if(!biblio)
        return 0;

    for(Livre *livre = biblio->livres; livre; livre = livre->suiv)
        if(compare_livres_lc(livre, numero, titre, auteur))
            return 1;
    
    return 0;
}