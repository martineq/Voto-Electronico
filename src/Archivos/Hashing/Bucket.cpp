/*
 * Bucket.cpp
 *
 *  Created on: 23/09/2011
 *      Author: lÑ#$dsa44
 */

#include "Bucket.h"

Bucket::Bucket(int tamanioDispersion){
	this->tamanioDeDispersion=tamanioDispersion;
	this->espacioLibre=LONGITUD_BLOQUE;
}

Registro* Bucket::getRegistro(int clave){
	if (this->listaDeRegistros.empty()) return NULL;
	else {
		list<Registro*>::iterator it = this->listaDeRegistros.begin();
		while (it!=listaDeRegistros.end()) {
			int claveDeRegistroActual = (*it)->obtenerClave();
			if (claveDeRegistroActual==clave) return *it;
			it++;
		}
	}
	return NULL;
}

//devuelve el resultado de la operacion
bool Bucket::agregarRegistro(Registro* unRegistro){
	if (this->getRegistro(unRegistro->obtenerClave())!=NULL) return false;
	else
		if ((int)sizeof(unRegistro)>this->espacioLibre) return false;
		else {
			this->listaDeRegistros.push_back(unRegistro);
			this->espacioLibre-=sizeof(unRegistro);
			return true;
		}
}

bool Bucket::eliminarRegistro(int clave){
	if (this->listaDeRegistros.empty()) return false;
	else {
		if (this->getRegistro(clave)==NULL) return false;
		else {
			list<Registro*>::iterator it = this->listaDeRegistros.begin();
			while (it!=listaDeRegistros.end()) {
				int claveDeRegistroActual = (*it)->obtenerClave();
				if (claveDeRegistroActual==clave) {
					this->espacioLibre+=sizeof(*it);
					this->listaDeRegistros.erase (it);
					return true;
				}
			}
		}
	}
}

bool Bucket::reemplazarRegistro(Registro* unRegistro){
	if (this->listaDeRegistros.empty()) return false;
	else {
		int clave=unRegistro->obtenerClave();
		if (this->eliminarRegistro(clave))
			if (this->agregarRegistro(unRegistro)) return true;
			else return false;
		else return false;
	}
}

int Bucket::getEspacioLibre (){return this->espacioLibre;}
int Bucket::getTamanioDeDispersion (){return this->tamanioDeDispersion;}
int Bucket::getCantidadDeRegistros () {return this->listaDeRegistros.size();}
void Bucket::setTamanioDeDispersion (int tamanio){this->tamanioDeDispersion=tamanio;}
list<Registro*>::iterator Bucket::ubicarPrimero(){
	list<Registro*>::iterator it = this->listaDeRegistros.begin();
	return it;
}

string* Bucket::serializar(){string* hola; return hola;}
void Bucket::deserializar(string* source){}
Bucket::~Bucket() {}
