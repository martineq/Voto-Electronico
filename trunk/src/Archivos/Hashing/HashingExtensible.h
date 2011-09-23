/*
 * HashingExtensible.h
 *
 *  Created on: 21/09/2011
 *      Author: martin
 */

#include <iostream>
#include <vector>
#include <cmath>
#include "../InterpreteDeRegistro.h"

using namespace std;

#ifndef HASHINGEXTENSIBLE_H_
#define HASHINGEXTENSIBLE_H_

class HashingExtensible {
private:
	FILE*		archivo;
	vector<int>	tablaDeHash;
	vector<int> tablaDeDispersion;
	//BLOQUE	ultimoBloqueAccedido;

	//Aplica la función de hash y devuelve la posicion en la tabla de Hash
	int obtenerPosicion(int clave);

	int obtenerDispersion(int bloque);

public:
	HashingExtensible();

	HashingExtensible(FILE* Archivo);

	int agregarRegistro(InterpreteDeRegistro* interprete,string* bytes);

	int modificarRegistro(InterpreteDeRegistro* interprete,string* elemento);

	int eliminarRegistro(int clave);

	virtual ~HashingExtensible();
};

#endif /* HASHINGEXTENSIBLE_H_ */
