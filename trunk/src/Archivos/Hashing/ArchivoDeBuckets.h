#ifndef ARCHIVODEBUCKETS_H_
#define ARCHIVODEBUCKETS_H_

#include <vector>

#include "../EnBloques/ArchivoBloques.h"
#include "Bucket.h"

class ArchivoDeBuckets {
private:
	ArchivoBloques*		archivo;
	int					tamanioBucket;
	int					ultimoNumeroDeBucketAlmacenado;
	vector<int>			bucketsLibres;

	/*
	 * Devuelve un puntero a un string* con memoria reservada.
	 */
	std::string* charToString(char* cadena);

	/*
	 * Devuelve un puntero a un char* con memoria reservada.
	 */

	char* stringToChar(std::string* cadena);

public:

	/*
	 * Crea un archivo de buckets.
	 */
	ArchivoDeBuckets(char* path, int tamanioBucket);

	/*
	 * Devuelve el numero de bucket solicitado.
	 */
	Bucket* obtenerBucket(int numeroDeBucket);

	/*
	 * Devuelve el valor del nuevo bucket.
	 */
	int crearNuevoBucket();

	/*
	 * Elimina el bucket del archivo.
	 */
	void liberarBucket(int numeroBucket);

	/*
	 * Modifica el bucket almacenado.
	 */
	void modificarBucket(int numeroDeBucket,Bucket* bucket);

	/*
	 * Almacena el bloque en el archivo, devuelve el valor del nuevo bucket
	 */
	int guardarBucket(Bucket* bucket);

	virtual ~ArchivoDeBuckets();
};

#endif /* ARCHIVODEBUCKETS_H_ */
