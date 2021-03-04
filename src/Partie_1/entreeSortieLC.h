#ifndef __ENTRE_SORTIE_H__
#define __ENTRE_SORTIE_H__

#include "biblioLC.h"

Biblio *charger_n_entrees(char *nomfic, int nombre_lignes);
void enregister_biblio(Biblio *biblio, char *nomfic);

#endif