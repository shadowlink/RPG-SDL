#ifndef __MAP__
#define __MAP__
#include <iostream>
#include "images.h"
#include <irrXML.h>

using namespace std;

class Tile{
	public:
		Tile();
		Tile(bool, string);
		~Tile();
		bool getSolido();
		void setSolido(bool);
		string getTileId();
		void setTileId(string);
		void setX(int);
		void setY(int);
		int getX();
		int getY();
	private:
		bool solido;
		string TileId;
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
		int id;
		Tile suelo[15][20];
		Tile solido[15][20];
		
};

#endif
