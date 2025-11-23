#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*===========================================================
                  ALGORITHMES DE PRIMALITÉ
===========================================================*/

// Algorithme 1 : O(N)
int estPremier1(int N) {
    if (N <= 1) return 0;
    for (int i = 2; i < N; i++)
        if (N % i == 0) return 0;
    return 1;
}

// Algorithme 2 : O(N/2)
int estPremier2(int N) {
    if (N <= 1) return 0;
    for (int i = 2; i <= N/2; i++)
        if (N % i == 0) return 0;
    return 1;
}

// Algorithme 3 : O(√N)
int estPremier3(int N) {
    if (N <= 1) return 0;
    int limite = (int)sqrt(N);
    for (int i = 2; i <= limite; i++)
        if (N % i == 0) return 0;
    return 1;
}

// Algorithme 4 : Optimisé (pairs + √N)
int estPremier4(int N) {
    if (N == 2) return 1;
    if (N <= 1 || N % 2 == 0) return 0;
    int limite = (int)sqrt(N);
    for (int i = 3; i <= limite; i += 2)
        if (N % i == 0) return 0;
    return 1;
}

/*===========================================================
                    LECTURE FICHIER TEXTE
===========================================================*/

// Charge un fichier dans un tableau dynamique
int* lire_fichier(const char *nom_fichier, int *taille) {
    FILE *f = fopen(nom_fichier, "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir %s\n", nom_fichier);
        return NULL;
    }

    int capacite = 100;
    int *tab = malloc(capacite * sizeof(int));
    if (!tab) {
        perror("Erreur allocation");
        fclose(f);
        return NULL;
    }

    int val;
    *taille = 0;

    while (fscanf(f, "%d", &val) == 1) {
        if (*taille >= capacite) {
            capacite *= 2;
            tab = realloc(tab, capacite * sizeof(int));
            if (!tab) {
                perror("Erreur realloc");
                fclose(f);
                return NULL;
            }
        }
        tab[*taille] = val;
        (*taille)++;
    }

    fclose(f);
    return tab;
}

/*===========================================================
              TESTER UN FICHIER AVEC LES 4 ALGOS
===========================================================*/

void tester_fichier(const char *nom_fichier) {
    printf("\n\n=====================================================\n");
    printf("   TEST DU FICHIER : %s\n", nom_fichier);
    printf("=====================================================\n");

    int taille;
    int *nombres = lire_fichier(nom_fichier, &taille);

    if (!nombres || taille == 0) {
        printf("Aucun nombre à tester dans %s\n", nom_fichier);
        return;
    }

    printf("Nombre de valeurs : %d\n", taille);

    clock_t deb, fin;
    double t1, t2, t3, t4;

    for (int i = 0; i < taille; i++) {
        int N = nombres[i];

        deb = clock();
        estPremier1(N);
        fin = clock();
        t1 = (double)(fin - deb) / CLOCKS_PER_SEC;

        deb = clock();
        estPremier2(N);
        fin = clock();
        t2 = (double)(fin - deb) / CLOCKS_PER_SEC;

        deb = clock();
        estPremier3(N);
        fin = clock();
        t3 = (double)(fin - deb) / CLOCKS_PER_SEC;

        deb = clock();
        estPremier4(N);
        fin = clock();
        t4 = (double)(fin - deb) / CLOCKS_PER_SEC;

        printf("N = %10d | A1: %.6f s | A2: %.6f s | A3: %.6f s | A4: %.6f s\n",
               N, t1, t2, t3, t4);
    }

    free(nombres);
}

/*===========================================================
                          MAIN
===========================================================*/

int main() {
    printf("========== DEBUT DU PROGRAMME ==========\n");

    tester_fichier("Random100.txt");
    tester_fichier("Random1000.txt");
    tester_fichier("Test-1.txt");
    tester_fichier("Test-2.txt");
    tester_fichier("Test-3.txt");

    printf("\n========== FIN DU PROGRAMME ==========\n");
    return 0;
}
