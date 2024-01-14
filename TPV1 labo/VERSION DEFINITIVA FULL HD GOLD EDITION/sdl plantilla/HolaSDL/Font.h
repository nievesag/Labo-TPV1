#ifndef FONT_H
#define FONT_H

#include "checkML.h"

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "texture.h"

// ENUNCIADO:
// Utiliza el paquete TTF de SDL para manejar los distintos textos del juego
// Encapsular la interacción con la biblioteca en la clase Font
// definir un objeto del juego Label para colocar piezas de texto en la pantalla
// (Button podría ser subtipo de Label).
class Font
{
	// atributos privados
private:
	TTF_Font* font = nullptr; // fuente

public:
	Font() = default;
	Font(const std::string& filename, int size);
	Font(const Font& font) = delete;
	~Font();

	void load(const std::string& filename, int size);
	void Free();


	SDL_Surface* generateSurface(const std::string& text, SDL_Color color) const;

	Texture* generateTexture(SDL_Renderer* renderer, const std::string& text,
		SDL_Color color) const;

};

#endif