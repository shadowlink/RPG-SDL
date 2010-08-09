#ifndef _CONSTANTES_
#define _CONSTANTES_

enum estados_personaje{
	PARADO,
	PARADO_DERECHA,
	PARADO_ARRIBA,
	ANDAR_DERECHA,
	PARADO_ABAJO,
	PARADO_IZQUIERDA,
	ANDAR_IZQUIERDA,
	ANDAR_ARRIBA,
	ANDAR_ABAJO,   
	MAX_ESTADOS
};

const Uint32 ANCHO=640;
const Uint32 ALTO=480;
const Uint32 T_ANCHO=32; //Ancho del Tile
const Uint32 T_ALTO=32; //Alto del Tile

#endif
