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

int Candidato::getTamanio(){
	int tamanioFecha 	= TAM_INT;
	int tamanioCargo 	= TAM_INT + cargo.size();
	int tamanioNombre 	= TAM_INT + nombre.size();
	int tamanioDni 		= TAM_INT;

	cout << "** tamanio candidato : " << tamanioCargo+tamanioDni+tamanioFecha+tamanioNombre << endl;
	cout << "** tamanio serializado: " << serializar()->size() << endl;
	return (tamanioCargo + tamanioDni + tamanioFecha + tamanioNombre);
}

int Candidato::getClave(){
	int c = 0;
	int size = fecha.length();

	for (int i=0; i < size ; i++)
		c += (int)this->fecha[i];

	size = cargo.length();
	for (int i=0; i< size ; i++)
		c += (int)this->cargo[i];


	size = nombre.length();
	for (int i=0; i < size; i++)
		c += (int)this->nombre[i];

	return c;
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
