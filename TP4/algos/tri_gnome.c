#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ========================================
// TRI GNOME
// Complexité: O(n²)
// Similaire au tri à bulles mais avec retour en arrière
// ========================================

/**
 * Tri Gnome
 * Compare l'élément courant avec le précédent
 * Si désordre: échange et recule, sinon avance
 */
void tri_gnome(int tab[], int n) {
    int i = 0;
    int temp;
    
    while (i < n) {
        if (i == 0 || tab[i] >= tab[i - 1]) {
            // Avancer si on est au début ou si l'ordre est bon
            i++;
        } else {
            // Échanger et reculer si désordre
            temp = tab[i];
            tab[i] = tab[i - 1];
            tab[i - 1] = temp;
            i--;
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
    
    // Ouverture du fichier CSV
    FILE* fichier = fopen("resultats_tri_gnome.csv", "w");
    if (fichier == NULL) {
        printf("Erreur: impossible de créer le fichier CSV\n");
        return 1;
    }
    
    // Écriture de l'en-tête du CSV
    fprintf(fichier, "Taille;Type_Test;Temps_Moyen(s);Temps_Min(s);Temps_Max(s);Complexite_Theorique\n");
    
    printf("=== TRI GNOME ===\n");
    printf("Début des tests...\n\n");
    
    // Boucle sur les tailles
    for (int t = 0; t < nb_tailles; t++) {
        int taille = tailles[t];
        
        // Allocation des tableaux
        int* tab_original = (int*)malloc(taille * sizeof(int));
        int* tab_test = (int*)malloc(taille * sizeof(int));
        
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
                tri_gnome(tab_test, taille);
                clock_t fin = clock();
                
                double temps = (double)(fin - debut) / CLOCKS_PER_SEC;
                temps_total += temps;
                
                if (temps < temps_min) temps_min = temps;
                if (temps > temps_max) temps_max = temps;
                
                test_actuel++;
                afficher_progression(test_actuel, total_tests, "Tri Gnome");
            }
            
            // Calcul de la moyenne
            double temps_moyen = temps_total / nb_repetitions;
            
            // Conversion des nombres au format français (virgule décimale)
            char str_moyen[50], str_min[50], str_max[50];
            double_to_french_string(temps_moyen, str_moyen);
            double_to_french_string(temps_min, str_min);
            double_to_french_string(temps_max, str_max);
            
            // Écriture dans le CSV (format français: ; et ,)
            fprintf(fichier, "%d;%s;%s;%s;%s;O(n²)\n", 
                    taille, types[type], str_moyen, str_min, str_max);
            fflush(fichier); // Forcer l'écriture immédiate
        }
        
        // Libération de la mémoire
        free(tab_original);
        free(tab_test);
    }
    
    // Fermeture du fichier
    fclose(fichier);
    
    printf("\n\n=== TESTS TERMINÉS ===\n");
    printf("Résultats enregistrés dans: resultats_tri_gnome.csv\n");
    
    return 0;
}
