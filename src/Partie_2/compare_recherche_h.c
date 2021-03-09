#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "biblioH.h"
#include "entreeSortieHach.h"

int main(void) {

    BiblioH *biblio_h = charger_n_entrees("ressources/GdeBiblio.txt", 1000);

    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu_h;

    int numeros[] = {
           1,   25,  198,     23,   49,
         190,  356,  897,      2,    10,
        1029, 1893, 26387, 38942, 18937,
        3648, 9894,  7848,  4765,  9384
    };

    printf("\n\n____________________ Recherche par numéro ____________________\n\n");

    for (int i = 0; i < 20; i++) {   
        temps_initial = clock();
        rechercher_biblio_numero(biblio_h,numeros[i]);
        temps_final = clock();
        temps_cpu_h = ((double) (temps_final - temps_initial)) / CLOCKS_PER_SEC;
        printf(" >> Recherche par le numéro : %f\n",temps_cpu_h);
    }

    // ------------------------------------------------------------------------------

    printf("\n\n____________________ Recherche par livre ____________________\n\n");

    char *titres[] = {
           "CPQIUDQPNYLN", "FWKHOPKMCOQHNWNKUE",       "BUDPEHDMF", "KMLNOZJKPQPXR0", "IOHORDTQKVWC", 
        "SOTBUXEHOYCHIFS",     "LNQIIEZHIBHAIV", "TYXBGJZUMLLPXD0",           "FLDE",     "SKLUZUWS",
            "FGHVUVHEAJL",         "LKEJOBEZJK",  "RGHBGUZJDPZKJE",   "MPOOPJAPONAA",   "LMAATYCWJA",
                  "OIHPS",         "ALZNPMKLNS",      "POJOIBAAXA",      "KHJBVIUAW", "WMLOPAWPO"
    };

    for (int i = 0; i < 20; i++) {   
        temps_initial = clock();
        rechercher_biblio_titre(biblio_h,titres[i]);
        temps_final = clock();
        temps_cpu_h = ((double) (temps_final - temps_initial)) / CLOCKS_PER_SEC;
        printf(" >> Recherche par le titre %f\n",temps_cpu_h);
    }

    // ------------------------------------------------------------------------------

    printf("\n\n____________________ Recherche par auteur ____________________\n\n");
    
    char *auteurs[] = {
            "zrlkosnu",    "qnrajro", "efsarcbynecd", "wxwtwheibqv",  "aijvwcyau",
        "orxxvrwctdsn",  "ffewggftw",      "gwofojj",  "selsftsedu", "nxcxmjcxoh",
           "azdzlopxa", "wxcoizaaze",     "osqnoazc",  "aqbiubaiaz",   "cqsyubrz",
          "mazopwabal",  "bczvhjabx",     "nbwgycaz",      "amayas",      "hamid"
    };

    LivreH *livre_liste_h = NULL;
    for (int i = 0; i < 20; i++) {   
        temps_initial = clock();
        livre_liste_h = rechercher_biblio_auteur(biblio_h,auteurs[i]);
        temps_final = clock();
        temps_cpu_h = ((double) (temps_final - temps_initial)) / CLOCKS_PER_SEC;
        liberer_livres(livre_liste_h);
        printf(" >> Recherche par l'auteur : %f\n",temps_cpu_h);
    }

    liberer_biblio(biblio_h);
    return 0;
}