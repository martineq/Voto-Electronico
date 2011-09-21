/*
 * HashingExtensible.cpp
 *
 *  Created on: 21/09/2011
 *      Author: lÑ#$dsa44
 */

#include "HashingExtensible.h"

HashingExtensible::HashingExtensible() {
	this->archivo = NULL;
}

int HashingExtensible::obtenerPosicion(int clave){
	//TODO
	// Falta emplear una función para transformar la clave en un hash
	int hash = clave;

	int n = log(this->tablaDeHash.size())/log(2);
	int posicion = hash & n;

	return posicion;
}

HashingExtensible::HashingExtensible(FILE* archivo){
	this->archivo = archivo;
}

int HashingExtensible::agregarRegistro(int clave,string elemento){
	int bloque;
	int posicion;
	vector<int>::iterator it;

	posicion = this->obtenerPosicion(clave);
	it 		 = this->tablaDeHash.end();

	if ( this->tablaDeHash.size() == 0 ){
		bloque = 0;
		this->tablaDeHash.insert(it,bloque);
		// BLOQUE = crearBloque(this->archivo);			//manejador de archivos
		// insertarRegistro(BLOQUE,string);				//manejador de bloques
		// guardarBloque(this->archivo, BLOQUE);		//manejador de archivos
		//agregar el string en el archivo en el bloque0
	}else{

	}
	return 0;
}

int HashingExtensible::modificarRegistro(int clave,string elemento){
	//TODO
	return 0;
}

int HashingExtensible::eliminarRegistro(int clave){
	//TODO
	return 0;
}

HashingExtensible::~HashingExtensible() {
	// TODO Auto-generated destructor stub
}

