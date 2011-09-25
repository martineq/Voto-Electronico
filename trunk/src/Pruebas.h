/*
 * Pruebas.h
 *
 *  Created on: 17/09/2011
 *      Author: mart
 */

#ifndef PRUEBAS_H_
#define PRUEBAS_H_
#include "./Entidades/Cargo.h"
#include "./Entidades/Votante.h"
#include "./Entidades/Distrito.h"
#include "./Entidades/Candidato.h"
#include "./Entidades/Lista.h"
#include "./Entidades/Eleccion.h"
#include "./ClasesDePrueba/RegistroDePrueba.h"
#include "./Archivos/Hashing/Bucket.h"
#include "./Archivos/Hashing/hashingExtensible.h"
#include <list>
#include <string>
#include <iostream>
using namespace std;

class Pruebas {
public:
	Pruebas();
	void pruebaHashingExtensible();
	void pruebaRegistro();
	int holaMundo();
	int serializarDeserializarCargo();
	void serializarDeserializarVotante();
	void serializarDeserializarDistrito();
	void serializarDeserializarLista();
	void serializarDeserializarCandidato();
	void serializarDeserializarEleccion();
	virtual ~Pruebas();
};

#endif /* PRUEBAS_H_ */
