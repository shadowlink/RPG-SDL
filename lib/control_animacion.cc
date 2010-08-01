#include <iostream>
#include "control_animacion.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//Constructor sobrecargado
Control_Animacion::Control_Animacion(char *frames) 
{
    int i = 0;
    char frames_tmp[1024];
    char *proximo;    
    
    strcpy(frames_tmp, frames);

    // Trabajamos con una copia de los cuadros indicados
    for(proximo = strtok(frames_tmp, ","); proximo; i++)
    {
		// Desmembramos la cadena separada por comas
		this->cuadros.push_back(atoi(proximo));
		proximo = strtok(NULL, ",\0");
    }
    
    // Inicializamos las variables
    this->paso = 0;
}

//Destructor
Control_Animacion::~Control_Animacion() 
{
	paso=0;
}

//Retorna la id de la imagen actual
int Control_Animacion::cuadro(void) 
{
    return cuadros[paso];
}

//Avanza al siguiente cuadro de animacion
int Control_Animacion::avanzar(void) 
{	
    if(paso+1 == cuadros.size()) 
    {
		paso = 0;
    }
    else
    {
		paso++;
	}
    return 0;
}

//Reinicia la animacion
void Control_Animacion::reiniciar(void) 
{
    paso = 0;
}

//Comprueba si es el primer paso
bool Control_Animacion::es_primer_cuadro(void) 
{
    if(paso == 0)
		return true;
    return false;
}

//Devuelve el numero de cuadros que compone la animacion
int Control_Animacion::numero_cuadros()
{
	return cuadros.size();
}
