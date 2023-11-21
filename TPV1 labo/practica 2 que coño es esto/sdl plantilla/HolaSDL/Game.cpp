#include "Game.h"


using namespace std;

struct TextureSpec
{
	const char* url;

	// width height
	int nw, nh;
};


// ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ PLACEHOLDERRRRRRRRRRRRRRRRRRR !!!!!!!!!!!!!!!!!!!
// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo TextureSpec 
array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"..\\images\\aliens2.png", 2, 3},	  // alien 1 // 32,32
	{ "..\\images\\aliens2.png", 2, 3 },			  // alien 2 // 44,32
	{ "..\\images\\aliens2.png", 2, 3 },			  // alien 3 // 48,32
	{ "..\\images\\spaceship.png", 1, 1 },			  // nave	 // 34,21
	{ "..\\images\\bunker.png", 4, 1 },				  // bunker  // 88,57
	{ "..\\images\\stars.png", 1, 1 }
};



// constructora del game
Game::Game()
{



}
