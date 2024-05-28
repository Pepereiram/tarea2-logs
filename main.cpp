#include <bits/stdc++.h>
using namespace std;
#include "Dijkstra.h"
typedef pair<double, int> ii;

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


//n es la cantidad de nodos y e de enlaces
void crearGrafo(vector<vector<ii>>* grafo, int i, int e) {
	//se le asigna tamaño 
	int v = 1 << i;
	(*grafo).resize(v);
	//añadir arista random a 0
	(*grafo)[0].push_back(generarArista(v-1 , 0));
    //rellenar los demas
	for(int k = 1; k < v; k++){
		//aqui hacer la wea random
		ii aristaRandom = generarArista(k , k);
		(*grafo)[k].push_back(aristaRandom);
	}
	//aqui rellenar los 2^j - (v)
	int h = (1 << e) - v;
	while(h > 0){
		//elegir el nodo 
		int indice = generarNodo(v);
		ii aristaRandom = generarArista(v , indice);
		(*grafo)[indice].push_back(aristaRandom);
		//generar una arista random 
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
    //aaaaaaaaa
	vector<vector<ii>> gr;
	crearGrafo(&gr, 2, 3);
	printGrafo(gr);
	vector<int> previos; 
	vector<double> distancias;
	int n = 1 << 2;
	int inicial = generarNodo(n);
	ColaPrioridad cola;
	// printeamos el nodo
	cout << "Nodo inicial: " << inicial << endl;
    caminoMasCorto(inicial, n, gr, cola, &distancias, &previos);
	
	for(int i = 0; i < n; i++) {
        cout << "Distancia para " << i << " es: " << distancias[i] << endl; 
        cout << "Previos para " << i << " es: " << previos[i] << endl; 
    }
	return 0;
}
// compile: g++ -std=c++11 main.cpp -o mainPenguin
