/*
 * Eleccion.h
 *
 *  Created on: 17/09/2011
 *      Author: martin
 */

#include <list>
#include <string>
#include "Distrito.h"
#include "Cargo.h"

#ifndef ELECCION_H_
#define ELECCION_H_

class Eleccion {
private:
	string			fecha;				// identificador
	Cargo			cargoPrincipal;		// identificador
	list<Distrito>	distritos;

public:
	Eleccion();

	string getFecha();

	string getCargo();


	virtual ~Eleccion();
};

#endif /* ELECCION_H_ */
