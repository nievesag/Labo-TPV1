#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

// le cambia el nombre para escribir uint :P
using uint = unsigned int; 

void firstTest()
{
	SDL_Window* window = nullptr; // puntero a ventana
	SDL_Renderer* renderer = nullptr; // puntero a renderer TODO EN EL MISMO RENDERER
	SDL_Texture* ibai_bueno = nullptr; // puntero a la textura de ibai pero bueno (que no malo) Variable para la textura
	SDL_Texture* ibai_perro = nullptr;
	// TEXTURA LISTA PARA SER USADA
	// 
	// tamaño de ventana
	constexpr uint winWidth = 800; 
	constexpr uint winHeight = 600; 

	// inicializa TODO 
	SDL_Init(SDL_INIT_EVERYTHING);

	// crea ventana
	window = SDL_CreateWindow("Ibai malagueño (oriental)", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);

	// crea renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// error
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	// 
	else {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1); // rgba (rgb con transparencia)
		

		// estas cosas dentro del else
		// ------------- IBAI MALAGUENO -------------
		string filename = "..\\images\\ibaimalagueno.png"; // nombre del fichero .png
		SDL_Surface* surface = IMG_Load(filename.c_str()); // leer
		ibai_bueno = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface); // borra la extructura auxiliar surface

		// -------------  QUE LE DEBE AL PSOE EL IBAI PERRO? -------------
		string filenamedog = "..\\images\\dog.png"; // nombre del fichero .png
		SDL_Surface* surfaceperro = IMG_Load(filenamedog.c_str()); // leer
		ibai_perro = SDL_CreateTextureFromSurface(renderer, surfaceperro);
		SDL_FreeSurface(surfaceperro); // borra la extructura auxiliar surface

		// FP DE ANIMACION 2D Y 3D EN MURCIA
		//int textW, textH; 
		//SDL_QueryTexture(ibai_perro, nullptr, nullptr, &textW, &textH); // Para saber el tamaño de la textura
		
		SDL_Rect srcRect, destRect; 
		srcRect.w = 128; 
		srcRect.h = 82; // sacar el tamaño manual (sin usar el query xd)

		// separa la pantalla en celdillas
		uint cellW = winWidth / 6; uint cellH = winHeight / 6;

		destRect.w = cellW;
		destRect.h = cellH;
		destRect.x = 0;
		destRect.y = 350; // Celda(0, 1)

		srcRect.x = 0 * 128; 
		srcRect.y = 0; // Tamaño frame textura (textura en grid de 6x1)


		
		SDL_RenderClear(renderer); // limpia pantalla

		SDL_RenderCopy(renderer, ibai_bueno, nullptr, nullptr); // Copia en buffer
		SDL_RenderCopy(renderer, ibai_perro, &srcRect, &destRect);

		SDL_RenderPresent(renderer); // muestra la escena
		SDL_Delay(5000); // espera 5 seg y cierra pantalla
	}

	// muerte y destruccion (no olvido borrar la memoria dinamica)
	SDL_DestroyTexture(ibai_bueno); // Borra memoria dinámica
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit(); // cierra pantalla
}

int main(int argc, char* argv[])
{
	firstTest();
	return 69;
}
