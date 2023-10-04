//
// Declaración de la clase Coche -> funciona como el struct coche
//

#include <string>

using namespace std;

class Coche
{
	// variables privadas
public: // ---------------------------- ATENCIÓN A NAVEGANTES: he puesto las varaiabes publicas para acceder a ellas desde lista coches (aun teniendo el incluye no accedea ellas (????))
	int codigo, precio;
	string nombre;
	
	// metodos publicos
public:
	// constructoras
	Coche() : codigo(0), precio(0), nombre("") {};
	Coche(int p, int c, string n);
	Coche(const Coche& coche);

	// declaracion de operadores -------------------------------------------- ?? los operadores de leer y escribir tienen que estar aqui o en lista
	// lee
	friend istream& operator>>(istream& in, Coche& c);
	// escribe
	friend ostream& operator<<(ostream& in, const Coche& c);
};

