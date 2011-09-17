/*
 * Serializable.h
 *
 *  Created on: 17/09/2011
 *      Author: lucas
 */

#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

#include <string>

class Serializable {
public:
	virtual std::string* serializar() = 0;

	virtual void deserializar(std::string* source) = 0;

};

#endif /* SERIALIZABLE_H_ */
