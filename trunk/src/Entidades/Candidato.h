/*
 * Candidato.h
 *
 *  Created on: 17/09/2011
 *      Author: mart
 */

#ifndef CANDIDATO_H_
#define CANDIDATO_H_
//Candidato ( ( (lista)ie, (votante)ie, (cargo)ie)i )
//Candidato ( (fecha),(cargo),(nombre),(dni), (cargo) )

#include <string>
using namespace std;


class Candidato {
private:
	string fecha;
	string cargo;
	string nombre;
	int dni;


public:
	Candidato();
	virtual ~Candidato();

};

#endif /* CANDIDATO_H_ */
