#include <iostream>
#include "map.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include "animacion.h"
#include "imagen.h"


using namespace std;
using namespace irr; // irrXML is located in the namespace irr::io
using namespace io;

Tile::Tile()
{
	TileId="";
	solido=false;
}

Tile::Tile(bool sol, string tilid)
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

string Tile::getTileId()
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

void Tile::setTileId(string id)
{
	TileId=id;
}

void Tile::setSolido(bool solido)
{
	this->solido=solido;
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
	//TiXmlDocument *doc = new TiXmlDocument("agenda.xml");

	int y=0, x=0, i=0, j=0;
	IrrXMLReader* xml = createIrrXMLReader("maps/mapa.tmx");
	std::string capa;
	std::string gid;
	Tile mitile;
	
	while(xml && xml->read())
	{
		switch(xml->getNodeType())
		{
			case EXN_ELEMENT:
			{
				if (!strcmp("layer", xml->getNodeName()))
				{
					capa = xml->getAttributeValue("name");
				}
				else
				{
					if (!strcmp("tile", xml->getNodeName()))
					{
						gid = xml->getAttributeValue("gid");
						if(capa=="Suelo")
						{
							if(x<20) //Final de la linea
							{
								mitile.setTileId(gid);
								mitile.setSolido(false);
								suelo[y][x]=mitile;
								x++;
							}
							else
							{
								x=0;
								y++;
								mitile.setTileId(gid);
								mitile.setSolido(false);
								suelo[y][x]=mitile;
								x++;								
							}
						}
						else if(capa=="Solido")
						{
							if(j<20) //Final de la linea
							{
								mitile.setTileId(gid);
								if(gid!="0")
								{
									cout<<gid<<endl;
									mitile.setSolido(true);
								}
								else
								{
									mitile.setSolido(false);
								}
								solido[i][j]=mitile;
								j++;
							}
							else
							{
								j=0;
								i++;
								mitile.setTileId(gid);
								if(gid!="0")
								{
									mitile.setSolido(true);
								}
								else
								{
									mitile.setSolido(false);
								}
								solido[i][j]=mitile;
								j++;								
							}							
						}
					}
				}
			}
			break;
		}
	}

	// delete the xml parser after usage
	delete xml;   
}


void Map::DibujarMapa(SDL_Surface* screen)
{
	//SDL_Rect rect;
	char buffer[34];
	int id;
	Imagen* img=new Imagen("resources/graphics/tilesets/camp.png", 19, 8, 0, 255, 0);
	for(int i=0; i<15; i++)
	{
		for(int j=0; j<20; j++)
		{
			strcpy(buffer, suelo[i][j].getTileId().c_str());
			id=atoi(buffer)-1;
			img->dibujar(screen, id ,32*j, 32*i);
			strcpy(buffer, solido[i][j].getTileId().c_str());
			id=atoi(buffer)-1;
			img->dibujar(screen, id ,32*j, 32*i);
		}
	}
}

bool Map::getSolido(int x, int y)
{
	#ifdef DEBUG
	cout<<"Compruebo: ["<<x<<"]["<<y<<"]"<<endl;
	if(solido[x][y].getSolido()==true)
	{
		cout<<x<<", "<<y<<" es solido"<<endl;
	}
	#endif
	return solido[x][y].getSolido();
}

Tile Map::getTile(int y, int x)
{
	return solido[y][x];
}


