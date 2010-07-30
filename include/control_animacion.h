// Listado: Control_Animacion.h
//
// Esta clase controla la secuencia de animación de los personajes de la 
// aplicación

#ifndef _CONTROL_ANIMACION_H_
#define _CONTROL_ANIMACION_H_

#include <vector>

const int MAX_NUM_CUADROS = 30;

class Control_Animacion {
 public:
    
    // Constructor
    Control_Animacion(char *frames);

    // Consultoras
    int cuadro(void);
    bool es_primer_cuadro(void);
    int numero_cuadros();
    
    // Modificadoras
    int avanzar(void);
    void reiniciar(void);

    // Destructor
    ~Control_Animacion();
    
 private:
    std::vector<int> cuadros;
    int paso;
};

#endif
