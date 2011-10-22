#include "ArchivoDeControl.h"

ArchivoDeControl::ArchivoDeControl(char* pathArchivo)
{
	string str(pathArchivo);

	archivo = new ManejadorDeArchivo(str);
}

void ArchivoDeControl::persistirVector(vector<int>* tabla){

	stringstream* stream =  new stringstream();
	int size = tabla->size();

	// Almaceno la cantidad de elementos de la lista.
	stream->write((char*)&size,sizeof(int));

	vector<int>::iterator it = tabla->begin();
	for(int i = 0; i < size; i++){
		int valor = *it;
		// Almaceno los elementos del vector.
		stream->write((char*)&valor,sizeof(int));

		it++;
	}

	int sizeVector = sizeof(int)*(size+1);
	char* vectorSerializado = new char[sizeVector];

	stream->read(vectorSerializado,sizeVector);

	archivo->escribir(vectorSerializado,sizeVector);

	delete[] vectorSerializado;
	delete stream;

}


vector<int> ArchivoDeControl::hidratarVector()
{
	vector<int> tabla;

	char* numero = new char[sizeof(int)];
	archivo->leer(numero,sizeof(int));

	stringstream* stream = new stringstream();
	stream->write(numero,sizeof(int));
	delete[] numero;

	int cantidadDeElementos = stream->get();
	delete stream;

	int sizeBuffer = sizeof(int)*cantidadDeElementos;
	char* vector = new char[sizeBuffer];
	archivo->leer(vector,sizeBuffer);

	stream =  new stringstream();
	stream->write(vector,sizeBuffer);
	delete[] vector;

	for(int i = 0; i < cantidadDeElementos; i++){
		int valor;
		stream->read((char*)&valor,sizeof(int));
		tabla.push_back(valor);
	}
	delete stream;

	return tabla;
}

void ArchivoDeControl::persistirLista(list<int> *lista)
{
	stringstream* stream =  new stringstream();
	int size = lista->size();

	// Almaceno la cantidad de elementos de la lista.
	stream->write((char*)&size,sizeof(int));

	list<int>::iterator it = lista->begin();
	for(int i = 0; i < size; i++){

		int valor = *it;
		// Almaceno los elementos del vector.
		stream->write((char*)&valor,sizeof(int));

		it++;
	}

	int sizeVector = sizeof(int)*(size+1);
	char* vectorSerializado = new char[sizeVector];

	stream->read(vectorSerializado,sizeVector);

	archivo->escribir(vectorSerializado,sizeVector);

	delete[] vectorSerializado;
	delete stream;
}

list<int> ArchivoDeControl::hidratarLista()
{
	list<int> lista;

	char* numero = new char[sizeof(int)];
	archivo->leer(numero,sizeof(int));

	stringstream* stream = new stringstream();
	stream->write(numero,sizeof(int));
	delete[] numero;

	int cantidadDeElementos = stream->get();
	delete stream;

	int sizeBuffer = sizeof(int)*cantidadDeElementos;
	char* vector = new char[sizeBuffer];
	archivo->leer(vector,sizeBuffer);

	stream =  new stringstream();
	stream->write(vector,sizeBuffer);
	delete[] vector;

	for(int i = 0; i < cantidadDeElementos; i++){
		int valor;
		stream->read((char*)&valor,sizeof(int));
		lista.push_back(valor);
	}
	delete stream;

	return lista;
}

bool ArchivoDeControl::vacio()
{
	bool archivoVacio = true;
	int fileSize = archivo->obtenerTamArchivo();
	if (fileSize != 0)
		archivoVacio = false;

	return archivoVacio;
}

ArchivoDeControl::~ArchivoDeControl() {
	delete archivo;
}

