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
	int tamListaAlquiler;

	// metodos publicos
public:
	// constructoras
	ListaAlquiler() : ListAlquiler(), tamListaAlquiler(0) {};
	ListaAlquiler(Alquiler* alquiler, int tam);
	ListaAlquiler(const ListaAlquiler& alquiler);

	// decaracion de metodos
	bool leerAlquileres();
	void ordenarAlquileres();
	void mostrarAlquileres();

	bool leerAlquileres(ListaCoches listCoches);

	friend ostream& operator<<(ostream&, const ListaAlquiler&);

	void deleteMem();

	~ListaAlquiler();

	// Getter
	int getTam() {
		return tamListaAlquiler;
	}
};

#endif