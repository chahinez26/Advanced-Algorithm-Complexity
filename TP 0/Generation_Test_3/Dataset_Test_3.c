#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction 10^n
long long power10(int exp) {
    long long result = 1;
    for (int i = 0; i < exp; i++)
        result *= 10;
    return result;
}

// Génère un pas aléatoire (entre min et max)
long long random_step(long long min, long long max) {
    return min + rand() % (max - min + 1);
}

int main() {
    int nb_par_categorie;

    printf("Combien de nombres par categorie ? : ");
    scanf("%d", &nb_par_categorie);

    FILE *f = fopen("Jeu_données_3.txt", "w");
    if (!f) {
        printf("Erreur création fichier.\n");
        return 1;
    }

    srand(time(NULL));

    int tailles[] = {3, 6, 9, 12};

    fprintf(f, "=== Test-3 Dataset : Croissant + Aleatoire ===\n\n");

    for (int i = 0; i < 4; i++) {

        int chiffres = tailles[i];
        long long debut = power10(chiffres - 1);
        long long fin = power10(chiffres) - 1;

        fprintf(f, "[%d chiffres]\n", chiffres);

        long long valeur = debut;

        for (int j = 0; j < nb_par_categorie; j++) {

            fprintf(f, "%lld\n", valeur);

            // Saut aléatoire adaptable selon la taille
            long long step = random_step(1, power10(chiffres - 2));

            valeur += step;

            if (valeur > fin)
                valeur = debut + rand() % (fin - debut);
        }

        fprintf(f, "\n");
    }

    fclose(f);

    printf("✅ Test-3 dataset (croissant + aleatoire) créé avec succès !\n");

    return 0;
}
