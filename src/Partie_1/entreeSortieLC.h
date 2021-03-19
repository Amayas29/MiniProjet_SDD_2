#ifndef __ENTRE_SORTIE_LC_H__
#define __ENTRE_SORTIE_LC_H__

#include "biblioLC.h"

//permet de charger une bibliotheque de nombre de livres donnée en parametre a partir d'un fichier
Biblio *charger_n_entrees_lc(char *nomfic, int nombre_lignes);

//permet de sauvgarder une bibliotheque dans un ficher
void enregister_biblio_lc(Biblio *biblio, char *nomfic);

#endif