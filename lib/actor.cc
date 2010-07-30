#include <iostream>
#include "actor.h"
#include "animacion.h"
#include <cstdlib>
#include <cmath>

Actor::Actor(string imagen)
{
	this->imagen=imagen;
	posX=32;
	posY=32;
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

Actor::~Actor()
{
	posX=0;
	posY=0;
}

int Actor::getX()
{
	return posX;
}

int Actor::getY()
{
	return posY;
}

int Actor::Arriba(Map* mapa)
{
	if(!ColisionMapaArriba(mapa))
	{
		posY-=8;
	}
}

int Actor::Abajo(Map* mapa)
{
	if(!ColisionMapaAbajo(mapa))
	{
		posY+=8;
	}
}

int Actor::Derecha(Map* mapa)
{
	if(!ColisionMapaDerecha(mapa))
	{
			posX+=8;			
	}
}

int Actor::Izquierda(Map* mapa)
{
	if(!ColisionMapaIzquierda(mapa))
	{
		posX-=8;
	}
}

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

void Actor::cambio_estado(estados_personaje e)
{
	estado=e;
}

estados_personaje Actor::estado_actual(void) 
{
    return estado;
}

bool Actor::ColisionMapaDerecha(Map* mapa)
{
	/*bool solido=false;
	int compruebaX=(posX/32)+1;
	
	#ifdef DEBUG
	cout<<"y="<<posY<<endl;
	cout<<"x="<<posX<<endl;
	cout<<"Pos: ["<<posY/32<<"]["<<posX/32<<"]"<<endl;
	cout<<posX<<"/32="<<posX/32<<endl;
	#endif
	
	if(mapa->getSolido(posY/32, compruebaX))
	{
		solido=true;
	}
	return solido;*/
	bool solido=false;
	int compruebaX;
	
	#ifdef DEBUG
	cout<<"y="<<posY<<endl;
	cout<<"x="<<posX<<endl;
	if(posX%32!=0) //Si no es entero
	{
		cout<<"No estoy en entero"<<endl;
		cout<<"Pos: ["<<posY/32<<"]["<<floor((posX/32))<<"]"<<endl;
		cout<<posX<<"/32="<<posX/32<<endl;
		compruebaX=floor((posX/32)+1);
	}
	else // si es entero
	{
		cout<<"Estoy en entero"<<endl;
		cout<<"Pos: ["<<posY/32<<"]["<<posX/32<<"]"<<endl;
		cout<<posX<<"/32="<<posX/32<<endl;	
		compruebaX=posX/32+1;	
	}	
	#endif
	if(posX+32<608)
	{
		if(mapa->getSolido(posY/32, compruebaX))
		{
			solido=true;
		}
		else if (posY%32!=0)
		{
			if (mapa->getSolido((posY/32)+1, compruebaX))
				solido=true;
			else if(mapa->getSolido((posY/32)-1, compruebaX))
			{
				//solido=true;
			}
		}
	}
	else
		solido=true;
	
	return solido;	

}

bool Actor::ColisionMapaIzquierda(Map* mapa)
{
	/*bool solido=false;
	int compruebaX=(posX/32)-1;
	
	#ifdef DEBUG
	cout<<"y="<<posY<<endl;
	cout<<"x="<<posX<<endl;
	cout<<"Pos: ["<<posY/32<<"]["<<posX/32<<"]"<<endl;
	cout<<posY<<"/32="<<posY/32<<endl;
	#endif
	
	if(mapa->getSolido(posY/32, compruebaX))
	{
		solido=true;
	}
	return solido;*/
	bool solido=false;
	int compruebaX;
	
	#ifdef DEBUG
	cout<<"y="<<posY<<endl;
	cout<<"x="<<posX<<endl;
	if(posX%32!=0) //Si no es entero
	{
		cout<<"No estoy en entero"<<endl;
		cout<<"Pos: ["<<posY/32<<"]["<<floor((posX/32))<<"]"<<endl;
		cout<<posX<<"/32="<<posX/32<<endl;
		compruebaX=floor((posX/32));
	}
	else // si es entero
	{
		cout<<"Estoy en entero"<<endl;
		cout<<"Pos: ["<<posY/32<<"]["<<posX/32<<"]"<<endl;
		cout<<posX<<"/32="<<posX/32<<endl;	
		compruebaX=posX/32-1;	
	}	
	#endif
	if(posX>32)
	{
		if(mapa->getSolido(posY/32, compruebaX))
		{
			solido=true;
		}
		else if (posY%32!=0)
		{
			if (mapa->getSolido((posY/32)+1, compruebaX))
			{
				solido=true;
			}
			else if(mapa->getSolido((posY/32)-1, compruebaX))
			{
				//solido=true;
			}
		}
	}
	else
		solido=true;
	
	return solido;
}

bool Actor::ColisionMapaArriba(Map* mapa)
{
/*	bool solido=false;
	int compruebaY=(posY/32)-1;
	
	#ifdef DEBUG
	cout<<"y="<<posY<<endl;
	cout<<"x="<<posX<<endl;
	cout<<"Pos: ["<<posY/32<<"]["<<posX/32<<"]"<<endl;
	cout<<posY<<"/32="<<posY/32<<endl;
	#endif
	
	if(mapa->getSolido(compruebaY, posX/32))
	{
		solido=true;
	}
	return solido;*/
	
	bool solido=false;
	int compruebaY;
	
	#ifdef DEBUG
	cout<<"y="<<posY<<endl;
	cout<<"x="<<posX<<endl;
	if(posY%32!=0) //Si no es entero
	{
		cout<<"No estoy en entero"<<endl;
		cout<<"Pos: ["<<floor((posY/32))<<"]["<<posX/32<<"]"<<endl;
		cout<<posX<<"/32="<<posX/32<<endl;
		compruebaY=floor((posY/32));
	}
	else // si es entero
	{
		cout<<"Estoy en entero"<<endl;
		cout<<"Pos: ["<<posY/32<<"]["<<posX/32<<"]"<<endl;
		cout<<posX<<"/32="<<posX/32<<endl;	
		compruebaY=posY/32-1;	
	}	
	#endif
	
	if(posY>32)
	{
		if(mapa->getSolido(compruebaY, posX/32))
		{
			solido=true;
		}
		else if (posX%32!=0)
		{
			if (mapa->getSolido(compruebaY, (posX/32)+1))
				solido=true;
			else if(mapa->getSolido(compruebaY, (posX/32)-1))
			{
				//solido=true;
			}
		}
	}
	else
		solido=true;
	return solido;
}

bool Actor::ColisionMapaAbajo(Map* mapa)
{
	/*bool solido=false;
	int compruebaY=(posY/32)+1;
	
	#ifdef DEBUG
	cout<<"y="<<posY<<endl;
	cout<<"x="<<posX<<endl;
	cout<<"Pos: ["<<posY/32<<"]["<<posX/32<<"]"<<endl;
	cout<<posY<<"/32="<<posY/32<<endl;
	#endif
	
	if(mapa->getSolido(compruebaY, posX/32))
	{
		solido=true;
	}
	return solido;*/
	bool solido=false;
	int compruebaY;
	
	#ifdef DEBUG
	cout<<"y="<<posY<<endl;
	cout<<"x="<<posX<<endl;
	if(posY%32!=0) //Si no es entero
	{
		cout<<"No estoy en entero"<<endl;
		cout<<"Pos: ["<<floor((posY/32))<<"]["<<posX/32<<"]"<<endl;
		cout<<posX<<"/32="<<posX/32<<endl;
		compruebaY=floor((posY/32));
	}
	else // si es entero
	{
		cout<<"Estoy en entero"<<endl;
		cout<<"Pos: ["<<posY/32<<"]["<<posX/32<<"]"<<endl;
		cout<<posX<<"/32="<<posX/32<<endl;	
		compruebaY=(posY/32)+1;	
	}	
	#endif
	if(posY+32<448)
	{
		if(mapa->getSolido(compruebaY, posX/32))
		{
			solido=true;
		}
		else if (posX%32!=0)
		{
			if (mapa->getSolido(compruebaY, (posX/32)+1))
				solido=true;
			else if(mapa->getSolido(compruebaY, (posX/32)-1))
			{
				//solido=true;
			}
		}
	}
	else
		solido=true;
	
	return solido;
}

void Actor::Actualizar(Map* mapa)
{
	teclado.actualizar();
	
	//ESTADOS
	switch(estado_actual()) 
	{	
	 case PARADO:	 
		 if(teclado.pulso(Teclado::TECLA_DERECHA))
			// Si "->" cambio de estado a parado derecha
			cambio_estado(PARADO_DERECHA);
		 else if(teclado.pulso(Teclado::TECLA_IZQUIERDA))
			// Si "<-" cambio de estado a parado izquierda 
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
