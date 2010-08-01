#include <iostream>
#include "animacion.h"

using namespace std;

//Constructor sobrecargado
Animacion::Animacion(char *ruta_imagen, int filas, int columnas, char *frames, int retardo_) 
{
    this->imagen = new Imagen(ruta_imagen, filas, columnas);
    this->control_animacion = new Control_Animacion(frames);
    this->retardo_ = retardo_;
}

//Animacion fija
void Animacion::animar(SDL_Surface *pantalla, int x, int y, int flip) 
{
    Uint32 t0;
    Uint32 t1;
    
    for( ; ; ) {

	imagen->dibujar(pantalla, control_animacion->cuadro(),x, y, flip);
	control_animacion->avanzar();
	SDL_Flip(pantalla);

	SDL_FillRect(pantalla, NULL, SDL_MapRGB(pantalla->format, 0, 0, 0));

	t0 = SDL_GetTicks();
	t1 = SDL_GetTicks();

	while((t1 - t0) < retardo_) {

	    t1 = SDL_GetTicks();

	}
	
    }

}

//Recorre los distintos cuadros de la rejilla para crear la animacion
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

//Devuelve el retardo de la animacion
Uint32 Animacion::retardo() 
{
    return retardo_;
}
