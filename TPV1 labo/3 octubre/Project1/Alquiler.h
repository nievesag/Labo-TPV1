//
// Declaración de la clase Alquiler -> funciona como el struct alquiler
//
using namespace std;

#ifndef ALQUILER_H
#define ALQUILER_H

#include "Date.h"
#include "Coche.h"

using namespace std;

class Alquiler
{
	// variables privadas
private:
	// info archivo rent -> codigo / fecha / cantidad
	Coche* coche; // puntero a coche
	Date* date; // puntero a fecha
	int cant;

	// metodos publicos
public:
	// constructoras
	Alquiler() : coche(), date(), cant() {};
	Alquiler(Coche* codigo, Date* date, int cant);
	Alquiler(const Alquiler& alquiler);

	// declaracion de operadores
	// lee 
	friend istream& operator>>(istream& in, Alquiler& a);
	// escribe
	friend ostream& operator<<(ostream& in, const Alquiler& a);

	// para acceso externo a variables privadas
	// Setter
	void setCoche(int c) {
		coche->setCodigo(c); // acceso al metodo setCodigo de coche (puntero->atributo =equivalente a= (*puntero).atributo)
	}

	// Getter
	int getCodigo() {
		return coche->getCodigo();
	}

	// wtf acceso a la fecha me esta desquiciando ligeramente ????????
	// Setter
	void setDate(Date& d) {
		date = &d;
	}

	// Getter
	int getDate() {
		return date;
	}

	// Setter
	void setCant(int ca) {
		cant = ca;
	}

	// Getter
	int getCant() {
		return cant;
	}
};
#endif