#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;

/*
Como estructura Q, se utiliza un Heap como cola de prioridad, este debe soportar las funciona-
lidades mencionadas en la descripción del algoritmo, y que se construya en tiempo lineal. En este
primer algoritmo, para la función decreaseKey se espera un tiempo logarítmico, en el que actualizar
un elemento de Q reordena la estructura del árbol
*/
struct ColaPrioridad {
    vector<ii> heap;
    unordered_map<int, int> posMap; // Map to store the position of nodes in the heap
    // { nodo : distancia, nod// Helper functionso2 : distancia2 , .....
    // }
    // posMap.find()
    
    // Inserta un elemento en el heap
    void push(ii p) {
        heap.push_back(p);
        int index = heap.size() - 1;
        posMap[p.second] = index;
        push_heap(heap.begin(), heap.end(), greater<ii>());
    }

    // Devuelve el elemento con mayor prioridad (el mínimo en este caso)
    ii top() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        return heap.front();
    }

    // Elimina el elemento con mayor prioridad (el mínimo en este caso)
    void pop() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        pop_heap(heap.begin(), heap.end(), greater<ii>());
        posMap.erase(heap.back().second);
        heap.pop_back();
    }

    // Verifica si el heap está vacío
    bool empty() const {
        return heap.empty();
    }

    // Función para disminuir la clave (distancia) de un nodo específico
    // input: 
    void decreaseKey(int node, int newDist) {
        int index = posMap[node];
        cout << "index: " << index << endl;
        heap[index].first = newDist;
        // Adjust the heap after decrease
        while (index != 0 && heap[parent(index)] > heap[index]) {
            swap(heap[index], heap[parent(index)]);
            posMap[heap[index].second] = index;
            posMap[heap[parent(index)].second] = parent(index);
            index = parent(index);
        }
    }

    // Imprime los elementos del heap (para depuración)
    void printHeap() const {
        for (const auto& element : heap) {
            cout << "(" << element.first << ", " << element.second << ") ";
        }
        cout << endl;
    }

private:
    // Helper functions
    int parent(int i) {
        return (i - 1) / 2;
    }

    int left(int i) {
        return 2 * i + 1;
    }

    int right(int i) {
        return 2 * i + 2;
    }
};

int main() {
    ColaPrioridad cp;

    // Insertar elementos en el heap
    cp.push({3, 100});
    cp.push({6, 600});
    cp.push({1, 200});
    cp.push({0, 150});
    cp.push({2, 300});
    cp.push({4, 400});
    cp.push({5, 500});

    cout << "Heap actual: ";
    cp.printHeap();

    // Mostrar el elemento de mayor prioridad (mínimo)
    cout << "Elemento de mayor prioridad: (" << cp.top().first << ", " << cp.top().second << ")" << endl;

    // Eliminar el elemento de mayor prioridad (mínimo)
    cp.pop();
    cout << "Heap después de eliminar el elemento de mayor prioridad: ";
    cp.printHeap();

    // Eliminar el elemento de mayor prioridad (mínimo)
    cp.pop();
    cout << "Heap después de eliminar el elemento de mayor prioridad: ";
    cp.printHeap();

    // Disminuir la clave de un nodo
    cp.decreaseKey(300, 0);
    cout << "Heap después de disminuir la clave del nodo 300: ";
    cp.printHeap();

    return 0;
}

// how to compile: g++ -std=c++11 heap.cpp -o heap


/*
HEAP(A,i) {
    l = LEFT(i)
    r = RIGHT(i)
    if (l <= A.heap-size && A[l] > A[i]) {
        largest = l
    } else {
        largest = i
    }
    if (r <= A.heap-size && A[r] > A[largest]) {
        largest = r
    }
    if (largest != i){
        exchange A[i] with A[largest]
        HEAP(A, largest)
    }
}
*/

//
//struct cola_prioridad {
//    vector<ii> heap;
//    void push(ii p) {
//        heap.push_back(p);
//        push_heap(heap.begin(), heap.end(), greater<ii>());
//    }
//    ii top() {
//        return heap.front();
//    }
//    void pop() {
//        pop_heap(heap.begin(), heap.end(), greater<ii>());
//        heap.pop_back();
//    }
//    bool empty() {
//        return heap.empty();
//    }
//    void printHeap() const {
//        for (const auto& element : heap) {
//            cout << "(" << element.first << ", " << element.second << ") ";
//        }
//        cout << endl;
//    }
//    // decrease_key
//};
//

//int main() {
//    ColaPrioridad cp;
//
//    // Insertar elementos en el heap
//    cp.push({3, 100});
//    cp.push({1, 200});
//    cp.push({2, 300});
//    cp.push({4, 400});
//
//    cout << "Heap actual: ";
//    cp.printHeap();
//
//    // Mostrar el elemento de mayor prioridad (mínimo)
//    cout << "Elemento de mayor prioridad: (" << cp.top().first << ", " << cp.top().second << ")" << endl;
//
//    // Eliminar el elemento de mayor prioridad (mínimo)
//    cp.pop();
//    cout << "Heap después de eliminar el elemento de mayor prioridad: ";
//    cp.printHeap();
//
//    return 0;
//}