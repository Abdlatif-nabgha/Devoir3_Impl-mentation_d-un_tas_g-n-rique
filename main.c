#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

// Fonction de comparaison pour les entiers (version pointeurs pour C)
int intComparator(const DataType* d1, const DataType* d2) {
    if (d1->key < d2->key) return -1;
    if (d1->key == d2->key) return 0;
    return 1;
}

int main() {
    printf("=== IMPLEMENTATION TAS EN C ===\n");

    PriorityQueue* myQueue = createQueue(20, intComparator);

    // Insertion directe
    DataType d1 = {10, 1}; insert(myQueue, d1);
    DataType d2 = {50, 2}; insert(myQueue, d2);
    DataType d3 = {30, 3}; insert(myQueue, d3);
    DataType d4 = {100, 4}; insert(myQueue, d4); // Max

    displayHeap(myQueue);

    printf("\nTest Peek (Max): %d\n", peek(myQueue).key);

    printf("\nTest DeleteMax:\n");
    while(!isEmpty(myQueue)) {
        DataType d = deleteMax(myQueue);
        printf("Retire: Key=%d, Val=%d\n", d.key, d.value);
    }

    // Libération de la mémoire de la structure principale
    free(myQueue->heapArray);
    free(myQueue);

    return 0;
}