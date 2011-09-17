/*
 * Distrito.cpp
 *
 *  Created on: 17/09/2011
 *      Author: martin
 */

#include "Distrito.h"

Distrito::Distrito(){
	this->distrito = "";
};

Distrito::Distrito(string distrito){
		this->distrito = distrito;
	}

string Distrito::getDistrito(){
		return this->distrito;
	}

void Distrito::setDistrito(string distrito){
		this->distrito = distrito;
	}

Distrito::~Distrito(){};
