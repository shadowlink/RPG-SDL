#ifndef _IMAGEN_
#define _IMAGEN_
#include <SDL/SDL.h>

class Imagen 
{
	public:
		Imagen(char *ruta, int filas = 1, int columnas = 1, Uint32 r = 255, Uint32 g = 0, Uint32 b = 255);  
		~Imagen();
		void dibujar(SDL_Surface *superficie, int i, int x, int y, int flip = 1);
		int anchura(void);
		int altura(void);
		int cuadros(void);
	private:
		SDL_Surface *imagen;
		SDL_Surface *imagen_invertida;
		int columnas;
		int filas;
		int w, h; 
		SDL_Surface * invertir_imagen(SDL_Surface *imagen);
		Uint32 colorkey;
};

#endif
