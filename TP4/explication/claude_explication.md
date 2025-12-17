Bien sûr ! Je vais vous expliquer chaque algorithme en détail avec des exemples visuels.

---

## 1. TRI À BULLES (Bubble Sort)

### 🎯 Pourquoi ce nom ?
Les grands éléments "remontent" comme des bulles vers la fin du tableau.

### 🔧 Comment ça marche ?

**Principe** : On compare chaque élément avec son voisin. Si ils sont dans le mauvais ordre, on les échange.

**Exemple avec [5, 2, 8, 1, 9]***

```
Passage 1 :
[5, 2, 8, 1, 9]  → Compare 5 et 2 → Échange
[2, 5, 8, 1, 9]  → Compare 5 et 8 → OK
[2, 5, 8, 1, 9]  → Compare 8 et 1 → Échange
[2, 5, 1, 8, 9]  → Compare 8 et 9 → OK
[2, 5, 1, 8, 9]  → 9 est à sa place définitive ✓

Passage 2 :
[2, 5, 1, 8, 9]  → Compare 2 et 5 → OK
[2, 5, 1, 8, 9]  → Compare 5 et 1 → Échange
[2, 1, 5, 8, 9]  → Compare 5 et 8 → OK
[2, 1, 5, 8, 9]  → 8 est à sa place définitive ✓

Passage 3 :
[2, 1, 5, 8, 9]  → Compare 2 et 1 → Échange
[1, 2, 5, 8, 9]  → Compare 2 et 5 → OK
[1, 2, 5, 8, 9]  → 5 est à sa place définitive ✓

Passage 4 :
[1, 2, 5, 8, 9]  → Aucun échange → TERMINÉ ✓
```

### 📊 Complexité
- **Meilleur cas** : O(n) - tableau déjà trié, un seul passage
- **Pire cas** : O(n²) - tableau trié à l'envers
- **Mémoire** : O(1) - tri sur place

### 🚀 Version optimisée (TriBulleOpt)
**Amélioration 1** : Variable booléenne `changement` pour détecter si on a fait des échanges. Si aucun échange → tableau trié → STOP.

**Amélioration 2** : À chaque passage, le dernier élément est à sa place, donc on réduit la zone à parcourir (`m = m-1`).

---

## 2. TRI GNOME (Gnome Sort)

### 🎯 Pourquoi ce nom ?
Imaginez un gnome de jardin qui range des pots de fleurs. Il avance, et quand il voit un désordre, il recule en arrangeant.

### 🔧 Comment ça marche ?

**Principe** : 
- Si l'élément actuel ≤ suivant → **avancer**
- Sinon → **échanger et reculer**
- Si au début → **avancer**

**Exemple avec [5, 2, 8, 1]**

```
Position i=0 : [5, 2, 8, 1]
              ^
Au début → avance à i=1

Position i=1 : [5, 2, 8, 1]
                 ^
5 > 2 → Échange et recule
              [2, 5, 8, 1]
              ^
i=0 → Au début, avance à i=1

Position i=1 : [2, 5, 8, 1]
                 ^
2 ≤ 5 → Avance à i=2

Position i=2 : [2, 5, 8, 1]
                    ^
5 ≤ 8 → Avance à i=3

Position i=3 : [2, 5, 8, 1]
                       ^
8 > 1 → Échange et recule
              [2, 5, 1, 8]
                    ^
i=2

Position i=2 : [2, 5, 1, 8]
                    ^
5 > 1 → Échange et recule
              [2, 1, 5, 8]
                 ^
i=1

Position i=1 : [2, 1, 5, 8]
                 ^
2 > 1 → Échange et recule
              [1, 2, 5, 8]
              ^
i=0 → Au début, avance...

Continue jusqu'à i=4 (fin) → TERMINÉ ✓
```

### 📊 Complexité
- **Meilleur cas** : O(n) - tableau déjà trié
- **Pire cas** : O(n²) - tableau trié à l'envers
- **Avantage** : Très simple à coder
- **Inconvénient** : Lent sur grands tableaux

---

## 3. TRI PAR DISTRIBUTION / BASE (Radix Sort)

### 🎯 Pourquoi ce nom ?
On trie selon la "base" du système de numération (unités, dizaines, centaines...).

### 🔧 Comment ça marche ?

**Principe** : Trier les nombres chiffre par chiffre, du **moins significatif** (unités) au **plus significatif** (centaines).

**Exemple avec [170, 45, 75, 90, 802, 24, 2, 66]**

```
ÉTAPE 1 : Tri selon les UNITÉS (chiffre des unités)
170 → 0
45  → 5
75  → 5
90  → 0
802 → 2
24  → 4
2   → 2
66  → 6

Regroupement par chiffre des unités :
0: [170, 90]
2: [802, 2]
4: [24]
5: [45, 75]
6: [66]

Résultat après tri unités : [170, 90, 802, 2, 24, 45, 75, 66]

ÉTAPE 2 : Tri selon les DIZAINES
170 → 7
90  → 9
802 → 0
2   → 0
24  → 2
45  → 4
75  → 7
66  → 6

Regroupement par chiffre des dizaines :
0: [802, 2]
2: [24]
4: [45]
6: [66]
7: [170, 75]
9: [90]

Résultat après tri dizaines : [802, 2, 24, 45, 66, 170, 75, 90]

ÉTAPE 3 : Tri selon les CENTAINES
802 → 8
2   → 0
24  → 0
45  → 0
66  → 0
170 → 1
75  → 0
90  → 0

Regroupement par chiffre des centaines :
0: [2, 24, 45, 66, 75, 90]
1: [170]
8: [802]

Résultat FINAL : [2, 24, 45, 66, 75, 90, 170, 802] ✓
```

### 🔑 Fonction clé(x, i)
```
clé(143, 0) = 3  (unités)
clé(143, 1) = 4  (dizaines)
clé(143, 2) = 1  (centaines)
```

Implémentation :
```c
int cle(int x, int i) {
    int diviseur = pow(10, i);
    return (x / diviseur) % 10;
}
```

### 📊 Complexité
- **Temps** : O(k × n) où k = nombre de chiffres
- **Espace** : O(n + 10) pour les buckets
- **Avantage** : Linéaire ! Très rapide pour des entiers
- **Inconvénient** : Ne marche qu'avec des entiers, besoin de mémoire supplémentaire

---

## 4. TRI RAPIDE (Quick Sort)

### 🎯 Pourquoi ce nom ?
C'est un des algorithmes de tri les plus **rapides** en pratique !

### 🔧 Comment ça marche ?

**Principe** : **Diviser pour régner**
1. Choisir un **pivot** (élément de référence)
2. **Partitionner** : mettre les petits à gauche, les grands à droite
3. **Récursion** : trier les deux parties séparément

**Exemple avec [5, 2, 8, 1, 9, 3]**

```
APPEL 1 : triRapide([5, 2, 8, 1, 9, 3], 0, 5)

Pivot = 5 (premier élément)

Partitionnement :
[5, 2, 8, 1, 9, 3]
 ^pivot

i parcourt de gauche, j de droite
i cherche élément > pivot
j cherche élément ≤ pivot

 i           j
[5, 2, 8, 1, 9, 3]
    ^   ^
2≤5     1≤5 → OK, mais i=1 < j=3

     i     j
[5, 2, 8, 1, 9, 3]
       ^  ^
8>5    1≤5 → Échange 8 et 1

[5, 2, 1, 8, 9, 3]
       ^  ^

       j  i
[5, 2, 1, 8, 9, 3]
          ^  ^
j > i → STOP

Pivot va à sa place (position j=2)
[3, 2, 1] | 5 | [8, 9]
         ↑
    Pivot à sa place définitive

APPEL 2 : triRapide([3, 2, 1], 0, 2)
Pivot = 3
Après partition : [1, 2] | 3

APPEL 3 : triRapide([1, 2], 0, 1)
Pivot = 1
Après partition : 1 | [2]

APPEL 4 : triRapide([8, 9], 4, 5)
Pivot = 8
Après partition : 8 | [9]

RÉSULTAT FINAL : [1, 2, 3, 5, 8, 9] ✓
```

### ⚠️ Correction de l'erreur du TP
Dans le PDF, la fonction `partitionner` a une erreur :
```c
// FAUX (dans le PDF)
fonction partitionner(E/tab : tableau[n] entiers ; d, f :entier)
    eltPivot ← tab[p];  // ← ERREUR : p n'existe pas !

// CORRECT
fonction partitionner(E/tab : tableau[n] entiers ; d, f :entier)
    eltPivot ← tab[d];  // ← Utiliser d (début)
```

### 📊 Complexité
- **Meilleur cas** : O(n log n) - pivot divise toujours en 2 moitiés égales
- **Cas moyen** : O(n log n) - le plus 
fréquent
- **Pire cas** : O(n²) - pivot toujours le plus petit/grand (tableau déjà trié)
- **Mémoire** : O(log n) pour la pile de récursion

### 🎯 Pourquoi c'est rapide ?
- Très peu de déplacements
- Bon usage du cache processeur
- Constante multiplicative faible

---

## 5. TRI PAR TAS (Heap Sort)

### 🎯 Qu'est-ce qu'un TAS ?
Un **tas** (heap) est un arbre binaire spécial stocké dans un tableau où :
- **Tas min** : chaque parent ≤ ses enfants
- **Tas max** : chaque parent ≥ ses enfants

**Représentation en tableau** :
```
        1
      /   \
     3     5
    / \   /
   7   9 11

Tableau : [1, 3, 5, 7, 9, 11]
Index :    0  1  2  3  4  5

Relations :
- Parent de i : (i-1)/2
- Fils gauche de i : 2i + 1
- Fils droit de i : 2i + 2
```

### 🔧 Comment ça marche ?

**Principe** :
1. **Construire un tas min** à partir du tableau
2. **Extraire le minimum** (racine) et le placer en fin
3. **Réorganiser** le tas
4. **Répéter** jusqu'à avoir tout trié

**Exemple avec [16, 10, 8, 11, 5, 6, 9, 1]**

```
PHASE 1 : Construction du tas min

Tableau initial : [16, 10, 8, 11, 5, 6, 9, 1]

Insérer 16 :
        16
[16]

Insérer 10 :
        10
       /
      16
[10, 16]
10 < 16 → remonter 10

Insérer 8 :
        8
       / \
      16  10
[8, 16, 10]

Insérer 11 :
        8
       / \
      11  10
     /
    16
[8, 11, 10, 16]

... Continue jusqu'à avoir tous les éléments ...

Tas min final :
        1
       / \
      5   6
     / \ / \
    11  10 8  9
   /
  16

[1, 5, 6, 11, 10, 8, 9, 16]

PHASE 2 : Extraction successive du minimum

Étape 1 : Extraire 1 (minimum)
- Placer 1 en fin du tableau trié
- Remplacer racine par dernier élément (16)
- Tamiser vers le bas

        16              5
       / \             / \
      5   6     →     10  6
     / \ / \         /  \ /
    11 10 8  9      11  16 8
   
   Résultat : 1 placé, reste [5, 10, 6, 11, 16, 8, 9]

Étape 2 : Extraire 5
        9               6
       / \             / \
      10  6     →     10  8
     / \ /           /  \
    11 16 8         11  16

   Résultat : [1, 5] placés, reste [6, 10, 8, 11, 16, 9]

... Continue jusqu'au bout ...

Tableau final trié : [1, 5, 6, 8, 9, 10, 11, 16] ✓
```

### 🔑 Opération TAMISER (heapify)
C'est l'opération clé pour maintenir la propriété du tas.

```c
void tamiser(int T[], int n, int i) {
    int min = i;
    int gauche = 2*i + 1;
    int droite = 2*i + 2;
    
    // Trouver le plus petit entre parent et enfants
    if (gauche < n && T[gauche] < T[min])
        min = gauche;
    if (droite < n && T[droite] < T[min])
        min = droite;
    
    // Si le parent n'est pas le plus petit, échanger et continuer
    if (min != i) {
        echanger(&T[i], &T[min]);
        tamiser(T, n, min);
    }
}
```

### 📊 Complexité
- **Construction du tas** : O(n)
- **Extraction de chaque élément** : O(log n) × n éléments = O(n log n)
- **Total** : O(n log n) dans **tous les cas** (meilleur, moyen, pire)
- **Mémoire** : O(1) - tri sur place
- **Avantage** : Complexité garantie O(n log n), pas de pire cas O(n²)

---

## 📊 TABLEAU COMPARATIF

| Algorithme | Meilleur | Moyen | Pire | Mémoire | Stable* |
|------------|----------|-------|------|---------|---------|
| Tri Bulles | O(n) | O(n²) | O(n²) | O(1) | ✓ |
| Tri Gnome | O(n) | O(n²) | O(n²) | O(1) | ✓ |
| Tri Distribution | O(kn) | O(kn) | O(kn) | O(n) | ✓ |
| Tri Rapide | O(n log n) | O(n log n) | O(n²) | O(log n) | ✗ |
| Tri par Tas | O(n log n) | O(n log n) | O(n log n) | O(1) | ✗ |

*Un tri est **stable** s'il préserve l'ordre relatif des éléments égaux.

---

## 🎯 QUAND UTILISER QUEL TRI ?

**Tri à Bulles** : 
- ✓ Petits tableaux (< 50 éléments)
- ✓ Tableaux presque triés
- ✓ Pédagogie
- ✗ Gros tableaux

**Tri Gnome** :
- ✓ Code ultra simple
- ✓ Petits tableaux
- ✗ Performances médiocres

**Tri par Distribution** :
- ✓ Grands tableaux d'entiers
- ✓ Nombres avec peu de chiffres
- ✗ Ne marche pas pour strings ou floats

**Tri Rapide** :
- ✓ Le meilleur en pratique pour cas général
- ✓ Très rapide en moyenne
- ✗ Pire cas O(n²) possible

**Tri par Tas** :
- ✓ Garantie O(n log n) même au pire cas
- ✓ Tri sur place
- ✗ Moins rapide que Quick Sort en pratique

---

Des questions sur un algorithme en particulier ? 😊