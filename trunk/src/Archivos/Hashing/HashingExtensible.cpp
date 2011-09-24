/*
 * HashingExtensible.cpp
 *
 *  Created on: 21/09/2011
 *      Author: daniel
 */

#include "HashingExtensible.h"

int HashingExtensible::obtenerDispersion(int bloque){
	//TODO
	//BLOQUE = leerBloque(this->archivo,bloque);
	return 0;

}

int HashingExtensible::numeroPosicionesAreemplazar(int numeroDeBucket){
	int dispersion = this->obtenerDispersion(numeroDeBucket);
	int repeticionesBloque = dispersion / this->tablaDeHash.size();
	return repeticionesBloque/2;
}

HashingExtensible::HashingExtensible(){;}

HashingExtensible::HashingExtensible(ArchivoBloques* archivoBloques) {
	char* R;
	this->archivo = archivoBloques;

	// Al crear el hashing creo el bloque 0 en forma lógica
	// el mismo tiene dispersion 1;
	int numeroDeBucket = 0;
	this->tablaDeHash.push_back( numeroDeBucket );
	int dispersion = this->tablaDeHash.size();
	this->tablaDeDispersion.push_back( dispersion );

	// Almaceno el bloque 0 en el archivo
	bucket = new Bucket(dispersion);
	//char* R = bucket->serializar();
	this->archivo->guardarBloque(numeroDeBucket,R);

}

int HashingExtensible::obtenerPosicion(int clave){
	//TODO
	// Falta emplear una función para transformar la clave en un hash
	int hash = clave;

	int n = log(this->tablaDeHash.size())/log(2);
	int posicion = hash & n;

	return posicion;
}

int HashingExtensible::agregarRegistro(InterpreteDeRegistro* interprete,string* bytes){
	int numeroDeBucket;
	char* R;
	string* B;
	int bucketCompleto;
	int posicion;
	Bucket* bucket;
	Bucket* bucketActualizado;
	vector<int>::iterator it;

	int dispersionNuevoBucket;
	int dispersionBucketActualizado;

	//Obtener clave es la función de hashing
	int clave = interprete->obtenerClave(bytes);

	// Se aplica la "función modulo" para obtener la posicion de la tabla aplicando el logaritmo en base 2 del tamaño de la tabla.
	posicion = this->obtenerPosicion(clave);

	numeroDeBucket = this->tablaDeHash.at(posicion);
	bucket = new Bucket();
	//string* B = this->archivo->obtenerBloque(numeroDeBucket);
	bucket->deserializar(B);
	bucketCompleto = bucket->agregarRegistro(bytes->length(),clave,bytes);	//manejador de bloques

	if (!bucketCompleto){
		//char* R = bucket->serializar();
		this->archivo->guardarBloque(numeroDeBucket,R);

	}else{
		// Se agrega un nuevo numeroDeBucket en la posicion actual
		int nuevoNumeroDeBucket = this->tablaDeDispersion.size();

		// Determina cuantas posiciones en la tabla de Hash serán reemplazadas
		int posicionesAreemplazar = numeroPosicionesAreemplazar(numeroDeBucket);

		if ( posicionesAreemplazar == 0 ){
			// Se duplica la tabla
			it 	= this->tablaDeHash.end();
			this->tablaDeHash.insert(it,this->tablaDeHash.begin(),it);
			this->tablaDeHash[posicion] = nuevoNumeroDeBucket;

			// Se calculan los nuevos tamaños de dispersion, del bucket a redispersar y del nuevo bucket.
			dispersionBucketActualizado = 2 * tablaDeDispersion[numeroDeBucket];
			dispersionNuevoBucket 		 = tablaDeDispersion[nuevoNumeroDeBucket];

		}else{
			// Se calculan los nuevos tamaños de dispersion, del bucket a redispersar y del nuevo bucket.
			dispersionBucketActualizado = 2 * tablaDeDispersion[numeroDeBucket];
			dispersionNuevoBucket 		 = dispersionBucketActualizado;

			// Actualiza la tabla de hash incoorporando el valor del nuevo bloque.
			while (posicionesAreemplazar > 0){
				posicionesAreemplazar--;
				this->tablaDeHash[posicion+posicionesAreemplazar*dispersionNuevoBucket] = nuevoNumeroDeBucket;
			}
		}

		// Se actualiza la dispersion del bucket a redispersar.
		this->tablaDeDispersion[numeroDeBucket] = dispersionBucketActualizado;

		// Se agrega la dispersión del nuevo bloque
		this->tablaDeDispersion.push_back(dispersionNuevoBucket);

		// Se crea el nuevo Bucket.
		Bucket* nuevoBucket = new Bucket(dispersionNuevoBucket);
		//R = nuevoBucket->serializar();
		this->archivo->guardarBloque(numeroDeBucket,R);

		// Se crea un nuevo Bucket para redispersar los elementos.
		Bucket* bucketActualizado = new Bucket(dispersionBucketActualizado);
		//R = bucketActualizado->serializar();
		this->archivo->guardarBloque(numeroDeBucket,R);

		// Se redispersan registros en bloque actual
		// string* registro = obtenerRegistro();
		// while (!bloqueVacio(BLOQUE)) {
		//		clave_aux = obtenerClave(registro);
		//		this->agregarRegistro(registro.lenght(),clave_aux,registro);
		//}

		// Reintento agregar el registro que generó la redispersion
			this->agregarRegistro(interprete,bytes);
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

