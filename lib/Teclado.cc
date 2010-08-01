#include <iostream>
#include "Teclado.h"

using namespace std;

//Constructor por defecto
Teclado::Teclado() 
{
    // Configuramos la teclas que usaremos en la aplicación
    teclas_configuradas[TECLA_SUBIR] = SDLK_UP;
    teclas_configuradas[TECLA_BAJAR] = SDLK_DOWN;
    teclas_configuradas[TECLA_ACEPTAR] = SDLK_RETURN;
    teclas_configuradas[TECLA_GOLPEAR] = SDLK_SPACE;
    teclas_configuradas[TECLA_IZQUIERDA] = SDLK_LEFT;
    teclas_configuradas[TECLA_DERECHA] = SDLK_RIGHT;
    teclas_configuradas[TECLA_SALTAR] = SDLK_UP;
}

//Actualiza el estado del teclado
void Teclado::actualizar(void) {
    teclas = SDL_GetKeyState(NULL);
}

//Comprueba si hay teclas pulsadas
bool Teclado::pulso(teclas_utilizadas tecla) {
    if(teclas[teclas_configuradas[tecla]])
		return true;
    else
		return false;
}
