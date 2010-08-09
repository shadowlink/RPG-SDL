#ifndef __CAMARA__
#define __CAMARA__
#include <iostream>
#include "images.h"
#include "consts.h"
#include "map.h"
#include "heroe.h"

using namespace std;

class Camara
{
	public:
		Camara();
		~Camara();
		void Actualizar(SDL_Surface*, Map*, Heroe*);
		void plot(Map*, Uint32, Uint32);
		void mouse_map(Map*, Uint32, Uint32);
};

#endif
