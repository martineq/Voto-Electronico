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
//	cantidadDeBytes   = this->fecha.size();
//	buffer.write((char*)&cantidadDeBytes,TAM_INT);
//	buffer.write((char*)this->fecha.c_str(),cantidadDeBytes);
	buffer.write((char*)this->fecha.c_str(),TAM_FECHA);
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
	stringstream * miString;
	delete source;
	int cantidadDeBytes;

//	hidrato la fecha
//	buffer.read((char*)&cantidadDeBytes,TAM_INT);
//	char* fechaSerializada = new char[cantidadDeBytes];
//	buffer.read((char*)fechaSerializada,cantidadDeBytes);
	char* fechaSerializada = new char[TAM_FECHA];
	buffer.read((char*)fechaSerializada,TAM_FECHA);

	miString = new stringstream();
	miString->write(fechaSerializada,TAM_FECHA);
	string* pasoAString = new string (miString->str());
	this->fecha = *pasoAString;
	delete []fechaSerializada;
	delete pasoAString;
	delete miString;

//  hidrato el cargo principal
	buffer.read((char*)&cantidadDeBytes,TAM_INT);
	char* cargoSerializado = new char[cantidadDeBytes];
	buffer.read((char*)cargoSerializado,cantidadDeBytes);
	miString = new stringstream();
	miString->write(cargoSerializado,cantidadDeBytes);
	pasoAString = new string (miString->str());
	this->cargo = *pasoAString;
	delete []cargoSerializado;
	delete pasoAString;
	delete miString;

//	hidrato la nombre
	buffer.read((char*)&cantidadDeBytes,TAM_INT);
	char* nombreSerializado = new char[cantidadDeBytes];
	buffer.read((char*)nombreSerializado,cantidadDeBytes);
	miString = new stringstream();
	miString->write(nombreSerializado,cantidadDeBytes);
	pasoAString = new string (miString->str());
	this->nombre = *pasoAString;
	delete []nombreSerializado;
	delete pasoAString;
	delete miString;

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
