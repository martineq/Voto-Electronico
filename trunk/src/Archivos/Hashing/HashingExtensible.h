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
#include "ArchivoDeBuckets.h"
#include "Bucket.h"

//#include "RegistroCandidato.h"
//#include "RegistroVotante.h"
//#include "HashingVotante.h"

using std::string;

#ifndef HASHINGEXTENSIBLE_H_
#define HASHINGEXTENSIBLE_H_

class HashingExtensible {
private:
	ArchivoDeBuckets*	archivo;
	vector<int>			tablaDeHash;
	vector<int> 		tablaDeDispersion;
	Bucket*				bucket;

	//Aplica la función de hash y devuelve la posicion en la tabla de Hash
	int obtenerPosicion(int clave);

	int obtenerDispersion(int bloque);

	int numeroPosicionesAreemplazar(int posicion);

	void redispersarBucket(Bucket* bucket,int numeroDeBucket,int posicionEnTablaDeHash);

	Bucket obtenerBucket(int numeroDeBucket);

public:
	HashingExtensible();

	HashingExtensible(ArchivoDeBuckets* nombreArchivo);

	int agregarRegistro(Registro* registro);

	int modificarRegistro(Registro* registro);

	int eliminarRegistro(int clave);

	virtual ~HashingExtensible();
};

#endif /* HASHINGEXTENSIBLE_H_ */
