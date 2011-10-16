/*
 * Configuracion.h
 *
 *  Created on: 15/10/2011
 *      Author: mart
 */

#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "./Archivos/EnBloques/ManejadorDeArchivo.h"

using namespace std;


class Configuracion {
private:

	string rutaConfig;
	string rutaHash;
	string rutaArbol;
	bool vAuto;
	bool vManual;
	void cargarArgumentos(int argc, const char** argv);
	void cargarchivoConfig();

public:

	Configuracion(int argc, const char** argv);
	virtual ~Configuracion();

	string pathHash();
	string pathArbol();
	bool isAuto();
	bool isManual();

};


#endif /* CONFIGURACION_H_ */
