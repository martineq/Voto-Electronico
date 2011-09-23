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

int HashingExtensible::obtenerDispersion(int bloque){
	//TODO
	//BLOQUE = leerBloque(this->archivo,bloque);
	return 0;

}

HashingExtensible::HashingExtensible(FILE* archivo){
	this->archivo = archivo;
	// reservar bloque 0 del archivo para metadata del hashing
	// la tabla de Hashing
	// la tabla de dispersion
}

int HashingExtensible::agregarRegistro(InterpreteDeRegistro* interprete,string* bytes){
	int bloque;
	int bloqueCompleto;
	unsigned int dispersion;
	int posicion;
	vector<int>::iterator it;

	int clave = interprete->obtenerClave(bytes);

	posicion = this->obtenerPosicion(clave);

	if ( this->tablaDeHash.size() == 0 ){

		this->tablaDeHash.push_back(bloque = 1);
		this->tablaDeDispersion.push_back(dispersion = 1);

		// Almaceno el bloque en el archivo
		// BLOQUE = crearBloque(this->archivo);					//manejador de archivos
		// insertarRegistro(BLOQUE,string);						//manejador de bloques
		// guardarBloque(this->archivo, BLOQUE);				//manejador de archivos

	}else{

		bloque = this->tablaDeHash.at(posicion);
		//BLOQUE = leerBloque(this->archivo,);
		// bloqueCompleto = insertarRegistro(BLOQUE,string);	//manejador de bloques

		bloqueCompleto = 0; //cambiar intruccion

		if (!bloqueCompleto){
			// guardarBloque(this->archivo, BLOQUE);			//manejador de archivos

		}else{
			dispersion = obtenerDispersion(bloque);
			if ( dispersion == this->tablaDeHash.size() ){

				// Se duplica la tabla
				it 	= this->tablaDeHash.end();
				this->tablaDeHash.insert(it,this->tablaDeHash.begin(),it);

				// Se duplica el tamaño del elemento en dispersion
				this->tablaDeDispersion[bloque] = 2*dispersion;
				// debería también disminuirse en el bloque correspondiente

				// Se agrega un nuevo bloque en la posicion actual
				int tamanioTabla = this->tablaDeHash.size();
				this->tablaDeDispersion.push_back(tamanioTabla);
				int ultimoBloque = this->tablaDeDispersion.size()-1;
				this->tablaDeHash[posicion] = ultimoBloque;

				// redispersar registros en bloque actual
				// vaciarBloque(BLOQUE)
				// while (!bloqueVacio(BLOQUE)) {
				// 		registro  = leerRegistro()
				//		clave_aux = obtenerClave()
				//		agregarRegistro(clave_aux,registro)
				//}

				// Reintento agregar el registro que generó la redispersion
			//	agregarRegistro(clave,elemento);


			}else{
				// no se duplica la tabla
			}

		}
	}
	return 0;
}

int HashingExtensible::modificarRegistro(InterpreteDeRegistro* interprete,string* elemento){
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

