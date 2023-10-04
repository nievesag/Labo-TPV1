//
// Implementación de la clase ListaCoches
//

#include "Coche.h"

using namespace std;

class ListaCoches
{
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

	// operadores
	//

	// declaracion de metodos
	bool leerModelos();
	int buscarCoche();
};

