#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "biblioH.h"
#include "../commun.h"

int fonction_clef(char *auteur) {
    
    int hach = 0;

    // On somme les code ascii des caracteres
    for(int i = 0; auteur[ i ]; i++)
        hach += auteur[ i ];
    
    return hach;
}

int fonction_hachage(int cle, int taille) {

    float a = (sqrt(5) - 1) / 2;

    return (int) (taille * (cle * a - ( (int) (cle * a) )) );
}

LivreH* creer_livre_h(int num, char *titre, char *auteur) {

    if(!titre || !auteur) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    LivreH *livre = (LivreH *) malloc(sizeof(LivreH));

    if(!livre) {
        print_probleme("Probleme d'allocation");
        return NULL;
    }

    // On calcul la clé du livre
    livre->clef = fonction_clef(auteur);
    livre->num = num;
    livre->titre = strdup(titre);
    livre->auteur = strdup(auteur);
    livre->suivant = NULL;

    return livre;
}

void afficher_livre_h(LivreH *livre) {

    if(!livre) {
        print_probleme("Pointeur non valide");
        return;
    }
    
    printf("\t >> %d %s %s\n", livre->num, livre->titre, livre->auteur);
}

void afficher_livres_h(LivreH *livres) {

    if(!livres)
        return;
    
    // On parcous la liste et on affiche les livres
    for(; livres; livres = livres->suivant)
        afficher_livre_h(livres);

}

void liberer_livre_h(LivreH *livre) {

    if(!livre)
        return;

    // On libere les donnés du livres
    free(livre->auteur);
    free(livre->titre);
    free(livre);
}

BiblioH *creer_biblio_h(int taille) {

    BiblioH *biblio = (BiblioH * ) malloc(sizeof(BiblioH));

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    biblio->nombresElems = 0;
    biblio->taille = taille;

    // On alloue le tableau
    biblio->tab = (LivreH **) malloc(sizeof(LivreH *) * taille);

    if(!biblio->tab) {
        free(biblio);
        print_probleme("Probleme d'allocation");
        return NULL;
    }

    // On l'initialise à NULL
    for(int i = 0; i < taille; i++)
        biblio->tab[ i ] = NULL;

    return biblio;
}

void afficher_biblio_h(BiblioH *biblio) {
    
    if(!biblio || !biblio->tab) {
        print_probleme("Pointeur non valide");
        return;
    }

    // On parcours la table et on affiche les listes
    for(int i = 0; i < biblio->taille; i++)
        afficher_livres_h(biblio->tab[ i ]);

}

void liberer_livres_h(LivreH *livres) {

    LivreH *tmp = NULL;

    // On parcours la liste pour liberer les livres
    while(livres) {
        tmp = livres->suivant;
        liberer_livre_h(livres);
        livres = tmp;
    }
}

void liberer_biblio_h(BiblioH *biblio) {

    if(!biblio || !biblio->tab)
        return;

    // On parcours la table et on libere les listes
    for(int i = 0; i < biblio->taille; i++)
        liberer_livres_h(biblio->tab[ i ]);

    // On libere le tableau et la structure
    free(biblio->tab);
    free(biblio);
}

void inserer_h(BiblioH *biblio, int num, char *titre, char *auteur) {

    if(!biblio || !biblio->tab) {
        print_probleme("Pointeur non valide");
        return;
    }

    // On crée le livre
    LivreH *livre = creer_livre_h(num, titre, auteur);
    if(!livre)
        return;

    // On calcule son indice dans la table
    int indice = fonction_hachage(livre->clef, biblio->taille);

    // On ajoute en tete dans la liste correspondante
    livre->suivant = biblio->tab[indice];
    biblio->tab[indice] = livre;    
    biblio->nombresElems ++;
}

LivreH *rechercher_biblio_numero_h(BiblioH *biblio, int numero) {

    if(!biblio || !biblio->tab) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    // On parcours la table
    for(int i = 0; i < biblio->taille; i++)
        // On parcours la liste à l'indice i
        for(LivreH *livre = biblio->tab[ i ]; livre; livre = livre->suivant)
            if(livre->num == numero)
                return livre;

    return NULL;
}

LivreH *rechercher_biblio_titre_h(BiblioH *biblio, char *titre) {

    if(!biblio || !biblio->tab) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    // On parcours la table
    for(int i = 0; i < biblio->taille; i++)
        // On parcours la liste à l'indice i
        for(LivreH *livre = biblio->tab[ i ]; livre; livre = livre->suivant)
            if(strcmp(livre->titre, titre) == 0)
                return livre;

    return NULL;
}

LivreH *rechercher_biblio_auteur_h(BiblioH *biblio, char *auteur) {

    if(!biblio || !biblio->tab) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    // On calcule l'indice de l'auteur dans la table
    int indice = fonction_hachage(fonction_clef(auteur), biblio->taille);

    LivreH *livres = biblio->tab[indice];
    LivreH *liste = NULL;

    /**
        * On parcours la liste pour reccupere les livres de l'auteurs
        * La fonction n'est pas parfait on peut avoir des auteurs different dans une même liste
    */
    LivreH *tmp = NULL;
    for(; livres; livres = livres->suivant) {
        // Si c'est pas l'auteur on l'ignore sinon on l'ajoute à la nouvelle liste
        if(strcmp(livres->auteur, auteur) != 0)
            continue;

        tmp = creer_livre_h(livres->num, livres->titre, livres->auteur);
        tmp->suivant = liste;
        liste = tmp;
    }

    return liste;
}

static int compare_livres_h(LivreH *livre, int numero, char *titre) {
    // Si le livre n'est pas NULL et que il a le bon numéro et le bon titre
    return livre && livre->num == numero && strcmp(livre->titre, titre) == 0;
}

int suppression_ouverage_h(BiblioH *biblio, int numero, char *titre, char *auteur) {
    
    if(!biblio || !biblio->tab) {
        print_probleme("Pointeur non valide");
        return 0;
    }

    // On reccupere l'indice selon l'auteur
    int indice = fonction_hachage(fonction_clef(auteur), biblio->taille);

    LivreH *livres = biblio->tab[indice];

    if(!livres)
        return 0;
  
    // Suppresion en tete
    if(livres->num == numero && strcmp(livres->titre, titre) == 0) {
        biblio->tab[indice] = biblio->tab[indice]->suivant;
        liberer_livre_h(livres);
        biblio->nombresElems--;
        return 1;
    }

    /*
        On boucle jusqu'à qu'on trouve le livre ou bien on a terminer la liste donc on a pas trouvé
        NB : Si on trouve on sort avec le precédent donc le chainage est facile à modifier
    */
    for(; livres && !compare_livres_h(livres->suivant, numero, titre); livres = livres->suivant);

    LivreH *supp = NULL;
    // Si on est sorti avec un pointeur non null donc son suivant c'est l'élément à supprimer
    if(livres) {
        supp = livres->suivant;
        livres->suivant = supp->suivant;
        liberer_livre_h(supp);
        biblio->nombresElems--;
        return 1;
    }

    return 0;
}

void fusion_biblios_h(BiblioH *dest, BiblioH *src) {

    if(!src || !dest || !src->tab || !dest->tab) {
        print_probleme("Pointeur non valide");
        return;
    }

    // On parcours la bibliotheque source
    for(int i = 0; i < src->taille; i++) {
        
        // On parcours la liste à l'indice i
        for(LivreH *livres = src->tab[i]; livres; livres = livres->suivant) {

            // On vérfie si le livre n'existe pas déja dans la bibliotheque destination
            if(existe_h(dest, livres->num, livres->titre, livres->auteur) == 0)
                inserer_h(dest, livres->num, livres->titre, livres->auteur);

        }
    }

    liberer_biblio_h(src);
}

LivreH *rechercher_exemplaires_h(BiblioH *biblio) {

    if(!biblio || !biblio->tab) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    LivreH *liste = NULL;

    // On parcours la table
    for(int i = 0; i < biblio->taille; i++) {

        /* 
            * On parcours la liste à l'indice i 
            * (les livres d'un meme auteurs sont dans une meme liste)
        */
        for(LivreH *livre = biblio->tab[ i ]; livre; livre = livre->suivant) {
            // On re-parcours la liste pour verfier si il n'a pas d'autre exemplaires
            for(LivreH *suivant = biblio->tab[ i ]; suivant; suivant = suivant->suivant) {
                
                // Si c'est le même on l'ignore
                if(suivant == livre)
                    continue;

                // Si c'est le mêmes auteur et le mêmes nom on ajout
                if(strcmp(livre->titre, suivant->titre) == 0 && strcmp(livre->auteur, suivant->auteur) == 0 ) {
                    
                    // On créeune copie du livre
                    LivreH *new = creer_livre_h(livre->num, livre->titre, livre->auteur);
                    if(!new)
                        continue;
                    
                    new->suivant = liste;
                    liste = new;

                    // Pour ajouter une seule fois !
                    break;
                }
            }
        }
    }

    return liste;
}

int existe_h(BiblioH *biblio, int numero, char *titre, char *auteur) {

    if(!biblio || !biblio->tab)
        return 0;

    // On réccupere l'indice selon l'auteur
    int indice = fonction_hachage(fonction_clef(auteur), biblio->taille);
    // On chercher le livre dans la liste
    for(LivreH *livres = biblio->tab[indice]; livres; livres = livres->suivant)
        if(compare_livres_h(livres, numero, titre))
            return 1;

    return 0;
}
