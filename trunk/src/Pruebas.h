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

class Pruebas {
public:
	Pruebas();
	int holaMundo();
	int serializarCargo();
	int cargaVotante();
	virtual ~Pruebas();
};

#endif /* PRUEBAS_H_ */
