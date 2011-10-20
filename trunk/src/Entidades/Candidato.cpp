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

Candidato::Candidato(string fecha, string cargo, string nombre, int dni) {
	this->fecha=fecha;
	this->cargo=cargo;
	this->nombre=nombre;
	this->dni=dni;
}

Candidato::~Candidato() {

}

string* Candidato::serializar() {
	int fechaInt;
	Serializadora serializadora;

	stringstream fechaStream (fecha);
	fechaStream >> fechaInt;

	serializadora.agregarInt(fechaInt);
	serializadora.agregarString(&cargo);
	serializadora.agregarString(&nombre);
	serializadora.agregarInt(dni);

	return serializadora.obtenerSerializacion();
}

void Candidato::deserializar(string* source) {

	Serializadora serializadora(source);

	stringstream fechaStream;
	fechaStream << serializadora.obtenerInt();

	fecha 	= fechaStream.str();
	cargo 	= serializadora.obtenerString();
	nombre 	= serializadora.obtenerString();
	dni 	= serializadora.obtenerInt();
}

void Candidato::verCandidato() {
	cout << "Nombre: " << this->nombre << endl;
	cout << "Cargo: "  << this->cargo  << endl;
	cout << "DNI: "    << this->dni    << endl;
	cout << "Fecha de eleccion: " << this->fecha << endl;
}

void Candidato::verEntidad(){
	verCandidato();
}

int Candidato::getTamanio(){
	int tamanioFecha 	= TAM_INT;
	int tamanioCargo 	= TAM_INT + cargo.size();
	int tamanioNombre 	= TAM_INT + nombre.size();
	int tamanioDni 		= TAM_INT;

	return (tamanioCargo + tamanioDni + tamanioFecha + tamanioNombre);
}

unsigned long Candidato::getClave(){
//	int c = 0;
//	int size = fecha.length();
//
//	for (int i=0; i < size ; i++)
//		c += (int)this->fecha[i];
//
//	size = cargo.length();
//	for (int i=0; i< size ; i++)
//		c += (int)this->cargo[i];
//
//
//	size = nombre.length();
//	for (int i=0; i < size; i++)
//		c += (int)this->nombre[i];

	  string stringClave = this->fecha + this->cargo + this->nombre;
	  locale loc;                 // the "C" locale

	  const collate<char>& coll = use_facet<collate<char> >(loc);

	  unsigned long myhash = coll.hash(stringClave.data(),stringClave.data()+stringClave.length());

	  return myhash;

}

Entidad *Candidato::duplicar()
{
	Candidato * copia = new Candidato();
	copia->cargo = this->cargo;
	copia->dni = this->dni;
	copia->fecha = this->fecha;
	copia->nombre = this->nombre;
	return  copia;
}

NombreDeEntidad Candidato::getNombreDeEntidad(){
	return tCandidato;
}

ResultadoComparacion Candidato::comparar(Entidad* entidad){
	if ( tCandidato != entidad->getNombreDeEntidad() ){
		return comparacionInvalida;
	}
	Candidato* candidatoNuevo = (Candidato*) entidad;
	int compararFecha = this->fecha.compare(candidatoNuevo->fecha);
	int compararCargo = this->cargo.compare(candidatoNuevo->cargo);
	int compararLista = this->nombre.compare(candidatoNuevo->nombre);
	if (compararFecha < 0){
		return menor;
	}
	if (compararFecha > 0){
		return mayor;
	}
	if (compararCargo < 0){
		return menor;
	}
	if (compararCargo > 0){
		return mayor;
	}
	if (compararLista < 0){
		return menor;
	}
	if (compararLista > 0){
		return mayor;
	}
	if (this->dni < candidatoNuevo->dni) {
		return menor;
	}
	if (this->dni > candidatoNuevo->dni){
		return mayor;
	}
	return igual;
}
