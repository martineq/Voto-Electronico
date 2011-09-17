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
	if ( this->nombre.compare(nomb) and this->password.compare(pass) ) return true;
	else return false;
}

Administrador::~Administrador() {

}
