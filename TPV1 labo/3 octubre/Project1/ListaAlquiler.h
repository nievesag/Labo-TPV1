//
// Declaracion de la clase ListaAlquiler
//

#ifndef LISTACOCHES_H
#define LISTACOCHES_H

#include "Alquiler.h"

using namespace std;

class ListaAlquiler
{
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
	ListaAlquiler(const ListaAlquiler& list);

	// decaracion de metodos
	bool leerAlquileres();
	void ordenarAlquileres();
	void mostrarAlquileres();

	void deleteMem();

	// Getter
	int getTam() {
		return tamListaAlquiler;
	}
};

#endif