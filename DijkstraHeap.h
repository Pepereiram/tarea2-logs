#include <bits/stdc++.h>
using namespace std;
#include "heap.h"
// Definimos los pares así al inicio para facilidad de su uso en la priority_queue
typedef pair<double, int> ii;
#define INF 1 << 23

void caminoMasCorto(int s, int n, vector<vector<ii>> gr, ColaPrioridad cola,
                            vector<double>* pdistancia, vector<int>* pPrevios) {
    //PASO 1:
    // Cambiamos el tamaño de distancia y previos
    (*pdistancia).resize(n);
    (*pPrevios).resize(n);

    //PASO 3
    // Metemos la fuente a la cola y asignamos su distancia
    (*pdistancia)[s] = 0;
    (*pPrevios)[s] = -1;
    cola.push({0, s});
    
    //PASO 4: 
    //se mete en la cola los nodos con sus distancias
    for(int i = 0; i < n; i++){
        if(i != s) {
            (*pdistancia)[i] = INF;
            (*pPrevios)[i] = -2;
            cola.push({INF,i}); // (distancia, nodo)
        }
    }
    //PASO 5:
    //heapifear
    cola.heapify(cola.heap, cola.heap.size(), 0);
    
    
    //PASO 6:
    // Mientras la cola no esté vacía, tenemos nodos que revisar
    int previo = -1;
    while(!cola.empty()) {
  
        // Sacamos el nodo que esté a menor distancia ahora mismo  
        auto [nodo_d, nodo] = cola.top();
        cola.pop();

        // Revisamos sus vecinos: vecino_d es el peso entre nodo y vecino
        for(auto [vecino_d, vecino]: gr[nodo]) {
            // Si la distancia guardada para el vecino es menor a la distancia de nodo + el peso
            if ((*pdistancia)[vecino] > nodo_d + vecino_d) {
                (*pdistancia)[vecino] = nodo_d + vecino_d; //se actualiza el valor de la distancia en el arreglo
                (*pPrevios)[vecino] = nodo;
                cola.decreaseKey(vecino , nodo_d + vecino_d); 
            }
        }
        
    }
    //PASO 7: 
    // Se retorna distancia y previos(ya se modificaron utilizando punteros)
}