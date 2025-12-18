# Devoir3_Impl-mentation_d-un_tas_g-n-
# Projet : Généricité et Tri par Tas (Heap Sort)

## 📌 Objectif du travail

Ce projet a pour but de :

* Tester et corriger un code fourni dans le support de cours
* Vérifier la **généricité** du code avec un autre type de données
* Réécrire le code en **langage C** en justifiant les choix techniques
* Implémenter l’**application 1 : le tri par tas (Heap Sort)**

---

## 🧪 1. Test et correction du code fourni

* Compilation et exécution du code initial
* Correction des erreurs syntaxiques et logiques
* Ajout de commentaires pour améliorer la compréhension

---

## 🔁 2. Test de la généricité du code

Le code est testé avec un nouveau type de données **Event** :

```c
typedef struct {
    int IdEvent;
    char title[50];
    float gain;
} Event;
```

* Le tri est effectué selon le champ `gain`
* Seule la fonction de comparaison est modifiée
* L’algorithme reste inchangé → généricité validée

---

## 🔧 3. Réécriture du code en C

### Choix réalisés

* Utilisation des `struct`
* Passage par pointeurs pour l’efficacité mémoire
* Découpage en fonctions (swap, heapify, heapSort)

Exemple de fonction générique :

```c
void swap(void *a, void *b, size_t size);
```

---

## 🌳 4. Application 1 : Tri par Tas (Heap Sort)

### Principe

Le tri par tas repose sur un **tas binaire (heap max)**.

### Étapes

1. Construction du tas
2. Échange de la racine avec le dernier élément
3. Réduction de la taille du tas
4. Réorganisation (heapify)

### Complexité

* Temps : `O(n log n)`
* Espace : `O(1)`

---

## 📂 Organisation du projet

```
heap-sort-project/
 ┣ README.md
 ┣ src/
 ┃ ┣ heap_sort.c
 ┃ ┣ generic_sort.c
 ┃ ┗ event_test.c
 ┗ include/
   ┗ sort.h
```

---

## 👨‍🎓 Auteur

**Ilyasse Ben Taleb**
**Abd Latif SIDI MED NABGHA**
Cycle Ingénieur – Génie Logiciel
ENSET Mohammedia

---

## 📜 Licence

Projet académique – usage pédagogique uniquement.
