/*
 * RegistroVotante.h
 *
 *  Created on: 22/09/2011
 *      Author: lÑ#$dsa44
 */

#ifndef REGISTROVOTANTE_H_
#define REGISTROVOTANTE_H_

#include "../InterpreteDeRegistro.h"

class RegistroVotante: public InterpreteDeRegistro {
public:
	RegistroVotante();

	int obtenerClave(string* bytes);

	virtual ~RegistroVotante();
};

#endif /* REGISTROVOTANTE_H_ */
