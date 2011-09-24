/*
 * HashingExtensible.h
 *
 *  Created on: 21/09/2011
 *      Author: martin
 */

#include <iostream>
#include <vector>
#include <cmath>
#include "Registro.h"
#include "../EnBloques/ArchivoBloques.h"
#include "RegistroCandidato.h"
#include "RegistroVotante.h"
#include "HashingVotante.h"
#include "Bucket.h"

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

	int agregarRegistro(Registro* interprete,string* bytes);

	int modificarRegistro(Registro* interprete,string* elemento);

	int eliminarRegistro(int clave);

	virtual ~HashingExtensible();
};

#endif /* HASHINGEXTENSIBLE_H_ */
