#include <iostream>
#include <windows.h>
using namespace std;

struct Registro {

	string nombre;
	double sueldo;
	int edad;

};

void func(Registro& reg, double *irpf, int *edad) {
	const double TIPO = 0.18;
	//const double* t = &TIPO;
	reg.edad++;
	*irpf = reg.sueldo * TIPO;
	cout << *irpf;
	edad = &reg.edad;
	cout << " ";
	cout << *edad; 

}

void funcC(const Registro& reg, double *irpf, int *edad) {
	const double TIPO = 0.18;

	// irpf = reg.sueldo * TIPO; -> hemos pasado el irpf por puntero como argumeno del metodo y aqui
	*irpf = reg.sueldo * TIPO;

	//
	*edad = reg.edad;
}


int main() {
	Registro r1;
	Registro* pr = new Registro;

	// los registros r1 y *pr toman valor
	r1.nombre = "Joserra";
	r1.edad = 59;
	r1.sueldo = 1540;

	double cotiza; int años;

	cotiza = 20;
	años = 38;

	double *c;
	int *a;

	c = &cotiza;
	a = &años;

	func(r1, c, a);
	funcC(*pr, c, a);
}