/*
 * Administrador.cpp
 *
 *  Created on: 17/09/2011
 *      Author: mart
 */

#include "Administrador.h"

Administrador::Administrador() {
	this->nombre="";
	this->password="";
}

Administrador::Administrador(string nomb, string pass) {
	this->nombre=nomb;
	this->password=pass;
}

bool Administrador::acceder(string nomb,string pass){
	if ((this->nombre==nomb) && (this->password==pass)) return true;
	else return false;
}

bool Administrador::alta (Bucket* bucket,Registro* unRegistro){
	return bucket->agregarRegistro(unRegistro);
}

Administrador::~Administrador() {

}
