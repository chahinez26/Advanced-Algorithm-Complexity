#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* ================== ALGOS ================== */

// A1 : Basique
int estPremier1(long long n) {
    if (n < 2) return 0;
    for (long long i = 2; i < n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// A2 : Optimisé sqrt
int estPremier2(long long n) {
    if (n < 2) return 0;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// A3 : Saut des pairs
int estPremier3(long long n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// A4 : 6k ± 1
int estPremier4(long long n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;

    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    }
    return 1;
}

/* ================== MESURE DE TEMPS ================== */

double mesurer_temps(int (*fonction)(long long), long long N) {
    struct timespec deb, fin;
    long long duree_ns;
    volatile int res;
    int rep = 1;

    while (1) {
        clock_gettime(CLOCK_MONOTONIC, &deb);

        for (int i = 0; i < rep; i++)
            res = fonction(N);

        clock_gettime(CLOCK_MONOTONIC, &fin);

        duree_ns =
            (fin.tv_sec - deb.tv_sec) * 1000000000LL +
            (fin.tv_nsec - deb.tv_nsec);

        if (duree_ns > 5000000) break; // min 5ms
        rep *= 2;
        if (rep > 10000000) break;
    }

    return (duree_ns / 1e9) / rep;
}

/* ================== UTILS ================== */

int nombre_chiffres(long long n) {
    int c = 0;
    while (n > 0) {
        c++;
        n /= 10;
    }
    return c;
}

/* ================== MAIN ================== */

int main() {
    FILE *f_in = fopen("jeu_donnees_3.txt", "r");
    FILE *f_out = fopen("resultats_complexite.csv", "a");

    if (!f_in) {
        printf("❌ Erreur ouverture test_3.txt\n");
        return 1;
    }

    if (!f_out) {
        printf("❌ Erreur création resultats_complexite_3.csv\n");
        return 1;
    }

    // Si le fichier CSV est vide, écrire l'en-tête
    fseek(f_out, 0, SEEK_END);
    if (ftell(f_out) == 0) {
        fprintf(f_out, "N,Chiffres,Premier,A1(s),A2(s),A3(s),A4(s)\n");
        fflush(f_out);
    }

    long long N;

    printf("🚀 Début des tests...\n");

    while (fscanf(f_in, "%lld", &N) == 1) {

        printf("🔍 Test du nombre : %lld\n", N);

        double t1 = mesurer_temps(estPremier1, N);
        double t2 = mesurer_temps(estPremier2, N);
        double t3 = mesurer_temps(estPremier3, N);
        double t4 = mesurer_temps(estPremier4, N);

        int premier = estPremier4(N);
        int chiffres = nombre_chiffres(N);

        fprintf(f_out, "%lld,%d,%s,%.9f,%.9f,%.9f,%.9f\n",
                N,
                chiffres,
                premier ? "Premier" : "Non Premier",
                t1, t2, t3, t4);

        fflush(f_out);  // 👈 Sauvegarde directe après chaque ligne
    }

    fclose(f_in);
    fclose(f_out);

    printf("\n✅ Tous les tests sont terminés.\n");
    return 0;
}
