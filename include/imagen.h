// Listado: Imagen.h
//
// Clase para gestionar el trabajo con imágenes y rejillas

#ifndef _IMAGEN_
#define _IMAGEN_

#include <SDL/SDL.h>


class Imagen {

 public:

    // Constructor

    Imagen(char *ruta, int filas = 1, int columnas = 1,\
	   Uint32 r = 255, Uint32 g = 0, Uint32 b = 255);
    
    void dibujar(SDL_Surface *superficie, int i, int x, int y, int flip = 1);

    // Consultoras

    int anchura(void);
    int altura(void);
    int cuadros(void);
    
    // Destructor 

    ~Imagen();

 private:

    SDL_Surface *imagen;
    SDL_Surface *imagen_invertida;

    // Propiedades de la rejilla de la imagen   
    int columnas;
    int filas;

    // Ancho y alto por frame o recuerdo de la animación
    int w, h; 

    // Invierte la imagen en horizontal
    SDL_Surface * invertir_imagen(SDL_Surface *imagen);

    // Color clave
    Uint32 colorkey;
};

#endif
