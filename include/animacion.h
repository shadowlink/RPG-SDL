// Listado: Animacion.h
//
// Clase Animación

#ifndef _ANIMACION_
#define _ANIMACION_

#include <SDL/SDL.h>

// Declaración adelantada

class Imagen;
class Control_Animacion;

// Clase

class Animacion {

 public:

    // Constructor
    
    Animacion(char *ruta_imagen, int filas, int columnas, char *frames, int retardo);

    // Animación fija e infinita en pantalla

    void animar(SDL_Surface *pantalla, int x, int y, int flip = 1);

    // Dibuja la animación paso por paso

    void paso_a_paso(SDL_Surface *pantalla, int x, int y, int flip = 1);
    Uint32 retardo();

 private:
    Imagen *imagen;
    Control_Animacion *control_animacion;
    Uint32 retardo_;
};

#endif
