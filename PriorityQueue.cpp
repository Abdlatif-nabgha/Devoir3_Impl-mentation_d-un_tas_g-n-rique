// PriorityQueue.cpp
#include "PriorityQueue.h"
#include <cstdlib> // Pour rand(), srand()
#include <ctime>   // Pour time()
#include <string>  // Pour std::to_string

// Forward declarations
void heapifyDown(PriorityQueue &queue, int index);
void heapifyUp(PriorityQueue &queue, int index);

Node *createNode(const DataType &data) {
  Node *node = new Node;
  *node = data;
  return node;
}

PriorityQueue *createQueue(int capacity, Comparator comparator) {
  PriorityQueue *queue = new PriorityQueue;
  queue->capacity = capacity;
  queue->size = 0;
  queue->heapArray = new Node *[capacity];
  queue->comparator = comparator;
  return queue;
}

PriorityQueue *createQueue(DataType *array, int size, Comparator comparator) {
  PriorityQueue *queue =
      createQueue(2 * size, comparator); // Capacité arbitraire plus grande
  for (int i = 0; i < size; i++) {
    queue->heapArray[i] = createNode(array[i]);
    queue->size++;
  }
  // Construction du tas (Build Heap)
  for (int i = (queue->size - 1) / 2; i >= 0; i--) {
    heapifyDown(*queue, i);
  }
  return queue;
}

bool isEmpty(const PriorityQueue &queue) { return queue.size == 0; }

void heapifyUp(PriorityQueue &queue, int index) {
  int parent = (index - 1) / 2;
  Node *bottom = queue.heapArray[index];

  while (index > 0 && queue.comparator(*queue.heapArray[parent], *bottom) < 0) {
    queue.heapArray[index] = queue.heapArray[parent]; // Descendre le parent
    index = parent;
    parent = (parent - 1) / 2;
  }
  queue.heapArray[index] = bottom;
}

void heapifyDown(PriorityQueue &queue, int index) {
  int largerChild;
  Node *top = queue.heapArray[index];

  while (index < queue.size / 2) { // Tant qu'il a au moins un enfant gauche
    int leftChild = 2 * index + 1;
    int rightChild = leftChild + 1;

    // Trouver le plus grand des deux enfants
    if (rightChild < queue.size &&
        queue.comparator(*queue.heapArray[leftChild],
                         *queue.heapArray[rightChild]) < 0) {
      largerChild = rightChild;
    } else {
      largerChild = leftChild;
    }

    // Si le top est déjà plus grand ou égal, on arrête
    if (queue.comparator(*top, *queue.heapArray[largerChild]) >= 0)
      break;

    // Sinon on remonte l'enfant
    queue.heapArray[index] = queue.heapArray[largerChild];
    index = largerChild;
  }
  queue.heapArray[index] = top;
}

bool insert(PriorityQueue &queue, DataType data) {
  if (queue.size == queue.capacity)
    return false;

  queue.heapArray[queue.size] = createNode(data);
  heapifyUp(queue, queue.size++); // Incrémenter la taille après l'appel
  return true;
}

DataType deleteMax(PriorityQueue &queue) {
  // Pré-condition: !isEmpty(queue). À gérer dans le main ou avec une exception.
  Node *root = queue.heapArray[0];
  queue.heapArray[0] = queue.heapArray[--queue.size];
  heapifyDown(queue, 0);

  DataType data = *root;
  delete root; // Libérer la mémoire du nœud retiré
  return data;
}

DataType peek(const PriorityQueue &queue) { return *queue.heapArray[0]; }

bool changePriority(PriorityQueue &queue, int index, float newGain) {
  if (index < 0 || index >= queue.size)
    return false;

  DataType oldData = *queue.heapArray[index];
  queue.heapArray[index]->gain = newGain;

  // Décider si on monte ou on descend
  // Note: Pour comparer avec l'ancienne donnée, on crée une copie temporaire
  // mise à jour
  DataType newData = *queue.heapArray[index];

  if (queue.comparator(oldData, newData) < 0) {
    // La nouvelle clé est plus grande (dans un MaxHeap), on doit monter
    heapifyUp(queue, index);
  } else {
    // La nouvelle clé est plus petite, on doit descendre
    heapifyDown(queue, index);
  }
  return true;
}

int dataTypeComparator(const DataType &d1, const DataType &d2) {
  if (d1.gain < d2.gain)
    return -1;
  if (d1.gain == d2.gain)
    return 0;
  return 1;
}

void randomDataArray(DataType *array, int size, int minVal, int maxVal) {
  srand(time(NULL));
  for (int i = 0; i < size; ++i) {
    array[i].gain = (float)((rand() % (maxVal - minVal + 1)) + minVal);
    array[i].idEvent = i + 1;
    array[i].title = "Event " + std::to_string(i + 1);
  }
}

void displayHeap(const PriorityQueue &queue) {
  std::cout
      << "\n..............................................................\n";
  std::cout << "heapArray:\n\tGain values: ";
  for (int i = 0; i < queue.size; i++) {
    std::cout << queue.heapArray[i]->gain << ", ";
  }
  std::cout << "\n\tsize: " << queue.size << ",\n\tcapacity: " << queue.capacity
            << std::endl;

  std::cout
      << "\n..............................................................\n";
  std::cout << "heapArray as a complete binary tree:\n\n";

  int nBlanks = 32;
  int itemsPerRow = 1;
  int column = 0;
  int j = 0;

  while (j < queue.size) {
    if (column == 0) {
      for (int k = 0; k < nBlanks; k++)
        std::cout << " ";
    }

    std::cout << queue.heapArray[j]->gain;

    if (++j == queue.size)
      break;

    if (++column == itemsPerRow) {
      nBlanks /= 2;
      itemsPerRow *= 2;
      column = 0;
      std::cout << "\n\n"; // Sauts de ligne pour l'arbre
    } else {
      for (int k = 0; k < nBlanks * 2 - 2; k++)
        std::cout << " ";
    }
  }
  std::cout << "\n\n..........................................................."
               "...\n\n";
}

void heapSort(DataType *array, int size) {
  PriorityQueue *queue = createQueue(array, size, dataTypeComparator);
  std::cout << "Array to heap created.\n";
  // displayHeap(*queue); // Optionnel

  // Heap Sort: on retire le max et on le met à la fin du tableau
  for (int i = size - 1; i >= 0; i--) {
    array[i] = deleteMax(*queue);
  }

  delete[] queue->heapArray;
  delete queue;
}