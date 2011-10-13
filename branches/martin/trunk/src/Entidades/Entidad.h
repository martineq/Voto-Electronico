/*
 * Entidad.h
 *
 *  Created on: 24/09/2011
 *      Author: lucas
 */

#ifndef ENTIDAD_H_
#define ENTIDAD_H_

#include <string>
#include "Serializable.h"
#include "Constantes.h"
#include "NombreDeEntidad.h"

using std::string;
using std::stringstream;
using std::istringstream;

class Entidad: public Serializable {

public:

	virtual int getTamanio() = 0;

	virtual int getClave() = 0;

	/*
	 * Instancia un nuevo objeto, copia de actual.
	 */
	virtual Entidad* duplicar() = 0;

	/*
	 * Devuelve el tipo de la entidad instanciada.
	 */
	virtual NombreDeEntidad getNombreDeEntidad() = 0;

	virtual ~Entidad () = 0;
};

#endif /* ENTIDAD_H_ */
