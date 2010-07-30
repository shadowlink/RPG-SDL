#include <iostream>
#include "map.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_ttf.h>

using namespace std;

Tile::Tile()
{
	TileId=' ';
	solido=false;
}

Tile::Tile(bool sol, char tilid)
{
	TileId=tilid;
	solido=sol;
}

Tile::~Tile()
{
	TileId=' ';
	solido=false;	
}

bool Tile::getSolido()
{
	return solido;
}

char Tile::getTileId()
{
	return TileId;
}

void Tile::setX(int x)
{
	posX=x;
}

void Tile::setY(int y)
{
	posY=y;
}

int Tile::getX()
{
	return posX;
}

int Tile::getY()
{
	return posY;
}



//MAP

Map::Map(int num)
{
	id=num;
}

Map::~Map()
{
	id=0;
}

void Map::CargarMapa()
{	
	int i=0;
	string linea="";
	string dir="maps/";
	char buffer [33];
	sprintf(buffer,"%d",id);
	string archivo=buffer;
	dir=dir+archivo;
	char direccion[dir.length()];
	strcpy(direccion, dir.c_str());
	fstream mapa;
	mapa.open(direccion, ios::in);
	if (mapa.is_open())
	{
		getline(mapa, linea);
		while(!mapa.eof())
		{		
			ProcesarLinea(linea, i);
			getline(mapa, linea);
			i++;
		}
	}
	else
	{
		cout<<"No se puede abrir el mapa: "<<id<<endl;
	}
	mapa.close();
}


void Map::DibujarMapa(SDL_Surface* screen)
{
	SDL_Rect rect;
	for(int i=0; i<15; i++)
	{
		for(int j=0; j<20; j++)
		{
			SDL_Surface* tile;
			if(mimapa[i][j].getSolido()==false)
			{
				tile=IMG_Load("resources/graphics/tiles/0.bmp");
			}
			else
			{
				tile=IMG_Load("resources/graphics/tiles/1.bmp");
			}
			rect.x=32*j;
			rect.y=32*i;
			rect.w=tile->w;
			rect.h=tile->h;
		
			SDL_BlitSurface(tile, NULL, screen, &rect);
			SDL_FreeSurface(tile);
		}
	}
}

void Map::ProcesarLinea(string linea, int i)
{
	int j=0;
	for(j=0; j<20; j++)
	{
		if(linea[j]=='0')//No es solido
		{
			Tile tile(false, '0');
			tile.setX(32*j);
			tile.setY(32*i);
			mimapa[i][j]=tile;
		}
		else if(linea[j]=='1') //Solido
		{
			Tile tile(true, '1');
			tile.setX(32*j);
			tile.setY(32*i);
			mimapa[i][j]=tile;
		}
	}

}

bool Map::getSolido(int x, int y)
{
	#ifdef DEBUG
	cout<<"Compruebo: ["<<x<<"]["<<y<<"]"<<endl;
	if(mimapa[x][y].getSolido()==true)
	{
		cout<<x<<", "<<y<<" es solido"<<endl;
	}
	#endif
	return mimapa[x][y].getSolido();
}

Tile Map::getTile(int y, int x)
{
	return mimapa[y][x];
}
