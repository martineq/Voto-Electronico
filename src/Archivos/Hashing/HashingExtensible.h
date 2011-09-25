/*
 * HashingExtensible.h
 *
 *  Created on: 21/09/2011
 *      Author: martin
 */

#include <iostream>
#include <vector>
#include <cmath>

#include "../../ClasesDePrueba/ArchivoDeBuckets.h"
#include "Bucket.h"
#include "Registro.h"


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
	list<int>			listaDeBucketsLibres;
	Bucket*				bucket;

	//Aplica la función de hash y devuelve la posicion en la tabla de Hash
	int obtenerPosicion(int clave);

	int obtenerDispersion(int bloque);

	int numeroPosicionesAreemplazar(int posicion);

	void redispersarBucket(Bucket* bucket,int numeroDeBucket,int posicionEnTablaDeHash);

	bool reducirTablaDeHash();

public:
	HashingExtensible();

	HashingExtensible(ArchivoDeBuckets* nombreArchivo);

	void agregarRegistro(Registro* registro);

	void modificarRegistro(Registro* registro);

	int eliminarRegistro(int clave);

	virtual ~HashingExtensible();
};

#endif /* HASHINGEXTENSIBLE_H_ */
