/*
 * Conteo.cpp
 *
 *  Created on: 08/10/2011
 *      Author: lucas
 */

#include "Conteo.h"

Conteo::Conteo() {
	fechaEleccion = "18991231";
	cargoEleccion = "";
	nombreLista = "";
	distrito = "";
	cantidadVotos = 0;
}

Conteo::Conteo(string fecha,string cargo,string lista,string distrito){
	this->fechaEleccion = fecha;
	this->cargoEleccion = cargo;
	this->nombreLista = lista;
	this->distrito = distrito;
	this->cantidadVotos = 0;
}

int Conteo::getTamanio(){
	int tamFecha    = this->fechaEleccion.length(); //por default siempre es 8
	int tamCargo    = TAM_INT + this->cargoEleccion.length();
	int tamLista    = TAM_INT + this->nombreLista.length();
	int tamDistrito = TAM_INT + this->distrito.length();
	int tamVotos    = TAM_INT;
	return (tamFecha + tamCargo + tamLista + tamDistrito + tamVotos);
}

int Conteo::getClave(){

}

string Conteo::getFechaEleccion(){
	return this->fechaEleccion;
}

string Conteo::getCargoEleccion(){
	return this->cargoEleccion;
}

string Conteo::getLista(){
	return this->nombreLista;
}

unsigned int Conteo::getCantidadVotos(){
	return this->cantidadVotos;
}

void Conteo::incrementarVotos(){
	this->cantidadVotos++;
}

void Conteo::decrementarVotos(){
	this->cantidadVotos--;
}
/*
 * Instancia un nuevo objeto, copia de actual.
 */
Entidad* Conteo::duplicar(){

}

string* Conteo::serializar(){

}

void Conteo::deserializar(string*){

}

NombreDeEntidad Conteo::getNombreDeEntidad(){
	return tConteo;
}



Conteo::~Conteo() {
	// TODO Auto-generated destructor stub
}
