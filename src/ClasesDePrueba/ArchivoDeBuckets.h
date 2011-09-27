#ifndef ARCHIVODEBUCKETS_H_
#define ARCHIVODEBUCKETS_H_

#include <vector>

#include "../Archivos/Hashing/Bucket.h"

class ArchivoDeBuckets {
private:
	vector<Bucket*>	archivo;
	vector<int>		bucketsLibres;

public:
	ArchivoDeBuckets();

	//ArchivoDeBuckets(string* path, int tamanioBucket);

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
