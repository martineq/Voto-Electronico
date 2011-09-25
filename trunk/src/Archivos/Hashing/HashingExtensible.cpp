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

HashingExtensible::HashingExtensible(){
	;
}

HashingExtensible::HashingExtensible(ArchivoDeBuckets* archivoBloques) {
	this->archivo = archivoBloques;
}

int HashingExtensible::obtenerPosicion(int clave){
	//TODO
	// Falta emplear una función para transformar la clave en un hash
	int hash = clave;

	int n = log(this->tablaDeHash.size())/log(2);
	int posicion = hash & n;

	return posicion;
}

void HashingExtensible::redispersarBucket(Bucket* bucket,int numeroDeBucket,int posicionEnTablaDeHash){
	vector<int>::iterator it;
	Bucket* nuevoBucket;
	Bucket* bucketActualizado;

	int nuevoNumeroDeBucket;
	int dispersionNuevoBucket;
	int dispersionBucketActualizado;

	// Se agrega un nuevo numeroDeBucket en la posicion actual
	nuevoNumeroDeBucket = this->tablaDeDispersion.size();

	// Determina cuantas posiciones en la tabla de Hash serán reemplazadas
	int posicionesAreemplazar = numeroPosicionesAreemplazar(numeroDeBucket);

	if ( posicionesAreemplazar == 0 ){

		// Se duplica la tabla
		it 	= this->tablaDeHash.end();
		this->tablaDeHash.insert(it,this->tablaDeHash.begin(),it);
		this->tablaDeHash[posicionEnTablaDeHash] = nuevoNumeroDeBucket;

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
			this->tablaDeHash[posicionEnTablaDeHash+posicionesAreemplazar*dispersionNuevoBucket] = nuevoNumeroDeBucket;
		}
	}

	// Se actualiza la dispersion del bucket a redispersar.
	this->tablaDeDispersion[numeroDeBucket] = dispersionBucketActualizado;

	// Se agrega la dispersión del nuevo bloque
	this->tablaDeDispersion.push_back(dispersionNuevoBucket);

	// Se crea el nuevo Bucket.
	nuevoBucket = new Bucket(dispersionNuevoBucket);
	this->archivo->guardarBucket(numeroDeBucket,nuevoBucket);

	// Se crea un nuevo Bucket para redispersar los elementos.
	bucketActualizado = new Bucket(dispersionBucketActualizado);
	this->archivo->guardarBucket(numeroDeBucket,bucketActualizado);

	// Se redispersan registros en bloque actual
	// string* registro = obtenerRegistro();
	// while (!bloqueVacio(BLOQUE)) {
	//		clave_aux = obtenerClave(registro);
	//		this->agregarRegistro(registro.lenght(),clave_aux,registro);
	//}

}

int HashingExtensible::agregarRegistro(Registro* registro){

	int numeroDeBucket;
	Bucket* bucket;
	bool bucketCompleto;
	int posicionEnTablaDeHash;

	//Obtener clave es la función de hashing
	int clave = registro->obtenerClave();

	// Se aplica la "función modulo" para obtener la posicion de la tabla aplicando el logaritmo en base 2 del tamaño de la tabla.
	posicionEnTablaDeHash = this->obtenerPosicion(clave);

	numeroDeBucket = this->tablaDeHash.at(posicionEnTablaDeHash);

	bucket = this->obtenerBucket(numeroDeBucket);
	bucketCompleto = bucket->agregarRegistro(registro);	//manejador de bloques

	if (!bucketCompleto){
		//char* R = bucket->serializar();
		this->archivo->guardarBucket(numeroDeBucket,bucket);

	}else{
		redispersarBucket(bucket,numeroDeBucket,posicionEnTablaDeHash);

		// Reintento agregar el registro que generó la redispersion
		this->agregarRegistro(registro);
	}
	return 0;
}

int HashingExtensible::modificarRegistro(Registro* registro){



	return 0;
}

int HashingExtensible::eliminarRegistro(int clave){
	//TODO
	return 0;
}

HashingExtensible::~HashingExtensible() {
	// TODO Auto-generated destructor stub
}

