#include "FileNotFoundError.h"

FileNotFoundError::FileNotFoundError(const string& message) : InvadersError(message) 
{ 
	errorMessage = message; 
}