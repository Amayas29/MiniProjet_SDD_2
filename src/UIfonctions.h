#ifndef __UIFUNCTIONS_H__
#define __UIFUNCTIONS_H__

#include "biblioLC.h"

void menu();
void menu_recherche();
void menu_output();
int get_choix(int min, int max);
int saisir_int(char *message);
void rechercher(Biblio *biblio);
void rechercher_livre_numero(Biblio *biblio);
void rechercher_livre_titre(Biblio *biblio);
void recherche_livres_auteur(Biblio *biblio);
void recherche_ouvrages_exemplaire(Biblio *biblio);
void supprimer(Biblio *biblio);

#endif