/*
 * Pruebas.h
 *
 *  Created on: 17/09/2011
 *      Author: mart
 */

#ifndef PRUEBAS_H_
#define PRUEBAS_H_
#include "../logica/Entidades/Cargo.h"
#include "../logica/Entidades/Votante.h"
#include "../logica/Entidades/Distrito.h"
#include "../logica/Entidades/Candidato.h"
#include "../logica/Entidades/Lista.h"
#include "../logica/Entidades/Eleccion.h"
#include "../logica/Entidades/Conteo.h"
#include "../logica/Entidades/Administrador.h"
#include "../logica/Archivos/Hashing/Bucket.h"
#include "../logica/Archivos/EnBloques/ArchivoBloques.h"
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
	Bucket* bucketVotante;
	Bucket* bucketDistrito;
	Bucket* bucketEleccion;
	Bucket* bucketCandidato;
	Bucket* bucketCargo;
	Bucket* bucketLista;
	Bucket* bucketConteo;
	void iniciarRegistrosDePrueba();
	void iniciarRegistrosDistrito();
	void iniciarEleccionesParaIntegracion();
	void iniciarVotantesParaIntegracion();
	void iniciarDistritosParaIntegracion();
	void iniciarCandidatosParaIntegracion();
	void iniciarListasParaIntegracion();
	void verContenidoBucketDistrito(Bucket*);
	void verContenidoBucketVotante(Bucket*);
	void verContenidoBucketEleccion(Bucket*);
	void verContenidoBucketCandidato(Bucket*);
	void verContenidoBucketLista(Bucket*);
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
