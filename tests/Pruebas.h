/*
 * Pruebas.h
 *
 *  Created on: 17/09/2011
 *      Author: mart
 */

#ifndef PRUEBAS_H_
#define PRUEBAS_H_

#include "../src/Entidades/Cargo.h"
#include "../src/Entidades/Votante.h"
#include "../src/Entidades/Distrito.h"
#include "../src/Entidades/Candidato.h"
#include "../src/Entidades/Lista.h"
#include "../src/Entidades/Eleccion.h"
#include "../src/Entidades/Conteo.h"
#include "../src/Entidades/Constantes.h"
#include "../src/Auxiliares/Log.h"
#include "../src/Auxiliares/Configuracion.h"
#include "../src/Logica/Administrador.h"
#include "../src/Archivos/Hashing/Bucket.h"
#include "../src/Archivos/Hashing/HashingExtensible.h"
#include "../src/Archivos/EnBloques/ArchivoBloques.h"
#include "../src/Archivos/ArbolBMas/bplustree.h"
#include "../src/Logica/AdministradorDeVotaciones.h"
#include <list>
#include <time.h>
#include <stdio.h>
#include "../src/Archivos/ArbolBMas/bplustree.h"
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
	Eleccion* eleccion1;
	Eleccion* eleccion2;
	Eleccion* eleccion3;
	Eleccion* eleccion4;
	Candidato* candidato1;
	Candidato* candidato2;
	Candidato* candidato3;
	Candidato* candidato4;
	Lista* lista1;
	Lista* lista2;
	Lista* lista3;
	Lista* lista4;
	Cargo* cargo1;
	Cargo* cargo2;
	Registro* registroVotante1;
	Registro* registroVotante2;
	Registro* registroVotante3;
	Registro* registroVotante4;
	Registro* registroDistrito1;
	Registro* registroDistrito2;
	Registro* registroDistrito3;
	Registro* registroDistrito4;
	Registro* registroEleccion1;
	Registro* registroEleccion2;
	Registro* registroEleccion3;
	Registro* registroEleccion4;
	Registro* registroCandidato1;
	Registro* registroCandidato2;
	Registro* registroCandidato3;
	Registro* registroCandidato4;
	Registro* registroLista1;
	Registro* registroLista2;
	Registro* registroLista3;
	Registro* registroLista4;
	Registro* registroCargo1;
	Registro* registroCargo2;
	Bucket* bucketVotante;
	HashingExtensible* heVotante;
	HashingExtensible* heDistrito;
	HashingExtensible* heEleccion;
	HashingExtensible* heCandidato;
	HashingExtensible* heLista;
	HashingExtensible* heCargo;
	Bucket* bucketDistrito;
	Bucket* bucketEleccion;
	Bucket* bucketCandidato;
	Bucket* bucketCargo;
	Bucket* bucketLista;
	Bucket* bucketConteo;
	void iniciarRegistrosDePrueba();
	void iniciarRegistrosDistrito();
	void verContenidoBucketDistrito(Bucket*);
	void verContenidoBucketVotante(Bucket*);
	void verContenidoBucketEleccion(Bucket*);
	void verContenidoBucketCandidato(Bucket*);
	void verContenidoBucketLista(Bucket*);
	void verContenidoBucketCargo(Bucket*);
	void cadenaAlfaNumAlAzar(char *s, const int len);
	void cadenaNumericaAlAzar(char *s, const int len);

public:
	Pruebas();
//	pruebas para el Archivo en Bloques
	void pruebaArchivoBloques();
	void SerializarGuardarEnBloqueHidratar();
//	pruebas para el Árbol B+
	void pruebaBMas();
	void pruebaBMasAuto();
	void pruebaBMasCarga();
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
//	pruebas para argumentos y archivo de configuración
	void pruebaConfiguracion(int argc, const char* argv[]);
//	pruebas de integracion
	void pruebaLog();
//	pruebas para ver si anda el compilador
	int holaMundo();
	virtual ~Pruebas();
};

#endif /* PRUEBAS_H_ */
