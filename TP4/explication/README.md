# TP4 - Algorithmes de Tri - Guide d'Utilisation

## 📋 Description

Ce projet implémente 5 algorithmes de tri en C avec un protocole de tests complet pour analyser leurs performances.

## 🗂️ Fichiers Générés

### Fichiers Source (.c)
- `tri_bulles.c` - Tri à bulles version basique
- `tri_bulles_opt.c` - Tri à bulles optimisé (arrêt anticipé)
- `tri_gnome.c` - Tri gnome
- `tri_distribution.c` - Tri par distribution (Radix Sort)
- `tri_rapide.c` - Tri rapide (Quick Sort) avec correction
- `tri_tas.c` - Tri par tas (Heap Sort)

### Exécutables (.exe)
- `tri_bulles.exe`
- `tri_bulles_opt.exe`
- `tri_gnome.exe`
- `tri_distribution.exe`
- `tri_rapide.exe`
- `tri_tas.exe`

### Fichiers CSV de Résultats
- `resultats_tri_bulles.csv`
- `resultats_tri_bulles_opt.csv`
- `resultats_tri_gnome.csv`
- `resultats_tri_distribution.csv`
- `resultats_tri_rapide.csv`
- `resultats_tri_tas.csv`

## 🚀 Compilation

Pour compiler tous les algorithmes :

```bash
gcc -o tri_bulles.exe tri_bulles.c
gcc -o tri_bulles_opt.exe tri_bulles_opt.c
gcc -o tri_gnome.exe tri_gnome.c
gcc -o tri_distribution.exe tri_distribution.c
gcc -o tri_rapide.exe tri_rapide.c
gcc -o tri_tas.exe tri_tas.c
```

## ▶️ Exécution

Pour exécuter un algorithme :

```bash
./tri_bulles.exe
./tri_bulles_opt.exe
./tri_gnome.exe
./tri_distribution.exe
./tri_rapide.exe
./tri_tas.exe
```

Chaque programme :
1. Affiche une barre de progression pendant les tests
2. Génère automatiquement un fichier CSV avec les résultats
3. Affiche un message de confirmation à la fin

## 📊 Protocole de Tests

### Tailles de Tableaux
- 100, 500, 1000, 5000, 10000, 50000, 100000 éléments

### Types de Tests
- **Aléatoire** : Valeurs générées aléatoirement (0-99999)
- **Croissant** : Tableau déjà trié en ordre croissant
- **Décroissant** : Tableau trié en ordre décroissant

### Répétitions
- 10 répétitions par configuration pour obtenir une moyenne fiable

### Métriques Mesurées
- Temps moyen d'exécution
- Temps minimum
- Temps maximum
- Complexité théorique

## 📈 Format des CSV

Chaque fichier CSV contient les colonnes suivantes :

```
Taille,Type_Test,Temps_Moyen(s),Temps_Min(s),Temps_Max(s),Complexite_Theorique
```

Exemple :
```
100,aleatoire,0.000012,0.000010,0.000015,O(n²)
100,croissant,0.000008,0.000007,0.000010,O(n²)
100,decroissant,0.000014,0.000012,0.000016,O(n²)
```

## 🔍 Complexités Théoriques

| Algorithme | Meilleur Cas | Cas Moyen | Pire Cas |
|------------|--------------|-----------|----------|
| **Tri à Bulles** | O(n²) | O(n²) | O(n²) |
| **Tri à Bulles Opt** | O(n) | O(n²) | O(n²) |
| **Tri Gnome** | O(n) | O(n²) | O(n²) |
| **Tri Distribution** | O(d×n) | O(d×n) | O(d×n) |
| **Tri Rapide** | O(n log n) | O(n log n) | O(n²) |
| **Tri par Tas** | O(n log n) | O(n log n) | O(n log n) |

## ⚠️ Correction Importante

Le fichier `tri_rapide.c` contient la **correction de l'erreur** mentionnée dans le TP :
- Utilisation correcte des indices `d` (début) et `f` (fin) dans la fonction `partitionner`
- Au lieu d'utiliser `p` qui pouvait être ambigu

## 💡 Analyse des Résultats

Pour analyser les résultats :
1. Ouvrez les fichiers CSV dans Excel, LibreOffice Calc, ou Python
2. Comparez les temps d'exécution selon les tailles
3. Observez l'impact du type de données (aléatoire vs trié)
4. Vérifiez que les complexités mesurées correspondent aux complexités théoriques

### Observations Attendues

- **Tri à Bulles Optimisé** : Très rapide sur tableaux croissants (O(n))
- **Tri Rapide** : Lent sur tableaux déjà triés (pire cas O(n²))
- **Tri par Tas** : Performances stables quel que soit le type de données
- **Tri Distribution** : Très efficace pour les grands tableaux

## 📝 Notes

- Les temps sont mesurés avec `clock()` de `<time.h>`
- Les tableaux sont alloués dynamiquement avec `malloc()`
- Chaque test utilise une copie du tableau original pour garantir l'équité
- La barre de progression permet de suivre l'avancement des tests
