#include "../src/Criptografia/RSA.h"

#include "Pruebas.h"
#include "SimulacionSistema.h"
#include "TestHashingExtensible.h"
#include "TestVotanteAleatorio.h"
#include "TestArchivoDeBuckets.h"
#include "TestVigenere.h"
#include "TestEncriptacionVotante.h"
#include "TestKasiski.h"

#include <iostream>
#include <list>

#ifndef TESTMAIN_H_
#define TESTMAIN_H_

class TestMain {
public:
	TestMain();
	void ejecutar();
	virtual ~TestMain();
};

#endif /* TESTMAIN_H_ */
