#include "ArchivoDeBuckets.h"

/*** METODOS PRIVADOS *********************************************************/

/*
 * Realiza un pasaje desde un char del tamanio del bucket a un string
 */

std::string* ArchivoDeBuckets::charToString(char* cadena){

	stringstream stream;
	stream.write(cadena,this->dimensionBucket);
	std::string* nuevoString = new string( stream.str() );

	cout << *nuevoString << "size " << nuevoString->size() << endl;
	return nuevoString;
}

/*
 * Realiza un pasaje desde un string a un char* del tamaño del bucket.
 * El string debe tener longitud menor al tamanioBucket.
 */

char* ArchivoDeBuckets::stringToChar(std::string* cadena){
	cout << "cadena: " << *cadena << endl;
	cout << "Conversion desde un char a un string" << endl;

	char* nuevaCadena = new char[this->dimensionBucket];
	memcpy(nuevaCadena,cadena->c_str(),this->dimensionBucket);

	return nuevaCadena;
}

int	ArchivoDeBuckets::obtenerNumeroDeBucket(int numeroDeBloque){
	return numeroDeBloque/this->dimensionBucket - 1;
}

int	ArchivoDeBuckets::obtenerNumeroDeBloque(int numeroDeBucket){
	return (numeroDeBucket+1)*this->dimensionBucket;
}

int ArchivoDeBuckets::guardarBukcetEnBloque(int numeroDeBloque,Bucket* bucket){

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

	this->archivo = new ArchivoBloques(path,tamanioBucket);
	this->dimensionBucket = tamanioBucket;
	this->ultimoNumeroDeBucketAlmacenado = -1;
}

Bucket *ArchivoDeBuckets::obtenerBucket(int numeroDeBucket){

	Bucket* bucket = NULL;

	if ( numeroDeBucket <= this->ultimoNumeroDeBucketAlmacenado ){

		#warning "Si el numeroDeBucket fue liberado me lo devuelve igual".
		int nrr = this->obtenerNumeroDeBloque(numeroDeBucket);
		char* bucketSerializado = new char[this->dimensionBucket];
		this->archivo->obtenerBloque(nrr,bucketSerializado);

		string* stringBucket = charToString(bucketSerializado);
		delete[] bucketSerializado;

		#warning "El bucketSerializado podría tener tamaño nulo, ver como lo resuelve el Bucket.";

		cout << "dimension del bucket a deserealizar: " << stringBucket->size() << endl;
		bucket = new Bucket(this->dimensionBucket,0);
		bucket->deserializar(stringBucket);

		delete stringBucket;
	}

	return bucket;
}

int ArchivoDeBuckets::liberarBucket(int numeroDeBucket){

	int nrr = this->obtenerNumeroDeBloque(numeroDeBucket);
	this->archivo->borrarBloque(nrr);
}

int ArchivoDeBuckets::modificarBucket(int numeroDeBucket,Bucket* bucket){

	int nrr = this->obtenerNumeroDeBloque(numeroDeBucket);
	this->guardarBukcetEnBloque(nrr,bucket);

}

int ArchivoDeBuckets::guardarBucket(Bucket* bucket)
{
	int nrr;
	this->archivo->crearNuevoBloque(&nrr);
	int numeroDeBucket = this->obtenerNumeroDeBucket(nrr);

	if ( this->ultimoNumeroDeBucketAlmacenado < numeroDeBucket )
		this->ultimoNumeroDeBucketAlmacenado++;

	this->guardarBukcetEnBloque(nrr,bucket);

	return numeroDeBucket;
}

int ArchivoDeBuckets::bucketDisponible(int numeroDeBucket)
{
}

int ArchivoDeBuckets::getDimensionDelBucket()
{
	return this->dimensionBucket;
}

void ArchivoDeBuckets::eliminarArchivoDeBuckets()
{
}

ArchivoDeBuckets::~ArchivoDeBuckets() {
	// De mart a MartinH: "this->archivo->cerrarArchivo();" ya no es necesaria.
	// Tendrías que reemplazarla con: "delete (this->archivo);".
	// Luego el destructor hace el "cerrarArchivo()" automáticamente.
	this->archivo->cerrarArchivo();
	cout << "se cerro el archivo";
}

