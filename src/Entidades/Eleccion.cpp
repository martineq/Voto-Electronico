/*
 * Eleccion.cpp
 *
 *  Created on: 17/09/2011
 *      Author: martin
 */

#include "Eleccion.h"

Eleccion::Eleccion() {
	this->fecha = "";
	this->cargoPrincipal = "";

}

Eleccion::Eleccion(string fecha,string cargoPrincipal){
	this->fecha 		= fecha;
	this->cargoPrincipal= cargoPrincipal;
}

string Eleccion::getFecha(){
	return this->fecha;
}

void Eleccion::setFecha(string fecha){
	this->fecha = fecha;
}

string Eleccion::getCargo(){
	return this->cargoPrincipal;
}

void Eleccion::setCargo(string cargoPrincipal){
	this->cargoPrincipal = cargoPrincipal;
}

bool Eleccion::agregarDistrito(Distrito distrito){
	bool encontrado = false;
	list<Distrito>::iterator iterador = this->distritos.begin();
	while (iterador != this->distritos.end() and (!encontrado)){
		if ((iterador->getDistrito()).compare(distrito.getDistrito()) == 0){
			encontrado = true;
		}
		iterador++;
	}
	if (!encontrado){
		this->distritos.push_back(distrito);
	}
	return (!encontrado); //devuelve el resultado de la inserción
}

bool Eleccion::eliminarDistrito(Distrito distrito){
	bool encontrado = false;
	list<Distrito>::iterator iterador = this->distritos.begin();
	while( iterador != this->distritos.end() and !encontrado ){
		if( (iterador->getDistrito().compare(distrito.getDistrito()))==0){
			encontrado = true;
			this->distritos.erase(iterador);
		}
		iterador++;
	}
	return (!encontrado); //devuelve el resultado de la inserción
}

list<Distrito> Eleccion::getLista(){
	return this->distritos;
}

list<Distrito>::iterator Eleccion::obtenerIterador(){
	list<Distrito>::iterator iterador = this->distritos.begin();
	return iterador;
}


Eleccion::~Eleccion() {
	// TODO Auto-generated destructor stub
}
