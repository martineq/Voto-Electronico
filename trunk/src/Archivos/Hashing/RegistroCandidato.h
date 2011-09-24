/*
 * RegistroCandidato.h
 *
 *  Created on: 22/09/2011
 *      Author: lÑ#$dsa44
 */

#ifndef REGISTROCANDIDATO_H_
#define REGISTROCANDIDATO_H_

#include "../Registro.h"
#include "../../Entidades/Candidato.h"

class RegistroCandidato: public Registro {
private:
	Candidato* candidato;
public:
	RegistroCandidato();

	int obtenerClave(string* bytes);


	string* serializar();
	void deserializar(string * source);


	virtual ~RegistroCandidato();
};

#endif /* REGISTROCANDIDATO_H_ */
