#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction pour compter le nombre de chiffres d’un entier
int nb_chiffres(int n) {
    int c = 0;
    if (n == 0) return 1;
    while (n > 0) {
        n /= 10;
        c++;
    }
    return c;
}

int main() {
    printf("Debut du programme...\n");

    // --- LECTURE DU FICHIER DE NOMBRES PREMIERS ---
    FILE *f = fopen("primes10.txt", "r");
    if (!f) {
        perror("Erreur ouverture fichier prime10.txt");
        return 1;
    }

    printf("Lecture dynamique du fichier...\n");

    int max_read = 100000;      // Limite de securite
    int *nombres = malloc(max_read * sizeof(int));
    if (!nombres) {
        perror("Erreur d'allocation memoire");
        fclose(f);
        return 1;
    }

    int n = 0;
    while (n < max_read && fscanf(f, "%d", &nombres[n]) == 1) {
        n++;
    }
    fclose(f);

    printf("Fichier charge : %d nombres lus.\n", n);
    srand(time(NULL));

    // -------------------------------------------------------------
    // 1. Random100
    // -------------------------------------------------------------
    printf("-----------------------------------------------------------\n");
    printf(" 1. Random100 \n");

    FILE *out1 = fopen("Random100.txt", "w");
    if (!out1) {
        perror("Erreur creation Random100.txt");
        free(nombres);
        return 1;
    }

    for (int i = 0; i < 100; i++) {
        int index = rand() % n;
        fprintf(out1, "%d\n", nombres[index]);
    }
    fclose(out1);
    printf("Random100.txt cree.\n");


    // -------------------------------------------------------------
    // 2. Random1000
    // -------------------------------------------------------------
    printf("-----------------------------------------------------------\n");
    printf(" 2. Random1000 \n");

    FILE *out2 = fopen("Random1000.txt", "w");
    if (!out2) {
        perror("Erreur creation Random1000.txt");
        free(nombres);
        return 1;
    }

    for (int i = 0; i < 1000; i++) {
        int index = rand() % n;
        fprintf(out2, "%d\n", nombres[index]);
    }
    fclose(out2);
    printf("Random1000.txt cree.\n");


    // -------------------------------------------------------------
    // 3. Test-1 : 100 nombres entre [1000, 1 000 000]
    // -------------------------------------------------------------
    printf("-----------------------------------------------------------\n");
    printf(" 3. Test-1 : [1000, 1000000] \n");

    FILE *f1 = fopen("Test-1.txt", "w");
    if (!f1) {
        perror("Erreur creation Test-1.txt");
        free(nombres);
        return 1;
    }

    int count = 0;
    while (count < 100) {
        int val = nombres[rand() % n];
        if (val >= 1000 && val <= 1000000) {
            fprintf(f1, "%d\n", val);
            count++;
        }
    }
    fclose(f1);
    printf("Test-1.txt cree.\n");


    // -------------------------------------------------------------
    // 4. Test-2 : 10 nombres par nombre de chiffres
    // -------------------------------------------------------------
    printf("-----------------------------------------------------------\n");
    printf(" 4. Test-2 : 10 nombres premiers par nombre de chiffres (1 à 7)\n");
    FILE *f2 = fopen("Test-2.txt", "w");
    if (!f2) {
     perror("Erreur creation Test-2.txt");
     free(nombres);
    return 1;
  }

    for (int digits = 3; digits <= 9; digits++) {

    int count_d = 0;
    int essais = 0;
    int max_essais = n * 3; // Limite pour eviter boucle infinie

    while (count_d < 20 && essais < max_essais) {
        int val = nombres[rand() % n];
        if (nb_chiffres(val) == digits) {
            fprintf(f2, "%d\n", val);
            count_d++;
        }
        essais++;
    }


    fprintf(f2, "\n");
}

   fclose(f2);
   printf(" Test-2.txt cree \n");

    free(nombres);

    return 0;
}
