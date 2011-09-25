/*
 * Entidad.h
 *
 *  Created on: 24/09/2011
 *      Author: lucas
 */

#ifndef ENTIDAD_H_
#define ENTIDAD_H_

#include "Serializable.h"
#include "Constantes.h"

class Entidad: public Serializable {
public:
	virtual int getTamanio() = 0;
	virtual int getClave() = 0;
};

#endif /* ENTIDAD_H_ */
