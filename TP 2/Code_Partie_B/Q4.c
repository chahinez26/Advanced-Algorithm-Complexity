#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ---------------------------------------------------
// Fonction : generer un tableau aleatoire
// ---------------------------------------------------
void remplirTableau(int A[], int n){
    for(int i = 0; i < n; i++){
        A[i] = rand() % 10;  // valeurs entre 0 et 99999
    }
}

// ---------------------------------------------------
// Methode A : Max et Min (naeve) + compteur
// ---------------------------------------------------
int MaxEtMinA(int A[], int n, int* max, int* min){
    int comp = 0;
    *max = A[0];
    *min = A[0];

    for(int i = 1; i < n; i++){
        comp++;
        if(A[i] > *max)
            *max = A[i];

        comp++;
        if(A[i] < *min)
            *min = A[i];
    }

    return comp;
}

// ---------------------------------------------------
// Methode B : Max et Min optimisee (par paires) + compteur
// ---------------------------------------------------
int MaxEtMinB(int A[], int n, int* max, int* min){
    int comp = 0;
    int start;

    if(n % 2 == 0){
        comp++;
        if(A[0] > A[1]){
            *max = A[0];
            *min = A[1];
        } else {
            *max = A[1];
            *min = A[0];
        }
        start = 2;
    } else {
        *max = *min = A[0];
        start = 1;
    }

    for(int i = start; i < n - 1; i += 2){
        comp++;
        int grand, petit;

        if(A[i] > A[i+1]){
            grand = A[i];
            petit = A[i+1];
        } else {
            grand = A[i+1];
            petit = A[i];
        }

        comp++;
        if(grand > *max)
            *max = grand;

        comp++;
        if(petit < *min)
            *min = petit;
    }

    return comp;
}

// ---------------------------------------------------
// Programme principal
// ---------------------------------------------------
int main(){

    srand(time(NULL));  // initialisation du random

    int n=1800000;
    //printf("Donner la taille du tableau n : ");
    //scanf("%d", &n);

    // allocation dynamique
    int* A = malloc(n * sizeof(int));
    if (A == NULL) {
        printf("Erreur d'allocation memoire\n");
        return 1;
    }

    remplirTableau(A, n);

    int max, min;
    clock_t debut, fin;
    double tempsA, tempsB;

    // ---- Temps pour la methode A ----
    debut = clock();
    int compA = MaxEtMinA(A, n, &max, &min);
    fin = clock();
    tempsA = (double)(fin - debut) / CLOCKS_PER_SEC;

    // ---- Temps pour la methode B ----
    debut = clock();
    int compB = MaxEtMinB(A, n, &max, &min);
    fin = clock();
    tempsB = (double)(fin - debut) / CLOCKS_PER_SEC;

    // ---- Affichage ----
    printf("\n========== RESULTATS ==========\n");
    printf("Taille du tableau : %d elements\n\n", n);

    printf("Methode A :\n");
    printf("   Comparaisons = %d\n", compA);
    printf("   Temps        = %f secondes\n\n", tempsA);

    printf("Methode B :\n");
    printf("   Comparaisons = %d\n", compB);
    printf("   Temps        = %f secondes\n\n", tempsB);

    return 0;
}
