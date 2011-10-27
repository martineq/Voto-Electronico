#include "ManejadorDeArchivo.h"

// Constructor con parámetro para abrir automáticamente
ManejadorDeArchivo::ManejadorDeArchivo(string nombre){
	this->abrir(nombre);
}

// Destructor
ManejadorDeArchivo::~ManejadorDeArchivo(){
	// Al destruir la clase cierro el archivo
	this->archivo.close();
}

// Borra el archivo del disco
void ManejadorDeArchivo::borrar(){
	std::remove(obtenerNombreArchivo().c_str());
}

// Devuelve el nombre del archivo
string ManejadorDeArchivo::obtenerNombreArchivo(){
	return this->nombre;
}

// Devuelve el tamaño del archivo
ios::pos_type ManejadorDeArchivo::obtenerTamArchivo(){
	ios::pos_type currPos = this->archivo.tellg();
	this->archivo.seekg(0,ios_base::end);
	ios::pos_type lastPos = this->archivo.tellg();
	this->archivo.seekg(currPos,ios_base::beg);
	return lastPos;
}

// Devuelve la posición del puntero de lectura, dentro del archivo
ios::pos_type ManejadorDeArchivo::obtenerPosicionDeLectura(){
	return this->archivo.tellg();
}

// Devuelve true si llegué al fin de archivo
bool ManejadorDeArchivo::fin(){
	bool esEof = (this->archivo.peek() == char_traits<char>::eof());

	if (esEof)
		this->archivo.clear(); // Saco el flag y permito operaciones posteriores

	return esEof;
}

// Guarda los datos bufferizados del archivo en el disco (acá aparece la noción del buffer del sistema)
void ManejadorDeArchivo::guardarBuffer(){
	if (this->archivo.is_open()) {
		this->archivo.flush();

		if (this->archivo.bad())
			cerr << "No se pudo grabar correctamente en el disco " << endl;
	}
	else {
		cerr << "El archivo no está abierto" << endl;
	}
}

// Posiciono el puntero de lectura en el final del archivo
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

// Posiciono el puntero de lectura en la posición <pos>
void ManejadorDeArchivo::posicionarse(ios::pos_type pos){
	if (this->archivo.is_open()) {
		this->archivo.seekg(pos, ios_base::beg);
		if (this->archivo.fail())
			cerr << "No se pudo posicionar correctamente el registro" << endl;
	}
	else {
		cerr << "El archivo no está abierto" << endl;
	}
}

// Escribo en el archivo el <registro>, de una longitud <cantBytes> (en la posición actual del archivo)
void ManejadorDeArchivo::escribir(const char* registro, size_t cantBytes){
	if (this->archivo.is_open()) {
		this->archivo.write(registro, cantBytes);

		if (this->archivo.fail())
			cerr << "No se pudo escribir correctamente el registro";
	} else {
		cerr << "El archivo no está abierto";
	}
}

// Leo desde el archivo y guardo en <registro>, con una longitud <cantBytes> (en la posición actual del archivo)
void ManejadorDeArchivo::leer(char* registro, size_t cantBytes){
	if (this->archivo.is_open()) {
		this->archivo.read(registro, cantBytes);
		if (this->archivo.fail())
			cerr << "No se pudo leer correctamente el registro";
	} else {
		cerr << "El archivo no está abierto";
	}
}


// Abro el archivo de nombre <nombre>
void ManejadorDeArchivo::abrir(string nombre){
	this->archivo.open(nombre.c_str(), ios::in | ios::out | ios::binary);

	// Si el archivo no existe, lo crea
	if (!this->archivo.is_open()) {

		this->archivo.clear();

		this->archivo.open(nombre.c_str(), ios::out | ios::binary);
		this->archivo.close();

		this->archivo.open(nombre.c_str(), ios::in|ios::out|ios::binary);

		if (! this->archivo.is_open())
			cerr << "ERROR: El archivo no pudo ser abierto" << endl;
	}
	this->nombre = nombre;
}



