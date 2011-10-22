/*
 * TestVotanteAleatorio.h
 *
 *  Created on: 17/10/2011
 *      Author: lÑ#$dsa44
 */

#ifndef TESTVOTANTEALEATORIO_H_
#define TESTVOTANTEALEATORIO_H_

#include <iostream>
#include "../src/Archivos/Hashing/HashingExtensible.h"
#include "../src/Archivos/Hashing/Registro.h"
#include "../src/ClasesAuxiliares/CreadorVotante.h"


class TestVotanteAleatorio {
public:
	TestVotanteAleatorio();

	void crearArchivoDeVotantes();
	void pruebaBusquedaEnArchivoDeVotantes();
	virtual ~TestVotanteAleatorio();
};

#endif /* TESTVOTANTEALEATORIO_H_ */
