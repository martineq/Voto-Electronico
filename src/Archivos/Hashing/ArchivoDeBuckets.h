#ifndef ARCHIVODEBUCKETS_H_
#define ARCHIVODEBUCKETS_H_

#include "../EnBloques/ArchivoBloques.h"
#include "Resultados.h"
#include "Bucket.h"

#define	STATUS_SIZE		4

class ArchivoDeBuckets {
private:
	ArchivoBloques*		archivo;
	Bucket*				ultimoBucket;
	int					numeroUltimoBucket;
	int					dimensionBucket;
	int					bucketsAlmacenados;


	/*
	 * Modifica el bucket interno por uno nuevo.
	 */
	void modificarBucketInterno(Bucket* bucket,int numeroDeBucket);

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
	void guardarBukcetEnBloque(int numeroDeBloque,Bucket* bucket);

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
	Resultados modificarBucket(int numeroDeBucket,Bucket* bucket);

	/*
	 * Elimina el bucket del archivo.
	 */
	Resultados liberarBucket(int numeroBucket);

	/*
	 *	Determina si el bucket que se desea obtener tiene contenido valido.
	 */
	Resultados bucketDisponible(int numeroDeBucket);

	/*
	 * Devuelve el tamaño del bucket.
	 */
	int getDimensionDelBucket();

	/*
	 * Elimina el archivo de buckets del disco.
	 */
	Resultados eliminarArchivoDeBuckets();

	/*
	 *	Cierra el archivo de buckets.
	 */
	~ArchivoDeBuckets();
};

#endif /* ARCHIVODEBUCKETS_H_ */
