#include "ArchivoDeBuckets.h"

/*
 * Realiza un pasaje desde un char del tamanio del bucket a un string
 */

std::string* ArchivoDeBuckets::charToString(char* cadena){

	stringstream stream;
	stream.write(cadena,this->tamanioBucket);
	std::string* nuevoString = new string( stream.str() );

	cout << *nuevoString << "size " << nuevoString->size() << endl;
	//cout << *nuevoString << endl;
	return nuevoString;
}

/*
 * Realiza un pasaje desde un string a un char* del tamaño del bucket.
 * El string debe tener longitud menor al tamanioBucket.
 */

char* ArchivoDeBuckets::stringToChar(std::string* cadena){
	cout << "cadena: " << *cadena << endl;
	cout << "Conversion desde un char a un string" << endl;

	char* nuevaCadena = new char[this->tamanioBucket];
	memcpy(nuevaCadena,cadena->c_str(),cadena->size());

	return nuevaCadena;
}

ArchivoDeBuckets::ArchivoDeBuckets(char* path, int tamanioBucket)
{
	this->archivo = new ArchivoBloques(path,tamanioBucket);
	this->tamanioBucket = tamanioBucket;
	this->ultimoNumeroDeBucketAlmacenado = -1;

}

int ArchivoDeBuckets::crearNuevoBucket()
{
	int numeroDeBucket;
	this->archivo->crearNuevoBloque(&numeroDeBucket);

	// Realizo una transformacion para que los bloques se asignen segun
	// los numeros naturales.
	numeroDeBucket = numeroDeBucket/this->tamanioBucket - 1;

	this->ultimoNumeroDeBucketAlmacenado++;

	return numeroDeBucket;
}

Bucket *ArchivoDeBuckets::obtenerBucket(int numeroDeBucket)
{
	Bucket* bucket2;
	if (this->ultimoNumeroDeBucketAlmacenado >= numeroDeBucket){

		char* bucketSerializado = new char[this->tamanioBucket];

		// transformo el valor a el espacio de bloques.
		numeroDeBucket = (numeroDeBucket+1)*this->tamanioBucket;
		this->archivo->obtenerBloque(numeroDeBucket,bucketSerializado);

		std::string* stringBucket = charToString(bucketSerializado);
		delete bucketSerializado;
//		cout << "Se obtuvo el siguiente bucket: " << *stringBucket << endl;

		bucket2 = new Bucket(0);
		bucket2->deserializar(stringBucket);

		delete stringBucket;
	}
	else
		throw "Bucket inexistente";


	return bucket2;
}

void ArchivoDeBuckets::liberarBucket(int numeroDeBucket)
{
	if ( this->ultimoNumeroDeBucketAlmacenado > numeroDeBucket ){
		this->bucketsLibres.push_back(numeroDeBucket);

		// transformo el valor a el espacio de bloques.
		numeroDeBucket = (numeroDeBucket+1)*this->tamanioBucket;
		this->archivo->borrarBloque(numeroDeBucket);
	}else{
		throw "Bucket disponible";
	}

}

void ArchivoDeBuckets::modificarBucket(int numeroDeBucket,Bucket* bucket){

	if (this->ultimoNumeroDeBucketAlmacenado >= numeroDeBucket ){

		std::string* stringBucket = bucket->serializar();
		int size = stringBucket->size();

		if (size < this->tamanioBucket){
			char* bucketSerializado = stringToChar(stringBucket);

			// transformo el valor a el espacio de bloques.
			numeroDeBucket = (numeroDeBucket+1)*this->tamanioBucket;
			this->archivo->guardarBloque(numeroDeBucket,bucketSerializado);
		}else{
			cerr << "Bucket supera el tamanio del bloque." << endl;
		}

		delete(stringBucket);
	}else{
		throw "numeroDeBucket excede cantidad de buckets almacenados.";
	}
}


int ArchivoDeBuckets::guardarBucket(Bucket* bucket)
{
	int numeroDeBucket;
	string* aux_bucketSerializado = bucket->serializar();

	cout << "bucketSerializado: " << *aux_bucketSerializado << " size: " << aux_bucketSerializado->size() << endl;

//	char* bucketSerializado = new char[this->tamanioBucket];
//	strcpy(bucketSerializado,aux_bucketSerializado->c_str());
	char* bucketSerializado = stringToChar(aux_bucketSerializado);

	// se busca en la lista de libres, si está vacio, se agrega al final.
	if ( this->bucketsLibres.empty() ){

		this->ultimoNumeroDeBucketAlmacenado++;
//		numeroDeBucket = this->ultimoNumeroDeBucketAlmacenado;
		archivo->crearNuevoBloque(&numeroDeBucket);
		archivo->guardarBloque(numeroDeBucket,bucketSerializado);
		numeroDeBucket = numeroDeBucket/this->tamanioBucket - 1;	// transformo el valor a el espacio de bloques.

		cout << "Se guardo el bucket: " << *aux_bucketSerializado << endl;
	}else{
		// si la lista tiene elementos, se obtiene el primer bucket disponible
		int cantidadDeBucketsLibres = this->bucketsLibres.size();
		numeroDeBucket = this->bucketsLibres.at(cantidadDeBucketsLibres);
		this->bucketsLibres.erase(this->bucketsLibres.end());

		// transformo el valor a el espacio de bloques.
		numeroDeBucket = (numeroDeBucket+1)*this->tamanioBucket;
		archivo->guardarBloque(numeroDeBucket,bucketSerializado);
		// transformo el valor a el espacio de bloques.
		numeroDeBucket = numeroDeBucket/this->tamanioBucket - 1;
	}

	delete(aux_bucketSerializado);
	delete(bucketSerializado);
	return numeroDeBucket;

}

ArchivoDeBuckets::~ArchivoDeBuckets() {
	this->archivo->cerrarArchivo();
}

