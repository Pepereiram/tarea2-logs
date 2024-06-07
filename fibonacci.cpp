//Implementacion de una Fibbonacci heap.

// Donde una estructura Q utuliza esto como cola de prioridad
// Implementando decrasedKey en tiempos constante
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <list>
#include <queue>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;

// Definimos los pares así al inicio para facilidad de su uso en la priority_queue
// Donde el primer elemento es el paso  y el segundo es el indice el nodo
typedef pair<double, int> ii;

class Node {
public:
    double key;
    int vertice;
    int degree;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    bool childCut;
    //constructor del nodo
    Node(ii pair) {
        this->key = pair.first;
        this->vertice = pair.second;
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
    unordered_map<int , Node*> posMap; // Mapa que recibe

    FibonacciHeap() {
        minNode = NULL;
        n = 0;
        // Inicializamos el mapa
        posMap = unordered_map<int, Node*>();
    }

    bool empty(){
        return n == 0;
    }

    // Tomamos un par ii y lo concatenamos en un string
    // string pairToString(ii pair) {
    //     return to_string(pair.first) + "-" + to_string(pair.second);
    // }

    Node* refNodo(int nodo){
        //string llave = pairToString({peso,nodo});
        return posMap[nodo];
    } 

    void insert(ii pair) {
        //Se crea nodo nuevo con la llave insertada
        Node* newNode = new Node(pair);
        // Verificamos que el min no sea nulo
        if (minNode != NULL) {
            // Insertamos newNode en la lista enlazada root
            newNode->left = minNode;         
            newNode->right = minNode->right; 
            minNode->right = newNode;        
            newNode->right->left = newNode;  
            if (newNode->key < minNode->key) {
                // Si es menor, lo reemplaza
                minNode = newNode;
            }
        //si no hay nodos, entonces sera el minimo
        } else {
            minNode = newNode;
        }
        n++;
        // Insertamos el nodo en el mapa
        posMap[pair.second] = newNode;
    }

    ii getMin() {
        //se retorna la llave del nodo minimo
        return {minNode->key, minNode->vertice};
    }

    //ver a futuro si dejar esto como funcion void
    int removeMin() {
        //se crea referencia para el antiguo nodo minimo
        Node* oldMin = minNode;
        // Verificamos que el minimo no sea nulo
        if (oldMin != NULL) { // sus (si es nulo va directo al return)
            
            if (oldMin->child != NULL) {
                Node* child = oldMin->child;
                //se itera por los hijos del antiguo minimo
                do {
                    //se añaden los hijos a la lista enlazada root
                    Node* next = child->right;
                    child->left = minNode;
                    child->right = minNode->right;
                    minNode->right = child;
                    child->right->left = child;
                    child->parent = NULL;
                    child = next;
                } while (child != oldMin->child);
            }
            //
            oldMin->left->right = oldMin->right; // z<->x<->w  = z -> w
            oldMin->right->left = oldMin->left;  // z<->x<->w  = z <- w
            // ver si hay que borrar la memoria alocada para oldMin

            // Verificamos si el minimo es el unico nodo
            if (oldMin == oldMin->right) {
                minNode = NULL;
            } else {
                // Si no es el unico nodo, se reemplaza el minimo
                minNode = oldMin->right;
                consolidate();
            }
            n--;
        }
        // Eliminamos el nodo del mapa
        //posMap.erase(pairToString({oldMin->key, oldMin->vertice}));
        return oldMin->key;
    }

    // "heapify"
    void consolidate() {
        // Es claro que: log(n) / log(2) = log2(n) *por corolario 19.5
        int maxDegree = log(n) / log(2);
        // Creamos el vector de nodos con los grados posibles para el heap
        vector<Node*> degreeTable(maxDegree + 1, nullptr);
        list<Node*> rootList;
        Node* current = minNode;
        // Meter toda la lista enlazada root en una lista de c++
        do {
            rootList.push_back(current);
            current = current->right;
        } while (current != minNode);
        // Recorremos la lista enlazada root para cada nodo x perteneciente a esta
        for (Node* node : rootList) { // 3 2 1
            Node* x = node;
            int d = x->degree;
            // Mientras haya nodos con el mismo grado que x
            while (degreeTable[d] != nullptr) {
                Node* y = degreeTable[d];
                if (x->key > y->key) {
                    // Si x tiene mayor valor los intercambiamos
                    Node* temp = x;
                    x = y;
                    y = temp;
                }
                // Enlazamos y con x (Se vuelve el hijo de x o el hermano de los hijos de x)

                link(y, x); 
                degreeTable[d] = nullptr;
                d++;
            }
            degreeTable[d] = x;
        }
        //se busca el minimo nuevo ( con k elementos en root, k < n -> O(n) )
        // minNode = nullptr;
        // for (Node* node : degreeTable) {
        //     if (node != nullptr) {
        //         if (minNode == nullptr) {

        //             minNode = node;
        //         } else {
        //             if (node->key < minNode->key) {
        //                 minNode = node;
        //             }
        //         }
        //     }
        // }

        // GPT
        minNode = nullptr;
        for (Node* node : degreeTable) {
            if (node != nullptr) {
                if (minNode == nullptr) {
                    minNode = node;
                } else {
                    // Asegurar que los nodos se añaden correctamente a la lista de raíces
                    node->left->right = node->right;
                    node->right->left = node->left;
                    
                    node->left = minNode;
                    node->right = minNode->right;
                    minNode->right->left = node;
                    minNode->right = node;
                    
                    if (node->key < minNode->key) {
                        minNode = node;
                    }
                }
            }
        }
    }

    // enlaza ambos nodos
    void link(Node* y, Node* x) { //se cuelga 3 en el 2
        // Elimina y de la lista enlazada root
        y->left->right = y->right; //  z<->y<->w  =  z->w 
        y->right->left = y->left;  //  z<->y<->w  =  z<-w 
        // Hace y hijo de x
        y->left = y; //  y<-y
        y->right = y; // y->y
        y->parent = x; // 
        if (x->child == NULL) {
            x->child = y; // y se cuelga de x
        } else {
            y->left = x->child;
            y->right = x->child->right;
            x->child->right = y;
            y->right->left = y;
        }
        x->degree++;
        y->childCut = false;
    }

    // Que es el relator? el relator es un programa que se encarga de hacer la reducción de la fibbonacci heap
    void decreaseKey(Node* x, int key) {
        //Si la llave es mayor, no se cambia nada
        if (key > x->key) {
            return;
        }        
        //se cambia el valor de la llave
        x->key = key;
        Node* y = x->parent;
        //si tiene padre y no se cumple la propiedad del heap
        if (y != nullptr) {
            if( x->key < y->key){
                cut(x, y);
                cascadingCut(y);
            }    
        }
        //se establece nuevo nodo minimo, si es necesario
        
        if (x->key < minNode->key) {
            minNode = x;
        }
    }

    void cut(Node* x, Node* y) {
        // COMENTARIO PEPE
        // en vola hay que chequear que x no se apunte a si mismo y luego hacer los cambios de punteros

        // remueve x de la lista de hijos de y (pasa?)
        x->left->right = x->right; // z <-> x <-> w  = z -> w
        x->right->left = x->left;  // z <- w , quedando z <-> w
        // disminuye el grado del padre
        y->degree--;
        //si el puntero al hijo de y era x
        if (y->child == x) {
            //apunta a otro de los nodos de los hijos
            y->child = x->right;
        }
        //si se quedo sin hijos, apunta a nulo
        if (y->degree == 0) {
            y->child = NULL;
        }
        //se adhiere x a la rootlist
        x->left = minNode;
        x->right = minNode->right;
        minNode->right = x;
        x->right->left = x;
        x->parent = NULL;
        x->childCut = false;
    }
    
    void cascadingCut(Node* y) {
        Node* z = y->parent;
        //si no el nodo raiz
        if (z != NULL) {
            //si nodo no esta marcado
            if (y->childCut == false) {
                //se marca xd
                y->childCut = true;
            } else {
                //si esta marcado, se corta y se sube por el arbol
                cut(y, z);
                cascadingCut(z);
            }
        }
    }    
};


//Funcion para printear el FibonacciHeap
void printFibonacciHeap(FibonacciHeap heap) {
    list<Node*> rootList;
    Node* current = heap.minNode;
    cout << "se printea xd" << endl;
    // Meter toda la lista enlazada root en una lista de c++
    do {
        rootList.push_back(current);
        current = current->right;
    } while (current != heap.minNode);
    //iterar por la lista imprimiendo wea
    for (Node* node : rootList) {
        cout << "Nodo: " << node->vertice << " con llave: " << node->key << endl;
    }
    
}


int generarXD(int j){
	// Generamos una arista del grafo aleatoria
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(0, j-1);
	return dist(gen);
}


int main(){
    FibonacciHeap* heap = new FibonacciHeap();
    // Insertamos 10 elementos
    for (int i = 0; i < 10; i++) {
        // generamos valores enteros aleatorios entre 0 y 100
        heap->insert({(double)generarXD(100), i});
    }
    // Imprimimos el heap
    cout << "Imprime el heap" << endl;
    printFibonacciHeap(*heap);
    // Eliminamos el minimo 5 veces
    for (int i = 0; i < 10; i++) {
        cout << "Elimina: " << heap->removeMin() << endl;
        if(i == 0){
            //decrease key 
            cout << "se cambia peso de nodo 2 por 99" << endl;
            Node* nodo2 = heap->refNodo(2);
            heap->decreaseKey(nodo2,99);
            printFibonacciHeap(*heap);
            //heap->decreaseKey(heap->minNode, 15);
        }
    }
}

// how to run: ./fibPenguin
// how to compile: g++ -std=c++11 fibonacci.cpp -o fibPenguin