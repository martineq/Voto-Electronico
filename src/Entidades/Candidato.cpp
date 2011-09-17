/*
 * Candidato.cpp
 *
 *  Created on: 17/09/2011
 *      Author: mart
 */

#include "Candidato.h"

Candidato::Candidato() {
	this->fecha="";
	this->cargo="";
	this->nombre="";
	this->dni=0;
}

Candidato::Candidato( string fecha, string cargo, string nombre, int dni) {
	this->fecha=fecha;
	this->cargo=cargo;
	this->nombre=nombre;
	this->dni=dni;
}

Candidato::~Candidato() {

}
