#ifndef __HEROE__
#define __HEROE__
#include <iostream>
#include "images.h"
#include "map.h"
#include "animacion.h"
#include "Teclado.h"
#include "consts.h"
#include "actor.h"

class Heroe : public Actor{
	public:
		Heroe(const string imagen);
		~Heroe();
		void Arriba(const Map*);
		void Abajo(const Map*);
		void Derecha(const Map*);
		void Izquierda(const Map*);
		void Actualizar(const Map*);
	private:
		Teclado teclado;
};
		

#endif
