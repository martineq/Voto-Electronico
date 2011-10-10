#include "HashingExtensible.h"

HashingExtensible::HashingExtensible(ArchivoDeBuckets* archivoBloques) {
	this->archivo = archivoBloques;
//	this->ultimoBucketLeido = NULL;
	#warning "Al realizar la creación debería leerse las tablas almacenadas."
	//TODO
}

int HashingExtensible::numeroPosicionesAreemplazar(int numeroDeBucket){

	int dispersion = this->tablaDeDispersion.at(numeroDeBucket);
	int repeticionesBloque =  this->tablaDeHash.size() / dispersion;
	return repeticionesBloque/2;

}

int HashingExtensible::obtenerPosicion(int clave){
	int posicion = 0;

	if (!this->tablaDeHash.empty()){
		posicion = clave % tablaDeHash.size();
	}

	return posicion;
}

//Bucket* HashingExtensible::obtenerBucket(int numeroDeBucket){
//	Bucket* bucket;
//
//	if ( numeroUltimoBucketLeido == numeroDeBucket ){
//		bucket = ultimoBucketLeido;
//	}else{
//		bucket = archivo->obtenerBucket(numeroDeBucket);
//		ultimoBucketLeido = bucket;
//		numeroUltimoBucketLeido = numeroDeBucket;
//	}
//	return bucket;
//}

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
	nuevoBucket = new Bucket(archivo->getDimensionDelBucket(),dispersionNuevoBucket);
	this->archivo->guardarBucket(nuevoBucket);

	// Se crea un nuevo Bucket para redispersar los elementos.
	bucketActualizado = new Bucket(archivo->getDimensionDelBucket(),dispersionBucketActualizado);
	this->archivo->guardarBucket(bucketActualizado);

	int cantidadDeRegistros = bucket->getCantidadDeRegistros();
	list<Registro*>::iterator iterador = bucket->ubicarPrimero();
	for(int i = 0;i< cantidadDeRegistros;i++){
		this->agregarRegistro(*iterador);
		iterador++;
	}

}

bool HashingExtensible::reducirTablaDeHash(){

	int n = tablaDeHash.size();
	n /= 2;

	int i = 0;
	int j = n;
	bool distintos = false;

	vector<int>::iterator inicio;

	// Busca si las dos mitades de la tabla son iguales.
	while (distintos == false && i<n){
		if ( tablaDeHash[i]==tablaDeHash[j] ){
			i++;
			j++;
			inicio++;
		}else{
			distintos = true;
		}
	}

	// Reduce la tabla a la mitad si son iguales.
	if ( distintos == false ){
		tablaDeHash.erase(inicio,tablaDeHash.end());
	}

	return distintos;
}


void HashingExtensible::liberarBucket(int posicionEnTablaDeHash){

	int numeroDeBucket = tablaDeHash.at(posicionEnTablaDeHash);

	// Si el bucket quedó vacío, entonces evalúo si el posterior tiene igual dispersión.
	// A la lista la trato como si fuese circular.
	int dispersionDelBucket = tablaDeDispersion.at(numeroDeBucket);

	// Calculo las posiciones del bucket Anterior y posterior.
	int posicionBucketAnterior = ( posicionEnTablaDeHash - dispersionDelBucket / 2 ) % tablaDeHash.size();
	int posicionBucketPosterior= ( posicionEnTablaDeHash + dispersionDelBucket / 2 ) % tablaDeHash.size();

	// Calculo la dispersión del bucketPosterior.
	int numeroDelBucketPosterior  = tablaDeHash[posicionBucketPosterior];
	int dispersionBucketPosterior = tablaDeDispersion.at(numeroDelBucketPosterior);

	bool reemplazarBucket = false;

	if (dispersionDelBucket == dispersionBucketPosterior){

		// Misma dispersión, reemplazo el bucket.
		reemplazarBucket = 1;
	}else{

		// Dispersión diferente, comparo el elemento anterior y siguiente para
		// ver si son el mismo bloque. De ser así, se lo reemplaza.
		if ( tablaDeHash[posicionBucketAnterior]==tablaDeHash[posicionBucketPosterior] ){

			reemplazarBucket = 1;
		}

	}

	if ( reemplazarBucket == 1 ){

		// Obtengo el bucket posterior/anterior.
		Bucket* bucketPosterior = this->archivo->obtenerBucket(numeroDelBucketPosterior);

		// Libero el bucket y lo ubico en la lista de libres.
		this->tablaDeDispersion.at(numeroDeBucket) = BUCKET_LIBRE;
		this->listaDeBucketsLibres.push_back(numeroDeBucket);
		this->archivo->liberarBucket(numeroDeBucket);

		//Reemplazo el bucket a eliminar por el posterior/anterior.
		tablaDeHash[posicionEnTablaDeHash] = tablaDeHash[posicionBucketPosterior];
		tablaDeDispersion[numeroDelBucketPosterior] *= 2;
		bucketPosterior->setTamanioDeDispersion(tablaDeDispersion[numeroDelBucketPosterior]);
		archivo->modificarBucket(numeroDelBucketPosterior,bucketPosterior);

		// Verificar si los bloques se encuentran duplicados.
		reducirTablaDeHash();

	}
}

void HashingExtensible::agregarRegistro(Registro* registro){

	int numeroDeBucket;
	Bucket* bucket;
	bool registroAgregado;
	int posicionEnTablaDeHash;

	//Obtener clave devuelve el resultado de aplicar la función de hashing sobre el registro.
	int clave = registro->obtenerClave();

	// Se aplica la "función modulo" para obtener la posicion de la tabla aplicando el logaritmo en base 2 del tamaño de la tabla.
	posicionEnTablaDeHash = this->obtenerPosicion(clave);

	if ( !this->tablaDeHash.empty()) {
		// Busco el numero de bucket si la tabla no está vacía.
		numeroDeBucket = this->tablaDeHash.at(posicionEnTablaDeHash);
		bucket = this->archivo->obtenerBucket(numeroDeBucket);

	}else {
		// Si la tabla está vacía entonces tengo que crear un nuevo bucket
		Bucket* nuevoBucket = new Bucket(archivo->getDimensionDelBucket(),0);
		numeroDeBucket = this->archivo->guardarBucket(nuevoBucket);

		// Agrego el nuevo bucket en la lógica del hashing y le asigno su dispersión.
		this->tablaDeHash.push_back(numeroDeBucket);
		this->tablaDeDispersion.push_back(this->tablaDeHash.size());

		// Obtengo el nuevo bucket y le modifico el tamaño de dispersión.
//		this->numeroUltimoBucketLeido = nuevoBucket;
//		this->ultimoBucketLeido = nuevoBucket;
		bucket = nuevoBucket;
		bucket->setTamanioDeDispersion(tablaDeDispersion.at(numeroDeBucket));
	}

	registroAgregado = bucket->agregarRegistro(registro);

	if (registroAgregado){
		this->archivo->modificarBucket(numeroDeBucket,bucket);

	}else{
		redispersarBucket(bucket,numeroDeBucket,posicionEnTablaDeHash);

		// Reintento agregar el registro que generó la redispersion
		this->agregarRegistro(registro);
	}

	delete(bucket);
}

void HashingExtensible::modificarRegistro(Registro* registro){
	bool exito = 0;

	int clave = registro->obtenerClave();
	int posicionEnTablaDeHash = obtenerPosicion(clave);
	int numeroDeBucket = tablaDeHash[posicionEnTablaDeHash];

	Bucket* bucket = this->archivo->obtenerBucket(numeroDeBucket);

	if (bucket != NULL){
		exito = bucket->reemplazarRegistro(registro);
		if (!exito){
			if ( bucket->getRegistro(numeroDeBucket) !=NULL ){
				// En este caso no hubo exito al almacenar el registro y
				// estaba disponible dentro del bucket.
				redispersarBucket(bucket,numeroDeBucket,posicionEnTablaDeHash);
				agregarRegistro(registro);
			}
		}
	}
}

int HashingExtensible::eliminarRegistro(int clave){
	int exito = 1;

	// Obtengo el Bucket a partir de la clave.
	int posicionEnTablaDeHash = obtenerPosicion(clave);
	int numeroDeBucket = tablaDeHash[posicionEnTablaDeHash];

	Bucket* bucket = this->archivo->obtenerBucket(numeroDeBucket);

	// Obtengo el registro.
	Registro* registro = bucket->getRegistro(clave);

	if ( registro !=NULL ){

		// Eliminamos el registro
		exito = bucket->eliminarRegistro(clave);

		// Si el bucket quedó vacío, evaluo si lo puedo liberar.
		if ( bucket->getCantidadDeRegistros() == 0 ){

			this->liberarBucket(posicionEnTablaDeHash);
		}
	}else{
		exito = 0;
	}

	return exito;
}

Registro* HashingExtensible::obtenerRegistro(int clave){

	// Obtengo el Bucket a partir de la clave.
	int posicionEnTablaDeHash = obtenerPosicion(clave);
	int numeroDeBucket = tablaDeHash[posicionEnTablaDeHash];

	Bucket* bucket = this->archivo->obtenerBucket(numeroDeBucket);
	Registro* registro = bucket->getRegistro(clave);
	delete bucket;

	return registro;
}

HashingExtensible::~HashingExtensible() {
	// TODO Auto-generated destructor stub
}

