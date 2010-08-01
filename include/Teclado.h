#ifndef _TECLADO_H_
#define _TECLADO_H_
#include <SDL/SDL.h>
#include <map>

using namespace std;

class Teclado 
{
	public:
		enum teclas_utilizadas 
		{
			TECLA_SUBIR,
			TECLA_BAJAR,
			TECLA_ACEPTAR,
			TECLA_GOLPEAR,
			TECLA_IZQUIERDA,
			TECLA_DERECHA,
			TECLA_SALTAR,
		};

		Teclado();
		void actualizar(void);
		bool pulso(teclas_utilizadas tecla);
	private:
		Uint8* teclas;
		map<teclas_utilizadas, SDLKey> teclas_configuradas;
};

#endif 
