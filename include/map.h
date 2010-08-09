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
		Uint32 getAlto()const;
		Uint32 getAncho()const;
		Tile getSuelo(const Uint32 x, const Uint32 y) const;
		Tile getSuelo2(const Uint32 x, const Uint32 y) const;
		Tile getSueloSolido(const Uint32 x, const Uint32 y) const;
	private:
		Uint32 id;
		Uint32 ancho;
		Uint32 alto;
		Tile suelo[15][30]; //Primera capa no solida
		Tile suelo2[15][30]; //Segunda capa no solida
		Tile solido[15][30]; //Capa solida
		Tile frontal[15][30]; //Objetos traspasables por detras
		
};

#endif
