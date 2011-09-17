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
