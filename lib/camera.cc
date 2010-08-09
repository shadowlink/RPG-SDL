#include <iostream>
#include "camera.h"
#include "consts.h"

using namespace std;

Camara::Camara()
{
}

Camara::~Camara()
{
}

void Camara::plot(Map* mapa, Uint32 f, Uint32 c)
{
}
	
void Camara::mouse_map(Map* mapa, Uint32 x, Uint32 y)
{
}

void Camara::Actualizar(SDL_Surface* screen, Map* mapa, Heroe* heroe)
{
	Uint32 centroX=0, centroY=0, inicial[2], lim_right[2], lim_bottom[2], id=0, x=0, y=0;
	Sint32 scrollX=0, scrollY=0;
	char buffer[1024];
	Imagen* img=new Imagen("resources/graphics/tilesets/camp.png", 19, 8, 0, 255, 0);
	
	centroX=heroe->getX();
	centroY=heroe->getY()+32;
	
	scrollX=centroX-(640/2);
	scrollY=centroY-(480/2);
	
	if(scrollX<0)
	{
		scrollX=0;
	}
	if(scrollX>(mapa->getAncho()*32)-ANCHO)
	{
		scrollX=((mapa->getAncho()*32)-ANCHO);
	}
	if(scrollY<0)
	{
		scrollY=0;
	}
	if(scrollY>(mapa->getAlto()*32)-ALTO)
	{
		scrollY=(mapa->getAlto()*32-ALTO);
	}
	
	inicial[0]=(0 + scrollY) / 32;
	inicial[1]=(0 + scrollX) / 32;
	lim_right[0]=(ANCHO + scrollX) / 32;
	lim_right[1]=(0 + scrollX) / 32;
	lim_bottom[0]=(0 + scrollY) / 32;
	lim_bottom[1]=(ALTO + scrollY) / 32;
	
	if(lim_right[1]>=mapa->getAncho())
	{
		lim_right[1]-=1;
	}
	if(lim_bottom[0]>=mapa->getAlto())
	{
		lim_bottom[0]-=1;
	}
	cout<<"###################"<<endl;
	cout<<"PosX: "<<heroe->getX()<<endl;
	cout<<"PosY: "<<heroe->getY()<<endl;
	cout<<"Inicial[0]: "<<inicial[0]<<endl;
	cout<<"lim_bottom[1]: "<<lim_bottom[1]<<endl;
	cout<<"Inicial[1]: "<<inicial[1]<<endl;
	cout<<"lim_right[0]: "<<lim_right[0]<<endl;
	for(int i=inicial[0]; i<lim_bottom[1]+1; i++)
	{
		for(int j=inicial[1]; j<lim_right[0]+1; j++)
		{
			strcpy(buffer, mapa->getSuelo(i, j).getTileId().c_str());
			id=atoi(buffer)-1;
			img->dibujar(screen, id ,(32*j)-scrollX, (32*i)-scrollY);
			strcpy(buffer, mapa->getSuelo2(i, j).getTileId().c_str());
			id=atoi(buffer)-1;
			img->dibujar(screen, id ,(32*j)-scrollX, (32*i)-scrollY);
			strcpy(buffer, mapa->getSueloSolido(i, j).getTileId().c_str());
			id=atoi(buffer)-1;
			img->dibujar(screen, id ,(32*j)-scrollX, (32*i)-scrollY);
		}
	}
}
