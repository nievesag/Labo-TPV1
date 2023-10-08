//
// Declaración de la clase Coche -> funciona como el struct coche
//
using namespace std;

#ifndef COCHE_H
#define COCHE_H

#include <string>

class Coche {

	// variables privadas
private:
	int codigo, precio;
	string nombre;
	
	// metodos publicos
public:
	// constructoras
	Coche() : codigo(0), precio(0), nombre("") {};
	Coche(int p, int c, string n);
	Coche(const Coche& coche);

	// declaracion de operadores
	// lee
	friend istream& operator>>(istream& in, Coche& c);
	// escribe
	friend ostream& operator<<(ostream& in, const Coche& c);

	// para acceso externo a variables privadas
	// Setter
	void setCodigo(int c) {
		codigo = c;
	}

	// Getter
	int getCodigo() {
		return codigo;
	}

	// Setter
	void setPrecio(int p) {
		precio = p;
	}

	// Getter
	int getPrecio() {
		return precio;
	}

	// Setter
	void setNombre(string n) {
		nombre = n;
	}

	// Getter
	string getNombre() {
		return nombre;
	}
};
#endif


