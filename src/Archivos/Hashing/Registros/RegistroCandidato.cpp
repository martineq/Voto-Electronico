/*
 * RegistroCandidato.cpp
 *
 *  Created on: 22/09/2011
 *      Author: lÑ#$dsa44
 */

#include "RegistroCandidato.h"

RegistroCandidato::RegistroCandidato() {
	// TODO Auto-generated constructor stub

}

int RegistroCandidato::obtenerClave(){
	this->contenido->serializar();
	return 0;
}

Entidad* RegistroCandidato::getContenido(){
	return this->contenido;
}


string* RegistroCandidato::serializar(){

}

void RegistroCandidato::deserializar(string * source){

}



RegistroCandidato::~RegistroCandidato() {
	// TODO Auto-generated destructor stub
}

