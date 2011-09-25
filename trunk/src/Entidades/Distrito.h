/*
 * Distrito.h
 *
 *  Created on: 17/09/2011
 *      Author: martin
 */

#include <string>
#include "Entidad.h"


using namespace std;

#ifndef DISTRITO_H_
#define DISTRITO_H_

class Distrito : public Entidad {

private:
	string distrito;

public:
	Distrito();
	Distrito(string distrito);

	string getDistrito();

	void setDistrito(string distrito);

	string* serializar();

	int getTamanio();

	void deserializar(string* source);

	~Distrito();

};

#endif /* DISTRITO_H_ */

