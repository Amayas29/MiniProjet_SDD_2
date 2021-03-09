#ifndef __ENTRE_SORTIE_H_H__
#define __ENTRE_SORTIE_H_H__

#include "biblioH.h"

BiblioH *charger_n_entrees_h(char *nomfic, int nombre_lignes ,int taille);
void enregister_biblio_h(BiblioH *biblio, char *nomfic);
void enregister_livres_h(LivreH *livres, char *nomfic);

#endif