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
	streamDatos.write((char*)&cargo,sizeOfCargo);
	streamDatos.write((char*)&cantCargos,TAM_INT);
	for (unsigned int i = 0; i < cantCargos;i++){
		sizeOfCargo = it->size();
		subCargo = (*it);
		streamDatos.write((char*)&sizeOfCargo,TAM_INT);
		streamDatos.write((char*)&subCargo,sizeOfCargo);
		it++;
		cout <<"Serializar Subcargo: "<<subCargo<<endl;
	}
	string* datos = new string(streamDatos.str());
	return datos;

}

void Cargo::deserializar(string * source){
	istringstream streamDatos(*source);
	int sizeOfCargo;
	unsigned int cantCargos;
	string subCargo;

    streamDatos.read((char*)&sizeOfCargo,TAM_INT);
    streamDatos.read((char*)&(this->cargo),sizeOfCargo);
    streamDatos.read((char*)&cantCargos,TAM_INT);
    cout << "CantCargos: "<<cantCargos<<endl;
//	cout <<"Size of Lista deserializar antes hidratar: "<<this->listaCargos.size();
	for (unsigned int i = 0; i < cantCargos;i++){
//		string subCargo;
		subCargo = "";
		sizeOfCargo = 0;
		streamDatos.read((char*)&sizeOfCargo,TAM_INT);
		streamDatos.read((char*)&subCargo,sizeOfCargo);
		this->listaCargos.push_back(subCargo);
		cout <<"DeSerializar Subcargo: "<<subCargo<<endl;
		cout << "Size interno: "<<this->listaCargos.size()<<endl;
	}
	cout <<"Size of Lista deserializar: "<<this->listaCargos.size()<<endl;
}
