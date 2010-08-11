#include <iostream>
#include "actor.h"
#include "animacion.h"
#include <cstdlib>
#include <cmath>

//Constructor sobrecargado
Actor::Actor(const string imagen)
{
	this->imagen=imagen;
	posX=32;
	posY=64;
    estado = PARADO;
    galeria_animaciones[PARADO_DERECHA] =
	new Animacion("resources/graphics/charasets/link.png", 4, 10, "30", 0);
    galeria_animaciones[ANDAR_DERECHA] =
	new Animacion("resources/graphics/charasets/link.png", 4, 10, "30,31,32,33,34,35,36,37,38,39", 0);	
    galeria_animaciones[ANDAR_ARRIBA] =
	new Animacion("resources/graphics/charasets/link.png", 4, 10, "20,21,22,23,24,25,26,27,28,29", 0);
    galeria_animaciones[ANDAR_ABAJO] = 
	new Animacion("resources/graphics/charasets/link.png", 4, 10, "0,1,2,3,4,5,6,7,8,9", 0);
    galeria_animaciones[PARADO_ARRIBA] =
	new Animacion("resources/graphics/charasets/link.png", 4, 10, "21", 0);
    galeria_animaciones[PARADO_IZQUIERDA] =
	new Animacion("resources/graphics/charasets/link.png", 4, 10, "11", 0);
    galeria_animaciones[PARADO_ABAJO] =
	new Animacion("resources/graphics/charasets/link.png", 4, 10, "1", 0);
    galeria_animaciones[ANDAR_IZQUIERDA] =
	new Animacion("resources/graphics/charasets/link.png", 4, 10, "10,11,12,13,14,15,16,17,18,19", 0);
}

//Destructor
Actor::~Actor()
{
	posX=0;
	posY=0;
}

//Devuelve la coordenada X
Uint32 Actor::getX()const
{
	return posX;
}

//Devuelve la coordenada Y
Uint32 Actor::getY()const
{
	return posY;
}

void Actor::setX(const int x)
{
	posX=x;
}

void Actor::setY(const int y)
{
	posY=y;
}

//Dibuja la animacion del personaje segun su estado actual
void Actor::Dibujar(SDL_Surface* screen, Sint32 scrollx, Sint32 scrolly)
{
	switch(estado) {
		case PARADO:
			galeria_animaciones[PARADO_DERECHA]->paso_a_paso(screen, posX-scrollx, posY-scrolly);
			estado = PARADO_DERECHA;
		break;
		case PARADO_DERECHA:
			galeria_animaciones[PARADO_DERECHA]->paso_a_paso(screen, posX-scrollx, posY-scrolly);
		break;

		case PARADO_IZQUIERDA:
			galeria_animaciones[PARADO_IZQUIERDA]->paso_a_paso(screen, posX-scrollx, posY-scrolly);
		break;

		case PARADO_ARRIBA:
			galeria_animaciones[PARADO_ARRIBA]->paso_a_paso(screen, posX-scrollx, posY-scrolly);
		break;

		case PARADO_ABAJO:
			galeria_animaciones[PARADO_ABAJO]->paso_a_paso(screen, posX-scrollx, posY-scrolly);
		break;
		
		case ANDAR_DERECHA:
			galeria_animaciones[ANDAR_DERECHA]->paso_a_paso(screen, posX-scrollx, posY-scrolly);
		break;
		
		case ANDAR_IZQUIERDA:
			galeria_animaciones[ANDAR_IZQUIERDA]->paso_a_paso(screen, posX-scrollx, posY-scrolly);
		break;
		
		case ANDAR_ARRIBA:
			galeria_animaciones[ANDAR_ARRIBA]->paso_a_paso(screen, posX-scrollx, posY-scrolly);
		break;
		
		case ANDAR_ABAJO:
			galeria_animaciones[ANDAR_ABAJO]->paso_a_paso(screen, posX-scrollx, posY-scrolly);
		break;
		 
		default:
		cerr << "Personaje::dibujar()  " << endl;
    }
}

//Cambia el estado del personaje
void Actor::cambio_estado(estados_personaje e)
{
	estado=e;
}

//Devuelve el estado actual del personaje
estados_personaje Actor::estado_actual() const
{
    return estado;
}

//Comprueba si colisiona con la baldosa de la derecha
bool Actor::ColisionMapaDerecha(const Map* mapa) const
{
	bool solido=false;
	Uint32 compruebaX;

	//Comprobamos si estamos en el centro de una baldosa
	//Calculamos la posicion de la baldosa a comprobar en consecuencia
	if(posX%T_ANCHO!=0) //No lo estamos
	{
		compruebaX=floor((posX/T_ANCHO)+1);
	}
	else //Lo estamos
	{
		compruebaX=posX/T_ANCHO+1;	
	}	

	//Si estamos dentro de los limites del mapa
	if(posX+T_ANCHO<mapa->getAncho()-T_ANCHO)
	{
		//Comprobamos si la baldosa que hemos calculado es solida
		if(mapa->getSolido(posY/T_ALTO, compruebaX))
		{
			solido=true;
		}
		else if (posY%T_ALTO!=0)
		{
			if (mapa->getSolido((posY/T_ALTO)+1, compruebaX))
				solido=true;
		}
	}
	else
		solido=true;
	
	return solido;	

}

//Comprueba si colisiona con la baldosa de la izquierda
bool Actor::ColisionMapaIzquierda(const Map* mapa) const 
{
	bool solido=false;
	Uint32 compruebaX;
	
	if(posX%T_ANCHO!=0) //Si no es entero
	{
		compruebaX=floor((posX/T_ANCHO));
	}
	else // si es entero
	{
		compruebaX=posX/T_ANCHO-1;	
	}	

	if(posX>T_ANCHO)
	{
		if(mapa->getSolido(posY/T_ALTO, compruebaX))
		{
			solido=true;
		}
		else if (posY%T_ALTO!=0)
		{
			if (mapa->getSolido((posY/T_ALTO)+1, compruebaX))
				solido=true;
		}
	}
	else
		solido=true;
	
	return solido;
}

//Comprueba si colisiona con la baldosa de arriba
bool Actor::ColisionMapaArriba(const Map* mapa) const
{
	bool solido=false;
	Uint32 compruebaY;
	
	if(posY%T_ALTO!=0) //Si no es entero
	{
		compruebaY=floor((posY/T_ALTO));
	}
	else // si es entero
	{
		compruebaY=posY/T_ALTO-1;	
	}	
	
	if(posY>T_ALTO)
	{
		if(mapa->getSolido(compruebaY, posX/T_ANCHO))
		{
			solido=true;
		}
		else if (posX%T_ANCHO!=0)
		{
			if (mapa->getSolido(compruebaY, (posX/T_ANCHO)+1))
				solido=true;
		}
	}
	else
		solido=true;
	return solido;
}

//Comprueba si colisiona con la baldosa de abajo
bool Actor::ColisionMapaAbajo(const Map* mapa) const 
{
	bool solido=false;
	Uint32 compruebaY;
	
	if(posY%T_ALTO!=0) //Si no es entero
	{
		compruebaY=floor((posY/T_ALTO));
	}
	else // si es entero
	{
		compruebaY=(posY/T_ALTO)+1;	
	}	

	if(posY+T_ALTO<mapa->getAlto()-T_ALTO)
	{
		if(mapa->getSolido(compruebaY, posX/T_ANCHO))
		{
			solido=true;
		}
		else if (posX%T_ANCHO!=0)
		{
			if (mapa->getSolido(compruebaY, (posX/T_ANCHO)+1))
				solido=true;
		}
	}
	else
		solido=true;
	
	return solido;
}


