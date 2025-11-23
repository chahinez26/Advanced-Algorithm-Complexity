#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Algorithme 1 : Approche naive
int estPremier1(int N) {
    if(N == 0 || N == 1) 
        return 0;
    else {
        for(int i = 2; i <= N-1; i++)
            if(N % i == 0) 
                return 0; 
        return 1; 
    }
}

// Algorithme 2 : Amélioration de l'approche naive
int estPremier2(int N) {
    if(N == 0 || N == 1) 
        return 0;
    else {
        for(int i = 2; i <= N/2; i++)
            if(N % i == 0) 
                return 0;
        return 1;
    }
}

// Algorithme 3 : Optimisation avec racine carrée
int estPremier3(int N) {
    if(N == 0 || N == 1) 
        return 0;
    else {
        for(int i = 2; i <= sqrt(N); i++)
            if(N % i == 0) 
                return 0;
        return 1;
    }
}

// Algorithme 4 : Optimisation pour nombres pairs
int estPremier4(int N) {
    if (N == 2) return 1;
    if (N == 0 || N == 1 || N % 2 == 0) 
        return 0;

    for (int i = 3; i <= sqrt(N); i += 2)
        if (N % i == 0)
            return 0;

    return 1;
}

int main() {
    printf("Debut du programme...\n");
    int taille_test = 12;
    int nb_tests[12] = {1000003,2000003,4000037,8000009,16000057, 32000011,64000031,  
                             128000003,256000001,512000009,1024000009,2048000011}; 
    
    double *temps_algo1 = malloc(taille_test * sizeof(double));
    double *temps_algo2 = malloc(taille_test * sizeof(double));
    double *temps_algo3 = malloc(taille_test * sizeof(double));
    double *temps_algo4 = malloc(taille_test * sizeof(double));

    if (!temps_algo1 || !temps_algo2 || !temps_algo3 || !temps_algo4) {
        perror("Erreur allocation temps");
        return 1;
    }

    clock_t deb, fin;

    /* TEST ALGORITHME 1 */
    printf("\n=========== TEST ALGORITHME 1 (Approche naive) ==========\n");
    for (int i = 0; i < taille_test; i++) {
        deb = clock();
        int res = estPremier1(nb_tests[i]);
        fin = clock();
        temps_algo1[i] = (double)(fin - deb) / CLOCKS_PER_SEC;

        printf("N = %10d | Temps: %.6f s | Premier: %s\n",
               nb_tests[i], temps_algo1[i], res ? "OUI" : "NON");
    }

    /* TEST ALGORITHME 2 */
    printf("\n========== TEST ALGORITHME 2 (Optimisation N/2) ==========\n");
    for (int i = 0; i < taille_test; i++) {
        deb = clock();
        int res = estPremier2(nb_tests[i]);
        fin = clock();
        temps_algo2[i] = (double)(fin - deb) / CLOCKS_PER_SEC;

        printf("N = %10d | Temps: %.6f s | Premier: %s\n",
               nb_tests[i], temps_algo2[i], res ? "OUI" : "NON");
    }

    /* TEST ALGORITHME 3 */
    printf("\n========== TEST ALGORITHME 3 (Optimisation √N) ==========\n");
    for (int i = 0; i < taille_test; i++) {
        deb = clock();
        int res = estPremier3(nb_tests[i]);
        fin = clock();
        temps_algo3[i] = (double)(fin - deb) / CLOCKS_PER_SEC;

        printf("N = %10d | Temps: %.6f s | Premier: %s\n",
               nb_tests[i], temps_algo3[i], res ? "OUI" : "NON");
    }

    /* TEST ALGORITHME 4 */
    printf("\n========== TEST ALGORITHME 4 (Optimisation pairs) ==========\n");
    for (int i = 0; i < taille_test; i++) {
        deb = clock();
        int res = estPremier4(nb_tests[i]);
        fin = clock();
        temps_algo4[i] = (double)(fin - deb) / CLOCKS_PER_SEC;

        printf("N = %10d | Temps: %.6f s | Premier: %s\n",
               nb_tests[i], temps_algo4[i], res ? "OUI" : "NON");
    }

    free(temps_algo1);
    free(temps_algo2);
    free(temps_algo3);
    free(temps_algo4);

    printf("\nFin du programme.\n");
    return 0;
}
