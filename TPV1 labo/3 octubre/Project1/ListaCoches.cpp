//
// Implementación de la clase ListaCoches
//


#include "ListaCoches.h"

using namespace std;

bool ListaCoches::leerModelos()
{
    // saca el tamaño de la lista de coches
    coches >> tamListaCoches;

    // crea el array dinamico ListaCoches con elementos de tipo coche y tamaño tamListaCoches
    ListaCoches = new coche[tamListaCoches];

    // bucle para leer los datos
    for (int i = 0; i < tamListaCoches; i++)
    {
        // lee el codigo
        coches >> ListaCoches[i].codigo;
        // lee el precio
        coches >> ListaCoches[i].precio;
        // lee el nombre
        coches >> ListaCoches[i].nombre;
        coches >> c;
        ListaCoches[i].nombre += " " + c; // para las dos palabras del modelo del coche
    }

    // ----------DEBUG------------
    /*
    for (int i = 0; i < tamListaCoches; i++) {
        cout << ListaCoches[i].codigo;
        cout << " ";
        cout << ListaCoches[i].nombre;
        cout << " ";
        cout << ListaCoches[i].precio;
        cout << "\n";
    }
    */
}

return coches.is_open(); // true -> archivo coches abierto / false -> error
}
