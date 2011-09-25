#ifndef ARCHIVODEBUCKETS_H_
#define ARCHIVODEBUCKETS_H_

#include "../EnBloques/ArchivoBloques.h"
#include "Bucket.h"

class ArchivoDeBuckets {
private:
	ArchivoBloques	archivo;

public:
	ArchivoDeBuckets();

	ArchivoDeBuckets(string* path, int tamanioBucket);

	Bucket* obtenerBucket(int numeroDeBucket);

	/*
	 * Devuelve el valor del nuevo bucket
	 */
	int crearNuevoBucket();

	/*
	 * Elimina el bucket del archivo
	 */
	void liberarBucket(int numeroBucket);

	/*
	 * Almacena el bloque en el archivo
	 */
	void guardarBucket(int numeroBucket, Bucket* bucket);

	virtual ~ArchivoDeBuckets();
};

#endif /* ARCHIVODEBUCKETS_H_ */
