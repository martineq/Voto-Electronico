#include "ArchivoDeBuckets.h"

/*** METODOS PRIVADOS *********************************************************/

Bucket* ArchivoDeBuckets::duplicarBucket(Bucket* bucket){

	Bucket* nuevoBucket = new Bucket(0,dimensionBucket);
	string* stringSerializado = bucket->serializar();
	nuevoBucket->deserializar(stringSerializado);
	delete stringSerializado;
	return nuevoBucket;
}

void ArchivoDeBuckets::modificarBucketInterno(Bucket* bucket, int numeroDeBucket){
		if ( ultimoBucket != NULL )
			delete ultimoBucket;

		ultimoBucket = duplicarBucket(bucket);
		numeroUltimoBucket = numeroDeBucket;
}

char* ArchivoDeBuckets::stringToChar(std::string* cadena){

	stringstream stream;

	int valido = bucketEnUso;
	stream.write((char*)&valido,STATUS_SIZE);
	stream.write(cadena->c_str(),cadena->size());

	char* nuevaCadena = new char[dimensionBucket];
	stream.read(nuevaCadena,dimensionBucket);

	return nuevaCadena;
}

int	ArchivoDeBuckets::obtenerNumeroDeBucket(int numeroDeBloque){
	return numeroDeBloque/this->dimensionBucket - 1;
}

int	ArchivoDeBuckets::obtenerNumeroDeBloque(int numeroDeBucket){
	return (numeroDeBucket+1)*this->dimensionBucket;
}

void ArchivoDeBuckets::guardarBukcetEnBloque(int nrr){

	string* stringBucket = ultimoBucket->serializar();
	char* bucketSerializado = stringToChar(stringBucket);

	cout << "bucketSerializado: (size = " << stringBucket->size()+4 << " ) "<< endl;
	int numeroDeBloque = obtenerNumeroDeBucket(nrr);

	this->archivo->guardarBloque(nrr,bucketSerializado);
	cout << "** Se ALMACENA EN DISCO el bucket: "<< numeroDeBloque << endl;
	delete[] bucketSerializado;

	delete stringBucket;
}

/*** METODOS PUBLICOS *********************************************************/

void ArchivoDeBuckets::mostrarBuckets(){
	int numeroDeBucket = 0;
	Bucket* bucket;


	while ( bucketNoDisponible != bucketDisponible(numeroDeBucket) ){

		bucket = this->obtenerBucket(numeroDeBucket);
		if (bucket != NULL){

			list<Registro*>::iterator it = bucket->ubicarPrimero();
			int cantidad = bucket->getCantidadDeRegistros();
			cout << endl << "Bucket "<<numeroDeBucket << " (disp = ";
			cout << bucket->getTamanioDeDispersion() <<") : ";
			for(int i = 0; i < cantidad ; i++ ){
				Entidad* e = ((Registro*)*it)->getContenido();
				cout <<" "<< e->getClave();
				delete e;
				it++;
			}
			cout << endl;
			numeroDeBucket++;
			delete bucket;

		}else
			cout << endl << "Bucket liberado " << endl;

	}
}

ArchivoDeBuckets::ArchivoDeBuckets(char* path, int tamanioBucket){

	// Agrego 1byte más para manejar el estado del bucket.
	tamanioBucket = tamanioBucket+STATUS_SIZE;

	archivo = new ArchivoBloques(path,tamanioBucket);
	dimensionBucket = tamanioBucket;
	bucketsAlmacenados = -1;
	cantidadBucketsLibres = 0;
	ultimoBucketLibre = -1;

	ultimoBucket = NULL;
	numeroUltimoBucket = -1;
	bucketSerializado = NULL;
}

Resultados ArchivoDeBuckets::bucketDisponible(int numeroDeBucket)
{
	Resultados resultado = bucketEnUso;

	if ( numeroDeBucket <= bucketsAlmacenados and numeroDeBucket >= 0){

		if ( numeroUltimoBucket != numeroDeBucket){

			int nrr = this->obtenerNumeroDeBloque(numeroDeBucket);
			char* bucketEnDisco = new char[this->dimensionBucket];
			this->archivo->obtenerBloque(nrr,bucketEnDisco);

			stringstream stream;
			stream.write(bucketEnDisco,this->dimensionBucket);
			delete[] bucketEnDisco;

			int numero;
			stream.read((char*)&numero,STATUS_SIZE);

			if (bucketEnUso == numero){

				if (this->bucketSerializado != NULL)
					delete bucketSerializado;
				bucketSerializado = new string(stream.str().substr(STATUS_SIZE,dimensionBucket-STATUS_SIZE));

				cout << "**Se OBTUVO DE DISCO el bucket: " << numeroDeBucket << endl;

			}else{
				resultado = bucketLibre;
			}
		}
	}else{
		resultado = bucketNoDisponible;
	}
	return resultado;
}

Bucket *ArchivoDeBuckets::obtenerBucket(int numeroDeBucket){

	Bucket* bucket = NULL;

		if ( bucketDisponible(numeroDeBucket) == bucketEnUso ){

			cout << "Bucket Accedido: "<< numeroDeBucket << " ultimo accedido:" << numeroUltimoBucket << endl;

			if ( numeroDeBucket != numeroUltimoBucket ){

				Bucket* nuevoBucket = new Bucket(0,dimensionBucket);
				nuevoBucket->deserializar(bucketSerializado);
				modificarBucketInterno(nuevoBucket,numeroDeBucket);
				delete nuevoBucket;
			}

			bucket = duplicarBucket(ultimoBucket);
		}

	return bucket;
}

Resultados ArchivoDeBuckets::liberarBucket(int numeroDeBucket){

	Resultados resultado = bucketDisponible(numeroDeBucket);

	if ( resultado == bucketEnUso ){

		if ( ultimoBucket != NULL )
			delete ultimoBucket;
		numeroUltimoBucket = -1;
		ultimoBucket = NULL;

		if ( numeroDeBucket == bucketsAlmacenados ){
			int nrr = this->obtenerNumeroDeBloque(numeroDeBucket);
			this->archivo->borrarBloque(nrr);
			bucketsAlmacenados--;

		}else{

			stringstream stream;
			int num = bucketLibre;
			stream.write((char*)&num,STATUS_SIZE);

			cantidadBucketsLibres++;
			stream.write((char*)&ultimoBucketLibre,STATUS_SIZE);
			ultimoBucketLibre = numeroDeBucket;

			char* cadena = new char[dimensionBucket];
			stream.read(cadena,STATUS_SIZE);

			int nrr = obtenerNumeroDeBloque(numeroDeBucket);
			archivo->guardarBloque(nrr,cadena);
			delete[] cadena;
		}

		resultado = operacionOK;
	}

	return resultado;
}

Resultados ArchivoDeBuckets::modificarBucket(int numeroDeBucket,Bucket* bucket){

	Resultados resultado;

	if ( bucket == NULL){
		resultado = bucketNULO;
	}else{
		resultado = bucketDisponible(numeroDeBucket);

		if (resultado == bucketEnUso){

			modificarBucketInterno(bucket,numeroDeBucket);

			int nrr = obtenerNumeroDeBloque(numeroDeBucket);
			guardarBukcetEnBloque(nrr);

			resultado = operacionOK;
		}
	}
	return resultado;
}

int ArchivoDeBuckets::guardarBucket(Bucket* bucket)
{
	int resultado;

	if ( cantidadBucketsLibres > 0 ){
		int nrrA = obtenerNumeroDeBloque(ultimoBucketLibre);

		if (cantidadBucketsLibres == 1){
			ultimoBucketLibre = -1;
		}else{
			char* cadena = new char[dimensionBucket];
			archivo->obtenerBloque(nrrA,cadena);
			stringstream buffer;
			buffer.write(cadena,dimensionBucket);
			delete[] cadena;
			int num;
			buffer.read((char*)&num,STATUS_SIZE);
			buffer.read((char*)&num,STATUS_SIZE);
			ultimoBucketLibre = num;
		}

		archivo->borrarBloque(nrrA);
		cantidadBucketsLibres--;
	}

	if (bucket != NULL){

		int nrr;
		this->archivo->crearNuevoBloque(&nrr);
		int numeroDeBucket = obtenerNumeroDeBucket(nrr);

		if ( this->bucketsAlmacenados < numeroDeBucket )
			this->bucketsAlmacenados++;

		modificarBucketInterno(bucket,numeroDeBucket);
		guardarBukcetEnBloque(nrr);

		resultado = numeroDeBucket;
	}else{
		resultado = bucketNULO;
	}
	return resultado;
}

int ArchivoDeBuckets::getDimensionDelBucket()
{
	return dimensionBucket;
}

Resultados ArchivoDeBuckets::eliminarArchivoDeBuckets()
{
}

ArchivoDeBuckets::~ArchivoDeBuckets() {
	delete this->archivo;
	if ( this->ultimoBucket != NULL )
		delete this->ultimoBucket;
	if (this->bucketSerializado != NULL)
		delete bucketSerializado;
	cout << "se cerro el archivo";
}

