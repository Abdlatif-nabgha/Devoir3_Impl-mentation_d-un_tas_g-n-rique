#include "priority_queue.h"

// Crée un noeud dynamiquement (équivalent du new Node en C++)
DataType* createNode(DataType data) {
    DataType* node = (DataType*)malloc(sizeof(DataType));
    if (!node) {
        printf("Erreur d'allocation memoire\n");
        exit(1);
    }
    *node = data;
    return node;
}

// Crée la file
PriorityQueue* createQueue(int capacity, int (*comparator)(const DataType*, const DataType*)) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (!queue) exit(1);

    queue->capacity = capacity;
    queue->size = 0;
    // Allocation du tableau de pointeurs
    queue->heapArray = (DataType**)malloc(sizeof(DataType*) * capacity);
    queue->comparator = comparator;
    return queue;
}

// Fonction utilitaire pour saisir une donnée
void scanData(DataType* data) {
    printf("key: "); scanf("%d", &data->key);
    printf("value: "); scanf("%d", &data->value);
}

// Remonte un élément pour maintenir la propriété du tas (Max-Heap)
void heapifyUp(PriorityQueue* queue, int index) {
    int parent = (index - 1) / 2;
    DataType* bottom = queue->heapArray[index];

    // Note : on utilise '->' car queue est un pointeur en C
    while (index > 0 && queue->comparator(queue->heapArray[parent], bottom) < 0) {
        queue->heapArray[index] = queue->heapArray[parent];
        index = parent;
        parent = (parent - 1) / 2;
    }
    queue->heapArray[index] = bottom;
}

// Descend un élément
void heapifyDown(PriorityQueue* queue, int index) {
    int largerChild;
    DataType* top = queue->heapArray[index];

    while (index < queue->size / 2) {
        int leftChild = 2 * index + 1;
        int rightChild = leftChild + 1;

        if (rightChild < queue->size && 
            queue->comparator(queue->heapArray[leftChild], queue->heapArray[rightChild]) < 0) {
            largerChild = rightChild;
        } else {
            largerChild = leftChild;
        }

        if (queue->comparator(top, queue->heapArray[largerChild]) >= 0) break;

        queue->heapArray[index] = queue->heapArray[largerChild];
        index = largerChild;
    }
    queue->heapArray[index] = top;
}

bool insert(PriorityQueue* queue, DataType data) {
    if (queue->size == queue->capacity) return false;

    queue->heapArray[queue->size] = createNode(data);
    heapifyUp(queue, queue->size);
    queue->size++; // Incrémentation après
    return true;
}

DataType deleteMax(PriorityQueue* queue) {
    // On suppose que la file n'est pas vide (à vérifier dans le main)
    DataType* rootPtr = queue->heapArray[0];
    DataType data = *rootPtr;

    queue->size--;
    queue->heapArray[0] = queue->heapArray[queue->size];
    heapifyDown(queue, 0);

    free(rootPtr); // Libération mémoire du pointeur retiré
    return data;
}

DataType peek(const PriorityQueue* queue) {
    return *queue->heapArray[0];
}

bool isEmpty(const PriorityQueue* queue) {
    return queue->size == 0;
}

void displayHeap(const PriorityQueue* queue) {
    printf("\n--- Heap Content ---\n");
    for (int i = 0; i < queue->size; i++) {
        printf("[%d] ", queue->heapArray[i]->key);
    }
    printf("\nSize: %d / Capacity: %d\n", queue->size, queue->capacity);
    printf("--------------------\n");
}