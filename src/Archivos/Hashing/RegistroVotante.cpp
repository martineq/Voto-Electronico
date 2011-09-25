/*
 * RegistroVotante.cpp
 *
 *  Created on: 22/09/2011
 *      Author: lÑ#$dsa44
 */

#include "RegistroVotante.h"

RegistroVotante::RegistroVotante() {
	this->contenido = new Votante();
	this->funcion = new HashingVotante();

}

int RegistroVotante::obtenerClave(){
	//TODO
	return 0;
}

Entidad* RegistroVotante::getContenido(){
	return this->contenido;
}

string* RegistroVotante::serializar(){

}

void RegistroVotante::deserializar(string * source){

}


RegistroVotante::~RegistroVotante() {
	// TODO Auto-generated destructor stub
}

