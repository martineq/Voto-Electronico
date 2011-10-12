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
	 * Lista de buckets libres.
	 */
	list<int> 			listaDeBucketsLibres;

	/*
	 * Se imprime por pantalla la tabla de dispersion.
	 */
	void imprimirTablaDeDispersion();

	/*
	 * Se imprime por pantalla la tabla de hash.
	 */
	void imprimirTablaDeHash();

	/*
	 * Aplica la función de hash y devuelve la posicion en la tabla de Hash.
	 */
	unsigned int obtenerPosicion(unsigned int clave);

	/*
	 * Devuelve cuantas posiciones de la tabla de hash serán reemplazadas basándose
	 * en la dispersión del bloque que se encuentra en <posicion> de la tabla.
	 */
	unsigned int numeroPosicionesAreemplazar(unsigned int posicion);

	/*
	 * Obtiene uno a uno los elementos del bucket y los vuelve a agregar en el archivo.
	 */
	Resultados redispersarBucket(Bucket* bucket,int numeroDeBucket,int posicionEnTablaDeHash);

	/*
	 * Evalua si puede liberar el bucket. Si se dan las condiciones, lo libera.
	 */
	Resultados liberarBucket(unsigned int numeroDeBucket);

	/*
	 * Reduce la tabla de hash si al dividir en dos la tabla, las dos mitades resultan
	 * iguales, e informa si se realizó o no la operación.
	 */
	Resultados reducirTablaDeHash();

	/*
	 * 	Se duplica un bucket.
	 */
	Bucket* duplicarBucket(Bucket* bucket);
public:

	/*
	 * Instancia un objeto hashing extensible para aplicar la lógica sobre
	 * un archivo de buckets.
	 */
	HashingExtensible(ArchivoDeBuckets* nombreArchivo);

	/*
	 * Agrega el registro al bucket determinado por la clave que contiene.
	 * Realiza verificacion de unicidad de clave.
	 * Devuelve claveRepetida si existe un registro con esa clave u operacionOK.
	 */
	Resultados agregarRegistro(Registro* registro);

	/*
	 * Modifica el registro al bucket determinado por la clave que contiene.
	 * Si el registro no se encuentra en el archivo de hashing devuelve el
	 * resultado "registroInexistente".
	 * Si el registro si se encuentra en el archivo de hashing puede devolver
	 * operacionOK u operacionFALLO.
	 */
	Resultados modificarRegistro(Registro* registro);

	/*
	 * Elimina el registro luego de buscarlo por la clave y libera el bucket
	 * que lo contiene de ser posible.
	 */
	Resultados eliminarRegistro(unsigned int clave);

	/*
	 *	Devuelve el registro a partir de la clave introducida.
	 *	Registro* es una nueva instancia por lo que debe ser eliminada tras ser
	 *	utilizada.
	 */
	Registro* obtenerRegistro(unsigned int clave);

	/*
	 * Muestra el contenido del archivo de hashing.
	 */
	void mostrarArchivoDeHash();

	/*
	 * Elimina la instancia de memoria.
	 */
	virtual ~HashingExtensible();
};

#endif /* HASHINGEXTENSIBLE_H_ */
