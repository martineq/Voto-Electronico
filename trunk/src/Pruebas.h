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
#include "./Archivos/EnBloques/ManejadorDeArchivo.h"
#include <list>
#include <string>
#include <iostream>
using namespace std;

class Pruebas {
public:
	Pruebas();
	int holaMundo();
	int ManejadorDeArch();
	int serializarDeserializarCargo();
	void serializarDeserializarVotante();
	void serializarDeserializarDistrito();
	void serializarDeserializarLista();
	void serializarDeserializarCandidato();
	void serializarDeserializarEleccion();
	virtual ~Pruebas();
};

#endif /* PRUEBAS_H_ */
