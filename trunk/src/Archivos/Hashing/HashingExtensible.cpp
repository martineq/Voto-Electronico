#include "HashingExtensible.h"

HashingExtensible::HashingExtensible(ArchivoDeBuckets* archivoBloques) {
	this->archivo = archivoBloques;
//	this->ultimoBucketLeido = NULL;
	#warning "Al realizar la creación debería leerse las tablas almacenadas."
	//TODO
}

unsigned int HashingExtensible::numeroPosicionesAreemplazar(unsigned int numeroDeBucket){

	int dispersion = this->tablaDeDispersion.at(numeroDeBucket);
	int repeticionesBloque =  this->tablaDeHash.size() / dispersion;
	return repeticionesBloque/2;

}

unsigned int HashingExtensible::obtenerPosicion(unsigned int clave){
	unsigned int posicion = 0;

	if (!this->tablaDeHash.empty()){
		posicion = clave % tablaDeHash.size();
	}

	return posicion;
}

Resultados HashingExtensible::redispersarBucket(Bucket* bucket,int numeroDeBucket,int posicionEnTablaDeHash){
	Resultados resultado = operacionOK;
	vector<int>::iterator it;
	Bucket* nuevoBucket = NULL;
	Bucket* bucketActualizado = NULL;

	int nuevoNumeroDeBucket = -1;
	int dispersionNuevoBucket = -1;
	int dispersionBucketActualizado =-1;

	// Se agrega un nuevo numeroDeBucket en la posicion actual
	nuevoNumeroDeBucket = this->tablaDeDispersion.size();

	// Se imprime la tabla de hash
	imprimirTablaDeDispersion();

	// Determina cuantas posiciones en la tabla de Hash serán reemplazadas
	int posicionesAreemplazar = numeroPosicionesAreemplazar(numeroDeBucket);

	if ( posicionesAreemplazar == 0 ){

		// Se duplica la tabla
		it 	= this->tablaDeHash.end();
		this->tablaDeHash.insert(it,this->tablaDeHash.begin(),it);
		this->tablaDeHash[posicionEnTablaDeHash] = nuevoNumeroDeBucket;

		// Se calcula la dispersión de nuevo bucket
		this->tablaDeDispersion.push_back(this->tablaDeHash.size());

		// Se calculan los nuevos tamaños de dispersion, del bucket a redispersar y del nuevo bucket.
		dispersionBucketActualizado	= 2 * tablaDeDispersion[numeroDeBucket];
		dispersionNuevoBucket 		= tablaDeDispersion[nuevoNumeroDeBucket];

	}else{
		// Se calculan los nuevos tamaños de dispersion, del bucket a redispersar y del nuevo bucket.
		dispersionBucketActualizado = 2 * tablaDeDispersion[numeroDeBucket];
		dispersionNuevoBucket 		 = dispersionBucketActualizado;

		// Se calcula la dispersión de nuevo bucket
		this->tablaDeDispersion.push_back(dispersionNuevoBucket);

		// Actualiza la tabla de hash incoorporando el valor del nuevo bloque.
		while (posicionesAreemplazar > 0){
			posicionesAreemplazar--;
			this->tablaDeHash[posicionEnTablaDeHash+posicionesAreemplazar*dispersionNuevoBucket] = nuevoNumeroDeBucket;
		}
	}

	// Se actualiza la dispersion del bucket a redispersar.
	this->tablaDeDispersion[numeroDeBucket] = dispersionBucketActualizado;

#warning "esto fue calculado anteriormente"
	// Se agrega la dispersión del nuevo bloque
//	this->tablaDeDispersion.push_back(dispersionNuevoBucket);

	// Se crea el nuevo Bucket.
	nuevoBucket = new Bucket(dispersionNuevoBucket,archivo->getDimensionDelBucket());
	int posBloque = this->archivo->guardarBucket(nuevoBucket);
	cout << "Se almacena un nuevo bloque para almacenar los desbordes en bloque: " << posBloque << endl;
	cout << "tamaño de dispersion: " << nuevoBucket->getTamanioDeDispersion() << endl;
	cout << "espacio libre: " << nuevoBucket->getEspacioLibre() << endl;

	// Se crea un nuevo Bucket para redispersar los elementos.
	bucketActualizado = new Bucket(dispersionBucketActualizado,archivo->getDimensionDelBucket());
	this->archivo->modificarBucket(numeroDeBucket,bucketActualizado);
	cout << "Se modifica el bloque " << numeroDeBucket << " para realizar la redispersion" << endl;
	cout << "tamaño de dispersion: " << bucketActualizado->getTamanioDeDispersion() << endl;
	cout << "espacio libre: " << bucketActualizado->getEspacioLibre() << endl;

	cout << "** Inicio de la redispersión" << endl << endl;
	int cantidadDeRegistros = bucket->getCantidadDeRegistros();
	list<Registro*>::iterator iterador = bucket->ubicarPrimero();
	for(int i = 0;i< cantidadDeRegistros;i++){

		if ( agregarRegistro(*iterador) == operacionFALLO ){
			resultado = operacionFALLO;
			cout << "OPERACION FALLO" << endl << endl;
		}
		else
			cout << "OPERACION EXITOSA" << endl << endl;

		iterador++;
	}
	cout << "** Fin de la redispersión" << endl << endl;

	return resultado;
}

Resultados HashingExtensible::reducirTablaDeHash(){

	Resultados resultado = operacionFALLO;

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
			resultado = operacionOK;
		}
	}

	// Reduce la tabla a la mitad si son iguales.
	if ( distintos == false ){
		tablaDeHash.erase(inicio,tablaDeHash.end());
	}

	return resultado;
}


Resultados HashingExtensible::liberarBucket(unsigned int posicionEnTablaDeHash){

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

Resultados HashingExtensible::agregarRegistro(Registro* registro){

	Resultados resultado = operacionOK;
	int numeroDeBucket = -1;
	Bucket* bucket = NULL;
	bool registroAgregado;
	int posicionEnTablaDeHash = -1;

	//Obtener clave devuelve el resultado de aplicar la función de hashing sobre el registro.
	int clave = registro->obtenerClave();
	cout << "clave obtenida: " << clave << endl;

	// Verficacion de unicidad de clave.
	Registro* registroDuplicado = obtenerRegistro(clave);
	if ( registroDuplicado == NULL ){

		// Se aplica la "función modulo" para obtener la posicion de la tabla aplicando el logaritmo en base 2 del tamaño de la tabla.
		posicionEnTablaDeHash = this->obtenerPosicion(clave);

		if ( !this->tablaDeHash.empty()) {
			// Busco el numero de bucket si la tabla no está vacía.
			numeroDeBucket = this->tablaDeHash.at(posicionEnTablaDeHash);
			bucket = this->archivo->obtenerBucket(numeroDeBucket);

		}else {
			// Si la tabla está vacía entonces tengo que crear un nuevo bucket
			Bucket* nuevoBucket = new Bucket(0,archivo->getDimensionDelBucket());
			numeroDeBucket = this->archivo->guardarBucket(nuevoBucket);
			cout << " Se crea un nuevo bloque: " << numeroDeBucket << endl;

			// Agrego el nuevo bucket en la lógica del hashing y le asigno su dispersión.
			this->tablaDeHash.push_back(numeroDeBucket);
			this->tablaDeDispersion.push_back(this->tablaDeHash.size());

			bucket = nuevoBucket;
			bucket->setTamanioDeDispersion(tablaDeDispersion.at(numeroDeBucket));
		}

		registroAgregado = bucket->agregarRegistro(registro);

		// Se imprime la tabla de hash
		imprimirTablaDeDispersion();

		if (registroAgregado){
			if ( this->archivo->modificarBucket(numeroDeBucket,bucket) == operacionOK)
				cout << "** Se almacena en numero de bloque: " << numeroDeBucket << endl;

		}else{
			resultado = redispersarBucket(bucket,numeroDeBucket,posicionEnTablaDeHash);

			// Reintento agregar el registro que generó la redispersion
			if ( resultado == operacionOK )
				resultado = this->agregarRegistro(registro);
		}
		delete bucket;

	}else{
		delete registroDuplicado;
		resultado = claveRepetida;
		cout << "clave repetida, se insertó previamente un registro con esa clave" << endl;
	}

	return resultado;
}

Resultados HashingExtensible::modificarRegistro(Registro* registro){
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
		delete bucket;
	}
}

Resultados HashingExtensible::eliminarRegistro(unsigned int clave){

	Resultados resultado = operacionOK;

	// Obtengo el Bucket a partir de la clave.
	int posicionEnTablaDeHash = obtenerPosicion(clave);
	int numeroDeBucket = tablaDeHash[posicionEnTablaDeHash];

	Bucket* bucket = archivo->obtenerBucket(numeroDeBucket);

	// Obtengo el registro.
	Registro* registro = bucket->getRegistro(clave);

	if ( registro !=NULL ){

		// Eliminamos el registro
		if ( !bucket->eliminarRegistro(clave) )
			resultado = operacionFALLO;

		// Si el bucket quedó vacío, evaluo si lo puedo liberar.
		if ( bucket->getCantidadDeRegistros() == 0 ){

			this->liberarBucket(posicionEnTablaDeHash);
		}
	}else
		resultado = operacionFALLO;

	delete bucket;

	return resultado;
}

Registro* HashingExtensible::obtenerRegistro(unsigned int clave){

	Registro* registro = NULL;

	// Obtengo el Bucket a partir de la clave.
	unsigned int posicionEnTablaDeHash = obtenerPosicion(clave);

	imprimirTablaDeHash();
	cout << "posicion en Tabla de Hash: " << posicionEnTablaDeHash << endl;

	if (posicionEnTablaDeHash < tablaDeHash.size()){

		int numeroDeBucket = tablaDeHash[posicionEnTablaDeHash];

		Bucket* bucket = this->archivo->obtenerBucket(numeroDeBucket);
		if (bucket != NULL)
			registro = bucket->getRegistro(clave);
		else
			cout << "*** BUCKET NO DISPONIBLE ****" << endl;

		delete bucket;
	}
	return registro;
}

void HashingExtensible::imprimirTablaDeHash()
{
	int size = this->tablaDeHash.size();

	if (size == 0)
		cout << "Tabla de hash vacia" << endl;
	else{
		cout << "Tabla de hash (size: "<<size<<"): ";
		for(int i = 0;i < size;i++){
			cout << " " << tablaDeHash[i];
		}
		cout << endl;
	}
}

void HashingExtensible::imprimirTablaDeDispersion()
{
	int size = this->tablaDeDispersion.size();

	if (size == 0)
		cout << "Tabla de dispersion vacia" << endl;
	else{
		cout << "Tabla de dispersion (size: "<<size<<"): ";
		for(int i = 0;i < size;i++){
			cout << " " << tablaDeDispersion[i];
		}
		cout << endl;
	}
}

HashingExtensible::~HashingExtensible() {
	// TODO Auto-generated destructor stub
}

