// PriorityQueue.h
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include <string>

// --- ADAPTATION POUR LA QUESTION 2 ---
// On remplace la structure simple par la structure "Event"
struct DataType {
    int idEvent;      // Identifiant unique
    std::string title; // Titre de l'événement
    float gain;       // Le gain (ce qui servira de priorité)

    // Fonction pour saisir les données
    void scan() {
        std::cout << "ID Event: "; std::cin >> idEvent;
        std::cout << "Titre: "; std::cin >> title;
        std::cout << "Gain: "; std::cin >> gain;
    }
};
// -------------------------------------

typedef DataType Node;
// Le comparateur prend deux DataType et retourne un entier
typedef int (*Comparator)(const DataType&, const DataType&);

struct PriorityQueue {
    DataType **heapArray; 
    int capacity;
    int size;
    Comparator comparator;
};

// Prototypes (identiques à la version précédente)
Node* createNode(const DataType& data);
PriorityQueue* createQueue(int capacity, Comparator comparator);
bool insert(PriorityQueue& queue, DataType data);
DataType deleteMax(PriorityQueue& queue);
DataType peek(const PriorityQueue& queue);
bool changePriority(PriorityQueue& queue, int index, float newGain); // Adapté pour le gain
bool isEmpty(const PriorityQueue& queue);
void displayHeap(const PriorityQueue& queue);

#endif