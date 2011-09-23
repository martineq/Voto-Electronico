/*
 * FuncionHashing.h
 *
 *  Created on: 22/09/2011
 *      Author: lÑ#$dsa44
 */

#include <string>

using std::string;

#ifndef FUNCIONHASHING_H_
#define FUNCIONHASHING_H_

class FuncionHashing {
public:
	FuncionHashing();

	virtual int aplicarDispersion(string* entidad_serializada) = 0;

	virtual ~FuncionHashing();
};

#endif /* FUNCIONHASHING_H_ */
