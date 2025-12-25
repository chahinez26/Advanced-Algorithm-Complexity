#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void entasser_min(int tab[], int n, int i) {
    int plus_petit = i;      // Initialiser le plus petit comme racine
    int gauche = 2 * i + 1;  // Fils gauche
    int droite = 2 * i + 2;  // Fils droit
    int temp;
    
    // Si le fils gauche est plus petit que la racine
    if (gauche < n && tab[gauche] < tab[plus_petit]) {
        plus_petit = gauche;
    }
    // Si le fils droit est plus petit que le plus petit actuel
    if (droite < n && tab[droite] < tab[plus_petit]) {
        plus_petit = droite;
    }
    // Si le plus petit n'est pas la racine
    if (plus_petit != i) {
        // Échanger
        temp = tab[i];
        tab[i] = tab[plus_petit];
        tab[plus_petit] = temp;
        // Entasser récursivement le sous-arbre affecté
        entasser_min(tab, n, plus_petit);
    }
}

int supprimer_min(int tab[], int *taille_tas) {
    // Le minimum est à la racine (indice 0)
    int min = tab[0];
    
    // Remplacer la racine par le dernier élément
    tab[0] = tab[(*taille_tas) - 1];
    
    // Réduire la taille du tas
    (*taille_tas)--;
    
    // Réorganiser le tas pour maintenir la propriété de tas minimum
    entasser_min(tab, *taille_tas, 0);
    
    return min;
}


void construire_tas_min(int tab[], int n) {
    // Commencer par le dernier nœud non-feuille et remonter
    for (int i = n / 2 - 1; i >= 0; i--) {
        entasser_min(tab, n, i);
    }
}
void tri_tas_avec_supprimer_min(int tab[], int n) {
    // Etape 1: Construire le tas minimum
    construire_tas_min(tab, n);
    int* tab_trie = (int*)malloc(n * sizeof(int));
    if (tab_trie == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    int taille_tas = n;
    // Étape 2: Extraire tous les éléments avec supprimer_min()
    for (int i = 0; i < n; i++) {
        tab_trie[i] = supprimer_min(tab, &taille_tas);
    }
    // Étape 3: Copier les éléments triés dans le tableau original
    for (int i = 0; i < n; i++) {
        tab[i] = tab_trie[i];
    }
    free(tab_trie);
}


void afficher_tas(int tab[], int n) {
    printf("Tas: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void generer_aleatoire(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        tab[i] = rand() % 100000;
    }
}


void generer_croissant(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        tab[i] = i;
    }
}


void generer_decroissant(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        tab[i] = n - i;
    }
}

void copier_tableau(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

void afficher_progression(int actuel, int total, const char* nom_algo) {
    int pourcentage = (actuel * 100) / total;
    int barres_remplies = (pourcentage * 40) / 100;
    const char* VERT = "\033[32m";
    const char* CYAN = "\033[36m";
    const char* JAUNE = "\033[33m";
    const char* RESET = "\033[0m";
    const char* GRAS = "\033[1m";
    const char* couleur;
    if (pourcentage < 33) couleur = JAUNE;
    else if (pourcentage < 66) couleur = CYAN;
    else couleur = VERT;
    printf("\r%s%-30s%s ", GRAS, nom_algo, RESET);
    printf("[");
    for (int i = 0; i < 40; i++) {
        if (i < barres_remplies) printf("%s█%s", couleur, RESET);
        else if (i == barres_remplies && pourcentage % (100/40) > 0) printf("%s▓%s", couleur, RESET);
        else printf("░");
    }
    printf("]");
    printf(" %s%3d%%%s (%d/%d)", couleur, pourcentage, RESET, actuel, total);
    fflush(stdout);
    if (actuel == total) printf(" %s✓ Terminé!%s\n", VERT, RESET);
}

void double_to_french_string(double value, char* buffer) {
    sprintf(buffer, "%.6f", value);
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '.') { buffer[i] = ','; break; }
    }
}

int verifier_tri(int tab[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (tab[i] > tab[i + 1]) {
            return 0; // Pas trié
        }
    }
    return 1; // Trié
}

int main() {
    // Initialisation du générateur aléatoire
    srand(time(NULL));
    
    // === TESTS DE PERFORMANCE ===
    printf("=== TRI PAR TAS AVEC SUPPRIMER_MIN ===\n");
    printf("Début des tests de performance...\n\n");
    
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
    FILE* fichier = fopen("resultats_tri_tas_min.csv", "w");
    if (fichier == NULL) {
        printf("Erreur: impossible de créer le fichier CSV\n");
        return 1;
    }
    
    // Écriture de l'en-tête du CSV
    fprintf(fichier, "Taille;Type_Test;Temps_Moyen(s);Temps_Min(s);Temps_Max(s);Complexite_Theorique;Methode\n");
    
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
                tri_tas_avec_supprimer_min(tab_test, taille);
                clock_t fin = clock();
                
                double temps = (double)(fin - debut) / CLOCKS_PER_SEC;
                temps_total += temps;
                
                if (temps < temps_min) temps_min = temps;
                if (temps > temps_max) temps_max = temps;
                
                // Vérifier que le tri est correct
                if (!verifier_tri(tab_test, taille)) {
                    printf("\nERREUR: Le tableau n'est pas trié correctement!\n");
                    return 1;
                }
                
                test_actuel++;
                afficher_progression(test_actuel, total_tests, "Tri Tas (supprimer_min)");
            }
            
            // Calcul de la moyenne
            double temps_moyen = temps_total / nb_repetitions;
            char str_moyen[50], str_min[50], str_max[50];
            double_to_french_string(temps_moyen, str_moyen);
            double_to_french_string(temps_min, str_min);
            double_to_french_string(temps_max, str_max);
            fprintf(fichier, "%d;%s;%s;%s;%s;O(n log n);supprimer_min\n", 
                    taille, types[type], str_moyen, str_min, str_max);
            fflush(fichier);
        }
        
        // Libération de la mémoire
        free(tab_original);
        free(tab_test);
    }
    
    // Fermeture du fichier
    fclose(fichier);
    
    printf("\n\n=== TESTS TERMINÉS ===\n");
    printf("Résultats enregistrés dans: resultats_tri_tas_min.csv\n");
    printf("\nVérification: Tous les tableaux triés sont corrects ✓\n");
    
    return 0;
}
