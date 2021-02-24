#include <stdio.h>
#include <string.h>
#include "entreeSortieLC.h"
#include "UIfonctions.h"

void menu() {
    printf("\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"\
           "\t::                                                               ::\n"\
           "\t::        ** Veuillez choisir une action :                       ::\n"\
           "\t::                                                               ::\n"\
           "\t::    1 ) -  Affichage de la bibliotheque                        ::\n"\
           "\t::    2 ) -  Recherches dans la bibliotheque                     ::\n"\
           "\t::    3 ) -  Suppression d'un livre                              ::\n"\
           "\t::    4 ) -  Ajout d'un livre                                    ::\n"\
           "\t::    5 ) -  Fusionner la bibliotheque avec une autre            ::\n"\
           "\t::    0 ) -  Quitter le programme                                ::\n"\
           "\t::                                                               ::\n"\
           "\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
}

void menu_recherche() {
    printf("\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"\
           "\t::                                                               ::\n"\
           "\t::        ** Veuillez choisir le type de recherche :             ::\n"\
           "\t::                                                               ::\n"\
           "\t::    1 ) -  Rechercher un ouvrage par son numero                ::\n"\
           "\t::    2 ) -  Rechercher un ouvrage par son titre                 ::\n"\
           "\t::    3 ) -  Rechercher tous les ouvrages d'un auteur            ::\n"\
           "\t::    4 ) -  Rechercher les ouvrages avec plusieurs exemplaires  ::\n"\
           "\t::    0 ) -  Annuler                                             ::\n"\
           "\t::                                                               ::\n"\
           "\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
}

void menu_output() {
    printf("\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"\
           "\t::                                                               ::\n"\
           "\t::        ** Veuillez choisir le flux de sortie :                ::\n"\
           "\t::                                                               ::\n"\
           "\t::    1 ) -  Affichage sur l'ecran                               ::\n"\
           "\t::    2 ) -  Ecriture dans un fichier                            ::\n"\
           "\t::    3 ) -  Affichage dans l'ecran et ecriture dans un fichier  ::\n"\
           "\t::                                                               ::\n"\
           "\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
}

int get_choix(int min, int max) {

    int choix = -1;

    while(choix < min || choix >= max)
        choix = saisir_int("\n\t\t - Votre choix : ");

    printf("\n");
    return choix;
}

int saisir_int(char *message) {

    int saisie;
    char BUFFER[BUFSIZ];

    while(1) {
        printf("%s", message);
        fgets(BUFFER, BUFSIZ, stdin);
        if(sscanf(BUFFER, " %d", &saisie) == 1)
            break;
    }

    return saisie;
}

void rechercher(Biblio *biblio) {
    int choix;
    menu_recherche();
    choix = get_choix(0, 5);

    if(choix == 0)
        return;
                
    switch (choix) {
        case 1: rechercher_livre_numero(biblio); break;
        case 2: rechercher_livre_titre(biblio); break;
        case 3: recherche_livres_auteur(biblio); break;
        case 4:recherche_ouvrages_exemplaire(biblio); break;
    }
}

void rechercher_livre_numero(Biblio *biblio) {
    int numero = saisir_int("\n\t - Entrer le numero de l'ouverage : ");
    printf("\n");

    Livre *livre = rechercher_biblio_numero(biblio, numero);
    if(!livre) {
        printf("\t >> Livre inexistant\n\n");
        return;
    }
                            
    afficher_livre(livre);
    printf("\n");
}

void rechercher_livre_titre(Biblio *biblio) {
    printf("\n\t - Veuillez saisir le titre du livre : ");
    char nom[BUFSIZ];
    fgets(nom, BUFSIZ, stdin);
    printf("\n");
        
    nom[strlen(nom)-1] = '\0';

    Livre *livre = rechercher_biblio_titre(biblio, nom);
    if(!livre) {
        printf("\t >> Livre inexistant\n\n");
        return;
    }

    afficher_livre(livre);
    printf("\n");
}

void recherche_livres_auteur(Biblio *biblio) {
    printf("\n\t - Veuillez saisir l'auteur des livres : ");

    char auteur[BUFSIZ];
    fgets(auteur,BUFSIZ,stdin);

    printf("\n");
        
    auteur[strlen(auteur)-1] = '\0';

    Biblio *bib = rechercher_biblio_auteur(biblio, auteur);
    if(!bib || !bib->livres) {
        printf("\t >> Aucun livres trouves\n\n");
       return;
    }
    
    printf("\t >> Les livres de l'auteurs : \n\n");
    afficher_biblio(bib);
    printf("\n");
}

void recherche_ouvrages_exemplaire(Biblio *biblio){
    Biblio *new = rechercher_exemplaires(biblio);

    if(!new || !new->livres) {
        printf("\t >> Aucun livres trouves\n\n");
        return;
    }

    menu_output();
    int choix = get_choix(1, 4);

    switch (choix) {
        case 1: {
            afficher_biblio(new);
            printf("\n");
            liberer_biblio(new);
            break;
        }

        case 2: {
            printf("\n\t - Veuillez saisir le nom du fichier : ");
            char nom_fic[BUFSIZ];
            fgets(nom_fic,BUFSIZ,stdin);
            printf("\n");
                
            nom_fic[strlen(nom_fic)-1] = '\0';

            enregister_biblio(new, nom_fic);
            liberer_biblio(new);
            break;
        }

        case 3: {

            afficher_biblio(new);
            printf("\n");

            printf("\n\t - Veuillez saisir le nom du fichier : ");
            char nom_fic[BUFSIZ];
            fgets(nom_fic,BUFSIZ,stdin);
            printf("\n");
                
            nom_fic[strlen(nom_fic)-1] = '\0';

            enregister_biblio(new, nom_fic);
            liberer_biblio(new);
            break;
        }
    }
} 