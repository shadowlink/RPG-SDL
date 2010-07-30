#include <iostream>
#include "images.h"

using namespace std;

//Obtiene el color de un pixel
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0; 
    }
}

SDL_Surface* load_image(char dir[], bool transparent)
{
	SDL_Surface *imagen;
	imagen=IMG_Load(dir);
	if(transparent)
	{
		Uint32 color=getpixel(imagen, 0, 0);
		SDL_SetColorKey(imagen, SDL_SRCCOLORKEY|SDL_RLEACCEL, color);
	}
	return imagen;
}
