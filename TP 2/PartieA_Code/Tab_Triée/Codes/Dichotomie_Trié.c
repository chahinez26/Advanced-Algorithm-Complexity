#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/***** CHARGER TABLEAU TRIÉ *****/
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

/***** RECHERCHE DICHOTOMIQUE *****/
int rechElets_Dicho(int tab[], int n, int x) {
    int debut = 0;
    int fin = n - 1;

    while (debut <= fin) {
        int milieu = (debut + fin) / 2;

        if (tab[milieu] == x)
            return 1;

        if (tab[milieu] < x)
            debut = milieu + 1;
        else
            fin = milieu - 1;
    }
    return 0;
}

/***** MESURE TEMPS HAUTE PRÉCISION *****/
double mesurerTempsDicho(int tab[], int n, int x) {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    volatile int r = rechElets_Dicho(tab, n, x);

    QueryPerformanceCounter(&end);
    return (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
}

int main() {

    int tailles[] = {100000, 200000, 400000, 600000, 800000,
                     1000000, 1200000, 1400000, 1600000, 1800000};

    FILE *excel = fopen("resultats_recherche_dicho.csv", "w");
    fprintf(excel, "Taille,Temps(s)\n");

    for (int t = 0; t < 10; t++) {

        int n = tailles[t];
        printf("\n--- Test Dicho n = %d ---\n", n);

        int *tabTrie = malloc(n * sizeof(int));

        // Charger tableau trié
        char fichier[100];
        sprintf(fichier, "data_trie_%d.txt", n);
        chargerTableau(fichier, tabTrie, n);

        // Pire cas : valeur non présente
        int x = tabTrie[n - 1] + 1000000;
        printf("%d",x);

        // Mesure du temps
        double temps = mesurerTempsDicho(tabTrie, n, x);

        printf("Temps dicho (n=%d) : %f s\n", n, temps);

        fprintf(excel, "%d,%f\n", n, temps);

        free(tabTrie);
    }

    fclose(excel);

    printf("\nFichier généré : resultats_recherche_dicho.csv\n");

    return 0;
}
