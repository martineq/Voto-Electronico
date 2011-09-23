/*
 * RegistroCandidato.h
 *
 *  Created on: 22/09/2011
 *      Author: lÑ#$dsa44
 */

#ifndef REGISTROCANDIDATO_H_
#define REGISTROCANDIDATO_H_

#include "../InterpreteDeRegistro.h"

class RegistroCandidato: public InterpreteDeRegistro {
public:
	RegistroCandidato();

	int obtenerClave(string* bytes);

	virtual ~RegistroCandidato();
};

#endif /* REGISTROCANDIDATO_H_ */
