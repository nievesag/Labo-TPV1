#include "FileFormatError.h"

FileFormatError::FileFormatError(const string& message) : InvadersError(message) 
{ 
	errorMessage = message; 
}