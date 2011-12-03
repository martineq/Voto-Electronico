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
#include <list>

using namespace std;

class RSA {
private:
	long long p;
	long long q;
	long long n;
	long long d;
	long long e;
	long long phi;
	list <int> primos;
	vector<long long> fila1;
	vector<long long> fila2;
	bool esPrimo (long long );
	void elegirD();
	long long aBinario(long long);
	void generarListaDePrimos();
	void calcularEATAQUE();
	void inicializarMatriz();
	void auxiliarE(bool calculoD);
public:
	RSA(bool inicializar = false);
	/*
	 * si encriptar es true entonces z = e.
	 * sino z = d.
	 */
	RSA(long z, long  n,bool encriptar);
	RSA* duplicar();
	long long getN();
	long long getE();
	long long getD();
	virtual ~RSA();
	void generarPyQ();
	void calcularN();
	void calcularPhi();
	void calcularE();
	long long encriptar(int);
	string encriptar(string);
	string desencriptar(string);
	int desencriptar(long long);
	void atacar();
	string* serializar ();
	void deserializar ();
	void setN (long long n);
	void setD (long long d);
	void setE (long long e);
	void setP (long long);
	void setQ (long long);
};

#endif /* RSA_H_ */
