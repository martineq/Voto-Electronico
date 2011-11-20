/*
 * TestKasiski.h
 *
 *  Created on: 20/11/2011
 *      Author: martin
 */

#ifndef TESTKASISKI_H_
#define TESTKASISKI_H_

#include "../src/Criptografia/Vigenere.h"
#include "../src/Criptografia/Kasiski.h"

#include <string>
#include "./Constitucion.h"

using std::string;
using std::cout;
using std::endl;

class TestKasiski {
public:
	TestKasiski();

	int testObtenerClaveDeVigenere();

	virtual ~TestKasiski();
};

#endif /* TESTKASISKI_H_ */
