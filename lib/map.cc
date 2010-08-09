#include <iostream>
#include <SDL/SDL_ttf.h>
#include "map.h"
#include "imagen.h"

using namespace std;
using namespace irr;
using namespace io;

//##############Clase Tile#########################

//Constructor por defecto
Tile::Tile()
{
	TileId="";
	solido=false;
	posX=0;
	posY=0;
}

//Constructor sobrecargado
Tile::Tile(const bool sol, const string tilid)
{
	TileId=tilid;
	solido=sol;
	posX=0;
	posY=0;
}

//Destructor
Tile::~Tile()
{
	TileId=' ';
	solido=false;	
	posX=0;
	posY=0;
}

//Devuelve el estado solido de una baldosa
bool Tile::getSolido() const
{
	return solido;
}

//Devuelve el Id de la imagen de la baldosa
string Tile::getTileId() const
{
	return TileId;
}

//Establece la coordenada X de la baldosa
void Tile::setX(const Uint32 x)
{
	posX=x;
}

//Establece la coordenada Y de la baldosa
void Tile::setY(const Uint32 y)
{
	posY=y;
}

//Devuelve la coordenada X de la baldosa
Uint32 Tile::getX() const
{
	return posX;
}

//Devuelve la coordenada Y de la baldosa
Uint32 Tile::getY() const
{
	return posY;
}

//Establece la Id de la imagen de la baldosa
void Tile::setTileId(const string id)
{
	TileId=id;
}

//Establece si una baldosa es sólida o no
void Tile::setSolido(const bool solido)
{
	this->solido=solido;
}


//##############Clase Map#########################

//Constructor sobrecargado
Map::Map(const Uint32 num)
{
	id=num;
}

//Destructor
Map::~Map()
{
	id=0;
}

//Lee el archivo .tmx y carga cada capa del mapa en una matriz bidimensional
void Map::CargarMapa()
{	
	int y=0, x=0, t=0, h=0;
	//Cargamos el mapa
	IrrXMLReader* xml = createIrrXMLReader("maps/mapa.tmx");
	std::string capa;
	std::string gid;
	Tile mitile;
	char buffer[1024];
	
	//Leemos el mapa
	while(xml && xml->read())
	{
		switch(xml->getNodeType())
		{
			//Caso de que sea una etiqueta de tipo elemento
			case EXN_ELEMENT:
			{
				//Si es un "layer" comprobamos cual es y lo guardamos
				if (!strcmp("layer", xml->getNodeName()))
				{
					capa = xml->getAttributeValue("name");
				}
				else if (!strcmp("map", xml->getNodeName()))
				{
					ancho=atoi(xml->getAttributeValue("width"));
					alto=atoi(xml->getAttributeValue("height"));
				}
				else
				{
					//Si encontramos un elemnto "tile" comprobamos en que capa estamos
					//y lo guardamos en la matriz correspondiente
					if (!strcmp("tile", xml->getNodeName()))
					{
						gid = xml->getAttributeValue("gid");
						if(capa=="Suelo")
						{
							if(x<30) //Final de la linea
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
						else if(capa=="Suelo2")
						{
							x=0;
							y=0;
							if(t<30) //Final de la linea
							{
								mitile.setTileId(gid);
								mitile.setSolido(false);
								suelo2[h][t]=mitile;
								t++;
							}
							else
							{
								t=0;
								h++;
								mitile.setTileId(gid);
								mitile.setSolido(false);
								suelo2[h][t]=mitile;
								t++;								
							}
						}
						else if(capa=="Solido")
						{
							h=0;
							t=0;
							if(x<30) //Final de la linea
							{
								mitile.setTileId(gid);
								if(gid!="0")
								{
									mitile.setSolido(true);
								}
								else
								{
									mitile.setSolido(false);
								}
								solido[y][x]=mitile;
								x++;
							}
							else
							{
								x=0;
								y++;
								mitile.setTileId(gid);
								if(gid!="0")
								{
									mitile.setSolido(true);
								}
								else
								{
									mitile.setSolido(false);
								}
								solido[y][x]=mitile;
								x++;								
							}							
						}
						else if(capa=="Frontal")
						{
							if(t<30) //Final de la linea
							{
								mitile.setTileId(gid);
								mitile.setSolido(false);
								frontal[h][t]=mitile;
								t++;
							}
							else
							{
								t=0;
								h++;
								mitile.setTileId(gid);
								mitile.setSolido(false);
								frontal[h][t]=mitile;
								t++;								
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

//Dibuja las diferentes capasa del mapa (salvo la frontal) en la pantalla
void Map::DibujarMapa(SDL_Surface* screen)
{
	char buffer[34];
	Uint32 id=0, i=0, j=0;
	Imagen* img=new Imagen("resources/graphics/tilesets/camp.png", 19, 8, 0, 255, 0);
	
	for(i=0; i<15; i++)
	{
		for(j=0; j<20; j++)
		{
			strcpy(buffer, suelo[i][j].getTileId().c_str());
			id=atoi(buffer)-1;
			img->dibujar(screen, id ,32*j, 32*i);
			strcpy(buffer, suelo2[i][j].getTileId().c_str());
			id=atoi(buffer)-1;
			img->dibujar(screen, id ,32*j, 32*i);
			strcpy(buffer, solido[i][j].getTileId().c_str());
			id=atoi(buffer)-1;
			img->dibujar(screen, id ,32*j, 32*i);
		}
	}
	delete img;
}

//Dibuja la capa frontal (atravesable por detras)
void Map::DibujaTras(SDL_Surface* screen)
{
	char buffer[34];
	Uint32 id=0, i=0, j=0;
	Imagen* img=new Imagen("resources/graphics/tilesets/camp.png", 19, 8, 0, 255, 0);
	
	for(i=0; i<15; i++)
	{
		for(j=0; j<20; j++)
		{
			strcpy(buffer, frontal[i][j].getTileId().c_str());
			id=atoi(buffer)-1;
			img->dibujar(screen, id ,T_ANCHO*j, T_ALTO*i);
		}
	}
	delete img;	
}

//Comprueba si una baldosa es solida
bool Map::getSolido(const Uint32 x, const Uint32 y) const
{
	return solido[x][y].getSolido();
}

Tile Map::getSuelo(const Uint32 x, const Uint32 y) const
{
	return suelo[x][y];
}

Tile Map::getSuelo2(const Uint32 x, const Uint32 y) const
{
	return suelo2[x][y];
}

Tile Map::getSueloSolido(const Uint32 x, const Uint32 y) const
{
	return solido[x][y];
}

//Retorna la altura del mapa en celdas
Uint32 Map::getAlto() const
{
	return alto;
}

//Retorna el ancho del mapa en celdas
Uint32 Map::getAncho() const
{
	return ancho;
}

