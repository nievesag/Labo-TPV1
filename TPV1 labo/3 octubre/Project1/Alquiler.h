//
// Declaración de la clase Alquiler -> funciona como el struct alquiler
//

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
	int dia;
	int mes;
	int year;
	int cant;

	// metodos publicos
public:
	// constructoras
	Alquiler() : coche(), date(), dia(), mes(), year(), cant() {};
	Alquiler(Coche* codigo, Date* date, int dia, int mes, int year, int cant);
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

	// Getter
	Date* getDate() {
		return date;
	}

	Coche* getCoche() {
		return coche;
	}

	void setDia(int d) {
		dia = d;
	}

	int getDia() {
		return dia;
	}

	void setMes(int m) {
		mes = m;
	}

	int getMes() {
		return mes;
	}

	void setYear(int y) {
		year = y;
	}

	int getYear() {
		return year;
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