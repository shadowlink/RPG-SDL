// Listado: Animacion.cpp
//
// Implementación de la clase animación

#include <iostream>

#include "animacion.h"
#include "imagen.h"
#include "control_animacion.h"

using namespace std;

Animacion::Animacion(char *ruta_imagen, int filas, int columnas,\
		     char *frames, int retardo_) {

    // Inicializamos las variables de la clase

    this->imagen = new Imagen(ruta_imagen, filas, columnas);
    this->control_animacion = new Control_Animacion(frames);
    this->retardo_ = retardo_;

}

void Animacion::animar(SDL_Surface *pantalla, int x, int y, int flip) {

    Uint32 t0;
    Uint32 t1;
    
    for( ; ; ) {

	imagen->dibujar(pantalla, control_animacion->cuadro(),x, y, flip);
	control_animacion->avanzar();
	SDL_Flip(pantalla);

	SDL_FillRect(pantalla, NULL, \
		     SDL_MapRGB(pantalla->format, 0, 0, 0));

	t0 = SDL_GetTicks();
	t1 = SDL_GetTicks();

	while((t1 - t0) < retardo_) {

	    t1 = SDL_GetTicks();

	}
	
    }

}

// El control de la temporalidad tiene que se externo

void Animacion::paso_a_paso(SDL_Surface *pantalla, int x, int y, int flip)
{
    Uint32 t0 = SDL_GetTicks();
    Uint32 t1 = SDL_GetTicks();
   
    if(control_animacion->numero_cuadros() < 2) 
    {	
		imagen->dibujar(pantalla, control_animacion->cuadro(), x, y, flip);
		control_animacion->avanzar();
    } 
    else 
    {
		do 
		{
			t1 = SDL_GetTicks();
		} 
		while((t1 - t0) < retardo_);
		
		imagen->dibujar(pantalla, control_animacion->cuadro(), x, y, flip);
		control_animacion->avanzar();

    }
}

Uint32 Animacion::retardo() {

    return retardo_;
}
