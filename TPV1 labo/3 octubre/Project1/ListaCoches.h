//
// Declaracion de la clase ListaCoches
//

#ifndef LISTACOCHES_H
#define LISTACOCHES_H

#include "Coche.h"

using namespace std;

class ListaCoches {

	// variables privadas
private:
	// declaracion del array dinamico ListaCoches
	Coche* ListCoche;
	int tamListaCoches; // = 0; // inicializacion a 0

	// metodos publicos
public:
	// constructoras
	ListaCoches() : ListCoche(), tamListaCoches(0) {};
	ListaCoches(Coche* list, int tam);
	ListaCoches(const ListaCoches& list);

	// declaracion de metodos
	bool leerModelos();
	int buscarCoche(int codigo, int size);

	void deleteMem();

	// Getter
	int getTam() {
		return tamListaCoches;
	}
};

#endif

