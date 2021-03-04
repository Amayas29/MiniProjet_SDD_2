#ifndef __ENTRE_SORTIE_H__
#define __ENTRE_SORTIE_H__

#include "biblioH.h"

BiblioH *charger_n_entrees(char *nomfic, int nombre_lignes);
void enregister_biblio(BiblioH *biblio, char *nomfic);

#endif