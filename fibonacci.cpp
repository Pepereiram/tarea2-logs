//Implementacion de una Fibbonacci heap.

// Donde una estructura Q utuliza esto como cola de prioridad
// Implementando decrasedKey en tiempos constante

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <list>
#include <queue>

using namespace std;

// Definimos los pares así al inicio para facilidad de su uso en la priority_queue
// Donde el primer elemento es el paso  y el segundo es el indice el nodo
typedef pair<int, int> ii;

class Node {
public:
    int key;
    int degree;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    bool childCut;
    Node(int key) {
        this->key = key;
        degree = 0;
        parent = NULL;
        child = NULL;
        left = this;
        right = this;
        childCut = false;
    }
};

class FibonacciHeap {
public:
    Node* minNode;
    int n;
    FibonacciHeap() {
        minNode = NULL;
        n = 0;
    }
    void insert(int key) {
        Node* newNode = new Node(key);
        if (minNode != NULL) {
            newNode->left = minNode;
            newNode->right = minNode->right;
            minNode->right = newNode;
            newNode->right->left = newNode;
            if (newNode->key < minNode->key) {
                minNode = newNode;
            }
        } else {
            minNode = newNode;
        }
        n++;
    }
    void merge(FibonacciHeap* other) {
        if (minNode == NULL) {
            minNode = other->minNode;
            n = other->n;
            return;
        }
        if (other->minNode == NULL) {
            return;
        }
        Node* left = minNode->left;
        Node* right = other->minNode->right;
        minNode->left = other->minNode;
        other->minNode->right = minNode;
        left->right = right;
        right->left = left;
        if (other->minNode->key < minNode->key) {
            minNode = other->minNode;
        }
        n += other->n;
    }
    int getMin() {
        return minNode->key;
    }
    int removeMin() {
        Node* oldMin = minNode;
        if (oldMin != NULL) {
            if (oldMin->child != NULL) {
                Node* child = oldMin->child;
                do {
                    Node* next = child->right;
                    child->left = minNode;
                    child->right = minNode->right;
                    minNode->right = child;
                    child->right->left = child;
                    child->parent = NULL;
                    child = next;
                } while (child != oldMin->child);
            }
            oldMin->left->right = oldMin->right;
            oldMin->right->left = oldMin->left;
            if (oldMin == oldMin->right) {
                minNode = NULL;
            } else {
                minNode = oldMin->right;
                consolidate();
            }
            n--;
        }
        return oldMin->key;
    }
    void consolidate() {
        int maxDegree = log(n) / log(2);
        vector<Node*> degreeTable(maxDegree + 1, (Node*)NULL);
        list<Node*> rootList;
        Node* current = minNode;
        do {
            rootList.push_back(current);
            current = current->right;
        } while (current != minNode);
        for (Node* node : rootList) {
            Node* x = node;
            int d = x->degree;
            while (degreeTable[d] != NULL) {
                Node* y = degreeTable[d];
                if (x->key > y->key) {
                    Node* temp = x;
                    x = y;
                    y = temp;
                }
                link(y, x);
                degreeTable[d] = NULL;
                d++;
            }
            degreeTable[d] = x;
        }
        minNode = NULL;
        for (Node* node : rootList) {
            if (node->key < minNode->key) {
                minNode = node;
            }
        }
    }
    void link(Node* y, Node* x) {
        y->left->right = y->right;
        y->right->left = y->left;
        y->left = y;
        y->right = y;
        y->parent = x;
        if (x->child == NULL) {
            x->child = y;
        } else {
            y->left = x->child;
            y->right = x->child->right;
            x->child->right = y;
            y->right->left = y;
        }
        x->degree++;
        y->childCut = false;
    }
    void decreaseKey(Node* x, int key) {
        if (key > x->key) {
            return;
        }
        x->key = key;
        Node* y = x->parent;
        if (y != NULL && x->key < y->key) {
            cut(x, y);
            cascadingCut(y);
        }
        if (x->key < minNode->key) {
            minNode = x;
        }
    }
    void cut(Node* x, Node* y) {
        x->left->right = x->right;
        x->right->left = x->left;
        y->degree--;
        if (y->child == x) {
            y->child = x->right;
        }
        if (y->degree == 0) {
            y->child = NULL;
        }
        x->left = minNode;
        x->right = minNode->right;
        minNode->right = x;
        x->right->left = x;
        x->parent = NULL;
        x->childCut = false;
    }
    void cascadingCut(Node* y) {
        Node* z = y->parent;
        if (z != NULL) {
            if (y->childCut == false) {
                y->childCut = true;
            } else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }
};
