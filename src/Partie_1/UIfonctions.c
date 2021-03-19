#include "UIfonctions.h"

#include <stdio.h>
#include <string.h>

#include "../commun.h"
#include "entreeSortieLC.h"

static void rechercher_livre_numero(Biblio *biblio);
static void rechercher_livre_titre(Biblio *biblio);
static void recherche_livres_auteur(Biblio *biblio);
static void recherche_ouvrages_exemplaire(Biblio *biblio);

void menu() {
    printf(
        "\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
        "\t::                                                               ::\n"
        "\t::        ** Veuillez choisir une action :                       ::\n"
        "\t::                                                               ::\n"
        "\t::    1 ) -  Affichage de la bibliotheque                        ::\n"
        "\t::    2 ) -  Recherches dans la bibliotheque                     ::\n"
        "\t::    3 ) -  Suppression d'un livre                              ::\n"
        "\t::    4 ) -  Ajout d'un livre                                    ::\n"
        "\t::    5 ) -  Fusionner la bibliotheque avec une autre            ::\n"
        "\t::    6 ) -  Enregistrer la bibliotheque                         ::\n"
        "\t::    0 ) -  Quitter le programme                                ::\n"
        "\t::                                                               ::\n"
        "\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
}

void menu_recherche() {
    printf(
        "\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
        "\t::                                                               ::\n"
        "\t::        ** Veuillez choisir le type de recherche :             ::\n"
        "\t::                                                               ::\n"
        "\t::    1 ) -  Rechercher un ouvrage par son numero                ::\n"
        "\t::    2 ) -  Rechercher un ouvrage par son titre                 ::\n"
        "\t::    3 ) -  Rechercher tous les ouvrages d'un auteur            ::\n"
        "\t::    4 ) -  Rechercher les ouvrages avec plusieurs exemplaires  ::\n"
        "\t::    0 ) -  Annuler                                             ::\n"
        "\t::                                                               ::\n"
        "\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
}

void menu_output() {
    printf(
        "\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
        "\t::                                                               ::\n"
        "\t::        ** Veuillez choisir le flux de sortie :                ::\n"
        "\t::                                                               ::\n"
        "\t::    1 ) -  Affichage sur l'ecran                               ::\n"
        "\t::    2 ) -  Ecriture dans un fichier                            ::\n"
        "\t::    3 ) -  Affichage dans l'ecran et ecriture dans un fichier  ::\n"
        "\t::                                                               ::\n"
        "\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
}

int get_choix(int min, int max) {
    int choix = -1;

    while (choix < min || choix >= max)
        choix = saisir_int("\n\t\t - Votre choix : ");

    printf("\n");
    return choix;
}

int saisir_int(char *message) {
    int saisie;
    char BUFFER[BUFSIZ];

    while (1) {
        printf("%s", message);
        fgets(BUFFER, BUFSIZ, stdin);
        if (sscanf(BUFFER, " %d", &saisie) == 1)
            break;
    }

    return saisie;
}

void rechercher(Biblio *biblio) {
    if (!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }

    int choix;
    menu_recherche();
    choix = get_choix(0, 5);

    if (choix == 0)
        return;

    switch (choix) {
        case 1:
            rechercher_livre_numero(biblio);
            break;
        case 2:
            rechercher_livre_titre(biblio);
            break;
        case 3:
            recherche_livres_auteur(biblio);
            break;
        case 4:
            recherche_ouvrages_exemplaire(biblio);
            break;
    }
}

static void rechercher_livre_numero(Biblio *biblio) {
    int numero = saisir_int("\n\t - Entrer le numero de l'ouverage : ");
    printf("\n");

    Livre *livre = rechercher_biblio_numero_lc(biblio, numero);
    if (!livre) {
        printf("\t >> Livre inexistant\n\n");
        return;
    }

    afficher_livre_lc(livre);
    printf("\n");
}

static void rechercher_livre_titre(Biblio *biblio) {
    printf("\n\t - Veuillez saisir le titre du livre : ");
    char nom[BUFSIZ];
    fgets(nom, BUFSIZ, stdin);
    printf("\n");

    nom[strlen(nom) - 1] = '\0';

    Livre *livre = rechercher_biblio_titre_lc(biblio, nom);
    if (!livre) {
        printf("\t >> Livre inexistant\n\n");
        return;
    }

    afficher_livre_lc(livre);
    printf("\n");
}

static void recherche_livres_auteur(Biblio *biblio) {
    printf("\n\t - Veuillez saisir l'auteur des livres : ");

    char auteur[BUFSIZ];
    fgets(auteur, BUFSIZ, stdin);

    printf("\n");

    auteur[strlen(auteur) - 1] = '\0';

    Biblio *bib = rechercher_biblio_auteur_lc(biblio, auteur);
    if (!bib || !bib->livres) {
        printf("\t >> Aucun livres trouves\n\n");
        liberer_biblio_lc(bib);
        return;
    }

    printf("\t >> Les livres de l'auteurs : \n\n");
    afficher_biblio_lc(bib);
    printf("\n");
    liberer_biblio_lc(bib);
}

static void recherche_ouvrages_exemplaire(Biblio *biblio) {
    Biblio *new = rechercher_exemplaires_lc(biblio);

    if (!new || !new->livres) {
        printf("\t >> Aucun livres trouves\n\n");
        liberer_biblio_lc(new);
        return;
    }

    menu_output();
    int choix = get_choix(1, 4);

    switch (choix) {
        case 1: {
            afficher_biblio_lc(new);
            printf("\n");
            break;
        }

        case 2: {
            printf("\n\t - Veuillez saisir le nom du fichier : ");
            char nom_fic[BUFSIZ];
            fgets(nom_fic, BUFSIZ, stdin);
            printf("\n");

            nom_fic[strlen(nom_fic) - 1] = '\0';

            enregister_biblio_lc(new, nom_fic);
            break;
        }

        case 3: {
            afficher_biblio_lc(new);
            printf("\n");

            printf("\n\t - Veuillez saisir le nom du fichier : ");
            char nom_fic[BUFSIZ];
            fgets(nom_fic, BUFSIZ, stdin);
            printf("\n");

            nom_fic[strlen(nom_fic) - 1] = '\0';

            enregister_biblio_lc(new, nom_fic);
            break;
        }
    }

    liberer_biblio_lc(new);
}

void supprimer(Biblio *biblio) {
    if (!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }

    int numero;
    char titre[BUFSIZ];
    char auteur[BUFSIZ];

    numero = saisir_int("\n\t - Veuillez inserer le numero du livre : ");

    printf("\n\t - Veuillez inserer le titre du livre : ");
    fgets(titre, BUFSIZ, stdin);
    titre[strlen(titre) - 1] = '\0';

    printf("\n\t - Veuillez inserer l'auteur du livre : ");
    fgets(auteur, BUFSIZ, stdin);
    auteur[strlen(auteur) - 1] = '\0';

    if (suppression_ouverage_lc(biblio, numero, titre, auteur)) {
        printf("\n\t >> La suppresion est bien effectuee\n\n");
        return;
    }

    printf("\n\t >> La suppresion c'est mal passee\n\n");
}

void ajouter(Biblio *biblio) {
    if (!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }

    int numero;
    char titre[BUFSIZ];
    char auteur[BUFSIZ];

    numero = saisir_int("\n\t - Veuillez inserer le numero du livre : ");

    printf("\n\t - Veuillez inserer le titre du livre : ");
    fgets(titre, BUFSIZ, stdin);
    titre[strlen(titre) - 1] = '\0';

    printf("\n\t - Veuillez inserer l'auteur du livre : ");
    fgets(auteur, BUFSIZ, stdin);
    auteur[strlen(auteur) - 1] = '\0';

    if (!existe_lc(biblio, numero, titre, auteur)) {
        inserer_en_tete_lc(biblio, numero, titre, auteur);
        printf("\n");
        return;
    }

    printf("\n\t - Livre deja existant\n");
}

void fusionner(Biblio *biblio) {
    printf("\n\t - Veuillez saisir le nom du fichier : ");
    char nom_fic[BUFSIZ];
    fgets(nom_fic, BUFSIZ, stdin);
    printf("\n");

    nom_fic[strlen(nom_fic) - 1] = '\0';

    int lignes = saisir_int("\n\t - Veuillez saisir le nombre de lignes : ");

    Biblio *new = charger_n_entrees_lc(nom_fic, lignes);

    if (!new)
        return;

    fusion_biblios_lc(biblio, new);

    printf("\n\t >> Fusion effectuée\n\n");
}

void enregistrer(Biblio *biblio) {
    if (!biblio)
        return;

    printf("\n\t - Veuillez saisir le nom du fichier : ");
    char nom_fic[BUFSIZ];
    fgets(nom_fic, BUFSIZ, stdin);
    printf("\n");

    nom_fic[strlen(nom_fic) - 1] = '\0';

    enregister_biblio_lc(biblio, nom_fic);

    printf("\n\t >> Enregistrement effectué\n\n");
}