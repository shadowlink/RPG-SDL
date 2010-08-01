#ifndef __MAP__
#define __MAP__
#include <iostream>
#include "images.h"
#include <irrXML.h>
#include "consts.h"
using namespace std;

class Tile{
	public:
		Tile();
		Tile(const bool, const string);
		~Tile();
		bool getSolido() const;
		void setSolido(const bool);
		string getTileId() const;
		void setTileId(const string);
		void setX(const Uint32);
		void setY(const Uint32);
		Uint32 getX()const;
		Uint32 getY()const;
	private:
		bool solido;
		string TileId;
		Uint32 posX;
		Uint32 posY;
};

class Map{
	public:
		Map(const Uint32);
		~Map();
		void CargarMapa();
		void DibujarMapa(SDL_Surface*);
		void DibujaTras(SDL_Surface*);
		bool getSolido(const Uint32, const Uint32) const;
	private:
		Uint32 id;
		Tile suelo[15][20]; //Primera capa no solida
		Tile suelo2[15][20]; //Segunda capa no solida
		Tile solido[15][20]; //Capa solida
		Tile frontal[15][20]; //Objetos traspasables por detras
		
};

#endif
