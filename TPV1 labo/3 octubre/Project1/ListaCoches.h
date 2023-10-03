//
// Implementación de la clase ListaCoches
//

#include "Coche.h"

using namespace std;


class ListaCoches
{

private:
	// declaracion del array dinamico ListaCoches
	Coche* ListCoche;
	int tamListaCoches; // = 0; // inicializacion a 0

public:
	// constructoras
	ListaCoches() : ListCoche(), tamListaCoches(0) {};
	ListaCoches(Coche* list, int tam);
	ListaCoches(const ListaCoches& list);

	// operadores
	//

	//metodos
	bool leerModelos();

};

