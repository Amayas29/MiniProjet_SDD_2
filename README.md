# Mini Projet 02 Structure de données

**Membre du binome**

- Amayas Sadi 28717408
- Hamid Kolli 28717594

---

*NB : On a modifier les noms des fonctions pour ne pas avoir des conflits lors des include des deux version (liste et table de hachage)*

*Les fonctions des listes sont suffixes pas `_lc` et celle des tables de hachages par `_h`*

## Exercice 01

### Q 1.1 

- Voici les signatures des fonctions manipulant les listes de livres :

```c
#ifndef __BIBLIOLC_H__
#define __BIBLIOLC_H__

typedef struct livre {
    int num;
    char *titre;
    char *auteur;
    struct livre *suiv;
} Livre;

typedef struct {
    Livre *livres;
} Biblio;

//permet de cree et retourner un livre
Livre *creer_livre_lc(int num, char *titre, char *auteur);

//permet de liberer la memoire
void liberer_livre_lc(Livre *livre);

//permet d'afficher un livre
void afficher_livre_lc(Livre *livre);

//permet de cree une bibliotheque
Biblio *creer_biblio_lc();

//permet de liberer une bibliotheque
void liberer_biblio_lc(Biblio *biblio);

//permet d'inserer un livre a la bibliotheque
void inserer_en_tete_lc(Biblio *biblio, int num, char *titre, char *auteur);

//permet dafficher tous les livres d'une bibliotheque
void afficher_biblio_lc(Biblio *biblio);

//permet de rechercher un livre dans une bibliotheque selon son nom
Livre *rechercher_biblio_numero_lc(Biblio *biblio, int numero);

//permet de rechercher un livre dans une bibliotheque selon son titre
Livre *rechercher_biblio_titre_lc(Biblio *biblio, char *titre);

//permet de rechercher tous les livres d'un auteur dans une bibliotheque
Biblio *rechercher_biblio_auteur_lc(Biblio *biblio, char *auteur);

//permet de supprimer un ouvrage dans une bibliotheque
int suppression_ouverage_lc(Biblio *biblio, int numero, char *titre, char *auteur);

//permet de fusionner deux bblioteque 
void fusion_biblios_lc(Biblio *src, Biblio *dest);

//permet de trouver tous les livres qui ont des exemplaire dans une bibliotheque
Biblio *rechercher_exemplaires_lc(Biblio *biblio);

//permet de retourner si un livre est present dans une bibliotheque
int existe_lc(Biblio *biblio, int numero, char *titre, char *auteur);

#endif
```

### Q 1.2

- Les fonctions manipulant les listes :

```c
Livre *creer_livre_lc(int num, char *titre, char *auteur) {
    
    if(!titre || !auteur) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    //on alloue la structure 
    Livre *livre = (Livre *) malloc(sizeof(Livre));
    if(!livre) {
        print_probleme("Erreur d'allocation");
        return NULL;
    }

    //on remplie les champs de la structure
    livre->num = num;
    livre->titre = strdup(titre);
    livre->auteur = strdup(auteur);

    return livre;
}

void liberer_livre_lc(Livre *livre) {

    if(!livre)
        return;
    //on libere les pointeurs et le livre
    free(livre->titre);
    free(livre->auteur);
    free(livre);
}

Biblio *creer_biblio_lc() {
    
    //on alloue la structure Biblio
    Biblio *biblio = (Biblio *) malloc(sizeof(Biblio));

    if(!biblio) {
        print_probleme("Erreur d'allocation");
        return NULL;
    }

    //on initialise ses champs a null
    biblio->livres = NULL;
    return biblio;
}

void liberer_biblio_lc(Biblio *biblio) {

    if(!biblio)
        return;

    Livre *tmp = NULL; 
    //on libere la memoire de tous les elements de la liste 
    while(biblio->livres) {
        tmp = biblio->livres->suiv;
        liberer_livre_lc(biblio->livres);
        biblio->livres = tmp;
    }
    
    
    free(biblio);
}

void inserer_en_tete_lc(Biblio *biblio, int num, char *titre, char *auteur) {
    
    if(!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }

    //on cree un livre
    Livre *livre = creer_livre_lc(num, titre, auteur);
    if(!livre)
        return;
    //on insert le livre en tete de liste 
    livre->suiv = biblio->livres;
    biblio->livres = livre;
}
```

### Q 1.3

```c
//permet de charger une bibliotheque de nombre de livres donnée en parametre a partir d'un fichier 
Biblio *charger_n_entrees_lc(char *nomfic, int nombre_lignes);

//permet de sauvgarder une bibliotheque dans un ficher
void enregister_biblio_lc(Biblio *biblio, char *nomfic);
```

- Le code des fonctions

```c
Biblio *charger_n_entrees_lc(char *nomfic, int nombre_lignes) {

    //ouverture du fichier
    FILE *file = fopen(nomfic, "r");
    if(!file) {
        print_probleme("Erreur d'ouverture du fichier");
        return NULL;
    }

    //on cree une bibliotheque
    Biblio *biblio = creer_biblio_lc();
    if(!biblio) {
        fclose(file);
        return NULL;
    }

    char BUFFER[512];
    int numero;
    char titre[256];
    char auteur[256];
    /*
    on parcours le fichier et on ajoute les nombre de ligne lu dans le fichier dans une bibliotheque 
    la boucle s'arrete si on a atteint le nombre de ligne demander ou la fin du fichier
    */
    for(int ligne = 0; ligne < nombre_lignes && fgets(BUFFER, 512, file); ligne++) {

        //on teste si on a bien lu 3 données sur une ligne, sionon on desaloue tous les structure allouer et on return null
        if(sscanf(BUFFER, "%d %s %s\n", &numero, titre, auteur) != 3) {
            print_probleme("Erreur de lecture depuis le fichiers");
            fclose(file);
            liberer_biblio_lc(biblio);
            return NULL;
        }
        /*
        si la lecture des données dans une ligne est bien passé on les insert dans la bibliotheque
        la fonction inserer cree un livre en utilisant les données lu
        */
        inserer_en_tete_lc(biblio, numero, titre, auteur);
    }

    fclose(file);
    return biblio;
}

void enregister_biblio_lc(Biblio *biblio, char *nomfic) {

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }
    // on ouvre e fichier en ecriture
    FILE *file = fopen(nomfic, "w");
    if(!file) {
        print_probleme("Erreur d'ouverture du fichier");
        return;
    }
    //on parcours tous les livres de la bibliotheque et on les ajoute au fichier
    for(Livre *livre = biblio->livres; livre; livre = livre->suiv)
        fprintf(file, "%d %s %s\n", livre->num, livre->titre, livre->auteur);
    
    fclose(file);
}
```

### Q 1.4

```c
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
```

### Q 1.5

*NB : On a déviser les partie chaque partie dans un dossier, du coup chaque partie contient son propre Makefile*

- Makefile Partie_1

```bash

CFLAGS = -Wall -g
CC = gcc
PROGS = mainListe 

all : $(PROGS)

# --------------------------------------------

mainListe : biblioLC.o entreeSortieLC.o UIfonctions.o mainListe.o
	$(CC) $(CFLAGS) -o $@ $^

mainListe.o : mainListe.c entreeSortieLC.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

biblioLC.o : biblioLC.c biblioLC.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

entreeSortieLC.o : entreeSortieLC.c entreeSortieLC.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

UIfonctions.o : UIfonctions.c UIfonctions.h entreeSortieLC.h biblioLC.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

# --------------------------------------------

clean :
	rm -rf $(PROGS) *.o
```

### Q 1.6

```c

void afficher_livre_lc(Livre *livre) {

      if(!livre) {
        print_probleme("Pointeur non valide");
        return;
    }
    
    printf("\t >> %d %s %s\n", livre->num, livre->titre, livre->auteur);
}

void afficher_biblio_lc(Biblio *biblio) {
    
    if(!biblio) {
        print_probleme("Pointeur non valide");
        return;
    }

    //on parcours tous les livres et on les affiche 
    for(Livre *livre = biblio->livres; livre; livre = livre->suiv)
        afficher_livre_lc(livre);
}

Livre *rechercher_biblio_numero_lc(Biblio *biblio, int numero) {
    
    if(!biblio) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    /*
    on recherche le livre, on parcours la liste tant qu'on a pas trouver le bon element 
    on arrete des qu'on trouve l'element recherché qui est le livre en fonction de son numero ou la fin de la liste  
    */
    Livre *livre = biblio->livres;
    //on fait l'initialisation avant la boucle for pour recuperer le livre
    for(; livre && livre->num != numero; livre = livre->suiv);

    return livre;
}

Livre *rechercher_biblio_titre_lc(Biblio *biblio, char *titre) {

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return NULL;
    }

    //on parcours tant qu'on trouve pas l'element, et on returne le livre si il existe sinon null
    Livre *livre = biblio->livres;
    for(; livre && strcmp(livre->titre, titre) != 0; livre = livre->suiv);

    return livre;
}

Biblio *rechercher_biblio_auteur_lc(Biblio *biblio, char *auteur) {

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return NULL;
    }
    // on cree une nouvelle bibliotheque (qui est une liste de livre) pour stoquer les livres trouver
    Biblio *new = creer_biblio_lc();
    if(!new)
        return NULL;
    
    //on cherche les livres par leur auteur et on les ajoute dans la bibliotheque cree
    for(Livre *livre = biblio->livres; livre; livre = livre->suiv) {
        if(strcmp(livre->auteur, auteur) == 0)
            inserer_en_tete_lc(new, livre->num, livre->titre, livre->auteur);
    }

    return new;
}

static int compare_livres_lc(Livre *livre, int numero, char *titre, char *auteur) {
    //returne si les deux livre sont egaux 
    return livre && livre->num == numero && strcmp(livre->titre, titre) == 0 && strcmp(livre->auteur, auteur) == 0; 
}

int suppression_ouverage_lc(Biblio *biblio, int numero, char *titre, char *auteur) {
    
    if(!biblio) {
        print_probleme("Pointeur non valide");
        return 0;
    }

    Livre *curr = biblio->livres;
    //on teste si l'element est en tete de liste on le supprime et on returne true
    if(compare_livres_lc(biblio->livres, numero, titre, auteur)) {
        biblio->livres = curr->suiv;
        liberer_livre_lc(curr);
        return 1;
    }

    /*
    on parcours la liste (on utilise le suivant d'un element pour avoir le precedent qui est l'element lui meme)
    on sort de la boucle si l'element n'est pas trouver ou on est au dernier element de la liste
    */
    for(; curr && !compare_livres_lc(curr->suiv, numero, titre, auteur); curr = curr->suiv);

    
    Livre *supp = NULL;
    if(curr) {
        //on recupere l'element a supprimer
        supp = curr->suiv;
        //on attache le precedent au suivant de l'element
        curr->suiv = supp->suiv;
        //on libere l'element a supprimer et on returne 1
        liberer_livre_lc(supp);
        return 1;
    }

    //si l'element n'est pas dans la liste on returne false
    return 0;
}

void fusion_biblios_lc(Biblio *dest, Biblio *src) {
    
    if(!dest || !src) {
        print_probleme("Pointeur non valide");
        return;
    }

    int add;
    //on parcours les deux bibliotheque on ajoute les elements  de la deuxieme a la premiere si il n'existent pas 
    for(Livre *livre = src->livres; livre; livre = livre->suiv) {
        add = 1;
        for(Livre *tete = dest->livres; tete; tete = tete->suiv) {
            if(compare_livres_lc(livre, tete->num, tete->titre, tete->auteur)) {
                add = 0;
                break;
            }
        }
        if(add)
            inserer_en_tete_lc(dest, livre->num, livre->titre, livre->auteur);
    }
    //on libere la deuxieme bibliotheque 
    liberer_biblio_lc(src);
}

Biblio *rechercher_exemplaires_lc(Biblio *biblio) {

    Biblio *new_biblio = creer_biblio_lc();

    if(!new_biblio)
        return NULL;
    //on parcours toute la liste deux fois et on teste si l'element a un exemplaire on l'ajoute a la liste
    for(Livre *livre = biblio->livres; livre; livre = livre->suiv) {
        for(Livre *suivant = biblio->livres; suivant; suivant = suivant->suiv) {
            
            if(suivant == livre)
                continue;
            
            if(strcmp(livre->titre, suivant->titre) == 0 && strcmp(livre->auteur, suivant->auteur) == 0) {
                inserer_en_tete_lc(new_biblio, livre->num, livre->titre, livre->auteur);
                break;
            }
        }
    }
    //on returne la liste des exemplaire 
    return new_biblio;
}

int existe_lc(Biblio *biblio, int numero, char *titre, char *auteur) {
    if(!biblio)
        return 0;

    for(Livre *livre = biblio->livres; livre; livre = livre->suiv)
        if(compare_livres_lc(livre, numero, titre, auteur))
            return 1;
    
    return 0;
}
```

### Q 1.7

Le main est un systeme d'interaction avec l'utilisateur, il posséde plusieurs menus et donne la possibilité à l'utilisateur de choisir l'option qu'il veut executer, donc l'utilisateur pourra intéragir comme il le souhaite avec les fonctions *(Un jeu de tests)*

- *1er Menu*

![Menu](ressources/Images/menu1.png)

- *2eme Menu*

![Menu](ressources/Images/menu2.png)

...

### 1.8

- Pour les fonctions d'affichage on a ajouter un fichier `UIfonctions.c` et son entête `UIFonctions.h`, le voici

```c
#ifndef __UIFUNCTIONS_H__
#define __UIFUNCTIONS_H__

#include "biblioLC.h"

void menu();
void menu_recherche();
void menu_output();
int get_choix(int min, int max);
int saisir_int(char *message);
void rechercher(Biblio *biblio);
void supprimer(Biblio *biblio);
void ajouter(Biblio *biblio);
void fusionner(Biblio *biblio);
void enregistrer(Biblio *biblio);

#endif
```

* Voici le main final de la partie 1

```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../commun.h"
#include "entreeSortieLC.h"
#include "UIfonctions.h"

int main(int argc, char **argv) {

    //on teste si le nombre d'argument donnée en parametre est bien 3
    if(argc != 3) {
        fprintf(stderr, "Manque d'arguments. \nUsage %s <nom fichier> <nombre lignes>\n", argv[0]);
        return 1;
    }

    //on ignore le nom du l'executable du tableau 
    argc --;
    argv ++;

    //on cast la chaine de caractere en entier
    int lignes = atoi(argv[1]);
    
    //on alloue la bibioteque 
    Biblio *biblio = charger_n_entrees_lc(argv[0], lignes);

    if(!biblio) {
        print_probleme("Pointeur non valide");
        return 1;
    }

    printf("\n\t ** Bienvenu : \n\n");

    int choix;

    while(1) {

        printf("\t\t==================================================\n\n");

        menu();
        choix = get_choix(0, 7);

        if(choix == 0)
            break;

        switch (choix) {
            case 1: {
                afficher_biblio_lc(biblio);
                printf("\n");
                break;
            }
            case 2: rechercher(biblio); break;

            case 3: supprimer(biblio); break;

            case 4: ajouter(biblio); break;

            case 5: fusionner(biblio); break;

            case 6: enregistrer(biblio); break;
        }
    }

    //on libere la bibliotheque
    liberer_biblio_lc(biblio);
    printf("\n\t ** Merci au revoir\n");
    return 0;
}
```