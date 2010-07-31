#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <iostream>
#include "actor.h"
#include "imagen.h"
#include "images.h"
#include "Teclado.h"
#include "animacion.h"
#include "map.h"


using namespace std;

const int WIDTH=640;
const int HEIGHT=480;

int sincronizar_fps(void) {
    static int t0;
    static int tl = SDL_GetTicks();
    static int frecuencia = 4000 / 100;
    static int tmp;

#ifdef FPS
    static int fps = 0;
    static int t_fps = 0;
#endif

    // Tiempo de referencia
    t0 = SDL_GetTicks();

#ifdef FPS  
    // Actualizamos información cada segundo
    if((t0 - t_fps) >= 1000) {
		cout << "FPS = " << fps << endl;
		fps = 0;
		t_fps += 1000 + 1;
    }
    fps++;
#endif

    // Estudio del tiempo
    if((t0 - tl) >= frecuencia) {
		tmp = (t0 - tl) / frecuencia;
		tl += tmp * frecuencia;
		return tmp;
    }
    else {
		// Tenemos que esperar para cumplir con la frecuencia
		SDL_Delay(frecuencia - (t0 - tl));
		tl += frecuencia;
		return 1;
    }
}

void iniciarSDL()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
	{
		cerr<<"Error en SDL_Init(): "<<SDL_GetError()<<endl;
		exit(1);
	}
	if(!TTF_Init() < 0) 
	{
		cerr<<"Error en SDL_TTF(): "<<SDL_GetError()<<endl;
		exit(1);	
	 }
}

void salir(SDL_Event evento)
{
	while(SDL_PollEvent(&evento)) 
	{
			if(evento.type == SDL_QUIT) // Si es de salida
				exit(0);
			if(evento.type==SDL_KEYDOWN)
				if(evento.key.keysym.sym == SDLK_ESCAPE)
					exit(0);

	}
}

// ---------------------------------------------------------------------

int main(int argc, char *argv[])
{

    
    SDL_Surface *screen;       // Definimos una superficie
    SDL_Event evento;            // Definimos una variable de eventos
    int time;
    SDL_Rect posicion;
    
    iniciarSDL();
    atexit(TTF_Quit); 
	atexit(SDL_Quit);            // Al salir, cierra SDL
	
    // Establecemos el modo de pantalla
	screen= SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_ANYFORMAT | SDL_HWSURFACE | SDL_DOUBLEBUF);
    if(screen == NULL) {
		cerr<<"Error al crear la superficie: "<<SDL_GetError()<<endl;
		exit(1);
    }
       
    SDL_WM_SetCaption("Engine RPG", NULL);
	
	//Teclado teclado;
	
	//Rejilla
	SDL_Surface *rejilla;
	rejilla=load_image("resources/graphics/rejilla.png", true);
	posicion.x=0;
	posicion.y=0;
	posicion.w=640;
	posicion.h=480;
	//------------------------------------------------------
	
	Map* mapa=new Map(1);
	mapa->CargarMapa();
	mapa->DibujarMapa(screen);
	Actor heroe("resources/graphics/charasets/heroe.bmp");
	heroe.Dibujar(screen);
	
	int x0, y0;
	estados_personaje s0;
	
	while(true)
	{
		x0=heroe.getX();
		y0=heroe.getY();
		s0=heroe.estado_actual();
		
		//Control de los FPS
		time=sincronizar_fps();
		salir(evento);
		heroe.Actualizar(mapa);
		
		if(x0 != heroe.getX() || y0 != heroe.getY() || s0 != heroe.estado_actual()) 
		{
			cout<<"Hola"<<endl;
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
			mapa->DibujarMapa(screen);	
			heroe.Dibujar(screen);
		}
		//camara.update(screen, heroe);
		SDL_BlitSurface(rejilla, NULL, screen, &posicion);
		SDL_Flip(screen);
	}
}
