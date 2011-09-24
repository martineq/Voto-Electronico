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
#include "../EnBloques/ArchivoBloques.h"

using std::string;

#ifndef HASHINGEXTENSIBLE_H_
#define HASHINGEXTENSIBLE_H_

class HashingExtensible {
private:
	ArchivoBloques*		archivo;
	vector<int>			tablaDeHash;
	vector<int> 		tablaDeDispersion;
	Bucket*				bucket;

	//Aplica la función de hash y devuelve la posicion en la tabla de Hash
	int obtenerPosicion(int clave);

	int obtenerDispersion(int bloque);

	int numeroPosicionesAreemplazar(int posicion);

public:
	HashingExtensible();

	HashingExtensible(ArchivoBloques* nombreArchivo);

	int agregarRegistro(InterpreteDeRegistro* interprete,string* bytes);

	int modificarRegistro(InterpreteDeRegistro* interprete,string* elemento);

	int eliminarRegistro(int clave);

	virtual ~HashingExtensible();
};

#endif /* HASHINGEXTENSIBLE_H_ */
