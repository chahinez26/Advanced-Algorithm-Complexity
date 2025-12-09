#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Fonction 1 : Generer un tableau non trie aleatoire

void remplirTableau(int A[], int n){
    for(int i = 0; i < n; i++){
        A[i] = rand() % 1000;     // valeurs entre 0 et 999
    }
}


// Fonction 2 : Recherche du maximum et minimum (Approche Naeve)

void MaxEtMinA(int A[], int n, int* max, int* min){
    *max = A[0];
    *min = A[0];

    for(int i = 1; i < n; i++){
        if(A[i] > *max)
            *max = A[i];

        if(A[i] < *min)
            *min = A[i];
    }
}
// version compteur
int MaxEtMinAc(int A[], int n, int* max, int* min){
    int comp = 0;  // compteur de comparaisons

    *max = A[0];
    *min = A[0];

    for(int i = 1; i < n; i++){
        comp++; // comparaison pour max
        if(A[i] > *max)
            *max = A[i];

        comp++; // comparaison pour min
        if(A[i] < *min)
            *min = A[i];
    }

    return comp; // retourner le nombre total de comparaisons
}



// Fonction 3 : Recherche du maximum et minimum (Algorithme plus efficase)
void MaxEtMinB(int A[], int n, int* max, int* min){
    int start;

    // Cas oe n est pair : comparer A[0] et A[1]
    if(n % 2 == 0){
        if(A[0] > A[1]){
            *max = A[0];
            *min = A[1];
        } else {
            *max = A[1];
            *min = A[0];
        }
        start = 2;    // on commence e comparer e partir du 3eme element
    }
    // Cas oe n est impair : premier element tout seul
    else {
        *max = A[0];
        *min = A[0];
        start = 1;
    }

    // Parcours par paires
    for(int i = start; i < n - 1; i += 2){
        int grand, petit;

        // Comparaison du couple A[i] et A[i+1]
        if(A[i] > A[i+1]){
            grand = A[i];
            petit = A[i+1];
        }
        else {
            grand = A[i+1];
            petit = A[i];
        }

        // mise e jour du max
        if(grand > *max)
            *max = grand;

        // mise e jour du min
        if(petit < *min)
            *min = petit;
    }
}

// version compteur
int MaxEtMinBc(int A[], int n, int* max, int* min){
    int comp = 0;
    int start;

    // Cas pair
    if(n % 2 == 0){
        comp++; // comparaison entre A[0] et A[1]
        if(A[0] > A[1]){
            *max = A[0];
            *min = A[1];
        } else {
            *max = A[1];
            *min = A[0];
        }
        start = 2;
    }
    // Cas impair
    else {
        *max = *min = A[0];
        start = 1;
    }

    // Comparaison par paires
    for(int i = start; i < n - 1; i += 2){
        comp++;  // comparaison du couple (A[i], A[i+1])
        int grand, petit;

        if(A[i] > A[i+1]){
            grand = A[i];
            petit = A[i+1];
        } else {
            grand = A[i+1];
            petit = A[i];
        }

        comp++;  // comparaison pour mettre e jour max
        if(grand > *max)
            *max = grand;

        comp++;  // comparaison pour mettre e jour min
        if(petit < *min)
            *min = petit;
    }

    return comp;
}


// Programme principal
int main(){
    
   int n=100000;
   int A[100000];

    // Initialiser le random
    srand(time(NULL));

    // Remplir le tableau avec des valeurs aleatoires
    remplirTableau(A, n);

    // Afficher le tableau
    printf("\nTableau genere :\n");
    for(int i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
    printf("\n\n");

    // Chercher max et min
    int max, min;

     //MaxEtMinA(A, n, &max, &min);

    //MaxEtMinB(A, n, &max, &min);

    // Affichage du resultat
    //printf("Max = %d\n", max);
    //printf("Min = %d\n", min);

    int compA = MaxEtMinAc(A, n, &max, &min);
    printf("Methode A : max=%d, min=%d, comparaisons=%d\n", max, min, compA);

    int compB = MaxEtMinBc(A, n, &max, &min);
    printf("Methode B : max=%d, min=%d, comparaisons=%d\n", max, min, compB);




    return 0;
}
