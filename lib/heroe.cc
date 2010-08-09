#include <iostream>
#include "heroe.h"
#include "animacion.h"
#include <cstdlib>
#include <cmath>

//Constructor sobrecargado
Heroe::Heroe(const string imagen):Actor(imagen)
{
}

//Destructor
Heroe::~Heroe()
{
}


//Mueve el personaje hacia arriba
void Heroe::Arriba(const Map* mapa)
{
	if(!ColisionMapaArriba(mapa))
	{
		setY(getY()-8);
	}
}

//Mueve el personaje hacia abajo
void Heroe::Abajo(const Map* mapa)
{
	if(!ColisionMapaAbajo(mapa))
	{
		setY(getY()+8);
	}
}

//Mueve el personaje hacia la derecha
void Heroe::Derecha(const Map* mapa)
{
	if(!ColisionMapaDerecha(mapa))
	{
			setX(getX()+8);			
	}
}

//Mueve el personaje hacia la izquierda
void Heroe::Izquierda(const Map* mapa)
{
	if(!ColisionMapaIzquierda(mapa))
	{
		setX(getX()-8);
	}
}

//Actualiza el estado del personaje a partir de una maquina de estados
void Heroe::Actualizar(const Map* mapa)
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
			Heroe::Derecha(mapa);
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
