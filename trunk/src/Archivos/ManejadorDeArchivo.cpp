#include "ManejadorDeArchivo.h"


ManejadorDeArchivo::ManejadorDeArchivo(){

}

ManejadorDeArchivo::~ManejadorDeArchivo(){

}


// Borra el archivo del disco
void ManejadorDeArchivo::borrar(){
	std::remove(obtenerNombreArchivo().c_str());
}

// Renombra el archivo en disco
void ManejadorDeArchivo::renombrar(string nombreNuevo){
	std::rename(obtenerNombreArchivo().c_str(), nombreNuevo.c_str());
}

// Devuelve el nombre del archivo con la terminación cambiada a "tmp", por ej. "arch.tmp"
string ManejadorDeArchivo::obtenerNombreArchivoTmp(){
	string nombreArchivoTemp = obtenerNombreArchivo();
	nombreArchivoTemp.erase(nombreArchivoTemp.length() - 3, 3);
	nombreArchivoTemp.append("tmp");
	return nombreArchivoTemp;
}

// Devuelve el nombre del archivo
string ManejadorDeArchivo::obtenerNombreArchivo(){
	return this->nombre;
}


pos_type ManejadorDeArchivo::obtenerTamArchivo(){
	ios::pos_type currPos = this->archivo.tellg();
	this->archivo.seekg(0,ios_base::end);
	ios::pos_type lastPos = this->archivo.tellg();
	this->archivo.seekg(currPos,ios_base::beg);
	return lastPos;
}

pos_type ManejadorDeArchivo::obtenerPosicionDeLectura(){
	return this->archivo.tellg();
}

bool ManejadorDeArchivo::fin(){
	bool esEof = (this->archivo.peek() == char_traits<char>::eof());

	if (esEof)
		this->archivo.clear(); // Saco el flag y permito operaciones posteriores

	return esEof;
}

void ManejadorDeArchivo::sincroBuffer(){
	if (this->archivo.is_open()) {
		this->archivo.flush();

		if (this->archivo.bad())
			cerr << "No se pudo grabar correctamente el registro en el disco " << endl;
	}
	else {
		cerr << "El archivo no está abierto" << endl;
	}
}

void ManejadorDeArchivo::posicionarseEnFin(){
	if (this->archivo.is_open()) {
		this->archivo.seekg(0, ios_base::end);

		if (this->archivo.fail())
			cerr << "No se pudo posicionar correctamente el registro" << endl;
	}
	else {
		cerr << "El archivo no está abierto" << endl;
	}
}

void ManejadorDeArchivo::posicionarse(ios::pos_type posicion){
	if (this->archivo.is_open()) {
		this->archivo.seekg(posicion, ios_base::beg);

		if (this->archivo.fail())
			cerr << "No se pudo posicionar correctamente el registro" << endl;
	}
	else {
		cerr << "El archivo no está abierto" << endl;
	}
}

void ManejadorDeArchivo::escribir(const char* registro, size_t cantBytes){
	if (this->archivo.is_open()) {
		this->archivo.write(registro, cantBytes);

		if (this->archivo.fail())
			cerr << "No se pudo escribir correctamente el registro";
	} else {
		cerr << "El archivo no está abierto";
	}
}

void ManejadorDeArchivo::leer(char* registro, size_t cantBytes){
	if (this->archivo.is_open()) {
		this->archivo.read(registro, cantBytes);

		if (this->archivo.fail())
			cerr << "No se pudo leer correctamente el registro";
	} else {
		cerr << "El archivo no está abierto";
	}
}

void ManejadorDeArchivo::cerrar(){
	this->archivo.close();
}

void ManejadorDeArchivo::abrir(string nombre){
	this->archivo.open(nombre.c_str(), ios::in | ios::out | ios::binary);

	// Si el archivo no existe, lo crea
	if (!this->archivo.is_open()) {

		this->archivo.clear();

		this->archivo.open(nombre.c_str(), ios::out | ios::binary);
		this->archivo.close();

		this->archivo.open(nombre.c_str(), ios::in|ios::out|ios::binary);

		if (! this->archivo.is_open())
			cerr << "El archivo no pudo ser abierto" << endl;
	}
	this->nombre = nombre;
}



