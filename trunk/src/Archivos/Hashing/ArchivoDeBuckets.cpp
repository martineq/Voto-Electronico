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

	if ( ultimoBucket != bucket ){

		if ( ultimoBucket != NULL)
			delete ultimoBucket;

		ultimoBucket = bucket;
		numeroUltimoBucket = numeroDeBucket;
	}
}

char* ArchivoDeBuckets::serializarBucket(Bucket* bucket){

	string* stringBucket = bucket->serializar();

	stringstream stream;
	stream.write(stringBucket->c_str(),stringBucket->size());

	char* nuevaCadena = new char[dimensionBucket];
	stream.read(nuevaCadena,stringBucket->size());

	delete stringBucket;
	return nuevaCadena;
}

Bucket* ArchivoDeBuckets::deserializadBucket(char* cadena){
	stringstream stream;

	stream.write(cadena,dimensionBucket);
	string* stringBucket = new string(stream.str());
	Bucket* bucket = new Bucket(0,dimensionBucket);
	bucket->deserializar(stringBucket);

	delete stringBucket;
	return bucket;
}

void ArchivoDeBuckets::guardarBukcetEnBloque(int nrr){

	char* bucketSerializado = serializarBucket(ultimoBucket);
	archivo->guardarBloque(nrr,bucketSerializado);
	delete[] bucketSerializado;
}

/*** METODOS PUBLICOS *********************************************************/

ArchivoDeBuckets::ArchivoDeBuckets(char* path, int tamanioBucket){

	archivo = new ArchivoBloques(path,tamanioBucket);
	dimensionBucket = tamanioBucket;
	ultimoBucket = NULL;
	numeroUltimoBucket = -1;
}

Bucket *ArchivoDeBuckets::obtenerBucket(int numeroDeBucket){

	Bucket* bucket = NULL;

		if ( numeroDeBucket != numeroUltimoBucket ){

			char* cadena = new char[dimensionBucket];
			this->archivo->obtenerBloque(numeroDeBucket,cadena);
			Bucket* nuevoBucket = deserializadBucket(cadena);
			delete[] cadena;
			modificarBucketInterno(nuevoBucket,numeroDeBucket);
		}

		bucket = ultimoBucket;

	return bucket;
}

void ArchivoDeBuckets::liberarBucket(int numeroDeBucket){

	modificarBucketInterno(NULL,-1);

}

void ArchivoDeBuckets::modificarBucket(int nrr,Bucket* bucket){

	modificarBucketInterno(bucket,nrr);
	guardarBukcetEnBloque(nrr);
}

int ArchivoDeBuckets::guardarBucket(Bucket* bucket)
{
	int nrr;
	archivo->crearNuevoBloque(&nrr);
	modificarBucketInterno(bucket,nrr);
	guardarBukcetEnBloque(nrr);

	return nrr;
}

int ArchivoDeBuckets::getDimensionDelBucket()
{
	return dimensionBucket;
}

ArchivoDeBuckets::~ArchivoDeBuckets() {
	delete archivo;
	if ( ultimoBucket != NULL )
		delete ultimoBucket;
	cout << endl << "se cerro el archivo" << endl;
}

