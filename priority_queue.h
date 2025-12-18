#ifndef PRIORITY_QUEUE_C_H
#define PRIORITY_QUEUE_C_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Définition de la donnée (DataType)
typedef struct {
    int key;
    int value;
} DataType;

// Définition de la structure du Tas
typedef struct {
    DataType **heapArray; // Tableau de pointeurs vers DataType
    int capacity;
    int size;
    // Pointeur de fonction pour le comparateur
    int (*comparator)(const DataType*, const DataType*);
} PriorityQueue;

// Prototypes des fonctions
DataType* createNode(DataType data);
PriorityQueue* createQueue(int capacity, int (*comparator)(const DataType*, const DataType*));
bool insert(PriorityQueue* queue, DataType data);
DataType deleteMax(PriorityQueue* queue);
DataType peek(const PriorityQueue* queue);
bool isEmpty(const PriorityQueue* queue);
void displayHeap(const PriorityQueue* queue);

// Fonction utilitaire
void scanData(DataType* data);

#endif