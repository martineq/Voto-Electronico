/*
 * Constantes.h
 *
 *  Created on: 17/09/2011
 *      Author: lucas
 */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_
#include <stdint.h>


//------- Rutas a poner en el archivo de configuracion ---------
//----------------------------------------------------------------


//Longitudes
#define LONGITUD_BLOQUE 1024
#define TAM_BOOL sizeof(bool)
#define TAM_LONG sizeof(long)
#define TAM_UNSINT sizeof(unsigned int)
#define TAM_INT sizeof(int)
#define TAM_SINT sizeof (short int)

//Estados Nodo
#define OK 0
#define OVERFLOW 1
#define UNDERFLOW 2

//Comparación de Elementos
#define IGUAL 0
#define MENOR -1
#define MAYOR 1


#endif /* CONSTANTES_H_ */
