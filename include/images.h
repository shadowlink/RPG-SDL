#ifndef images_h
#define images_h
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

Uint32 getpixel(SDL_Surface, int, int);
SDL_Surface* load_image(char dir[], bool);

#endif
