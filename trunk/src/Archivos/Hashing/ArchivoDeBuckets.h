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

	/*
	 *	Duplica el bucket.
	 */
	Bucket* duplicarBucket(Bucket* bucket);

	/*
	 *	Modifica el bucket interno por uno nuevo.
	 */
	void modificarBucketInterno(Bucket* bucket,int numeroDeBucket);

	/*
	 * Devuelve un bucket a partir de un char*.
	 */
	Bucket* deserializarBucket(char* cadena);

	/*
	 * Devuelve un puntero a un char* con memoria reservada.
	 */

	char* serializarBucket(Bucket* bucket);

	/*
	 * Guardar el Bucket en bloque.
	 */
	void guardarBukcetEnBloque(int numeroDeBloque);

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
	 * El elemento es una copia del bucket almacenado por lo que debe ser liberado,
	 * luego de ser utilizado.
	 */
	Bucket* obtenerBucket(int numeroDeBucket);

	/*
	 * Modifica el bucket almacenado.
	 */
	void modificarBucket(int numeroDeBucket,Bucket* bucket);

	/*
	 * Elimina el bucket del archivo.
	 */
	void liberarBucket(int numeroBucket);

	/*
	 *	Determina si el bucket que se desea obtener tiene contenido valido.
	 */
	Resultados bucketDisponible(int numeroDeBucket);

	/*
	 * Devuelve el tamaño del bucket.
	 */
	int getDimensionDelBucket();

	/*
	 *	Cierra el archivo de buckets.
	 */
	~ArchivoDeBuckets();
};

#endif /* ARCHIVODEBUCKETS_H_ */
