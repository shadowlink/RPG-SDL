#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <iostream>
#include "actor.h"
#include "map.h"

using namespace std;

int sincronizar_fps(void) {
    static Uint32 t0;
    static Uint32 tl = SDL_GetTicks();
    static Uint32 frecuencia = 4000 / 100;
    static Uint32 tmp;

#ifdef FPS
    static Uint32 fps = 0;
    static Uint32 t_fps = 0;
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
	 Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096);
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
	//Iniciamos SDL
    iniciarSDL();
    
    //Declaracion de variables
    SDL_Surface *screen;
    SDL_Event evento;        
    Uint32 time;
    Sint32 x0, y0;
	estados_personaje s0;
    SDL_Rect posicion;
    Mix_Music *mainTheme;
	mainTheme=Mix_LoadMUS("resources/music/z3.mid");
	char rejillaDir[]="resources/graphics/rejilla.png";
	
    //A la salida liberamos SDL y todos los subsitemas abiertos
    atexit(TTF_Quit); 
    atexit(Mix_CloseAudio);
	atexit(SDL_Quit);        
	
    // Establecemos el modo de pantalla
	screen= SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_ANYFORMAT | SDL_HWSURFACE | SDL_DOUBLEBUF);
    if(screen == NULL) {
		cerr<<"Error al crear la superficie: "<<SDL_GetError()<<endl;
		exit(1);
    }
    
    //Titulo de la ventana
    SDL_WM_SetCaption("Engine RPG", NULL);
	
	//Rejilla
	SDL_Surface *rejilla;
	rejilla=load_image(rejillaDir, true);
	posicion.x=0;
	posicion.y=0;
	posicion.w=640;
	posicion.h=480;
	//------------------------------------------------------
	
	//Cargamos la música, el mapa y el heroe
	Mix_FadeInMusic(mainTheme, -1, 1500);
	Map* mapa=new Map(1);
	mapa->CargarMapa();
	mapa->DibujarMapa(screen);
	Actor heroe("resources/graphics/charasets/heroe.bmp");
	mapa->DibujaTras(screen);
	heroe.Dibujar(screen);
	
	//Bucle principal
	while(true)
	{
		//Guardamos la posicion y estado del heroe al inicio de cada iteración
		x0=heroe.getX();
		y0=heroe.getY();
		s0=heroe.estado_actual();
		
		//Control de los FPS
		time=sincronizar_fps();
		//Control de eventos
		salir(evento);
		//Comprobamos y actualizamos la posicion y estado del heroe si es necesario
		heroe.Actualizar(mapa);
		
		//Si el heroe se ha movido actualizamos la pantalla
		if(x0 != heroe.getX() || y0 != heroe.getY() || s0 != heroe.estado_actual()) 
		{
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
			mapa->DibujarMapa(screen);	
			heroe.Dibujar(screen);
			//Esta capa dibuha los objetos que se pueden traspasar por detras
			mapa->DibujaTras(screen);
		}
		//camara.update(screen, heroe);
		//Dibujamos la rejilla en la pantalla
		SDL_BlitSurface(rejilla, NULL, screen, &posicion);
		//Actualizamos la panatalla
		SDL_Flip(screen);
	}
}
