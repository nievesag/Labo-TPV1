//
// Implementación de la clase ListaCoches
//

#include <array>
#include "ListaCoches.h"
#include <fstream>
#include "Coche.h" // ??????? si lista coches.h incluche coche.h esto tiene que incluirlo????????

using namespace std;

bool ListaCoches::leerModelos()
{
    // abre el archivo coches.txt
    fstream coches("coches.txt");

    string c;

    // saca el tamaño de la lista de coches
    coches >> tamListaCoches;

    // crea el array dinamico ListaCoches con elementos de tipo coche y tamaño tamListaCoches
    ListCoche = new Coche[tamListaCoches];

    // bucle para leer los datos
    for (int i = 0; i < tamListaCoches; i++)
    {
        // lee el codigo
        coches >> ListCoche[i].codigo;
        // lee el precio
        coches >> ListCoche[i].precio;
        // lee el nombre
        coches >> ListCoche[i].nombre;
        coches >> c;
        ListCoche[i].nombre += " " + c; // para las dos palabras del modelo del coche
    }
    return coches.is_open(); // true -> archivo coches abierto / false -> error
}
