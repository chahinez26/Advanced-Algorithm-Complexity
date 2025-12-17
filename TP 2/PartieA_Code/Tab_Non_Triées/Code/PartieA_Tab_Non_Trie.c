#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/****************************
 *     CHARGER TABLEAU
 ****************************/
void chargerTableau(char *nomFichier, int tab[], int n) {
    FILE *f = fopen(nomFichier, "r");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir %s\n", nomFichier);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &tab[i]);
    }

    fclose(f);
}

/****************************
 *  RECHERCHE NON TRIEE
 ****************************/
int rechElets_TabNonTries(int tab[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (tab[i] == x)
            return 1;
    }
    return 0;
}

/****************************
 * MESURE TEMPS DE RECHERCHE
 ****************************/
double mesurerTempsRecherche(int tab[], int n, int x) {
    clock_t start = clock();

    rechElets_TabNonTries(tab, n, x);

    clock_t end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

/****************************
 *            MAIN
 ****************************/
int main() {
    // Les tailles imposées
    int tailles[] = {
        100000, 200000, 400000, 600000, 800000,
        1000000, 1200000, 1400000, 1600000, 1800000
    };
    int nbTests = 10;

    // Fichier Excel (CSV)
    FILE *excel = fopen("resultats_recherche_non_triee.csv", "w");
    if (excel == NULL) {
        printf("Erreur : impossible de créer fichier CSV\n");
        return 1;
    }

    fprintf(excel, "Taille,Temps(s)\n");

    printf("==== Début des tests ====\n");

    for (int t = 0; t < nbTests; t++) {

        int n = tailles[t];
        printf("\n--- Chargement tableau de taille %d ---\n", n);

        // Allocation
        int *tab = malloc(n * sizeof(int));
        if (tab == NULL) {
            printf("Erreur malloc\n");
            return 1;
        }

        // Nom du fichier à charger
        char fichier[100];
        sprintf(fichier, "data_non_trie_%d.txt", n);

        // Charger données
        chargerTableau(fichier, tab, n);
        printf("tab[0] = %d, tab[n-1] = %d\n", tab[0], tab[n-1]);

        // PIRE CAS = dernier élément
        int x = tab[n - 1];

        // Mesure du temps
        double temps = mesurerTempsRecherche(tab, n, x);

        printf("Temps recherche (n=%d) : %f secondes\n", n, temps);

        // Sauvegarde dans Excel
        fprintf(excel, "%d,%f\n", n, temps);

        free(tab);
    }

    fclose(excel);

    printf("\n==== FIN | Fichier généré : resultats_recherche_non_triee.csv ====\n");

    return 0;
}
