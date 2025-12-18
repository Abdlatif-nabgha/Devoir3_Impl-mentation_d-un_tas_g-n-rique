// main_event.cpp
#include <iostream>
#include "PriorityQueue.h"

// --- Comparateur personnalisé pour les Events ---
// On compare les événements en fonction de leur GAIN.
// Retourne 1 si d1 > d2, -1 si d1 < d2, 0 sinon.
int eventComparator(const DataType& d1, const DataType& d2) {
    if (d1.gain < d2.gain) return -1;
    if (d1.gain > d2.gain) return 1;
    return 0;
}

int main() {
    // Création d'une file de priorité pour les événements
    PriorityQueue *eventQueue = createQueue(50, eventComparator);

    std::cout << "=== TEST GENERICTE : GESTION D'EVENEMENTS ===\n";

    // Insertion d'événements tests
    insert(*eventQueue, {1, "Concert", 500.50});
    insert(*eventQueue, {2, "Loto", 100.00});
    insert(*eventQueue, {3, "Tournoi Poker", 5000.00}); // Plus grand gain
    insert(*eventQueue, {4, "Vente Garage", 50.00});

    std::cout << "\n--- Etat du Tas apres insertions ---\n";
    // Note : displayHeap affichera les adresses ou nécessiterait une petite modif pour afficher le titre.
    // Pour ce test, on vérifie surtout l'ordre de sortie.
    std::cout << "Taille du tas : " << eventQueue->size << std::endl;

    // Test du Peek (doit être le Tournoi de Poker car gain 5000)
    DataType top = peek(*eventQueue);
    std::cout << "Evenement prioritaire (Max Gain) : " << top.title << " (" << top.gain << ")\n";

    // Test de suppression (On vide la file pour voir si c'est trié par gain)
    std::cout << "\n--- Depilement (Doit sortir du plus grand gain au plus petit) ---\n";
    while(!isEmpty(*eventQueue)) {
        DataType e = deleteMax(*eventQueue);
        std::cout << "Traitement de : " << e.title << " [Gain: " << e.gain << "]\n";
    }

    // Nettoyage
    delete[] eventQueue->heapArray;
    delete eventQueue;

    return 0;
}