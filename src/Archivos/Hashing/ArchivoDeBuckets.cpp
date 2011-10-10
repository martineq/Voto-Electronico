#include "ArchivoDeBuckets.h"

/*** METODOS PRIVADOS *********************************************************/

void ArchivoDeBuckets::modificarBucketInterno(Bucket* bucket, int numeroDeBucket){
	if (numeroDeBucket != this->numeroUltimoBucket){
		if ( this->ultimoBucket != NULL ){
			delete this->ultimoBucket;
			cout << "Se borró el bucket" << endl;
		}
		this->ultimoBucket = bucket;
		this->numeroUltimoBucket = numeroDeBucket;
	}
}

char* ArchivoDeBuckets::stringToChar(std::string* cadena){

	stringstream stream;

	int valido = bucketOcupado;
	stream.write((char*)&valido,STATUS_SIZE);
	stream.write(cadena->c_str(),cadena->size());

	cout << "cadena: " << stream.str() << endl;
	cout << "Conversion desde un char a un string" << endl;

	char* nuevaCadena = new char[this->dimensionBucket];
	stream.get(nuevaCadena,this->dimensionBucket);

	return nuevaCadena;
}

int	ArchivoDeBuckets::obtenerNumeroDeBucket(int numeroDeBloque){
	return numeroDeBloque/this->dimensionBucket - 1;
}

int	ArchivoDeBuckets::obtenerNumeroDeBloque(int numeroDeBucket){
	return (numeroDeBucket+1)*this->dimensionBucket;
}

void ArchivoDeBuckets::guardarBukcetEnBloque(int numeroDeBloque,Bucket* bucket){

	string* stringBucket = bucket->serializar();
	char* bucketSerializado = stringToChar(stringBucket);

	cout << "bucketSerializado: (size = " << stringBucket->size() << " ) "<< endl;

	this->archivo->guardarBloque(numeroDeBloque,bucketSerializado);
	delete[] bucketSerializado;

	cout << "Se guardo el bucket: " << *stringBucket << endl;
	delete stringBucket;
}

/*** METODOS PUBLICOS *********************************************************/

ArchivoDeBuckets::ArchivoDeBuckets(char* path, int tamanioBucket){

	// Agrego 1byte más para manejar el estado del bucket.
	tamanioBucket = tamanioBucket+STATUS_SIZE;

	this->archivo = new ArchivoBloques(path,tamanioBucket);
	this->dimensionBucket = tamanioBucket;
	this->bucketsAlmacenados = -1;

	this->ultimoBucket = NULL;
	this->numeroUltimoBucket = -1;
}

Resultados ArchivoDeBuckets::bucketDisponible(int numeroDeBucket)
{
	Resultados resultado = bucketOcupado;

	if ( numeroDeBucket <= this->bucketsAlmacenados ){

		if ( this->numeroUltimoBucket != numeroDeBucket){

			int nrr = this->obtenerNumeroDeBloque(numeroDeBucket);
			char* bucketSerializado = new char[this->dimensionBucket];
			this->archivo->obtenerBloque(nrr,bucketSerializado);

			stringstream stream;
			stream.write(bucketSerializado,STATUS_SIZE);

			if (bucketOcupado == stream.get()){

				stringstream streamBucket;
				streamBucket.write(bucketSerializado,dimensionBucket-STATUS_SIZE);
				string* stringBucket = new string(streamBucket.str());

				#warning "El bucketSerializado podría tener tamaño nulo, ver como lo resuelve el Bucket.";

				cout << "dimension del bucket a deserealizar: " << stringBucket->size() << endl;
				Bucket* nuevoBucket = new Bucket(0,this->dimensionBucket);
				nuevoBucket->deserializar(stringBucket);

				this->modificarBucketInterno(nuevoBucket,numeroDeBucket);

				delete stringBucket;
			}else{
				resultado = bucketLibre;
			}
		}
		//else reutiliza el bucket en memoria.
	}else{
		resultado = bucketNoDisponible;
	}
	return resultado;
}

Bucket *ArchivoDeBuckets::obtenerBucket(int numeroDeBucket){

	Bucket* bucket = NULL;

		if (bucketDisponible(numeroDeBucket)==bucketOcupado)
			bucket = this->ultimoBucket;

	return bucket;
}

Resultados ArchivoDeBuckets::liberarBucket(int numeroDeBucket){

	int nrr = this->obtenerNumeroDeBloque(numeroDeBucket);

	Resultados resultado = bucketDisponible(numeroDeBucket);
	if (resultado == bucketOcupado){
		if ( this->ultimoBucket != NULL )
			delete this->ultimoBucket;
		this->numeroUltimoBucket = -1;
		this->ultimoBucket = NULL;
		this->archivo->borrarBloque(nrr);
		resultado = operacionOK;
	}

	return resultado;
}

Resultados ArchivoDeBuckets::modificarBucket(int numeroDeBucket,Bucket* bucket){

	int nrr = this->obtenerNumeroDeBloque(numeroDeBucket);

	Resultados resultado = bucketDisponible(numeroDeBucket);
	if (resultado == bucketOcupado){
		this->modificarBucketInterno(bucket,numeroDeBucket);
		this->guardarBukcetEnBloque(nrr,bucket);
	}

	return resultado;
}

int ArchivoDeBuckets::guardarBucket(Bucket* bucket)
{
	int nrr;
	this->archivo->crearNuevoBloque(&nrr);
	int numeroDeBucket = this->obtenerNumeroDeBucket(nrr);

	if ( this->bucketsAlmacenados < numeroDeBucket )
		this->bucketsAlmacenados++;

	this->guardarBukcetEnBloque(nrr,bucket);
	this->modificarBucketInterno(bucket,numeroDeBucket);

	return numeroDeBucket;
}

int ArchivoDeBuckets::getDimensionDelBucket()
{
	return this->dimensionBucket;
}

Resultados ArchivoDeBuckets::eliminarArchivoDeBuckets()
{
}

ArchivoDeBuckets::~ArchivoDeBuckets() {
	delete this->archivo;
	if ( this->ultimoBucket != NULL )
		delete this->ultimoBucket;
	cout << "se cerro el archivo";
}
