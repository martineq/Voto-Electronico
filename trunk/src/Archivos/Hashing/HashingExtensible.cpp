#include "HashingExtensible.h"

HashingExtensible::HashingExtensible(int dimensionDelBucket,char* pathArchivoDeDatos,char* pathArchivoDeControl){
	archivo = new ArchivoDeBuckets(pathArchivoDeDatos,dimensionDelBucket);

	archivoDeControl = new ArchivoDeControl(pathArchivoDeControl);

	if (!archivoDeControl->vacio()){
		this->listaDeBucketsLibres = archivoDeControl->hidratarLista();
		this->tablaDeTraduccion = archivoDeControl->hidratarVector();
		this->tablaDeHash = archivoDeControl->hidratarVector();
		this->tablaDeDispersion = archivoDeControl->hidratarVector();

		// Elimina el archivo actual y espera a que el programa termine
		// para almacenar la nueva configuracion.
		delete archivoDeControl;
		remove(pathArchivoDeControl);
		archivoDeControl = new ArchivoDeControl(pathArchivoDeControl);
	}
}

Bucket* HashingExtensible::duplicarBucket(Bucket* bucket){

	Bucket* nuevoBucket = new Bucket(0,archivo->getDimensionDelBucket());
	string* stringSerializado = bucket->serializar();
	nuevoBucket->deserializar(stringSerializado);
	delete stringSerializado;
	return nuevoBucket;
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

Resultados HashingExtensible::estadoDelBucket(unsigned int numeroDeBucket){

	Resultados resultado = bucketNoDisponible;

	if (numeroDeBucket < tablaDeTraduccion.size()){

		if (listaDeBucketsLibres.empty())
			resultado = bucketDisponible;

		else{
			if (BUCKET_LIBRE == tablaDeHash[numeroDeBucket])
				resultado = bucketLibre;
			else
				resultado = bucketDisponible;
		}

	}
	return resultado;
}

Resultados HashingExtensible::agregarRegistroInt(Registro *registro,int clave){

	unsigned int nrr;
	unsigned int numeroDeBucket;
	unsigned int posicionEnTablaDeHash;

	Bucket* bucket = NULL;

	Resultados resultado = operacionOK;

	// Se aplica la "función modulo" para obtener la posicion de la tabla.
	posicionEnTablaDeHash = this->obtenerPosicion(clave);

	if ( !this->tablaDeHash.empty()) {
		// Busco el numero de bucket.
		numeroDeBucket = tablaDeHash.at(posicionEnTablaDeHash);
		nrr = tablaDeTraduccion[numeroDeBucket];
		bucket = archivo->obtenerBucket(nrr);

	}else {
		// Si la tabla está vacía entonces tengo que crear un nuevo bucket.
		if (this->listaDeBucketsLibres.empty()){
			numeroDeBucket = 0;
			bucket = new Bucket(0,archivo->getDimensionDelBucket());
			nrr = archivo->guardarBucket(bucket);
			tablaDeTraduccion.push_back(nrr);

		}else{

			numeroDeBucket = listaDeBucketsLibres.back();
			listaDeBucketsLibres.pop_back();
			nrr = tablaDeTraduccion[numeroDeBucket];
			bucket = archivo->obtenerBucket(nrr);
		}

		// Determino el tamaño de dispersion.
		int dispersion = tablaDeHash.size()+1;
		bucket->setTamanioDeDispersion(dispersion);

		// Agrego el nuevo bucket en la lógica del hashing.
		tablaDeHash.push_back(numeroDeBucket);
		tablaDeDispersion.push_back(dispersion);
	}


	int espacioLibre = bucket->getEspacioLibre();

	bool registroAgregado = false;

	if ( espacioLibre > 0.2 * archivo->getDimensionDelBucket() ){

		// Se intenta agregar el registro al bucket, si no se pude se redispersa.
		registroAgregado = bucket->agregarRegistro(registro);
	}

	if (registroAgregado)
		archivo->modificarBucket(nrr,bucket);

	else{
		resultado = redispersarBucket(bucket,numeroDeBucket,posicionEnTablaDeHash);

		// Reintento agregar el registro que generó la redispersion
		if ( resultado == operacionOK )
			resultado = agregarRegistro(registro);
	}
//	delete bucket;

	return resultado;
}

Resultados HashingExtensible::redispersarBucket(Bucket* bucket,int numeroDeBucket,int posicionEnTablaDeHash){
	Resultados resultado = operacionOK;
	vector<int>::iterator it;
	Bucket* nuevoBucket = NULL;
	Bucket* bucketActualizado = NULL;

	int nuevoNumeroDeBucket = -1;
	int dispersionNuevoBucket = -1;
	int dispersionBucketAredispersar =-1;
	int posBloque;

	bucket = duplicarBucket(bucket);

	bool usandoBucketLibre = false;

	if ( listaDeBucketsLibres.empty() )
		// Se agrega un nuevo numeroDeBucket en la posicion actual.
		nuevoNumeroDeBucket = tablaDeDispersion.size();
	
	else{
		// Obtengo el último bucket libre.
		nuevoNumeroDeBucket = listaDeBucketsLibres.back();
		listaDeBucketsLibres.pop_back();
		usandoBucketLibre = true;
	}

	// Determina cuantas posiciones en la tabla de Hash serán reemplazadas.
	int posicionesAreemplazar = numeroPosicionesAreemplazar(numeroDeBucket);

	if ( posicionesAreemplazar == 0 ){

		// Se duplica la tabla de hash.
		it 	= tablaDeHash.end();
		tablaDeHash.insert(it,tablaDeHash.begin(),it);
		tablaDeHash[posicionEnTablaDeHash] = nuevoNumeroDeBucket;

		// Se determina el tamaño de dispersión del nuevo bucket.
		if ( usandoBucketLibre and (tablaDeDispersion.size()>nuevoNumeroDeBucket)){
			tablaDeDispersion.at( nuevoNumeroDeBucket ) = tablaDeHash.size();
		}
		else
			tablaDeDispersion.push_back(tablaDeHash.size());

		// Se obtienen los nuevos tamaños de dispersion.
		dispersionBucketAredispersar= 2 * tablaDeDispersion[numeroDeBucket];
		dispersionNuevoBucket 		= tablaDeDispersion[nuevoNumeroDeBucket];

	}else{
		// Se modifica/n valores de la tabla de hash.

		// Se calculan los nuevos tamaños de dispersion, del bucket a redispersar y del nuevo bucket.
		dispersionBucketAredispersar = 2 * tablaDeDispersion[numeroDeBucket];
		dispersionNuevoBucket 		 = dispersionBucketAredispersar;

		// Se agrega la dispersión del nuevo bucket a la lógica interna del hashing.
		if ( usandoBucketLibre )
			tablaDeDispersion.at( nuevoNumeroDeBucket ) = dispersionNuevoBucket;
		else
			tablaDeDispersion.push_back(dispersionNuevoBucket);

		// Actualiza la tabla de hash incoorporando el valor del nuevo bloque.
		while (posicionesAreemplazar > 0){
			posicionesAreemplazar--;
			int posicion = (posicionEnTablaDeHash+posicionesAreemplazar*dispersionNuevoBucket);
			posicion = posicion % tablaDeHash.size();
			tablaDeHash[posicion] = nuevoNumeroDeBucket;
		}
	}

	// Se actualiza la dispersion del bucket a redispersar.
	tablaDeDispersion[numeroDeBucket] = dispersionBucketAredispersar;

	// Se crea el nuevo Bucket.
	nuevoBucket = new Bucket(dispersionNuevoBucket,archivo->getDimensionDelBucket());

	if ( usandoBucketLibre ){
		int nrr = tablaDeTraduccion[nuevoNumeroDeBucket];
		archivo->modificarBucket(nrr,nuevoBucket);
		posBloque = nuevoNumeroDeBucket;

	}else{
		posBloque = this->archivo->guardarBucket(nuevoBucket);

		// Agrego el valor del bucket a la tabla de traduccion.
		tablaDeTraduccion.push_back(posBloque);
	}

	// Se crea un nuevo Bucket para redispersar los elementos.
	bucketActualizado = new Bucket(dispersionBucketAredispersar,archivo->getDimensionDelBucket());
	int nrr = tablaDeTraduccion[numeroDeBucket];
	archivo->modificarBucket(nrr,bucketActualizado);

	int cantidadDeRegistros = bucket->getCantidadDeRegistros();
	list<Registro*>::iterator iterador = bucket->ubicarPrimero();

	for(int i = 0;i< cantidadDeRegistros;i++){

		unsigned long clave = (*iterador)->obtenerClave();

		if ( agregarRegistroInt(*iterador,clave) != operacionOK )
			resultado = operacionFALLO;

		iterador++;
	}

	// libero el bucket que instancie para la redispersion
	delete bucket;

	return resultado;
}

/* METODOS PUBLICOS ***********************************************************/

Registro* HashingExtensible::obtenerRegistro(Registro* registro){

	Registro* registroObtenido = NULL;

	unsigned int posicionEnTablaDeHash = obtenerPosicion(registro->obtenerClave());

	if (posicionEnTablaDeHash < tablaDeHash.size()){

		int numeroDeBucket = tablaDeHash[posicionEnTablaDeHash];

		Resultados resultado = estadoDelBucket(numeroDeBucket);

		if ( resultado == bucketDisponible ){
			int nrr = tablaDeTraduccion[numeroDeBucket];
			Bucket* bucket = archivo->obtenerBucket(nrr);
			registroObtenido = bucket->getRegistro(registro);
		}
	}

	return registroObtenido;
}

Resultados HashingExtensible::cargarRegistro(Registro *registro){

	unsigned long clave = registro->obtenerClave();
	//cout << "clave: " << clave << endl;

	return agregarRegistroInt(registro,clave);
}

Resultados HashingExtensible::agregarRegistro(Registro* registro){

	Resultados resultado = claveRepetida;

	// Verficacion de unicidad de clave.
	unsigned long clave = registro->obtenerClave();
//	cout << "clave: " << clave << endl;
	Registro* registroDuplicado = obtenerRegistro(registro);

	if ( !registroDuplicado )
		resultado = agregarRegistroInt(registro,clave);

	else{
		//cout << "clave repetida "<<endl;
		delete registroDuplicado;
	}

	return resultado;
}

Resultados HashingExtensible::reducirTablaDeHash(){

	Resultados resultado = operacionFALLO;

	int n = tablaDeHash.size();
	int m = n/2;

	int i = 0;
	int j = m;
	bool distintos = false;

	vector<int>::iterator inicio;

	// Busca si las dos mitades de la tabla son iguales.
	while ( (distintos == false) && (i < m) ){
		if ( tablaDeHash[i++]==tablaDeHash[j++] )
			inicio++;
		else
			distintos = true;
	}

	// Reduce la tabla a la mitad si son iguales.
	if ( distintos == false ){
		tablaDeHash.resize(m);
		resultado = operacionOK;

		//cout << "Se redujo la tabla de Hash ";
	}

	return resultado;
}


Resultados HashingExtensible::liberarBucket(unsigned int posicionEnTablaDeHash){

	//cout << endl << "Se inicia la liberacion del bucket " << endl;

	Resultados resultado = operacionOK;

	int numeroDeBucket = tablaDeHash.at(posicionEnTablaDeHash);

	if ( tablaDeHash.size() == 1 ){

		// Libero el bucket y lo ubico en la lista de libres.
		tablaDeDispersion.pop_back();   //ESTO LO SACO!!
		tablaDeHash.pop_back();

		// Se procede a liberar el bucket
		int nrrBucket = tablaDeTraduccion[numeroDeBucket];
		archivo->liberarBucket(nrrBucket);

		// Agrego el numero de bucket a la lista de buckets libres.
		listaDeBucketsLibres.push_back(numeroDeBucket);

	}else{

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

			// calculo la cantidad de posiciones a reemplazar en la tabla de hash.
			int posicionesAreemplazar = tablaDeHash.size()/dispersionDelBucket;

			// Libero el bucket y lo ubico en la lista de libres.
			if ( numeroDeBucket == (int)(tablaDeDispersion.size() -1 ) )
				tablaDeDispersion.pop_back();
			else
				tablaDeDispersion.at(numeroDeBucket) = BUCKET_LIBRE;


			// Se procede a liberar el bucket
			int nrrBucket = tablaDeTraduccion[numeroDeBucket];
			archivo->liberarBucket(nrrBucket);

			// Agrego el numero de bucket a la lista de buckets libres.
			listaDeBucketsLibres.push_back(numeroDeBucket);

			// Obtengo el bucket posterior/anterior.
			int nrrBucketPosterior = tablaDeTraduccion[numeroDelBucketPosterior];
			Bucket* bucketPosterior = archivo->obtenerBucket(nrrBucketPosterior);

			// Actualiza la tabla de hash incoorporando el valor del nuevo bloque.
			while (posicionesAreemplazar > 0){
				posicionesAreemplazar--;
				int posicion = (posicionEnTablaDeHash+posicionesAreemplazar*dispersionDelBucket);
				posicion = posicion % tablaDeHash.size();
				tablaDeHash[posicion] = numeroDelBucketPosterior;
			}

			// Cambio la dispersion del bucket posterior.
			tablaDeDispersion[numeroDelBucketPosterior] /= 2;
			bucketPosterior->setTamanioDeDispersion(tablaDeDispersion[numeroDelBucketPosterior]);
			archivo->modificarBucket(nrrBucketPosterior,bucketPosterior);

			imprimirTablaDeHash();
			imprimirTablaDeDispersion();

			// Verificar si los bloques se encuentran duplicados.
			if ( resultado == operacionOK )
				resultado = reducirTablaDeHash();

		}
	}
	return resultado;
}

Resultados HashingExtensible::modificarRegistro(Registro* registro){
	Resultados resultado = registroInexistente;

	if ( !tablaDeHash.empty() ){

		unsigned long clave = registro->obtenerClave();
		int posicionEnTablaDeHash = obtenerPosicion(clave);
		int numeroDeBucket = tablaDeHash[posicionEnTablaDeHash];

		if ( bucketDisponible == estadoDelBucket(numeroDeBucket) ){

			int nrr = tablaDeTraduccion[numeroDeBucket];

			Bucket* bucket = archivo->obtenerBucket(nrr);

			bool registroReemplazado = bucket->reemplazarRegistro(registro);

			if ( registroReemplazado ){

				archivo->modificarBucket(nrr,bucket);
				resultado = operacionOK;


			}else{

				Registro* registroObtenido = bucket->getRegistro(registro);

				if ( registroObtenido != NULL ){
					// En este caso no hubo exito al almacenar el registro y
					// estaba disponible dentro del bucket.
					bucket->eliminarRegistro(registroObtenido);

					resultado = redispersarBucket(bucket,numeroDeBucket,posicionEnTablaDeHash);

					if ( resultado == operacionOK )
						agregarRegistro(registro);
				}

				delete registroObtenido;
			}
		}
	}
	return resultado;
}

Resultados HashingExtensible::eliminarRegistro(Registro* registro){

	Resultados resultado = operacionOK;

	// Obtengo el Bucket a partir de la clave.
	unsigned long clave = registro->obtenerClave();
	int posicionEnTablaDeHash = obtenerPosicion(clave);
	if ( tablaDeHash.size() > 0 ){
		int numeroDeBucket = tablaDeHash[posicionEnTablaDeHash];

		if ( bucketDisponible == estadoDelBucket(numeroDeBucket) ){

			int nrr = tablaDeTraduccion[numeroDeBucket];
			Bucket* bucket = archivo->obtenerBucket(nrr);

			// Obtengo el registro.
			//cout << "Registro a buscar en eliminar registro: " << registro->obtenerClave() << endl;
			Registro* registroObtenido = bucket->getRegistro(registro);

			if ( registroObtenido !=NULL ){

				// Eliminamos el registro
				if ( bucket->eliminarRegistro(registroObtenido) )
					archivo->modificarBucket(nrr,bucket);

				else
					resultado = operacionFALLO;

				// Si el bucket quedó vacío, evaluo si lo puedo liberar.
				if ( bucket->getCantidadDeRegistros() == 0 )
					liberarBucket(posicionEnTablaDeHash);

				delete registroObtenido;
			}

			else
				resultado = operacionFALLO;

			imprimirTablaDeHash();
			imprimirTablaDeDispersion();
		}
	}else{
		resultado = operacionFALLO;
	}

	return resultado;
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

void HashingExtensible::mostrarArchivoDeHash()
{
	cout << endl;
	int size = tablaDeTraduccion.size();

	for(int i=0;i< size;i++){
		bool bucketLibre = false;
		int nrr = tablaDeTraduccion[i];

		cout << "tamaño de la tabla de dispersion: "<< tablaDeDispersion.size() << endl;

		if ( tablaDeTraduccion.size() > tablaDeDispersion.size() ){
			bool fin = false;
			list<int>::iterator it2 = listaDeBucketsLibres.begin();
			while (!fin){
				cout << "salida tabla: " << *it2 << endl;
				if ( it2 == listaDeBucketsLibres.end() )
					fin = true;

				else {
					if ( i == *it2 ){
						bucketLibre = true;
						fin = true;
					}
					else
						it2++;
				}
			}
		}else{
			if ( tablaDeDispersion[i] == BUCKET_LIBRE )
				bucketLibre = true;
		}

		cout << tablaDeTraduccion[i] << " B"<<i << " :";

		if (bucketLibre)
			cout << "Bucket libre " << endl;

		else{
			Bucket* bucket = archivo->obtenerBucket(nrr);
			int espacioLibre = bucket->getEspacioLibre();
			cout << "(free=" << espacioLibre<<") :";
			int cantRegs = bucket->getCantidadDeRegistros();
			cout << " (cant: " << cantRegs << "): " << endl;
			list<Registro*>::iterator it = bucket->ubicarPrimero();
			for(int i = 0; i < cantRegs; i++){
				(*it)->verContenido();
				it++;
				cout << endl;
			}
			cout << endl;
		}

	}

	this->imprimirTablaDeHash();
	this->imprimirTablaDeDispersion();
}

HashingExtensible::~HashingExtensible() {
	archivoDeControl->persistirLista(&listaDeBucketsLibres);
	archivoDeControl->persistirVector(&tablaDeTraduccion);
	archivoDeControl->persistirVector(&tablaDeHash);
	archivoDeControl->persistirVector(&tablaDeDispersion);
	delete archivoDeControl;

	delete archivo;
}

