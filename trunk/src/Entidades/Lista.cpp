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
//	buffer.write((char*)&cantidadDeBytes,TAM_INT);
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
	stringstream * miString;
	delete source;
	int cantidadDeBytes;

//	hidrato la nombre
	buffer.read((char*)&cantidadDeBytes,TAM_INT);
	char* nombreSerializado = new char[cantidadDeBytes];
	buffer.read((char*)nombreSerializado,cantidadDeBytes);
	miString = new stringstream();
	miString->write(nombreSerializado,cantidadDeBytes);
	string* pasoAString = new string (miString->str());
	this->nombre = *pasoAString;
	delete []nombreSerializado;
	delete pasoAString;
	delete miString;

//	hidrato la fecha
//	buffer.read((char*)&cantidadDeBytes,TAM_INT);
	cantidadDeBytes = TAM_FECHA;
	char* fechaSerializada = new char[cantidadDeBytes];
	buffer.read((char*)fechaSerializada,cantidadDeBytes);
	miString = new stringstream();
	miString->write(fechaSerializada,cantidadDeBytes);
	pasoAString = new string (miString->str());
	this->fecha = *pasoAString;
	delete []fechaSerializada;
	delete pasoAString;
	delete miString;

//	hidrato el cargo
	buffer.read((char*)&cantidadDeBytes,TAM_INT);
	char* cargoSerializado = new char[cantidadDeBytes];
	buffer.read((char*)cargoSerializado,cantidadDeBytes);
	miString = new stringstream();
	miString->write(cargoSerializado,cantidadDeBytes);
	pasoAString = new string (miString->str());
	this->cargo = *pasoAString;
	delete []cargoSerializado;
	delete pasoAString;
	delete miString;
//	hidrato cantidad De Votos
	buffer.read((char*)&this->cantidadDeVotos,TAM_SINT);
}

Entidad *Lista::duplicar()
{
	Lista* copia = new Lista();
	copia->cantidadDeVotos = this->cantidadDeVotos;
	copia->cargo = this->cargo;
	copia->fecha = this->fecha;
	copia->nombre = this->nombre;
	return copia;
}

NombreDeEntidad Lista::getNombreDeEntidad(){
	return tLista;
}

