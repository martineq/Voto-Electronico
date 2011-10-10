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
#include "./Entidades/Conteo.h"
#include "./Entidades/Administrador.h"
#include "./Archivos/Hashing/Bucket.h"
#include "./Archivos/EnBloques/ArchivoBloques.h"
#include <list>
#include <string>
#include <iostream>
using namespace std;

class Pruebas {
private:
	Votante* votante1;
	Votante* votante2;
	Votante* votante3;
	Votante* votante4;
	Distrito* distrito1;
	Distrito* distrito2;
	Distrito* distrito3;
	Distrito* distrito4;
	Registro* registroVotante1;
	Registro* registroVotante2;
	Registro* registroVotante3;
	Registro* registroVotante4;
	Registro* registroDistrito1;
	Registro* registroDistrito2;
	Registro* registroDistrito3;
	Registro* registroDistrito4;
	Bucket* bucketVotante;
	Bucket* bucketDistrito;
	Bucket* bucketEleccion;
	Bucket* bucketCandidato;
	Bucket* bucketCargo;
	Bucket* bucketLista;
	Bucket* bucketConteo;
	void iniciarRegistrosDePrueba();
	void iniciarRegistrosDistrito();
	void inciarVotantesParaIntegracion();
	void iniciarDistritosParaIntegracion();
	void verContenidoBucketDistrito(Bucket*);
	void verContenidoBucketVotante(Bucket*);
public:
	Pruebas();
//	pruebas para el Archivo en Bloques
	void pruebaArchivoBloques();
	void SerializarGuardarEnBloqueHidratar();
//	pruebas para serializar y deserializar
	void pruebaAgregarRegistrosAlBucket();
	void pruebaEliminarRegistrosDelBucket();
	void pruebaReemplazarRegistroEnBucket();
	void serializarDeserializarBucket();
//	pruebas para serializar y deserializar entidades
	int serializarDeserializarCargo();
	void serializarDeserializarVotante();
	void serializarDeserializarDistrito();
	void serializarDeserializarLista();
	void serializarDeserializarCandidato();
	void serializarDeserializarEleccion();
//	pruebas de integracion
	void pruebaDeSimulacionDePrograma ();
//	pruebas para ver si anda el compilador
	int holaMundo();
	virtual ~Pruebas();
};

#endif /* PRUEBAS_H_ */
