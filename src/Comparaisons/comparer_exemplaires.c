#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../Partie_1/biblioLC.h"
#include "../Partie_1/entreeSortieLC.h"
#include "../Partie_2/biblioH.h"
#include "../Partie_2/entreeSortieHach.h"
#include "../commun.h"

#define NB_ITERATION 50000

int main(void) {
    // On ouvre le fichier ou enregistrer les temps
    FILE *file_exemplaires = fopen("file_exemplaires.log", "w");
    if (!file_exemplaires) {
        print_probleme("Erreur de chargement");
        return 1;
    }

    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu_lc;
    double temps_cpu_h;

    Biblio *biblio_lc = NULL;
    BiblioH *biblio_h = NULL;

    Biblio *liste_lc = NULL;
    LivreH *liste_h = NULL;

    // On varie la taille de 1000 jusqu'à NB_ITERATION (par defaut c'est 50000)
    for (int taille = 1000; taille <= NB_ITERATION; taille += 1000) {
        // On charge les bibliotheques

        biblio_lc = charger_n_entrees_lc("../../ressources/GdeBiblio.txt", taille);
        if (!biblio_lc) {
            print_probleme("Erreur de chargement");
            fclose(file_exemplaires);
            return 1;
        }

        biblio_h = charger_n_entrees_h("../../ressources/GdeBiblio.txt", taille, taille);
        if (!biblio_h) {
            print_probleme("Erreur de chargement");
            liberer_biblio_lc(biblio_lc);
            fclose(file_exemplaires);
            return 1;
        }

        // On lance les recherches d'exemplaires et on calcule les temps pour chaque verision
        temps_initial = clock();
        liste_lc = rechercher_exemplaires_lc(biblio_lc);
        temps_final = clock();
        temps_cpu_lc = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

        temps_initial = clock();
        liste_h = rechercher_exemplaires_h(biblio_h);
        temps_final = clock();
        temps_cpu_h = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

        fprintf(file_exemplaires, "%d %f %f\n", taille, temps_cpu_lc, temps_cpu_h);

        // On libere la memoire alloue à la fin du tour pour passer au suivant
        liberer_livres_h(liste_h);
        liberer_biblio_lc(liste_lc);
        liberer_biblio_lc(biblio_lc);
        liberer_biblio_h(biblio_h);
    }

    fclose(file_exemplaires);
    return 0;
}