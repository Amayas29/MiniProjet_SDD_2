#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "commun.h"
#include "entreeSortieLC.h"

static void menu();
static void menu_recherche();
static void menu_output();
static int get_choix(int min, int max);
static int saisir_int(char *message);
static void rechercher(Biblio *biblio);
static void rechercher_livre_numero(Biblio *biblio);
static void rechercher_livre_titre(Biblio *biblio);
static void recherche_livres_auteur(Biblio *biblio);
static void recherche_ouvrages_exemplaire(Biblio *biblio);

int main(int argc, char **argv) {

    if(argc != 3) {
        fprintf(stderr, "Manque d'arguments. \nUsage %s <nom fichier> <nombre lignes>\n", argv[0]);
        return 1;
    }

    argc --;
    argv ++;

    int lignes = atoi(argv[1]);
    Biblio *biblio = charger_n_entrees(argv[0], lignes);
    
    int choix;

    while(1) {
        menu();
        choix = get_choix(0, 6);

        if(choix == 0)
            break;

        switch (choix) {
            case 1: afficher_biblio(biblio); break;
            case 2: rechercher(biblio); break;
            case 3: break;
            case 4: break;
            case 5: break;
        }
    }

    liberer_biblio(biblio);
    return 0;
}

static void menu() {
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

static void menu_recherche() {
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

static void menu_output() {
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

static int get_choix(int min, int max) {

    int choix = -1;

    while(choix < min || choix >= max)
        choix = saisir_int("\n\t\t - Votre choix : ");

    printf("\n");
    return choix;
}

static int saisir_int(char *message) {

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

static void rechercher(Biblio *biblio){
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

static void rechercher_livre_numero(Biblio *biblio){
    int numero = saisir_int("\n\t - Entrer le numero de l'ouverage : ");
    printf("\n");

    Livre *livre = rechercher_biblio_numero(biblio, numero);
    if(!livre) {
        printf("\t >> Livre inexistant\n\n");
        return;
    }
                            
    printf("\t >> ");
    afficher_livre(livre);
    printf("\n");

}

static void rechercher_livre_titre(Biblio *biblio){
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

    printf("\t >> ");
    afficher_livre(livre);
    printf("\n");

}


static void recherche_livres_auteur(Biblio *biblio){
    printf("\n\t - Veuillez saisir l'auteur du livre : ");
    char auteur[BUFSIZ];
    fgets(auteur,BUFSIZ,stdin);
    printf("\n");
        
    auteur[strlen(auteur)-1] = '\0';

    Biblio *bib = rechercher_biblio_auteur(biblio, auteur);
    if(!bib || !bib->livres) {
        printf("\t >> Livre inexistant\n\n");
       return;
    }
    
    printf("\t >> Les livres de l'auteurs : \n");
    afficher_biblio(bib);
    printf("\n");

   
}

static void recherche_ouvrages_exemplaire(Biblio *biblio){
    
} 