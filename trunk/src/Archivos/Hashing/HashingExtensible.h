#include <vector>
#include <cmath>

#include "ArchivoDeBuckets.h"
#include "ArchivoDeControl.h"
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
	 * Archivo donde se almacena información necesaria para reconstruir el
	 * hashing luego de ser almacenado.
	 */
	ArchivoDeControl*	archivoDeControl;

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
	list<int>			listaDeBucketsLibres;

	/*
	 * Traduce de direcciones fisicas a lógicas.
	 */
	vector<int>			tablaDeTraduccion;

	/*
	 * Mantiene una lista de buckets durante la redispersión.
	 */
	list<Bucket*>		bucketsEnRedispersion;

	/*
	 * Permite activar o desactivar el flag de redispersion.
	 */
	bool				redispersando;

	/*
	 *	Duplica el bucket.
	 */
	Bucket* duplicarBucket(Bucket* bucket);

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
	 * Devuelve BucketDisponible, BucketLibre o BucketNoDisponible.
	 */
	Resultados estadoDelBucket(unsigned int numeroDeBucket);

	/*
	 * Metodo para agregar registro.
	 */
	Resultados agregarRegistroInt(Registro* regisrtro,int clave);
public:

	/*
	 * Permite operar con un archivo de hashing dinámico, recibiendo los path
	 * del archivo donde se almacenarán los datos y uno de control para funcionamiento
	 * interno del hashing. Además es necesario pasarle el tamaño del bucket.
	 * Si se desea eliminar los archivos, se debe realizar directamente sobre
	 * el path de los archivos.
	 */
	HashingExtensible(int dimensionDelBucket,char* archivoDeDatos,char* archivoDeControl);

	/*
	 * Agrega el registro al bucket determinado por la clave que contiene.
	 * No realiza verificacion de unicidad de clave.
	 * Devuelve operacion OK.
	 */
	Resultados cargarRegistro(Registro* registro);

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
	Resultados eliminarRegistro(Registro* registro);

	/*
	 *	Devuelve el registro a partir del registro introducido.
	 *	Registro* es una nueva instancia por lo que debe ser eliminada tras ser
	 *	utilizada.
	 */
	Registro* obtenerRegistro(Registro* registro);

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
