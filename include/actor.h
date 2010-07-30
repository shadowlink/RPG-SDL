#ifndef __ACTOR__
#define __ACTOR__
#include <iostream>
#include "images.h"
#include "map.h"
#include "animacion.h"
#include "Teclado.h"

using namespace std;
enum estados_personaje{
	PARADO,
	PARADO_DERECHA,
	PARADO_ARRIBA,
	ANDAR_DERECHA,
	PARADO_ABAJO,
	PARADO_IZQUIERDA,
	ANDAR_IZQUIERDA,
	ANDAR_ARRIBA,
	ANDAR_ABAJO,   
	MAX_ESTADOS
};
class Actor{
	public:
		
		Actor(string);
		~Actor();
		int Arriba(Map*);
		int Abajo(Map*);
		int Derecha(Map*);
		int Izquierda(Map*);
		void Dibujar(SDL_Surface*);
		void cambio_estado(estados_personaje);
		void Actualizar(Map*);
		estados_personaje estado_actual(void);
		int getX();
		int getY();
	private:
		bool ColisionMapaDerecha(Map*);
		bool ColisionMapaIzquierda(Map*);
		bool ColisionMapaArriba(Map*);
		bool ColisionMapaAbajo(Map*);
		Teclado teclado;
		string imagen;
		int posX;
		int posY;
		estados_personaje estado;
		Animacion *galeria_animaciones[MAX_ESTADOS];
};
		

#endif
