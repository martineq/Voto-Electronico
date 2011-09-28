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
#include "./Archivos/Hashing/Registros/RegistroDistrito.h"
#include "./Archivos/Hashing/Bucket.h"
#include "./Archivos/Hashing/HashingExtensible.h"
#include <list>
#include <string>
#include <iostream>
using namespace std;

class Pruebas {
private:
	Distrito* distrito1;
	Distrito* distrito2;
	Distrito* distrito3;
	Distrito* distrito4;
	Registro* registro1;
	Registro* registro2;
	Registro* registro3;
	Registro* registro4;
	Bucket* bucket;
	void iniciarRegistrosDistrito();
	void verContenidoBucket();
public:
	Pruebas();
//	pruebas para el hashing
	void pruebaAgregarRegistrosHashingExtensible();
//	pruebas para serializar y deserializar
	void pruebaAgregarRegistrosAlBucket();
	void pruebaEliminarRegistrosDelBucket();
	void pruebaReemplazarRegistroEnBucket();
	void serializarBucket();
	void deserializarBucket();
//	pruebas para serializar y deserializar entidades
	int serializarDeserializarCargo();
	void serializarDeserializarVotante();
	void serializarDeserializarDistrito();
	void serializarDeserializarLista();
	void serializarDeserializarCandidato();
	void serializarDeserializarEleccion();
//	pruebas para ver si anda el compilador
	int holaMundo();
	virtual ~Pruebas();
};

#endif /* PRUEBAS_H_ */
