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
#include "./Entidades/Constantes.h"
#include "Log.h"
#include "./Archivos/Hashing/Bucket.h"
#include "./Archivos/Hashing/HashingExtensible.h"
#include "./Archivos/EnBloques/ArchivoBloques.h"
#include "./Archivos/ArbolBMas/bplustree.h"
#include <list>
#include <time.h>
#include <stdio.h>
#include "./Archivos/ArbolBMas/bplustree.h"
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
	bplustree* arbolB;
	string* getString(vector<char>);
	void agregarBoletaAlArbol(Registro*);
	void iniciarRegistrosDePrueba();
	void iniciarRegistrosDistrito();
	void iniciarEleccionesParaIntegracion();
	void iniciarVotantesParaIntegracion();
	void iniciarDistritosParaIntegracion();
	void iniciarCandidatosParaIntegracion();
	void iniciarListasParaIntegracion();
	void iniciarCargosParaIntegracion();
	void verContenidoBucketDistrito(Bucket*);
	void verContenidoBucketVotante(Bucket*);
	void verContenidoBucketEleccion(Bucket*);
	void verContenidoBucketCandidato(Bucket*);
	void verContenidoBucketLista(Bucket*);
	void verContenidoBucketCargo(Bucket*);
	void verContenidoArbolListas();
public:
	Pruebas();
//	pruebas para el Archivo en Bloques
	void pruebaArchivoBloques();
	void SerializarGuardarEnBloqueHidratar();
//	pruebas para el Árbol B+
	void pruebaBMas();
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
	void cargarBaseDeDatos(Administrador);
	void inicioDeSimulacion(Administrador);
	void destruir();
	void pruebaDeSimulacionDePrograma ();
	void pruebaLog();
//	pruebas para ver si anda el compilador
	int holaMundo();
	virtual ~Pruebas();
};

#endif /* PRUEBAS_H_ */
