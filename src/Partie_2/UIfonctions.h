#ifndef __UIFUNCTIONS_H__
#define __UIFUNCTIONS_H__

#include "biblioH.h"

//permet d'afficher le menu pricipale
void menu();

//permet d'afficher le menu de recherche
void menu_recherche();

//permet d'afficher le menu pour choisir le flux de sortie pour l'enregistrement
void menu_output();

//permet de tester les message utilisateur pour les menu en s'assurant de la bonne saisie 
int get_choix(int min, int max);

//permet de recuperer un entier en affichant un message
int saisir_int(char *message);

//permet de gerer les recherche selon le leurs types
void rechercher(BiblioH *biblio);

//permet de gerer la suppression dans une bibliotheque
void supprimer(BiblioH *biblio);

//permet les gerer les ajouts des livres
void ajouter(BiblioH *biblio);

//permet de gerer la fusion de deux bibliotheque (la deuxieme est donnée  sous forme d'un fichier en stdin)
void fusionner(BiblioH *biblio);

//permet de sauvgarder la bibliotheque dans un fichier donner
void enregistrer(BiblioH *biblio);

#endif