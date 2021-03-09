#include <stdlib.h>
#include <string.h>
#include "../commun.h"
#include "biblioLC.h"


Livre *creer_livre_lc(int num, char *titre, char *auteur) {
    
    if(!titre || !auteur) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    //on alloue la structure 
    Livre *livre = (Livre *) malloc(sizeof(Livre));
    if(!livre) {
        print_probleme("Erreur d'allocation");
        return NULL;
    }

    //on remplie les champs de la structure
    livre->num = num;
    livre->titre = strdup(titre);
    livre->auteur = strdup(auteur);

    return livre;
}

void liberer_livre_lc(Livre *livre) {

    if(!livre)
        return;
    //on libere les pointeurs et le livre
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
    
    //on allou la structure Biblio
    Biblio *biblio = (Biblio *) malloc(sizeof(Biblio));

    if(!biblio) {
        print_probleme("Erreur d'allocation");
        return NULL;
    }

    //on initialise ses champs a null
    biblio->livres = NULL;
    return biblio;
}

void liberer_biblio_lc(Biblio *biblio) {

    if(!biblio)
        return;

    Livre *tmp = NULL; 
    //on libere la memoire e tout les element de la liste 
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

    //on cree un livre
    Livre *livre = creer_livre_lc(num, titre, auteur);
    if(!livre)
        return;
    //on insert le livre en tete de liste 
    livre->suiv = biblio->livres;
    biblio->livres = livre;
}

void afficher_biblio_lc(Biblio *biblio) {
    
    if(!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }

    //on parcoure tout les livres et on les affiche 
    for(Livre *livre = biblio->livres; livre; livre = livre->suiv)
        afficher_livre_lc(livre);
}

Livre *rechercher_biblio_numero_lc(Biblio *biblio, int numero) {
    
    if(!biblio) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    /*
    on recherche le livre, on parcoure la liste tant qu'on a pas trouver le bon element 
    on arrete des qu'on trouve l'element recherché qui est le livre en fonction de son numero ou la fin de la liste  
    */
    Livre *livre = biblio->livres;
    //on fait l'initialisation avant la boucle for pour recuperer le livre
    for(; livre && livre->num != numero; livre = livre->suiv);

    return livre;
}

Livre *rechercher_biblio_titre_lc(Biblio *biblio, char *titre) {

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    //on parcoure tant qu'on trouve pas l'element, et on returne le livre si il existe sinon null
    Livre *livre = biblio->livres;
    for(; livre && strcmp(livre->titre, titre) != 0; livre = livre->suiv);

    return livre;
}

Biblio *rechercher_biblio_auteur_lc(Biblio *biblio, char *auteur) {

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return NULL;
    }
    // on cree une nouvelle biblioteque (qui est une liste de livre) pour stoquer les livres trouver
    Biblio *new = creer_biblio_lc();
    if(!new)
        return NULL;
    
    //on cherche les livres par leur auteur et on les ajoute dans la biblioteque cree
    for(Livre *livre = biblio->livres; livre; livre = livre->suiv) {
        if(strcmp(livre->auteur, auteur) == 0)
            inserer_en_tete_lc(new, livre->num, livre->titre, livre->auteur);
    }

    return new;
}

static int compare_livres_lc(Livre *livre, int numero, char *titre, char *auteur) {
    //returne si les deux livre sont egaux 
    return livre && livre->num == numero && strcmp(livre->titre, titre) == 0 && strcmp(livre->auteur, auteur) == 0; 
}

int suppression_ouverage_lc(Biblio *biblio, int numero, char *titre, char *auteur) {
    
    if(!biblio) {
        print_probleme("Pointeur non valide");
        return 0;
    }

    Livre *curr = biblio->livres;
    //on teste si l'element est en tete de liste on le supprime et on returne true
    if(compare_livres_lc(biblio->livres, numero, titre, auteur)) {
        biblio->livres = curr->suiv;
        liberer_livre_lc(curr);
        return 1;
    }

    /*
    on parcoure la liste (on utilise le suivant d'un element pour avoir le precedent qui est l'element lui meme)
    on sort de la boucle si l'element n'est pas trouver ou on est au dernier element de la liste
    */
    for(; curr && !compare_livres_lc(curr->suiv, numero, titre, auteur); curr = curr->suiv);

    
    Livre *supp = NULL;
    if(curr) {
        //on recupere l'element a supprimer
        supp = curr->suiv;
        //on attache le precedent au suivant de l'element
        curr->suiv = supp->suiv;
        //on libere l'element a supprimer et on returne 1
        liberer_livre_lc(supp);
        return 1;
    }

    //si l'element n'est pas dans la liste on returne false
    return 0;
}

void fusion_biblios_lc(Biblio *dest, Biblio *src) {
    
    if(!dest || !src) {
        print_probleme("Pointeur non valide");
        return;
    }

    int add;
    //on parcoure les deux biblioteque on ajoute les element  de la deuxieme a la premiere si il n'existent pas 
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
    //on libere la deuxieme biblioteque 
    liberer_biblio_lc(src);
}

Biblio *rechercher_exemplaires_lc(Biblio *biblio) {

    Biblio *new_biblio = creer_biblio_lc();

    if(!new_biblio)
        return NULL;
    //on parcoure tout la liste deux fois et on teste si l'element a un exemplaire on l'ajoute a la liste
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
    //on returne la liste des exemplaire 
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