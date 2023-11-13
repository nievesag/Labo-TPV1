//
// Declaracion de la clase ListaCoches
//

#ifndef LISTACOCHES_H
#define LISTACOCHES_H

#include "Coche.h"
#include <string>

using namespace std;

class ListaCoches {

	// variables privadas
private:
	// declaracion del array dinamico ListaCoches
	Coche* ListCoche;
	int tamListaCoches;

	// metodos publicos
public:
	// constructoras
	ListaCoches() : ListCoche(nullptr), tamListaCoches(0) {};
	//ListaCoches(Coche* list, int tam);
	//ListaCoches(const ListaCoches& list);

	/*// declaracion de operadores
	// lee
	friend istream& operator>>(istream& in, ListaCoches& lc);
	// escribe
	friend ostream& operator<<(ostream& in, const ListaCoches& lc);
	*/
	// declaracion de metodos
	bool leerModelos();
	int buscarCoche(int codigo, int size);

	~ListaCoches();

	// Getter
	int getTam() {
		return tamListaCoches;
	}

	Coche* getListCoches() {
		return ListCoche;
	}
};

#endif

