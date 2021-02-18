#include <stdlib.h>
#include <stdio.h>
#include "commun.h"
#include "entreeSortieLC.h"

int main(int argc, char **argv) {

    if(argc != 3) {
        fprintf(stderr, "Manque d'arguments. \nUsage %s <nom fichier> <nombre lignes>\n", argv[0]);
        return 1;
    }

    argc --;
    argv ++;

    int lignes = atoi(argv[1]);
    Biblio *biblio = charger_n_entrees(argv[0], lignes);
    liberer_biblio(biblio);

    return 0;
}