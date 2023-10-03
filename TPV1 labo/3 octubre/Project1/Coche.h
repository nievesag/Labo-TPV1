//
// Declaración de la clase Coche
//


using namespace std;
#include <string>

class Coche
{
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

	// declaracion de metodos
	bool leerModelos();

	
};

