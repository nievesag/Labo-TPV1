//
// Implementación de la clase ListaCoches
//

#include "ListaCoches.h"
#include <array>
#include <fstream>
#include <iostream>

using namespace std;

bool ListaCoches::leerModelos()
{
    // abre el archivo coches.txt
    fstream cochesRead("coches.txt");

    // c para el primer nombre, extra para el segundo
    string c, extra;

    // code para los valores del codigo y el precio
    int code;

    // saca el tamaño de la lista de coches
    cochesRead >> tamListaCoches;

    // crea el array dinamico ListaCoches con elementos de tipo coche y tamaño tamListaCoches
    ListCoche = new Coche[tamListaCoches];

    // bucle para leer los datos
    for (int i = 0; i < tamListaCoches; i++)
    {
        // lee el codigo
        cochesRead >> code;
        // lo mete en la lista
        ListCoche[i].setCodigo(code);

        // lee el precio
        cochesRead >> code; 
        // lo mete en el precio
        ListCoche[i].setPrecio(code);

        // lee el nombre
        cochesRead >> c;
        cochesRead >> extra;
        ListCoche[i].setNombre(c + " " + extra); // para las dos palabras del modelo del coche
    }

    /*
    // -----------DEBUG------------
    for (int i = 0; i < tamListaCoches; i++) {
        cout << ListCoche[i];
        cout << &ListCoche[i];
        cout << "\n";
    }
    */

    return cochesRead.is_open(); // true -> archivo coches abierto / false -> error
}

int ListaCoches::buscarCoche(int codigo, int size)
{
    //int size;
    int ini = 0, fini = size - 1;
    int med = -1;

    Coche *p = ListCoche;
    bool enc = false;

    // bucle continua mientras no se haya encontrado y no se pase ini de fini
    while (!enc && ini <= fini) {

        // reinicia el medio en cada vuelta
        med = (ini + fini) / 2;

        // si el codigo dado es menor que el que hemos encontrado
        //coche.getCodigo() 
        if (codigo < p[med].getCodigo()) {
            // se mueve el indice del final hacia abajo la distancia de med - 1
            fini = med - 1;
        }
        // coche.codigo
        else if (codigo > p[med].getCodigo()) {
            // se mueve el indice del principio hacia arriba la distancia med +1
            ini = med + 1;
        }
        // si son iguales se ha encontrado
        else enc = true;
    }

    if (ini > fini) med = -1;

    return med;
}

void insertaCoche(int codigo, int precio, string nombre) 
{
    // TODO
}

// destructora
ListaCoches::~ListaCoches() {

    delete[] ListCoche;
    ListCoche = nullptr;
    tamListaCoches = 0;
}
