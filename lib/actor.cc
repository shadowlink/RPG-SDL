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

//Mueve el personaje hacia arriba
void Actor::Arriba(const Map* mapa)
{
	if(!ColisionMapaArriba(mapa))
	{
		posY-=8;
	}
}

//Mueve el personaje hacia abajo
void Actor::Abajo(const Map* mapa)
{
	if(!ColisionMapaAbajo(mapa))
	{
		posY+=8;
	}
}

//Mueve el personaje hacia la derecha
void Actor::Derecha(const Map* mapa)
{
	if(!ColisionMapaDerecha(mapa))
	{
			posX+=8;			
	}
}

//Mueve el personaje hacia la izquierda
void Actor::Izquierda(const Map* mapa)
{
	if(!ColisionMapaIzquierda(mapa))
	{
		posX-=8;
	}
}

//Dibuja la animacion del personaje segun su estado actual
void Actor::Dibujar(SDL_Surface* screen)
{
	switch(estado) {
		case PARADO:
			galeria_animaciones[PARADO_DERECHA]->paso_a_paso(screen, posX, posY);
			estado = PARADO_DERECHA;
		break;
		case PARADO_DERECHA:
			galeria_animaciones[PARADO_DERECHA]->paso_a_paso(screen, posX, posY);
		break;

		case PARADO_IZQUIERDA:
			galeria_animaciones[PARADO_IZQUIERDA]->paso_a_paso(screen, posX, posY);
		break;

		case PARADO_ARRIBA:
			galeria_animaciones[PARADO_ARRIBA]->paso_a_paso(screen, posX, posY);
		break;

		case PARADO_ABAJO:
			galeria_animaciones[PARADO_ABAJO]->paso_a_paso(screen, posX, posY);
		break;
		
		case ANDAR_DERECHA:
			galeria_animaciones[ANDAR_DERECHA]->paso_a_paso(screen, posX, posY);
		break;
		
		case ANDAR_IZQUIERDA:
			galeria_animaciones[ANDAR_IZQUIERDA]->paso_a_paso(screen, posX, posY);
		break;
		
		case ANDAR_ARRIBA:
			galeria_animaciones[ANDAR_ARRIBA]->paso_a_paso(screen, posX, posY);
		break;
		
		case ANDAR_ABAJO:
			galeria_animaciones[ANDAR_ABAJO]->paso_a_paso(screen, posX, posY);
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
	if(posX%TWIDTH!=0) //No lo estamos
	{
		compruebaX=floor((posX/TWIDTH)+1);
	}
	else //Lo estamos
	{
		compruebaX=posX/TWIDTH+1;	
	}	

	//Si estamos dentro de los limites del mapa
	if(posX+TWIDTH<WIDTH-TWIDTH)
	{
		//Comprobamos si la baldosa que hemos calculado es solida
		if(mapa->getSolido(posY/THEIGHT, compruebaX))
		{
			solido=true;
		}
		else if (posY%THEIGHT!=0)
		{
			if (mapa->getSolido((posY/THEIGHT)+1, compruebaX))
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
	
	if(posX%TWIDTH!=0) //Si no es entero
	{
		compruebaX=floor((posX/TWIDTH));
	}
	else // si es entero
	{
		compruebaX=posX/TWIDTH-1;	
	}	

	if(posX>TWIDTH)
	{
		if(mapa->getSolido(posY/THEIGHT, compruebaX))
		{
			solido=true;
		}
		else if (posY%THEIGHT!=0)
		{
			if (mapa->getSolido((posY/THEIGHT)+1, compruebaX))
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
	
	if(posY%THEIGHT!=0) //Si no es entero
	{
		compruebaY=floor((posY/THEIGHT));
	}
	else // si es entero
	{
		compruebaY=posY/THEIGHT-1;	
	}	
	
	if(posY>THEIGHT)
	{
		if(mapa->getSolido(compruebaY, posX/TWIDTH))
		{
			solido=true;
		}
		else if (posX%TWIDTH!=0)
		{
			if (mapa->getSolido(compruebaY, (posX/TWIDTH)+1))
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
	
	if(posY%THEIGHT!=0) //Si no es entero
	{
		compruebaY=floor((posY/THEIGHT));
	}
	else // si es entero
	{
		compruebaY=(posY/THEIGHT)+1;	
	}	

	if(posY+THEIGHT<HEIGHT-THEIGHT)
	{
		if(mapa->getSolido(compruebaY, posX/TWIDTH))
		{
			solido=true;
		}
		else if (posX%TWIDTH!=0)
		{
			if (mapa->getSolido(compruebaY, (posX/TWIDTH)+1))
				solido=true;
		}
	}
	else
		solido=true;
	
	return solido;
}

//Actualiza el estado del personaje a partir de una maquina de estados
void Actor::Actualizar(const Map* mapa)
{
	teclado.actualizar();
	
	//Construimos una maquina de estados y sus transiciones
	switch(estado_actual()) 
	{	
	 case PARADO:	 
		 if(teclado.pulso(Teclado::TECLA_DERECHA))
			cambio_estado(PARADO_DERECHA);
		 else if(teclado.pulso(Teclado::TECLA_IZQUIERDA))
			cambio_estado(PARADO_IZQUIERDA);
		 else if(teclado.pulso(Teclado::TECLA_SUBIR))
			cambio_estado(PARADO_ARRIBA);
		 else if(teclado.pulso(Teclado::TECLA_BAJAR))
			cambio_estado(PARADO_ABAJO);
		 break;
	 case PARADO_DERECHA:
		 if(teclado.pulso(Teclado::TECLA_SUBIR))
			cambio_estado(PARADO_ARRIBA);
		 else if(teclado.pulso(Teclado::TECLA_DERECHA)) 
		 {
			Derecha(mapa);
			cambio_estado(ANDAR_DERECHA);
		 } 
		 else if(teclado.pulso(Teclado::TECLA_IZQUIERDA))
			cambio_estado(PARADO_IZQUIERDA);
		 else if(teclado.pulso(Teclado::TECLA_BAJAR))
			cambio_estado(PARADO_ABAJO);  
		 break;
	 case PARADO_IZQUIERDA:
		 if(teclado.pulso(Teclado::TECLA_SUBIR))
			cambio_estado(PARADO_ARRIBA);
		 else if(teclado.pulso(Teclado::TECLA_IZQUIERDA)) 
		 {
			Izquierda(mapa);
			cambio_estado(ANDAR_IZQUIERDA);
		 } 
		 else if(teclado.pulso(Teclado::TECLA_BAJAR))
			cambio_estado(PARADO_ABAJO);
		 else if(teclado.pulso(Teclado::TECLA_DERECHA))
			cambio_estado(PARADO_DERECHA);
		 break;		
	 case PARADO_ARRIBA:
		 if(teclado.pulso(Teclado::TECLA_SUBIR))
		 {
			Arriba(mapa);
			cambio_estado(ANDAR_ARRIBA);
		 }
		 else if(teclado.pulso(Teclado::TECLA_IZQUIERDA)) 
			cambio_estado(PARADO_IZQUIERDA);
		 else if(teclado.pulso(Teclado::TECLA_BAJAR))
			cambio_estado(PARADO_ABAJO);
		 else if(teclado.pulso(Teclado::TECLA_DERECHA))
			cambio_estado(PARADO_DERECHA);
		 break;	
	 case PARADO_ABAJO:
		 if(teclado.pulso(Teclado::TECLA_SUBIR))
			cambio_estado(PARADO_ARRIBA);
		 else if(teclado.pulso(Teclado::TECLA_IZQUIERDA)) 
			cambio_estado(PARADO_IZQUIERDA);
		 else if(teclado.pulso(Teclado::TECLA_BAJAR))
		 {
			Abajo(mapa);
			cambio_estado(ANDAR_ABAJO);
		 }
		 else if(teclado.pulso(Teclado::TECLA_DERECHA))
			cambio_estado(PARADO_DERECHA);
		 break;	
	 case ANDAR_DERECHA:
		 if(teclado.pulso(Teclado::TECLA_SUBIR))
			cambio_estado(PARADO_ARRIBA);
		 else if(teclado.pulso(Teclado::TECLA_IZQUIERDA)) 
			cambio_estado(PARADO_IZQUIERDA);
		 else if(teclado.pulso(Teclado::TECLA_BAJAR))
			cambio_estado(ANDAR_ABAJO);
		 else if(teclado.pulso(Teclado::TECLA_DERECHA))
			Derecha(mapa);
		 break;	
	 break;
	 case ANDAR_IZQUIERDA:
		 if(teclado.pulso(Teclado::TECLA_SUBIR))
			cambio_estado(PARADO_ARRIBA);
		 else if(teclado.pulso(Teclado::TECLA_IZQUIERDA))
			Izquierda(mapa);
		 else if(teclado.pulso(Teclado::TECLA_BAJAR))
			cambio_estado(PARADO_ABAJO);
		 else if(teclado.pulso(Teclado::TECLA_DERECHA))
			cambio_estado(PARADO_DERECHA);
		 break;	
	 break;
	 case ANDAR_ARRIBA:
		 if(teclado.pulso(Teclado::TECLA_SUBIR))
			Arriba(mapa);
		 else if(teclado.pulso(Teclado::TECLA_IZQUIERDA)) 
			cambio_estado(PARADO_IZQUIERDA);
		 else if(teclado.pulso(Teclado::TECLA_BAJAR))
			cambio_estado(PARADO_ABAJO);
		 else if(teclado.pulso(Teclado::TECLA_DERECHA))
			cambio_estado(PARADO_DERECHA);
		 break;	
	 break;
	 case ANDAR_ABAJO:
		 if(teclado.pulso(Teclado::TECLA_SUBIR))
			cambio_estado(PARADO_ARRIBA);
		 else if(teclado.pulso(Teclado::TECLA_IZQUIERDA)) 
			cambio_estado(PARADO_IZQUIERDA);
		 else if(teclado.pulso(Teclado::TECLA_BAJAR))
			Abajo(mapa);
		 else if(teclado.pulso(Teclado::TECLA_DERECHA))
			cambio_estado(PARADO_DERECHA);
			 break;	
	 break;
	 default:
		 cerr << "No se conoce este estado " <<estado_actual()<< endl;
	 }	
}
