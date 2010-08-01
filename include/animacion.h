#ifndef _ANIMACION_
#define _ANIMACION_
#include <SDL/SDL.h>
#include "imagen.h"
#include "control_animacion.h"

class Animacion {
	public:
		Animacion(char *ruta_imagen, int filas, int columnas, char *frames, int retardo);
		void animar(SDL_Surface *pantalla, int x, int y, int flip = 1);
		void paso_a_paso(SDL_Surface *pantalla, int x, int y, int flip = 1);
		Uint32 retardo();
	private:
		Imagen *imagen;
		Control_Animacion *control_animacion;
		Uint32 retardo_;
};

#endif
