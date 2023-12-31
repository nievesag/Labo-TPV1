//
// Declaración de la clase Alquiler -> funciona como el struct alquiler
//

#ifndef ALQUILER_H
#define ALQUILER_H

#include "Date.h"
#include "Coche.h"
#include "ListaCoches.h"

using namespace std;

class Alquiler
{
	// variables privadas
private:
	// info archivo rent -> codigo / fecha / cantidad
	Coche* coche; // puntero a coche
	Date* date; // puntero a fecha
	int date2;
	int dia;
	int mes;
	int year;
	int cant;

	// metodos publicos
public:
	// constructoras
	Alquiler() : coche(nullptr), date(nullptr), date2(0), dia(0), mes(0), year(0), cant(0) {};
	Alquiler(Coche* codigo, Date* date,int date2, int dia, int mes, int year, int cant);
	Alquiler(const Alquiler& alquiler);

	// declaracion de operadores
	// lee 
	//friend istream& operator>>(istream& in, Alquiler& a);
	// escribe
	friend ostream& operator<<(ostream& in, const Alquiler& a);


	bool operator<(const Alquiler& izq) const;

	Alquiler leeAlquiler(ListaCoches& listCoches);


	// para acceso externo a variables privadas
	// Setter
	void setCoche(Coche* c) {

		//puntero hacia coche
		coche = c;
		
		//coche->setCodigo(c); // acceso al metodo setCodigo de coche (puntero->atributo =equivalente a= (*puntero).atributo)
	}


	// Getter
	int getCodigo() {
		return coche->getCodigo();
	}

	// Getter
	// lo he cambiado porque es mas comodo
	int getDate() {
		return date2;
	}

	void setDate(int d) {
		date2 = d;
	}

	Coche* getCoche(int pos) {
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