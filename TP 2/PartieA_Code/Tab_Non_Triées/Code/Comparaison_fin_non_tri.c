#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/*************** CHARGER TABLEAU ****************/
void chargerTableau(char *nomFichier, int tab[], int n) {
    FILE *f = fopen(nomFichier, "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir %s\n", nomFichier);
        exit(1);
    }
    for (int i = 0; i < n; i++)
        fscanf(f, "%d", &tab[i]);
    fclose(f);
}

/*************** ALGO 1 : Séquentiel simple ***************/
int rechSeqSimple(int tab[], int n, int x) {
    for (int i = 0; i < n; i++)
        if (tab[i] == x)
            return 1;
    return 0;
}

/*************** ALGO 2 : Séquentiel optimisé ***************/
int rechSeqOpti(int tab[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (tab[i] == x)
            return 1;
        if (tab[i] > x)
            return 0;
    }
    return 0;
}

/*************** ALGO 3 : Dichotomie ***************/
int rechDicho(int tab[], int n, int x) {
    int deb = 0, fin = n - 1;
    while (deb <= fin) {
        int mid = (deb + fin) / 2;
        if (tab[mid] == x)
            return 1;
        if (tab[mid] < x)
            deb = mid + 1;
        else
            fin = mid - 1;
    }
    return 0;
}

/*************** MESURE TEMPS (windows) ***************/
double mesurer(int (*func)(int[], int, int),
               int tab[], int n, int x, int *retour) {

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    QueryPerformanceCounter(&start);
    volatile int r = func(tab, n, x);
    QueryPerformanceCounter(&end);

    *retour = r;
    return (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
}

/*********************** MAIN *************************/
int main() {

    int tailles[] = {100000,200000,400000,600000,800000,
                     1000000,1200000,1400000,1600000,1800000};

    FILE *csv = fopen("comparaison_algorithmes.csv", "w");
    fprintf(csv, "Taille,SeqSimple,SeqOpti,Dicho\n");

    printf("===== Début des tests (tableaux triés) =====\n");

    for (int t = 0; t < 10; t++) {

        int n = tailles[t];
        printf("\n--- Test n = %d ---\n", n);

        int *tabTrie = malloc(n * sizeof(int));

        char fichier[100];
        sprintf(fichier, "data_non_trie_%d.txt", n);

        chargerTableau(fichier, tabTrie, n);

        /* PIRE CAS : x n'existe pas */
        int x = 100000000;

        int ret;
        double t1, t2, t3;

        /***** Algo 1 : Séquentiel simple *****/
        t1 = mesurer(rechSeqSimple, tabTrie, n, x, &ret);
        printf("Seq Simple : %f s -> %s\n", t1, ret ? "Trouvé" : "Non trouvé");

        /***** Algo 2 : Séquentiel optimisé *****/
        t2 = mesurer(rechSeqOpti, tabTrie, n, x, &ret);
        printf("Seq Opti   : %f s -> %s\n", t2, ret ? "Trouvé" : "Non trouvé");

        /***** Algo 3 : Dichotomie *****/
        t3 = mesurer(rechDicho, tabTrie, n, x, &ret);
        printf("Dicho      : %f s -> %s\n", t3, ret ? "Trouvé" : "Non trouvé");

        /* Sauvegarde CSV */
        fprintf(csv, "%d,%f,%f,%f\n", n, t1, t2, t3);

        free(tabTrie);
    }

    fclose(csv);

    printf("\n===== Tests terminés =====\n");
    printf("Fichier généré : comparaison_algorithmes.csv\n");

    return 0;
}
