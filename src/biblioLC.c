#include <stdlib.h>
#include <string.h>
#include "commun.h"
#include "biblioLC.h"

Livre *creer_livre(int num, char *titre, char *auteur) {

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

void liberer_livre(Livre *livre) {

    if(!livre)
        return;
    
    free(livre->titre);
    free(livre->auteur);
    free(livre);
}

void afficher_livre(Livre *livre) {

      if(!livre) {
        print_probleme("Pointeur non valide");
        return;
    }
    
    printf("\t >> %d %s %s\n", livre->num, livre->titre, livre->auteur);
}

Biblio *creer_biblio() {
    Biblio *biblio = (Biblio *) malloc(sizeof(Biblio));

    if(!biblio) {
        print_probleme("Erreur d'allocation");
        return NULL;
    }

    biblio->livres = NULL;
    return biblio;
}

void liberer_biblio(Biblio *biblio) {

    if(!biblio)
        return;

    Livre *tmp = NULL; 

    while(biblio->livres) {
        tmp = biblio->livres->suiv;
        liberer_livre(biblio->livres);
        biblio->livres = tmp;
    }
    
    free(biblio);
}

void inserer_en_tete(Biblio *biblio, int num, char *titre, char *auteur) {
    
    if(!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }

    Livre *livre = creer_livre(num, titre, auteur);
    if(!livre)
        return;
    
    livre->suiv = biblio->livres;
    biblio->livres = livre;
}

void afficher_biblio(Biblio *biblio) {
    
    if(!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }

    for(Livre *livre = biblio->livres; livre; livre = livre->suiv)
        afficher_livre(livre);
}

Livre *rechercher_biblio_numero(Biblio *biblio, int numero) {
    
    if(!biblio) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    Livre *livre = biblio->livres;
    for(; livre && livre->num != numero; livre = livre->suiv);

    return livre;
}

Livre *rechercher_biblio_titre(Biblio *biblio, char *titre) {

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    Livre *livre = biblio->livres;
    for(; livre && strcmp(livre->titre, titre) != 0; livre = livre->suiv);

    return livre;
}

Biblio *rechercher_biblio_auteur(Biblio *biblio, char *auteur) {

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    Biblio *new = creer_biblio();
    if(!new)
        return NULL;
    
    for(Livre *livre = biblio->livres; livre; livre = livre->suiv) {
        if(strcmp(livre->auteur, auteur) == 0)
            inserer_en_tete(new, livre->num, livre->titre, livre->auteur);
    }

    return new;
}

static int compare_livres(Livre *livre, int numero, char *titre, char *auteur) {
    return livre && livre->num == numero && strcmp(livre->titre, titre) == 0 && strcmp(livre->auteur, auteur) == 0; 
}

void suppression_ouverage(Biblio *biblio, int numero, char *titre, char *auteur) {
    
    if(!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }

    Livre *curr = biblio->livres;

    if(compare_livres(biblio->livres, numero, titre, auteur)) {
        biblio->livres = curr->suiv;
        liberer_livre(curr);
        return;
    }

    for(; curr && !compare_livres(curr->suiv, numero, titre, auteur); curr = curr->suiv);

    Livre *sup = NULL;
    if(!curr) {
        sup = curr->suiv;
        curr->suiv = sup->suiv;
        liberer_livre(sup);
    }
}

void fusion_biblios(Biblio *src, Biblio *dest) {
    
    if(!src || !dest) {
        print_probleme("Pointeur non valide");
        return;
    }

    int add;
    for(Livre *livre = dest->livres; livre; livre = livre->suiv) {
        add = 1;
        for(Livre *tete = src->livres; tete; tete = tete->suiv) {
            if(compare_livres(livre, tete->num, tete->titre, tete->auteur)) {
                add = 0;
                break;
            }
        }
        if(add)
            inserer_en_tete(src, livre->num, livre->titre, livre->auteur);
    }
    liberer_biblio(dest);
}

Biblio *rechercher_exemplaires(Biblio *biblio) {

    Biblio *new_biblio = creer_biblio();

    if(!new_biblio)
        return NULL;

    for(Livre *livre = biblio->livres; livre; livre = livre->suiv) {
        for(Livre *suivant = biblio->livres; suivant; suivant = suivant->suiv) {
            
            if(suivant == livre)
                continue;
            
            if(strcmp(livre->titre, suivant->titre) == 0 && strcmp(livre->auteur, suivant->auteur) == 0)
                inserer_en_tete(new_biblio, suivant->num, suivant->titre, suivant->auteur);
        }
    }

    return new_biblio;
}

int existe(Biblio *biblio, int numero, char *titre, char *auteur) {
    if(!biblio)
        return 0;

    for(Livre *livre = biblio->livres; livre; livre = livre->suiv)
        if(compare_livres(livre, numero, titre, auteur))
            return 1;
    
    return 0;
}