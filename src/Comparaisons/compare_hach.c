#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../Partie_2/biblioH.h"
#include "../Partie_2/entreeSortieHach.h"
#include "../commun.h"

#define NB_ITERATION 10000

int main(int argc, char *argv[]) {

    char *src_name = argv[ 0 ];

    argc--;
    argv++;

    if (argc != 2) {
        fprintf(stderr, "Manque de parametre.\n >> Usage %s <file_name> <nombre de lignes>\n", src_name);
        return 1;
    }

    int lignes = atoi(argv[1]);

    FILE *file_hach = fopen("file_hach.log", "w");
    if(!file_hach) {
        print_probleme("Erreur de chargement");
        return 1;
    }

    BiblioH *biblio_h = NULL;
    
    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu_h;
    
    char *auteurs[] = {
            "zrlkosnu",    "qnrajro", "efsarcbynecd", "wxwtwheibqv",  "aijvwcyau",
        "orxxvrwctdsn",  "ffewggftw",      "gwofojj",  "selsftsedu", "nxcxmjcxoh",
           "azdzlopxa", "wxcoizaaze",     "osqnoazc",  "aqbiubaiaz",   "cqsyubrz",
          "mazopwabal",  "bczvhjabx",     "nbwgycaz",      "amayas",      "hamid"
    };

    LivreH *liste = NULL;
    for(int taille = 1; taille <= NB_ITERATION; taille++) {

        biblio_h = charger_n_entrees_h(argv[0], lignes, taille);
        if(!biblio_h) {
            print_probleme("Erreur de chargement");
            fclose(file_hach);
            return 1;
        }

        temps_initial = clock();
        for (int i = 0; i < 20; i++) {
            liste = rechercher_biblio_auteur_h(biblio_h, auteurs[ i ]);
            liberer_livres_h(liste);
        }
        temps_final = clock();

        temps_cpu_h = ((double) (temps_final - temps_initial)) / CLOCKS_PER_SEC;

        fprintf(file_hach,"%d %f\n", taille, temps_cpu_h);
        liberer_biblio_h(biblio_h);
    }

    fclose(file_hach);
    return 0;
}