//
// Declaración e imeplementación de la clase Vector2D -> no necesita cpp
//

#ifndef VECTOR2D_H
#define VECTOR2D_H

// !!! por las plantillas usar definiciones de funciones en el h -> el código depende del argumento que le pases (código no cerrado)
template <typename T> class Vector2D 
{
	// variables privadas
private: 
	T x, y;

	// metodos publicos
public:
	// METODOS
	
	// ---- constructora ----
	// constructora con las variables declaradas
	Vector2D::Vector2D(T x, T y)
		: x(x), y(y) {} // los corchetes vacios inicializa las variables a 0

	// constructora con un vector (deberiamos ponerlo con el setter????) -> 
	// no entiendo por que da error oop
	// Vector2D::Vector2D(const Vector2D& vec) 
	//	: x(vec.getX()), y(vec.getY()) { }

	// ---- destructora ----
	// lo he pensado otra vez e igual no hace falta una destructora porque no usa memoria
	// dinamica (aka new) :v (me hacia ilusion el :v)
	Vector2D::~Vector2D() {

		// ????
		//delete[] ????;
	}

	// ---- getters ----
	// getter x
	T getX() {
		return x;
	}
	
	// getter y
	T getY() {
		return y;
	}

	// ---- OPERADORES ----
	
	// operador +
	Vector2D<T>& operator+(Vector2D<T> const& other) {
		Vector2D<T> aux (0,0);

		aux.x = this->getX() + other.x;
		aux.y = this->getY() + other.y;

		return aux;
	}

	// operador -
	Vector2D<T>& operator-(Vector2D<T> const& other) {
		Vector2D<T> aux(0, 0);

		aux.x = this->getX() - other.x;
		aux.y = this->getY() - other.y;

		return aux;
	}

	// producto escalar (*)
	T& operator*(Vector2D<T> const& other) {
		// pe = (v1*u2)+(v2+u2)
		T esc = (getX() * other.x) + (getY() * other.y);
		return esc;
	}

	// producto vector-escalar (*)	
	Vector2D<T>& operator*(int const& other) {
		Vector2D<T> aux(0, 0);

		aux.x = getX() * other;
		aux.y = getY() * other;

		return aux;
	}
	
	// establecer alias
	template <typename T> using Point2D = Vector2D;
};


// CODIGO PARA PROBAR VECTOR2D (PONER EN EL MAIN)
// (poner #include "Vector2D.h"; en el main para probarlo individualmente)
/*
	// --- MIRAR QUE SE CREA BIEN
	Vector2D<int> uwu(1, 2);

	cout << uwu.getX() << " " << uwu.getY() << endl;

	Vector2D<int> owo(2, 1);

	cout << owo.getX() << " " << owo.getY() << endl;
	
	// --- MIRAR QUE RESTE/SUME BIEN
	Vector2D<int> ewe = owo - uwu;

	cout << ewe.getX() << " " << ewe.getY() << endl;

	// --- MIRAR QUE HAGA EL PRODUCTO ESCALAR BIEN
	cout << (uwu*owo) << endl;

	// --- MIRAR QUE HAGA EL PRODUCTO CON UN ESCALAR BIEN
	Vector2D<int> iwi = uwu * 2;

	cout << iwi.getX() << " " << iwi.getY() << endl;
*/
#endif

