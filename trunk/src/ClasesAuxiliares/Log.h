/*
 * Log.h
 *
 *  Created on: 14/10/2011
 *      Author: daniel
 */

#ifndef LOG_H_
#define LOG_H_

#include <time.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Configuracion.h"
#include "../Entidades/Votante.h"
#include "../Entidades/Lista.h"

using namespace std;

class Log {
private:
	FILE* archivo;
	void insertarTimestamp();
	void insertarVotante(Votante*,string);
	void insertarEleccion(Eleccion*,string);
	void insertarLista(Lista*,string);
	string convertIntToString(int);
public:
	Log();
	void abrir(Configuracion* configuracion);
	void cerrar();
	void insertarMensajeConEntero(int);
	void insertarMensajeConEntidad(Entidad*,string);
	void insertarMensaje(string);
	void insertarMensajeSeparador (int);
	virtual ~Log();
};

#endif /* LOG_H_ */
