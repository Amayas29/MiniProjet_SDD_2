#ifndef __UIFUNCTIONS_H__
#define __UIFUNCTIONS_H__

#include "biblioH.h"

void menu();
void menu_recherche();
void menu_output();
int get_choix(int min, int max);
int saisir_int(char *message);
void rechercher(BiblioH *biblio);
void supprimer(BiblioH *biblio);
void ajouter(BiblioH *biblio);
void fusionner(BiblioH *biblio);
void enregistrer(BiblioH *biblio);

#endif