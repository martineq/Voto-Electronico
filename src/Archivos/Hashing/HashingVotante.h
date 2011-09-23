/*
 * HashingVotante.h
 *
 *  Created on: 22/09/2011
 *      Author: lÑ#$dsa44
 */

#ifndef HASHINGVOTANTE_H_
#define HASHINGVOTANTE_H_

#include "FuncionHashing.h"
#include "../../Entidades/Votante.h"

class HashingVotante: public FuncionHashing {
public:
	HashingVotante();

	int aplicarDispersion(string* entidad_serializada);

	~HashingVotante();
};

#endif /* HASHINGVOTANTE_H_ */
