/*
 * HashingExtensible.h
 *
 *  Created on: 21/09/2011
 *      Author: martin
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#ifndef HASHINGEXTENSIBLE_H_
#define HASHINGEXTENSIBLE_H_

class HashingExtensible {
private:
	FILE*		archivo;
	vector<int>	tablaDeHash;

	//Aplica la función de hash y devuelve la posicion en la tabla de Hash
	int obtenerPosicion(int clave);

public:
	HashingExtensible();

	HashingExtensible(FILE* Archivo);

	int agregarRegistro(int clave,string elemento);

	int modificarRegistro(int clave,string elemento);

	int eliminarRegistro(int clave);

	virtual ~HashingExtensible();
};

#endif /* HASHINGEXTENSIBLE_H_ */
