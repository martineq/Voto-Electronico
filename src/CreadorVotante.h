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
#include "./Entidades/Votante.h"


#ifndef CREADORVOTANTE_H_
#define CREADORVOTANTE_H_

using namespace std;

class CreadorVotante {
private:

	int		semilla;

	string getNombre();
	string getApellido();
	int getDNI();
	string getClave();
	string getDomicilio();
	string getDistrito();
	int getCantLineas(string path);

public:
	CreadorVotante(int seed);
	Votante* crearVotante();
	virtual ~CreadorVotante();
};

#endif /* CREADORVOTANTE_H_ */
