#ifndef __MAP__
#define __MAP__
#include <iostream>
#include "map.h"
#include "images.h"

using namespace std;

class Tile{
	public:
		Tile();
		Tile(bool, char);
		~Tile();
		bool getSolido();
		char getTileId();
		void setX(int);
		void setY(int);
		int getX();
		int getY();
	private:
		bool solido;
		char TileId;
		int posX;
		int posY;
};

class Map{
	public:
		Map(int);
		~Map();
		void CargarMapa();
		void DibujarMapa(SDL_Surface*);
		Tile getTile(int, int);
		bool getSolido(int, int);
	private:
		void ProcesarLinea(string, int);
		int id;
		Tile mimapa[15][20];
};

#endif
