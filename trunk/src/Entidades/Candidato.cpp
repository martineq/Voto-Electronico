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
	stringstream buffer;
	int cantidadDeBytes;
	cantidadDeBytes   = this->fecha.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->fecha.c_str(),cantidadDeBytes);
	cantidadDeBytes   = this->cargo.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->cargo.c_str(),cantidadDeBytes);
	cantidadDeBytes   = this->nombre.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->nombre.c_str(),cantidadDeBytes);
	buffer.write((char*)&this->dni,TAM_INT);
	string* datos = new string(buffer.str());
	return datos;
}

void Candidato::deserializar(string* source) {
	istringstream buffer (*source);
	delete source;
	int cantidadDeBytes;

//	hidrato la fecha
	buffer.read((char*)&cantidadDeBytes,TAM_INT);
	char* fechaSerializada = new char[cantidadDeBytes];
	buffer.read((char*)fechaSerializada,cantidadDeBytes);
	string* pasoAString = new string (fechaSerializada);
	this->fecha = *pasoAString;
	delete []fechaSerializada;
	delete pasoAString;

//  hidrato el cargo principal
	buffer.read((char*)&cantidadDeBytes,TAM_INT);
	char* cargoSerializado = new char[cantidadDeBytes];
	buffer.read((char*)cargoSerializado,cantidadDeBytes);
	pasoAString = new string (cargoSerializado);
	this->cargo = *pasoAString;
	delete []cargoSerializado;
	delete pasoAString;

//	hidrato la nombre
	buffer.read((char*)&cantidadDeBytes,TAM_INT);
	char* nombreSerializado = new char[cantidadDeBytes];
	buffer.read((char*)nombreSerializado,cantidadDeBytes);
	pasoAString = new string (nombreSerializado);
	this->nombre = *pasoAString;
	delete []nombreSerializado;
	delete pasoAString;

//	hidrato dni
	buffer.read((char*)&this->dni,TAM_INT);
}

void Candidato::verCandidato() {
	cout << "Nombre: " << this->nombre << endl;
	cout << "Cargo: "  << this->cargo  << endl;
	cout << "DNI: "    << this->dni    << endl;
	cout << "Fecha de eleccion: " << this->fecha << endl;
}

int Candidato::getTamanio(){
	int tamanioCargo = TAM_INT + this->cargo.size();
	int tamanioDni = TAM_INT;
	int tamanioFecha = this->fecha.size(); //por definición siempre va a ser 8
	int tamanioNombre = TAM_INT + this->nombre.size();
	return (tamanioCargo + tamanioDni + tamanioFecha + tamanioNombre);
}

int Candidato::getClave(){
	return 0;
}

NombreDeEntidad Candidato::getNombreDeEntidad(){
	return tCandidato;
}
