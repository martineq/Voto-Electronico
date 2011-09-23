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

string* Distrito::serializar(){
	stringstream streamDatos;
	int sizeOfDistrito = this->distrito.size();
	streamDatos.write((char*)&sizeOfDistrito,TAM_INT);
	streamDatos.write((char*)distrito.c_str(),sizeOfDistrito);
	string* datos = new string(streamDatos.str());
	return datos;
}

void Distrito::deserializar(string * source){
	istringstream streamDatos(*source);
	delete source;
	stringstream * miString = new stringstream();
	int sizeOfDistrito;
    streamDatos.read((char*)&sizeOfDistrito,TAM_INT);
    char* distritoChar = new char[sizeOfDistrito];
    streamDatos.read((char*)distritoChar,sizeOfDistrito);
    miString->write(distritoChar,sizeOfDistrito);
    string distritoString = miString->str();
    this->distrito = distritoString;
    delete []distritoChar;
    delete miString;
}



Distrito::~Distrito(){};
