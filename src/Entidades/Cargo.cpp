/*
 * Cargo.cpp
 *
 *  Created on: 17/09/2011
 *      Author: lucas
 */

#include "Cargo.h"

Cargo::Cargo() {
	this->cargo = "";
}

Cargo::Cargo(string cargoPrincipal){
	this->cargo = cargoPrincipal;
}

/*
void Cargo::modificarCargo(string nuevoCargo){
	this->Cargo = nuevoCargo;
}*/

string Cargo::getCargo(){
	return this->cargo;
}

list<string> Cargo::devolverSubCargos(){
	return this->listaCargos;
}

bool Cargo::agregarCargo(string subCargo){
	bool repetido = false;
	list<string>::iterator it = this->listaCargos.begin();
	while (it != this->listaCargos.end() and (!repetido)){
		if (it->compare(subCargo) == 0){
			repetido = true;
		}
		it++;
	}
	if (!repetido){
		this->listaCargos.push_back(subCargo);
	}
	return (!repetido); //devuelve el resultado de la inserción
}

bool Cargo::eliminarCargo(string subCargo){
	bool existeCargo = false;
	list<string>::iterator it = this->listaCargos.begin();
	while (it != this->listaCargos.end() and (!existeCargo)){
		if (it->compare(subCargo) == 0){
			existeCargo = true;
			this->listaCargos.erase(it);
		}
		it++;
	}
	return existeCargo;
}

int Cargo::getTamanio(){
	int tamanioCargo = TAM_INT + this->cargo.size();
	int tamanioLista = TAM_INT * this->listaCargos.size();
	list<string>::iterator it = this->listaCargos.begin();
	while (it != this->listaCargos.end()){
		tamanioLista += it->size();
	}
	return (tamanioCargo + tamanioLista);
}

int Cargo::getClave(){
	return 0;
}


Cargo::~Cargo() {
	this->listaCargos.clear();
}



string* Cargo::serializar(){
	stringstream streamDatos;
	int sizeOfCargo = this->cargo.size();
	list<string>::iterator it = this->listaCargos.begin();
	unsigned int cantCargos = this->listaCargos.size();
	string subCargo;
	streamDatos.write((char*)&sizeOfCargo,TAM_INT);
	streamDatos.write((char*)cargo.c_str(),sizeOfCargo);
	streamDatos.write((char*)&cantCargos,TAM_INT);
	for (unsigned int i = 0; i < cantCargos;i++){
		sizeOfCargo = it->size();
		subCargo = (*it);
		streamDatos.write((char*)&sizeOfCargo,TAM_INT);
		streamDatos.write((char*)subCargo.c_str(),sizeOfCargo);
		it++;
	}
	string* datos = new string(streamDatos.str());
	return datos;

}

void Cargo::deserializar(string * source){
	istringstream streamDatos(*source);
	delete source;
	int sizeOfCargo;
	unsigned int cantCargos;
    streamDatos.read((char*)&sizeOfCargo,TAM_INT);
    char* cargoChar = new char[sizeOfCargo];
    streamDatos.read((char*)cargoChar,sizeOfCargo);
    string cargoString(cargoChar);
    delete [] cargoChar;
    this->cargo = cargoString;
    streamDatos.read((char*)&cantCargos,TAM_INT);
	for (unsigned int i = 0; i < cantCargos;i++){
		streamDatos.read((char*)&sizeOfCargo,TAM_INT);
		stringstream * miString = new stringstream();
		char* cargoTemp = new char[sizeOfCargo];
		streamDatos.read(cargoTemp,sizeOfCargo);
		miString->write(cargoTemp,sizeOfCargo);
		string subCargo = miString->str();
		this->listaCargos.push_back(subCargo);
		delete [] cargoTemp;
		delete miString;
	}
}

Entidad *Cargo::duplicar()
{
	Cargo * copia = new Cargo();
	copia->cargo = this->cargo;
	list<string>::iterator it = this->listaCargos.begin();
	while (it != this->listaCargos.end()){
		copia->agregarCargo(*it);
	}
	return copia;
}

NombreDeEntidad Cargo::getNombreDeEntidad(){
	return tCargo;
}
