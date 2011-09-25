#include "ArchivoDeBuckets.h"

ArchivoDeBuckets::ArchivoDeBuckets(){

}

Bucket *ArchivoDeBuckets::obtenerBucket(int numeroDeBucket)
{
	if (this->archivo.size() > numeroDeBucket)
		this->archivo[numeroDeBucket];
	else
		throw "Bucket inexistente";
}

int ArchivoDeBuckets::crearNuevoBucket()
{
	Bucket* bucket = new Bucket(0);
	int numeroDeBucket = guardarBucket(bucket);
	return numeroDeBucket;
}

void ArchivoDeBuckets::liberarBucket(int numeroDeBucket)
{
	if ( this->archivo.size() > numeroDeBucket ){
		this->bucketsLibres.push_back(numeroDeBucket);
		delete(this->archivo.at(numeroDeBucket));
		this->archivo.at(numeroDeBucket) = NULL;
	}else{
		throw "Bucket inexistente";
	}

}

void ArchivoDeBuckets::modificarBucket(int numeroDeBucket,Bucket* bucket){
	if (this->archivo.size() > numeroDeBucket ){
		bucket = this->archivo.at(numeroDeBucket);
		if ( bucket != NULL ){
			delete(this->archivo.at(numeroDeBucket));
			this->archivo.at(numeroDeBucket)=bucket;
		}else{
			throw "bucket en lista de libres";
		}
	}else{
		throw "numeroDeBucket excede cantidad de buckets almacenados.";
	}
}


int ArchivoDeBuckets::guardarBucket(Bucket* bucket)
{
	int numeroDeBucket;
		// se busca en la lista de libres, si está vacio
		// se agrega al final
	if ( this->bucketsLibres.empty() ){
		this->archivo.push_back(bucket);
		numeroDeBucket = this->archivo.size()-1;
	}else{

		// si la lista tiene elementos, se obtiene el primer
		// bucket disponible
		numeroDeBucket = this->bucketsLibres.front();
		bucketsLibres.erase(bucketsLibres.begin());
		archivo[numeroDeBucket] = bucket;
	}

	return numeroDeBucket;

}

ArchivoDeBuckets::~ArchivoDeBuckets() {
	// TODO Auto-generated destructor stub
}

