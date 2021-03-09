#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../Partie_1/biblioLC.h"
#include "../Partie_1/entreeSortieLC.h"
#include "../Partie_2/biblioH.h"
#include "../Partie_2/entreeSortieHach.h"
#include "../commun.h"

int main(void) {

    Biblio *biblio_lc = charger_n_entrees_lc("../../ressources/GdeBiblio.txt", 1000);
    if(!biblio_lc) {
        print_probleme("Erreur de chargement");
        return 1;
    }

    BiblioH *biblio_h = charger_n_entrees_h("../../ressources/GdeBiblio.txt", 1000);
    if(!biblio_h) {
        print_probleme("Erreur de chargement");
        liberer_biblio_lc(biblio_lc);
        return 1;
    }

    FILE *file_numeros = fopen("file_numeros.log","w");
    if(!file_numeros) {
        print_probleme("Erreur de chargement");
        liberer_biblio_h(biblio_h);
        liberer_biblio_lc(biblio_lc);
        return 1;
    }

    FILE *file_titres = fopen("file_titres.log","w");
    if(!file_titres) {
        print_probleme("Erreur de chargement");
        liberer_biblio_h(biblio_h);
        liberer_biblio_lc(biblio_lc);
        fclose(file_numeros);
        return 1;
    }

    FILE *file_auteurs = fopen("file_auteurs.log","w");
    if(!file_auteurs) {
        print_probleme("Erreur de chargement");
        liberer_biblio_h(biblio_h);
        liberer_biblio_lc(biblio_lc);
        fclose(file_numeros);
        fclose(file_titres);
        return 1;
    }

    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu_lc;
    double temps_cpu_h;
    
    int numeros[] = {
           1,   25,  198,     23,   49,
         190,  356,  897,      2,    10,
        1029, 1893, 26387, 38942, 18937,
        3648, 9894,  7848,  4765,  9384
    };

    for (int i = 0; i < 20; i++) {

        temps_initial = clock();
        rechercher_biblio_numero_lc(biblio_lc, numeros[i]);
        temps_final = clock();
        temps_cpu_lc = ((double) (temps_final - temps_initial)) / CLOCKS_PER_SEC;
        
        temps_initial = clock();
        rechercher_biblio_numero_h(biblio_h, numeros[i]);
        temps_final = clock();
        temps_cpu_h = ((double) (temps_final - temps_initial)) / CLOCKS_PER_SEC;

        fprintf(file_numeros,"%d %f %f\n", numeros[i], temps_cpu_lc, temps_cpu_h);
    }

    // ------------------------------------------------------------------------------
   
    char *titres[] = {
           "CPQIUDQPNYLN", "FWKHOPKMCOQHNWNKUE",       "BUDPEHDMF", "KMLNOZJKPQPXR0", "IOHORDTQKVWC", 
        "SOTBUXEHOYCHIFS",     "LNQIIEZHIBHAIV", "TYXBGJZUMLLPXD0",           "FLDE",     "SKLUZUWS",
            "FGHVUVHEAJL",         "LKEJOBEZJK",  "RGHBGUZJDPZKJE",   "MPOOPJAPONAA",   "LMAATYCWJA",
                  "OIHPS",         "ALZNPMKLNS",      "POJOIBAAXA",      "KHJBVIUAW", "WMLOPAWPO"
    };

    for (int i = 0; i < 20; i++) {   

        temps_initial = clock();
        rechercher_biblio_titre_lc(biblio_lc, titres[i]);
        temps_final = clock();
        temps_cpu_lc = ((double) (temps_final - temps_initial)) / CLOCKS_PER_SEC;

        temps_initial = clock();
        rechercher_biblio_titre_h(biblio_h, titres[i]);
        temps_final = clock();
        temps_cpu_h = ((double) (temps_final - temps_initial)) / CLOCKS_PER_SEC;

        fprintf(file_titres,"%s %f %f\n", titres[i], temps_cpu_lc, temps_cpu_h);
    }

    // ------------------------------------------------------------------------------
    
    char *auteurs[] = {
            "zrlkosnu",    "qnrajro", "efsarcbynecd", "wxwtwheibqv",  "aijvwcyau",
        "orxxvrwctdsn",  "ffewggftw",      "gwofojj",  "selsftsedu", "nxcxmjcxoh",
           "azdzlopxa", "wxcoizaaze",     "osqnoazc",  "aqbiubaiaz",   "cqsyubrz",
          "mazopwabal",  "bczvhjabx",     "nbwgycaz",      "amayas",      "hamid"
    };

    Biblio *biblio_search = NULL;
    LivreH *livre_liste_h = NULL;

    for (int i = 0; i < 20; i++) {   

        temps_initial = clock();
        biblio_search =  rechercher_biblio_auteur_lc(biblio_lc, auteurs[i]);
        temps_final = clock();
        temps_cpu_lc = ((double) (temps_final - temps_initial)) / CLOCKS_PER_SEC;

        liberer_biblio_lc(biblio_search);

        temps_initial = clock();
        livre_liste_h = rechercher_biblio_auteur_h(biblio_h, auteurs[i]);
        temps_final = clock();
        temps_cpu_h = ((double) (temps_final - temps_initial)) / CLOCKS_PER_SEC;

        liberer_livres_h(livre_liste_h);

        fprintf(file_titres,"%s %f %f\n", auteurs[i], temps_cpu_lc, temps_cpu_h);       
    }

    liberer_biblio_lc(biblio_lc);
    liberer_biblio_h(biblio_h);
    fclose(file_numeros);
    fclose(file_titres);
    fclose(file_auteurs);
    return 0;
}