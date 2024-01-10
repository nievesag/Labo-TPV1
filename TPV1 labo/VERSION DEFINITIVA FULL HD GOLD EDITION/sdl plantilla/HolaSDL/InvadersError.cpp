#include "InvadersError.h"
#include "string"

InvadersError::InvadersError(const string& message) : logic_error(message)
{
    errorMessage = message;
}

char const* InvadersError::what() const
{
    return errorMessage.c_str(); // devuelve el mensaje de error en const string
}