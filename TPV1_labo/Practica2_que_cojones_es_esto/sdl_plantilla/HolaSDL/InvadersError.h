#ifndef INVADERSERROR_H
#define INVADERSERROR_H

#include <stdexcept>
using namespace std;

class InvadersError : public logic_error
{
    // SUPERCLASE DE LAS DEM�S EXCEPCIONES
    // Reutiliza el constructor y m�todo what de logic_error para almacenamiento y uso del mensaje de la excepci�n
protected:
    string errorMessage;
public:
    InvadersError(const string& message);
    char const* what() const override;
};
#endif