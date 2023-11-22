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

	Vector2D() {} // constructora vacia

	// ---- constructora ----
	// constructora con las variables declaradas
	Vector2D::Vector2D(T x, T y)
		: x(x), y(y) {} // los corchetes vacios inicializa las variables a 0

	// ---- getters ----
	// const porque no editan las variables 
	// getter x
	T getX() const {
		return x;
	}

	// getter y
	T getY() const {
		return y;
	}

	// ----- setters -----------
	void setX(T newX) {
		x = newX;
	}

	void setY(T newY) {
		y = newY;
	}

	// ---- OPERADORES ----

	// operador +
	Vector2D<T>& operator+(Vector2D<T> const& other) {
		Vector2D<T> aux(0, 0);

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
};

	// establecer alias
	template <class T = double> using Point2D = Vector2D<T>;

#endif