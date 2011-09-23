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
#include "Constantes.h"
#include "Serializable.h"
#include <string>
#include <list>
#include <iostream>

using namespace std;

class Candidato:public Serializable{

private:
	string fecha;		//Identificador
	string cargo;		//Identificador
	string nombre;		//Identificador
	int dni;			//Identificador

public:
	Candidato();
	Candidato(string fecha, string cargo, string nombre, int dni);
	void verCandidato ();
	virtual ~Candidato();
	string* serializar();
	void deserializar(string*);

};

#endif /* CANDIDATO_H_ */
