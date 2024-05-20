#include <bits/stdc++.h>
using namespace std;
// Definimos los pares así al inicio para facilidad de su uso en la priority_queue
typedef pair<int, int> ii;

#define INF 1 << 23

/*  EJEMPLO DE GRAFO
*  0->[< 0, 1 >,< 0, 2 >]
*  1->[< 0, 2 >]  
*  2->[< 0 , 4>]
*  3->[< 0 , 1 >,< 0 , 4 >]
*  4->[< 0 , 1>]
*/

struct cola_prioridad {
    vector<ii> heap;
    void push(ii p) {
        heap.push_back(p);
        push_heap(heap.begin(), heap.end(), greater<ii>());
    }
    ii top() {
        return heap.front();
    }
    void pop() {
        pop_heap(heap.begin(), heap.end(), greater<ii>());
        heap.pop_back();
    }
    bool empty() {
        return heap.empty();
    }
};


vector<int> caminoMasCorto(int s, int n, vector<vector<ii>> gr, cola_prioridad cola,
                            vector<int>* pdistancia, vector<int>* pPrevios) { //n numero de nodos, s nodo inicial, gr es la lista de adyacencia del grafo que ahora tiene pares (distancia, nodo)
    //PASO 1:
    // Cambiamos el tamaño de distancia y previos
    (*pdistancia).resize(n);
    (*pPrevios).resize(n);
    // camino final es 0 4 2 1 : [-1, 2, x, 4, x, 0]

    //PASO 2
    // Iniciamos la pq con pares que guardaran (distancia,nodo)
    // y cambiamos su configuración para que nos de los más pequeños primero
    // ** esto se reemplaza en los casos de heap y cola de fibonacci
    //priority_queue<ii, vector<ii>, greater<ii>> Q;

    //PASO 3
    // Metemos la fuente a la cola y asignamos su distancia
    (*pdistancia)[s] = 0;
    (*pPrevios)[s] = -1;
    cola.push({0, s});
    
    //PASO 4: 
    //**** distancia ya esta inicializada con infinito
    //falta inicializar bien previos
    //se mete en la cola los nodos con sus distancias
    for(int i = 0; i < n; i++){
        if(i != s) {
            (*pdistancia)[i] = INF;
            (*pPrevios)[i] = -2;
            cola.push({INF,i}); // (distancia, nodo)
        }
    }
    
    //PASO 6:
    // Mientras la cola no esté vacía, tenemos nodos que revisar
    while(!cola.empty()) {

        // Sacamos el nodo que esté a menor distancia ahora mismo
        auto [nodo_d, nodo] = cola.top();
        cola.pop();

        // Revisamos sus vecinos: vecino_d es el peso entre nodo y vecino
        for(auto [vecino_d, vecino]: gr[nodo]) {
            // Si la distancia guardada para el vecino es menor a la distancia de nodo + el peso
            if ((*pdistancia)[vecino] > nodo_d + vecino_d) {
                (*pdistancia)[vecino] = nodo_d + vecino_d; //se actualiza el valor de la distancia em el arreglp
                (*pPrevios)[vecino] =  nodo;
                //cola.decreasekey(vecino , nodo_d + vecino_d); se actualiza el valor de distancia en la cola
            }
        }
    }

    //PASO 7: 
    // Se retorna distancia y previos(ya se modificaron utilizando punteros)
}