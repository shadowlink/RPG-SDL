#ifndef _CONTROL_ANIMACION_H_
#define _CONTROL_ANIMACION_H_
#include <vector>

const int MAX_NUM_CUADROS = 30;

class Control_Animacion {
	public:
		Control_Animacion(char *frames);
		~Control_Animacion();
		int cuadro(void);
		bool es_primer_cuadro(void);
		int numero_cuadros();
		int avanzar(void);
		void reiniciar(void);
	private:
		std::vector<int> cuadros;
		int paso;
};

#endif
