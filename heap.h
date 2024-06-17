#include <bits/stdc++.h>
using namespace std;
typedef pair<double, int> ii;

/*
Como estructura Q, se utiliza un Heap como cola de prioridad, este debe soportar las funciona-
lidades mencionadas en la descripción del algoritmo, y que se construya en tiempo lineal. En este
primer algoritmo, para la función decreaseKey se espera un tiempo logarítmico, en el que actualizar
un elemento de Q reordena la estructura del árbol
*/
struct ColaPrioridad {
    vector<ii> heap;
    unordered_map<int, int> posMap; // Tabla de hashing que mapea el vertice con su posicion en el heap

    void push(ii p) {
        heap.push_back(p);
        int index = heap.size() - 1;
        posMap[p.second] = index;
    }

    // Devuelve el elemento con mayor prioridad (el mínimo en este caso)
    ii top() {
        return heap.front();
    }

    // Elimina el elemento con mayor prioridad (el mínimo en este caso)
    void pop() {
        int final = heap.size()-1;
        swap(heap[0], heap[final]);
        posMap[heap[0].second] = 0;
        posMap.erase(heap[final].second);
        heap.pop_back();
        heapify(final, 0);
    }

    // Verifica si el heap está vacío
    bool empty() {
        return heap.empty();
    }

    // Función para disminuir la clave (distancia) de un nodo específico
    void decreaseKey(int vertice, double Dist) {
        // se actualiza el peso en la tabla de hashing y en el heap
        int indiceHeap = posMap[vertice];
        heap[indiceHeap].first = Dist;
        // nodo va escalando en el arbol mientras sea menor al padres
        while (indiceHeap != 0 && heap[(indiceHeap-1)/2] > heap[indiceHeap]) {
            swap(heap[indiceHeap], heap[(indiceHeap-1)/2]);
            posMap[heap[indiceHeap].second] = indiceHeap;
            posMap[heap[(indiceHeap-1)/2].second] = (indiceHeap-1)/2;
            indiceHeap = (indiceHeap-1)/2;
        }
    }

    void heapify(int tamano_heap, int raiz_subarbol) {
        //se define el nodo con menor peso como la raiz
        int menor = raiz_subarbol;
        //se calculan los indices de los nodos hijos a la raiz
        int izq = 2*raiz_subarbol + 1;
        int der = 2*raiz_subarbol + 2;
        //si el hijo izquierdo existe y tiene menor peso, se guarda el hijo en variable "menor"
        if (izq < tamano_heap && heap[izq] < heap[menor]) {
            menor = izq;
        }
        //si el hijo derecho existe y tiene menor peso, se guarda el hijo en variable "menor"
        if (der < tamano_heap && heap[der] < heap[menor]) {
            menor = der;
        }   
        //si uno de los hijos era menor a la raíz
        if (menor != raiz_subarbol ) {
            //se cambian de posicion
            swap(heap[raiz_subarbol], heap[menor]);
            //cambiamos los indices en el map para que coincidan con los nuevos indices
            posMap[heap[raiz_subarbol].second] = raiz_subarbol;
            posMap[heap[menor].second] = menor;
            //se hace llamada recursiva
            heapify(tamano_heap, menor);
        }
    }
    
};