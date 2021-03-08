# Mini Projet 02 Structure de données

**Membre du binome**

- Amayas Sadi 28717408
- Hamid  28717594

---

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
