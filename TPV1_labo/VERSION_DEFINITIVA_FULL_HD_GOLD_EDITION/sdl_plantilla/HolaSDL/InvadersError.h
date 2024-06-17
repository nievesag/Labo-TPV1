#ifndef INVADERSERROR_H
#define INVADERSERROR_H

#include <stdexcept>
#include "checkML.h"

class InvadersError : public std::logic_error
{
    // SUPERCLASE DE LAS DEMÁS EXCEPCIONES
    // Reutiliza el constructor y método what de logic_error para almacenamiento y uso del mensaje de la excepción
protected:
    std::string errorMessage;
public:
    InvadersError(const std::string& message);
    char const* what() const override;
};
#endif