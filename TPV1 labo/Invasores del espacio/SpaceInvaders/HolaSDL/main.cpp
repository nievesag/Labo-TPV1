#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include "Vector2D.h"

using namespace std;

using uint = unsigned int;

void xd()
{
	
}

int main(int argc, char* argv[])
{
	
	Vector2D<int> uwu(1, 2);

	cout << uwu.getX() << " " << uwu.getY() << endl;
	
	Vector2D<int> owo(2, 1);

	cout << owo.getX() << " " << owo.getY() << endl;

	Vector2D<int> ewe = owo - uwu;

	cout << ewe.getX() << " " << ewe.getY() << endl;

	cout << (uwu*owo) << endl;

	Vector2D<int> iwi = uwu * 2;

	cout << iwi.getX() << " " << iwi.getY() << endl;


	return 69;
}
