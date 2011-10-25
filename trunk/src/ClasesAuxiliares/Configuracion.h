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
#include "../Archivos/EnBloques/ManejadorDeArchivo.h"

using namespace std;

class Configuracion {
private:
	string rutaConfig;
	string rutaHash;
	string rutaArbol;
	string rutaPass;

	string rutaApellidos;
	string rutaDistritos;
	string rutaDomicilios;
	string rutaNombres;
	string rutaLog;

	int tamanioNodo;
	int tamanioBucket;
	bool vAuto;
	bool vManual;
	void cargarArgumentos(int argc, const char** argv);
	void cargarArchivoConfig();
	void mostrarAyuda();
	void mostrarVersion();

public:
	Configuracion(int argc, const char** argv);
	string pathHash();
	string pathArbol();
	string pathPassword();

	string pathApellidos();
	string pathNombres();
	string pathDomicilios();
	string pathDistritos();
	string pathLog();

	bool isAuto();
	bool isManual();
	int darTamanioNodo();
	int darTamanioBucket();
	virtual ~Configuracion();
};

#endif /* CONFIGURACION_H_ */
