#ifndef __ENTRE_SORTIE_H__
#define __ENTRE_SORTIE_H__

#include "biblioLC.h"

Biblio *charger_n_entrees_lc(char *nomfic, int nombre_lignes);
void enregister_biblio_lc(Biblio *biblio, char *nomfic);

#endif