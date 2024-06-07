#include <bits/stdc++.h>
using namespace std;
#include "fibonacci.h"
// Definimos los pares así al inicio para facilidad de su uso en la priority_queue
typedef pair<double, int> ii;

#define INF 1 << 23

/*  EJEMPLO DE GRAFO
*  0->[< 0, 1 >,< 0, 2 >]
*  1->[< 0, 2 >]  
*  2->[< 0 , 4>]
*  3->[< 0 , 1 >,< 0 , 4 >]
*  4->[< 0 , 1>]
*/

void caminoMasCortoFib(int s, int n, vector<vector<ii>> gr, FibonacciHeap cola,
                            vector<double>* pdistancia, vector<int>* pPrevios) { //n numero de nodos, s nodo inicial, gr es la lista de adyacencia del grafo que ahora tiene pares (distancia, nodo)
    //PASO 1:
    // Cambiamos el tamaño de distancia y previos
    cout << "paso 1" << endl;
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
    cout << "paso 2" << endl;
    (*pdistancia)[s] = 0;
    (*pPrevios)[s] = -1;
    cola.insert({0, s});
    
    //PASO 4: 
    //**** distancia ya esta inicializada con infinito
    //falta inicializar bien previos
    //se mete en la cola los nodos con sus distancias
    cout << "paso 3" << endl;
    for(int i = 0; i < n; i++){
        if(i != s) {
            (*pdistancia)[i] = INF;
            (*pPrevios)[i] = -2;
            cola.insert({INF,i}); // (distancia, nodo)
        }
    }
    //PASO 5:
    //heapifear    
    
    //PASO 6:
    cout << "paso 4" << endl;
    // Mientras la cola no esté vacía, tenemos nodos que revisar
    int previo = -1;
    while(!cola.empty()) {
        cout << "se mira el menor elemento" << endl;
        // Sacamos el nodo que esté a menor distancia ahora mismo  
        auto [nodo_d, nodo] = cola.getMin();
        cout << "remueve minimo" << endl;
        cola.removeMin();

        cout << "revisar vecinos" << endl;
        // Revisamos sus vecinos: vecino_d es el peso entre nodo y vecino
        for(auto [vecino_d, vecino]: gr[nodo]) {
            cout << "vecino que estamos mirando: " << vecino << endl;
            // Si la distancia guardada para el vecino es menor a la distancia de nodo + el peso
            if ((*pdistancia)[vecino] > nodo_d + vecino_d) {
                cout << "if: distancia vecino menor a la distancia del nodo + peso" << endl;
                double distanciaAntigua = (*pdistancia)[vecino];
                (*pdistancia)[vecino] = nodo_d + vecino_d; //se actualiza el valor de la distancia en el arreglo
                (*pPrevios)[vecino] = nodo;
                //obtener referencia al nodo que almacena (distanciaAntigua, vecino)
                cout << "se obtiene referencia al nodo del vecino " << endl; 
                Node* pVecino = cola.refNodo(distanciaAntigua, vecino);
                cout << "se hace el decrease key de " << pVecino << endl;
                cola.decreaseKey(pVecino , nodo_d + vecino_d);
                cout << "paso el decrease key" << endl;
            }
        }
    }

    //PASO 7: 
    // Se retorna distancia y previos(ya se modificaron utilizando punteros)
}




/*
int main(){
    vector<double> distancias; 
    vector<int> previos;
    //asjdnasjnads el tamaño del grafo
    int n = 6;
    //Creamos un grafo de ejemplo
    vector<vector<ii>> gr(n);
    gr[0].push_back({3, 1});
    gr[1].push_back({3, 0});

    gr[0].push_back({10, 4});
    gr[4].push_back({10, 0});
    
    gr[1].push_back({11, 3});
    gr[3].push_back({11, 1});
    
    gr[3].push_back({9, 2});
    gr[2].push_back({9, 3});
    
    gr[4].push_back({5, 3});
    gr[3].push_back({5, 4});
    
    gr[0].push_back({8, 2});
    gr[2].push_back({8, 0});

    gr[1].push_back({6, 5});
    gr[5].push_back({6, 1});

    //hacer cola de prioridad
    ColaPrioridad cola;
    //probar la weaita jajaja
    caminoMasCorto(2, n, gr, cola, &distancias, &previos);

    for(int i = 0; i < n; i++) {
        cout << "Distancia para " << i << " es: " << distancias[i] << endl;
        cout << "Previos para " << i << " es: " << previos[i] << endl; 
    }

    return 0;
}
*/

// how to compile: g++ -std=c++11 DijkstraFib.cpp -o djPenguinFib
// how to compile: g++ -std=c++11 DijkstraFib.cpp -o djPenguinFib