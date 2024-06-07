#include "Font.h"

#include "checkML.h"

#include <iostream>
#include <SDL.h>
#include "Errors/InvadersError.h"

Font::Font(const std::string& filename, int size) { load(filename, size); }

Font::~Font() { Free(); }

void Font::load(const std::string& filename, int size) {
	font = TTF_OpenFont(filename.c_str(), size); // crea font
}

void Font::Free() {
	TTF_CloseFont(font); // destruye font
	font = nullptr;
}

SDL_Surface* Font::generateSurface(const std::string& text, SDL_Color color) const
{
	// devuelve la surface
	return TTF_RenderUTF8_Solid(font, text.c_str(), color);
}

Texture* Font::generateTexture(SDL_Renderer* renderer, const std::string& text, SDL_Color color) const
{
	// genera una surface, necesaria para poder generar la textura
	SDL_Surface* surface = generateSurface(text.c_str(), color);

	// genera la textura
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	// error
	if (texture == nullptr)
		throw InvadersError("al crear una textura a partir de texto");

	// devuelve la textura creada
	return new Texture(renderer, texture, 1, 1);
}