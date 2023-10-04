//
// Declaración de la clase Coche -> funciona como el struct coche
//

#include <string>

using namespace std;

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

	// declaracion de operadores -------------------------------------------- ?? los operadores de leer y escribir tienen que estar aqui o en lista ??
	// lee
	friend istream& operator>>(istream& in, Coche& c);
	// escribe
	friend ostream& operator<<(ostream& in, const Coche& c);

	// declaraciones de metodos
		// Setter
	void setCodigo(int c);

		// Getter
	int getCodigo();

	// Setter
	void setPrecio(int p);

	// Getter
	int getPrecio();

	// Setter
	void setNombre(string n);

	// Getter
	string getNombre();
};

