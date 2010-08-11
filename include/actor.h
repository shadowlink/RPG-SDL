#ifndef __ACTOR__
#define __ACTOR__
#include <iostream>
#include "images.h"
#include "map.h"
#include "animacion.h"
#include "consts.h"

class Actor{
	public:
		Actor(const string);
		~Actor();
		void Dibujar(SDL_Surface*, Sint32, Sint32);
		void cambio_estado(estados_personaje);
		estados_personaje estado_actual()const;
		Uint32 getX() const;
		Uint32 getY() const;
		void setX(const int);
		void setY(const int);
	protected:
		bool ColisionMapaDerecha(const Map*) const;
		bool ColisionMapaIzquierda(const Map*) const;
		bool ColisionMapaArriba(const Map*) const;
		bool ColisionMapaAbajo(const Map*) const;
	private:
		string imagen;
		Uint32 posX;
		Uint32 posY;
		estados_personaje estado;
		Animacion *galeria_animaciones[MAX_ESTADOS];
};
		

#endif
