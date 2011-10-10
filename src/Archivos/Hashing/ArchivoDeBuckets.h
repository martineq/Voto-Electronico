#ifndef ARCHIVODEBUCKETS_H_
#define ARCHIVODEBUCKETS_H_

#include <vector>

#include "../EnBloques/ArchivoBloques.h"
#include "Bucket.h"

class ArchivoDeBuckets {
private:
	ArchivoBloques*		archivo;
	int					dimensionBucket;
	int					ultimoNumeroDeBucketAlmacenado;

	/*
	 * Devuelve un puntero a un string* con memoria reservada.
	 */
	std::string* charToString(char* cadena);

	/*
	 * Devuelve un puntero a un char* con memoria reservada.
	 */

	char* stringToChar(std::string* cadena);

	/*
	 * Obtiene el numero de bucket a partir del nrr.
	 */
	int obtenerNumeroDeBucket(int numeroDeBloque);

	/*
	 * Obtiene el nrr del bloque a partir de un numero de bucket.
	 */
	int	obtenerNumeroDeBloque(int numeroDeBucket);

	/*
	 * Guardar el Bucket en bloque.
	 */
	int guardarBukcetEnBloque(int numeroDeBloque,Bucket* bucket);


public:

	/*
	 * Crea un archivo de buckets.
	 */
	ArchivoDeBuckets(char* path, int tamanioBucket);

	/*
	 * Almacena el bloque en el archivo, devuelve el valor del nuevo bucket
	 */
	int guardarBucket(Bucket* bucket);

	/*
	 * Devuelve el numero de bucket solicitado, si no lo encuentra devuelve NULL.
	 */
	Bucket* obtenerBucket(int numeroDeBucket);

	/*
	 * Modifica el bucket almacenado.
	 */
	int modificarBucket(int numeroDeBucket,Bucket* bucket);

	/*
	 * Elimina el bucket del archivo.
	 */
	int liberarBucket(int numeroBucket);

	/*
	 *	Determina si el bucket que se desea obtener tiene contenido valido.
	 */
	int bucketDisponible(int numeroDeBucket);

	/*
	 * Devuelve el tamaño del bucket.
	 */
	int getDimensionDelBucket();

	/*
	 * Elimina el archivo de buckets del disco.
	 */
	void eliminarArchivoDeBuckets();

	/*
	 *	Cierra el archivo de buckets.
	 */
	~ArchivoDeBuckets();
};

#endif /* ARCHIVODEBUCKETS_H_ */
