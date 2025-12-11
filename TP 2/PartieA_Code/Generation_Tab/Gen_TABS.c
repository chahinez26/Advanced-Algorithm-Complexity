#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction pour créer un tableau non trié rempli de valeurs aléatoires
void genererTableauNonTrie(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        tab[i] = rand() % 1000000; // valeurs aléatoires entre 0 et 999999
    }
}

// Fonction pour copier un tableau
void copierTableau(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

// Fonction de comparaison pour qsort()
int comparer(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Fonction pour trier un tableau
void trierTableau(int tab[], int n) {
    qsort(tab, n, sizeof(int), comparer);
}

void sauvegarderTableau(char *nomFichier, int tab[], int n) {
    FILE *f = fopen(nomFichier, "w");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir %s\n", nomFichier);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d\n", tab[i]);
    }

    fclose(f);
}

int main() {
    srand(time(NULL));

    int tailles[] = {100000, 200000, 400000, 600000, 800000,
                     1000000, 1200000, 1400000, 1600000, 1800000};

    int nbTests = 10;

    for (int t = 0; t < nbTests; t++) {

        int n = tailles[t];
        printf("\n--- Génération des données pour n = %d ---\n", n);

        int *tabNonTrie = malloc(n * sizeof(int));
        int *tabTrie    = malloc(n * sizeof(int));

        // 1) Générer le tableau non trié
        genererTableauNonTrie(tabNonTrie, n);

        // 2) Sauvegarder le tableau non trié
        char fichierNonTrie[100];
        sprintf(fichierNonTrie, "data_non_trie_%d.txt", n);
        sauvegarderTableau(fichierNonTrie, tabNonTrie, n);

        // 3) Copier et trier
        copierTableau(tabNonTrie, tabTrie, n);
        trierTableau(tabTrie, n);

        // 4) Sauvegarder le tableau trié
        char fichierTrie[100];
        sprintf(fichierTrie, "data_trie_%d.txt", n);
        sauvegarderTableau(fichierTrie, tabTrie, n);

        // (Plus tard : ici on fera les recherches A.1, A.2, A.3)

        free(tabNonTrie);
        free(tabTrie);
    }

    return 0;
}

