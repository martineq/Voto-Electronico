#include "ArchivoDeBuckets.h"

ArchivoDeBuckets::ArchivoDeBuckets(char* path, int tamanioBucket)
{
	this->archivo = new ArchivoBloques(path,tamanioBucket);
	this->tamanioBucket = tamanioBucket;
	this->ultimoNumeroDeBucketAlmacenado = -1;

}

int ArchivoDeBuckets::crearNuevoBucket()
{
	Bucket* bucket = new Bucket(0);
	int numeroDeBucket = ++this->ultimoNumeroDeBucketAlmacenado;
	cout << "tamanio del string serializado: " << bucket->serializar()->size() << endl;
	stringstream stream;
	stream << bucket->serializar();
	char* cadena = new char[bucket->serializar()->size()+1];
	stream.read(cadena,bucket->serializar()->size());
	//char bucketSerializado = *(bucket->serializar()->c_str());
	cout << "tamanio del char serializado: " << sizeof(*cadena) << endl;
	this->archivo->guardarBloque(numeroDeBucket,cadena);
	cout << "Se almacenó el siguiente bucket " << cadena << endl;
	delete(cadena);
	return numeroDeBucket;
}

Bucket *ArchivoDeBuckets::obtenerBucket(int numeroDeBucket)
{
	Bucket* bucket;
	if (this->ultimoNumeroDeBucketAlmacenado >= numeroDeBucket){

		char* bucketSerializado = new char[this->tamanioBucket];
		this->archivo->obtenerBloque(numeroDeBucket,bucketSerializado);
		bucket = new Bucket(0);
		std::string stringBucket = bucketSerializado;
		delete bucketSerializado;
		cout << "Se obtuvo el siguiente bucket " << stringBucket << endl;
		bucket->deserializar(&stringBucket);
	}
	else
		throw "Bucket inexistente";


	return bucket;
}

void ArchivoDeBuckets::liberarBucket(int numeroDeBucket)
{
	if ( this->ultimoNumeroDeBucketAlmacenado > numeroDeBucket ){
		this->bucketsLibres.push_back(numeroDeBucket);
		this->archivo->borrarBloque(numeroDeBucket);
	}else{
		throw "Bucket disponible";
	}

}

void ArchivoDeBuckets::modificarBucket(int numeroDeBucket,Bucket* bucket){

	if (this->ultimoNumeroDeBucketAlmacenado > numeroDeBucket ){

		char* bucketSerializado = new char[this->tamanioBucket];
		bucketSerializado = (char*)bucket->serializar()->c_str();
		this->archivo->guardarBloque(numeroDeBucket,bucketSerializado);
	}else{
		throw "numeroDeBucket excede cantidad de buckets almacenados.";
	}
}


int ArchivoDeBuckets::guardarBucket(Bucket* bucket)
{
	int numeroDeBucket;
	char* bucketSerializado = new char[this->tamanioBucket];

//	bucketSerializado = (char*)bucket->serializar()->c_str();
	strcpy(bucketSerializado,bucket->serializar()->c_str());
		// se busca en la lista de libres, si está vacio
		// se agrega al final
	if ( this->bucketsLibres.empty() ){
		this->ultimoNumeroDeBucketAlmacenado++;
		numeroDeBucket = this->ultimoNumeroDeBucketAlmacenado;
		archivo->guardarBloque(numeroDeBucket,bucketSerializado);
		cout << "Se guardo el bucket: " << bucketSerializado << endl;

	}else{

		// si la lista tiene elementos, se obtiene el primer
		// bucket disponible

		int cantidadDeBucketsLibres = this->bucketsLibres.size();
		numeroDeBucket = this->bucketsLibres.at(cantidadDeBucketsLibres);
		this->bucketsLibres.erase(this->bucketsLibres.end());
		archivo->guardarBloque(numeroDeBucket,bucketSerializado);

	}

	return numeroDeBucket;

}

ArchivoDeBuckets::~ArchivoDeBuckets() {
	this->archivo->cerrarArchivo();
}

