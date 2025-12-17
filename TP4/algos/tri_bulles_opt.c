#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ========================================
// TRI À BULLES - VERSION OPTIMISÉE
// Complexité: O(n²) pire cas, O(n) meilleur cas
// Optimisation: arrêt si aucun échange n'est effectué
// ========================================

/**
 * Tri à bulles optimisé
 * S'arrête si aucun échange n'est effectué (tableau déjà trié)
 */
void tri_bulles_optimise(int tab[], int n) {
    int i, j, temp;
    int echange; // Flag pour détecter si un échange a été fait
    
    for (i = 0; i < n - 1; i++) {
        echange = 0; // Aucun échange au début de chaque passage
        
        for (j = 0; j < n - i - 1; j++) {
            if (tab[j] > tab[j + 1]) {
                // Échange des éléments
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
                echange = 1; // Un échange a été effectué
            }
        }
        
        // Si aucun échange n'a été fait, le tableau est trié
        if (echange == 0) {
            break;
        }
    }
}

/**
 * Génère un tableau avec des valeurs aléatoires
 */
void generer_aleatoire(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        tab[i] = rand() % 100000;
    }
}

/**
 * Génère un tableau trié en ordre croissant
 */
void generer_croissant(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        tab[i] = i;
    }
}

/**
 * Génère un tableau trié en ordre décroissant
 */
void generer_decroissant(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        tab[i] = n - i;
    }
}

/**
 * Copie un tableau source vers un tableau destination
 */
void copier_tableau(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

/**
 * Affiche une barre de progression avec couleurs
 */
void afficher_progression(int actuel, int total, const char* nom_algo) {
    int pourcentage = (actuel * 100) / total;
    int barres_remplies = (pourcentage * 40) / 100;
    
    // Couleurs ANSI
    const char* VERT = "\033[32m";
    const char* CYAN = "\033[36m";
    const char* JAUNE = "\033[33m";
    const char* RESET = "\033[0m";
    const char* GRAS = "\033[1m";
    
    // Choisir la couleur selon le pourcentage
    const char* couleur;
    if (pourcentage < 33) couleur = JAUNE;
    else if (pourcentage < 66) couleur = CYAN;
    else couleur = VERT;
    
    // Effacer la ligne et afficher
    printf("\r%s%-30s%s ", GRAS, nom_algo, RESET);
    
    printf("[");
    for (int i = 0; i < 40; i++) {
        if (i < barres_remplies) {
            printf("%s█%s", couleur, RESET);
        } else if (i == barres_remplies && pourcentage % (100/40) > 0) {
            printf("%s▓%s", couleur, RESET);
        } else {
            printf("░");
        }
    }
    printf("]");
    
    printf(" %s%3d%%%s", couleur, pourcentage, RESET);
    printf(" (%d/%d)", actuel, total);
    
    fflush(stdout);
    
    if (actuel == total) {
        printf(" %s✓ Terminé!%s\n", VERT, RESET);
    }
}

/**
 * Convertit un double en chaîne avec virgule comme séparateur décimal
 */
void double_to_french_string(double value, char* buffer) {
    sprintf(buffer, "%.6f", value);
    // Remplacer le point par une virgule
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '.') {
            buffer[i] = ',';
            break;
        }
    }
}

// Note: Fonction de vérification du tri
int verifier_tri(int T[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (T[i] > T[i + 1]) {
            return 0; // Pas trié
        }
    }
    return 1; // Trié correctement
}

int main() {
    // Initialisation du générateur aléatoire
    srand(time(NULL));
    
    // Tailles de tableaux à tester
    int tailles[] = {100, 500, 1000, 5000, 10000, 50000, 100000};
    int nb_tailles = 7;
    
    // Types de tests
    char* types[] = {"aleatoire", "croissant", "decroissant"};
    int nb_types = 3;
    
    // Nombre de répétitions par test
    int nb_repetitions = 10;
    
    // Calcul du nombre total de tests
    int total_tests = nb_tailles * nb_types * nb_repetitions;
    int test_actuel = 0;
    
    // Codes couleur pour l'affichage
    const char* VERT = "\033[32m";
    const char* CYAN = "\033[36m";
    const char* JAUNE = "\033[33m";
    const char* RESET = "\033[0m";
    const char* GRAS = "\033[1m";
    
    // Ouverture du fichier CSV
    FILE* fichier = fopen("resultats_tri_bulles_opt.csv", "w");
    if (fichier == NULL) {
        printf("%sErreur: impossible de créer le fichier CSV%s\n", JAUNE, RESET);
        return 1;
    }
    
    // Écriture de l'en-tête du CSV
    fprintf(fichier, "Taille;Type_Test;Temps_Moyen(s);Temps_Min(s);Temps_Max(s);Complexite_Theorique\n");
    
    // En-tête stylisé
    printf("\n");
    printf("%s╔══════════════════════════════════════════════════════════════╗%s\n", CYAN, RESET);
    printf("%s║       TRI À BULLES - VERSION OPTIMISÉE - TESTS              ║%s\n", CYAN, RESET);
    printf("%s╚══════════════════════════════════════════════════════════════╝%s\n", CYAN, RESET);
    printf("\n");
    printf("%sConfiguration:%s\n", GRAS, RESET);
    printf("  • Tailles testées: ");
    for (int i = 0; i < nb_tailles; i++) {
        printf("%d%s", tailles[i], (i < nb_tailles - 1) ? ", " : "\n");
    }
    printf("  • Types de tests: aléatoire, croissant, décroissant\n");
    printf("  • Répétitions par test: %d\n", nb_repetitions);
    printf("  • Total de tests: %s%d%s\n\n", GRAS, total_tests, RESET);
    
    printf("%sDébut des tests...%s\n\n", VERT, RESET);
    
    clock_t debut_global = clock();
    
    // Boucle sur les tailles
    for (int t = 0; t < nb_tailles; t++) {
        int taille = tailles[t];
        
        // Allocation des tableaux
        int* tab_original = (int*)malloc(taille * sizeof(int));
        int* tab_test = (int*)malloc(taille * sizeof(int));
        
        if (tab_original == NULL || tab_test == NULL) {
            printf("%sErreur d'allocation mémoire pour taille %d%s\n", JAUNE, taille, RESET);
            continue;
        }
        
        // Boucle sur les types de tests
        for (int type = 0; type < nb_types; type++) {
            // Génération du tableau selon le type
            if (type == 0) {
                generer_aleatoire(tab_original, taille);
            } else if (type == 1) {
                generer_croissant(tab_original, taille);
            } else {
                generer_decroissant(tab_original, taille);
            }
            
            double temps_total = 0.0;
            double temps_min = 1e9;
            double temps_max = 0.0;
            
            // 10 répétitions pour chaque configuration
            for (int rep = 0; rep < nb_repetitions; rep++) {
                // Copie du tableau original
                copier_tableau(tab_original, tab_test, taille);
                
                // Mesure du temps
                clock_t debut = clock();
                tri_bulles_optimise(tab_test, taille);
                clock_t fin = clock();
                
                double temps = (double)(fin - debut) / CLOCKS_PER_SEC;
                temps_total += temps;
                
                if (temps < temps_min) temps_min = temps;
                if (temps > temps_max) temps_max = temps;
                
                // Vérification que le tri est correct
                if (!verifier_tri(tab_test, taille)) {
                    printf("\n%sERREUR: Le tableau n'est pas correctement trié!%s\n", JAUNE, RESET);
                }
                
                test_actuel++;
                
                // Créer un message détaillé pour la progression
                char message[100];
                snprintf(message, sizeof(message), 
                         "Tri Bulles Opt [n=%d, %s]", 
                         taille, types[type]);
                
                afficher_progression(test_actuel, total_tests, message);
            }
            
            // Calcul de la moyenne
            double temps_moyen = temps_total / nb_repetitions;
            
            // Conversion des nombres au format français (virgule décimale)
            char str_moyen[50], str_min[50], str_max[50];
            double_to_french_string(temps_moyen, str_moyen);
            double_to_french_string(temps_min, str_min);
            double_to_french_string(temps_max, str_max);
            
            // Écriture dans le CSV (format français: ; et ,)
            fprintf(fichier, "%d;%s;%s;%s;%s;O(n²) pire cas - O(n) meilleur cas\n", 
                    taille, types[type], str_moyen, str_min, str_max);
            fflush(fichier); // Forcer l'écriture immédiate
        }
        
        // Libération de la mémoire
        free(tab_original);
        free(tab_test);
    }
    
    clock_t fin_global = clock();
    double temps_total_global = (double)(fin_global - debut_global) / CLOCKS_PER_SEC;
    
    // Fermeture du fichier
    fclose(fichier);
    
    // Résumé final stylisé
    printf("\n\n");
    printf("%s╔══════════════════════════════════════════════════════════════╗%s\n", VERT, RESET);
    printf("%s║                    TESTS TERMINÉS ✓                         ║%s\n", VERT, RESET);
    printf("%s╚══════════════════════════════════════════════════════════════╝%s\n", VERT, RESET);
    printf("\n");
    printf("%sRésumé:%s\n", GRAS, RESET);
    printf("  • Nombre total de tests: %s%d%s\n", CYAN, total_tests, RESET);
    printf("  • Temps total d'exécution: %s%.2f secondes%s\n", CYAN, temps_total_global, RESET);
    printf("  • Fichier généré: %sresultats_tri_bulles_opt.csv%s\n", VERT, RESET);
    printf("\n");
    
    return 0;
}
