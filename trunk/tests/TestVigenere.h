/*
 * TestCriptografia.h
 *
 *  Created on: 12/11/2011
 *      Author: tincho
 */

#ifndef TESTVIGENERE_H_
#define TESTVIGENERE_H_

#include <iostream>
#include <vector>
#include <string>
#include "../src/Criptografia/Vigenere.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

class TestVigenere {
public:
	TestVigenere();
	int testCifrado();
	int testEnBloques();
	virtual ~TestVigenere();
};

#endif /* TESTVIGENERE_H_ */
