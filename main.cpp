#include <bits/stdc++.h>
using namespace std;
#include "DijkstraHeap.h"
#include "DijkstraFib.h"
typedef pair<double, int> ii;
// <peso, nodo>

ii generarArista(int j, int nodo){
	// Generamos una arista del grafo aleatoria
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> peso(0,1);
	uniform_int_distribution<int> dist(0, j-1);
	int res = dist(gen);
	while(res == nodo){
		res = dist(gen);
	}
	return {peso(gen), res};
}

int generarNodo(int j){
	// Generamos una arista del grafo aleatoria
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(0, j-1);
	return dist(gen);
}


// cambiar funcion de multigrafo a grafo normal

//n es la cantidad de nodos y e de enlaces
void crearGrafo(vector<vector<ii>>* grafo, int i, int e) {
	//se le asigna tamaño 
	int v = 1 << i;
	(*grafo).resize(v);
	//añadir arista random a 0
	ii aristaInicial = generarArista(v, 0);
    (*grafo)[0].push_back(aristaInicial);
	(*grafo)[aristaInicial.second].push_back({aristaInicial.first, 0});  // Añadimos la arista inversa

    //rellenar los demas
	for(int k = 1; k < v; k++){
		// generar arista random para el nodo 
		ii aristaRandom = generarArista(v, k);
        (*grafo)[k].push_back(aristaRandom);
        (*grafo)[aristaRandom.second].push_back({aristaRandom.first, k});
	}
	//aqui rellenar los 2^j - (v)
	int h = (1 << e) - v;
	while(h > 0){
		//elegir el nodo 
		int indice = generarNodo(v);
		//generar arista random
		ii aristaRandom = generarArista(v , indice);
		(*grafo)[indice].push_back(aristaRandom);
		(*grafo)[aristaRandom.second].push_back({aristaRandom.first, indice});  // Añadimos la arista inversa
		h--;
	}
}


// Funcion para printear el grafo, como lista de adyacencia
void printGrafo(vector<vector<ii>> grafo) {
	for (int i = 0; i < grafo.size(); ++i) {
		cout << i << ": ";
		for (int j = 0; j < grafo[i].size(); ++j) {
			cout << "(" << grafo[i][j].first << "," << grafo[i][j].second << ")";
		}
		cout << endl;
	}
}


//main xd aqui se mainea
int main(){
	vector<vector<ii>> gr;
	crearGrafo(&gr, 2, 2);
	printGrafo(gr);
	vector<int> previos; 
	vector<double> distancias;
	vector<int> previosFib; 
	vector<double> distanciasFib;
	int n = 1 << 2;
	int inicial = generarNodo(n);
	ColaPrioridad cola;
	FibonacciHeap fib;

	// printeamos el nodo
	cout << "Nodo inicial: " << inicial << endl;
	cout << "paso heap" << endl;
    caminoMasCorto(inicial, n, gr, cola, &distancias, &previos);
	cout << "paso fib" << endl; 
    caminoMasCortoFib(inicial, n, gr, fib, &distanciasFib, &previosFib);
	
	cout << "---------------- HEAP --------------" << endl;
	for(int i = 0; i < n; i++) {
        cout << "Distancia para " << i << " es: " << distancias[i] << endl; 
        cout << "Previos para " << i << " es: " << previos[i] << endl; 
    }

	cout << "------------- FIBONACCI -------------" << endl;
	for(int i = 0; i < n; i++) {
        cout << "Distancia para " << i << " es: " << distanciasFib[i] << endl; 
        cout << "Previos para " << i << " es: " << previosFib[i] << endl; 
    }
	return 0;
}

// compile: g++ -std=c++1S1 main.cpp -o mainPenguin
