#include "Lista.h"

Lista::Lista() {
	this->nombre="";
	this->fecha="";
	this->cargo="";
	this->cantidadDeVotos=0;
}

Lista::Lista(string nombre, string fecha, string cargo) {
	this->nombre=nombre;
	this->fecha=fecha;
	this->cargo=cargo;
	this->cantidadDeVotos=0;
}

Lista::~Lista() {
	// TODO Auto-generated destructor stub
}

string Lista::getNombre () {
	return nombre;
}
string Lista::getFecha () {
	return fecha;
}

int Lista::getTamanio(){
	int tamanioNombre = TAM_INT + this->nombre.size();
	int tamanioFecha = this->fecha.size(); //por default 8
	int tamanioCargo = TAM_INT + this->cargo.size();
	int tamanioCantVotos = sizeof(short int);
	return (tamanioNombre + tamanioFecha + tamanioCargo + tamanioCantVotos);
}

int Lista::getClave(){
	return 0;
}

string Lista::getCargo () {
	return cargo;
}
short int Lista::getCantidadDeVotos () {
	return cantidadDeVotos;
}
void Lista::incrementarVotos () {
	this->cantidadDeVotos++;
}

string* Lista::serializar() {
	stringstream buffer;
	int cantidadDeBytes;
	cantidadDeBytes   = this->nombre.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->nombre.c_str(),cantidadDeBytes);
	cantidadDeBytes   = this->fecha.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->fecha.c_str(),cantidadDeBytes);
	cantidadDeBytes   = this->cargo.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->cargo.c_str(),cantidadDeBytes);
	buffer.write((char*)&this->cantidadDeVotos,TAM_SINT);
	string* datos = new string(buffer.str());
	return datos;
}

void Lista::deserializar(string* source) {
	istringstream buffer (*source);
	delete source;
	int cantidadDeBytes;

//	hidrato la nombre
	buffer.read((char*)&cantidadDeBytes,TAM_INT);
	char* nombreSerializado = new char[cantidadDeBytes];
	buffer.read((char*)nombreSerializado,cantidadDeBytes);
	string* pasoAString = new string (nombreSerializado);
	this->nombre = *pasoAString;
	delete []nombreSerializado;
	delete pasoAString;

//	hidrato la fecha
	buffer.read((char*)&cantidadDeBytes,TAM_INT);
	char* fechaSerializada = new char[cantidadDeBytes];
	buffer.read((char*)fechaSerializada,cantidadDeBytes);
	pasoAString = new string (fechaSerializada);
	this->fecha = *pasoAString;
	delete []fechaSerializada;
	delete pasoAString;

//	hidrato el cargo
	buffer.read((char*)&cantidadDeBytes,TAM_INT);
	char* cargoSerializado = new char[cantidadDeBytes];
	buffer.read((char*)cargoSerializado,cantidadDeBytes);
	pasoAString = new string (cargoSerializado);
	this->cargo = *pasoAString;
	delete []cargoSerializado;
	delete pasoAString;

//	hidrato cantidad De Votos
	buffer.read((char*)&this->cantidadDeVotos,TAM_SINT);
}

NombreDeEntidad Lista::getNombreDeEntidad(){
	return tLista;
}

