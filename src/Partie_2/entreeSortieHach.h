#ifndef __ENTRE_SORTIE_H_H__
#define __ENTRE_SORTIE_H_H__

#include "biblioH.h"

//Permet de cree et de charger un bibliotheque d'un fichier
BiblioH *charger_n_entrees_h(char *nomfic, int nombre_lignes, int taille);

//Permet d'enregisterer une bibliotheue dans un fichier
void enregister_biblio_h(BiblioH *biblio, char *nomfic);

//Permet d'enregisterer une liste de livres dans un fichier
void enregister_livres_h(LivreH *livres, char *nomfic);

#endif