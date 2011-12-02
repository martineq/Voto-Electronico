/*
 * CreadorVotante.h
 *
 *  Created on: 10/10/2011
 *      Author: lucas
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "Configuracion.h"
#include "../Entidades/Votante.h"


#ifndef CREADORVOTANTE_H_
#define CREADORVOTANTE_H_

using namespace std;

class CreadorVotante {
private:
	int		semilla;

	string getNombre(string path);
	string getApellido(string path);
	int getDNI();
	string getClave();
	string getDomicilio(string path);
	string getDistrito(string path);
	int getCantLineas(string path);

public:
	CreadorVotante(int seed);
	Votante* crearVotante(Configuracion* configuracion);
	Votante* crearVotante(Configuracion* configuracion, RSA* rsa);
	virtual ~CreadorVotante();
};

#endif /* CREADORVOTANTE_H_ */
