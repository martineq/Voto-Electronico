#include <vector>
#include <cmath>

#include "ArchivoDeBuckets.h"
#include "Bucket.h"
#include "Registro.h"

#ifndef HASHINGEXTENSIBLE_H_
#define HASHINGEXTENSIBLE_H_

class HashingExtensible {

#define BUCKET_LIBRE	-1

private:

	/*
	 * Archivo sobre el cual se aplica el hashing extensible.
	 */
	ArchivoDeBuckets*	archivo;

	/*
	 * Tabla de hash necesaria para emplear el hashing extensible.
	 */
	vector<int>			tablaDeHash;
	/*
	 * Tabla de dispersión, para evitar accesos a disco.
	 */
	vector<int> 		tablaDeDispersion;

	/*
	 * Lista de Buckets libres, permite evitar accesos a disco.
	 */
	list<int>			listaDeBucketsLibres;

	/*
	 * Mantiene en memoria el último bucket leído, para evitar accesos a disco.
	 */
	Bucket*				ultimoBucketLeido;

	/*
	 * Mantiene en memoria el número del último bucket leído, para evitar accesos a disco.
	 */
	int					numeroUltimoBucketLeido;

	/*
	 * Aplica la función de hash y devuelve la posicion en la tabla de Hash.
	 */
	int obtenerPosicion(int clave);

	/*
	 * Devuelve cuantas posiciones de la tabla de hash serán reemplazadas basándose
	 * en la dispersión del bloque que se encuentra en <posicion> de la tabla.
	 */
	int numeroPosicionesAreemplazar(int posicion);

	/*
	 * Obtiene uno a uno los elementos del bucket y los vuelve a agregar en el archivo.
	 */
	void redispersarBucket(Bucket* bucket,int numeroDeBucket,int posicionEnTablaDeHash);

	/*
	 * Evalua si puede liberar el bucket. Si se dan las condiciones, lo libera.
	 */
	void liberarBucket(int numeroDeBucket);

	/*
	 * Reduce la tabla de hash si al dividir en dos la tabla, las dos mitades resultan
	 * iguales, e informa si se realizó o no la operación.
	 */
	bool reducirTablaDeHash();

public:

	/*
	 * Instancia un objeto hashing extensible para aplicar la lógica sobre
	 * un archivo de buckets.
	 */
	HashingExtensible(ArchivoDeBuckets* nombreArchivo);

	/*
	 * Agrega el registro al bucket determinado por la clave que contiene.
	 */
	void agregarRegistro(Registro* registro);

	/*
	 * Modifica el registro al bucket determinado por la clave que contiene.
	 */
	void modificarRegistro(Registro* registro);

	/*
	 * Elimina el registro luego de buscarlo por la clave y libera el bucket
	 * que lo contiene de ser posible.
	 */
	int eliminarRegistro(int clave);


	/*
	 * Lógica que decide si emplear el último bucket leído o acceder a disco
	 * para buscar uno nuevo.
	 */
	Bucket* obtenerBucket(int numeroDeBucket);

	/*
	 * Elimina la instancia de memoria.
	 */

	virtual ~HashingExtensible();
};

#endif /* HASHINGEXTENSIBLE_H_ */
