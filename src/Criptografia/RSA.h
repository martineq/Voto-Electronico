/*
 * RSA.h
 *
 *  Created on: 10/11/2011
 *      Author: daniel
 */

#ifndef RSA_H_
#define RSA_H_
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <cmath>
#include <time.h>
#include <iostream>
using namespace std;

class RSA {
private:
	int p;
	int q;
	int n;
	int d;
	int e;
	int phi;
	vector<int> fila1;
	vector<int> fila2;
	bool esPrimo (int);
	void elegirD();
	long aBinario(long);
public:
	RSA();
	virtual ~RSA();
	void generarPyQ();
	void calcularN();
	void calcularPhi();
	void calcularE();
	long encriptar(int);
	int desencriptar(long);
	void atacar();
};

#endif /* RSA_H_ */
