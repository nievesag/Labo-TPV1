//
// Declaracion de la clase ListaAlquiler
//

#ifndef LISTAALQUILERES_H
#define LISTAALQUILERES_H

#include "Alquiler.h"
#include "Date.h"
#include <fstream>

using namespace std;

class ListaAlquiler {

	// variables privadas
private:
	// declaracion del array dinamico ListaAlquiler
	Alquiler* ListAlquiler;
	Alquiler* alquiler;
	int tamListaAlquiler;

	// metodos publicos
public:
	// constructoras
	ListaAlquiler() : ListAlquiler(nullptr), tamListaAlquiler(0) {};
	//ListaAlquiler(Alquiler* alquiler, int tam);
	//ListaAlquiler(const ListaAlquiler& alquiler);

	// decaracion de metodos
	bool leerAlquileres(ListaCoches listCoches);
	void ordenarAlquileres();
	void mostrarAlquileres();

	friend ostream& operator<<(ostream& out, const ListaAlquiler&);

	~ListaAlquiler();

	// setter
	int setTam(int tam) {
		tamListaAlquiler = tam;
	}

	// Getter
	int getTam() {
		return tamListaAlquiler;
	}

	void setAlquiler(Alquiler* a) {
		alquiler = a;
	}

};

#endif