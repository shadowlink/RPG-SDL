#ifndef __ENEMIGO__
#define __ENEMIGO__
#include <iostream>
#include "images.h"
#include "map.h"
#include "animacion.h"
#include "Teclado.h"
#include "consts.h"

class Actor{
	public:
		Actor(const string);
		~Actor();
		void Arriba(const Map*);
		void Abajo(const Map*);
		void Derecha(const Map*);
		void Izquierda(const Map*);
		void Dibujar(SDL_Surface*);
		void cambio_estado(estados_personaje);
		void Actualizar(const Map*);
		estados_personaje estado_actual()const;
		Uint32 getX() const;
		Uint32 getY() const;
	private:
		bool ColisionMapaDerecha(const Map*) const;
		bool ColisionMapaIzquierda(const Map*) const;
		bool ColisionMapaArriba(const Map*) const;
		bool ColisionMapaAbajo(const Map*) const;
		Teclado teclado;
		string imagen;
		Uint32 posX;
		Uint32 posY;
		estados_personaje estado;
		Animacion *galeria_animaciones[MAX_ESTADOS];
};
		

#endif
