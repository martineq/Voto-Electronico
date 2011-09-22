#include "Votante.h"

Votante::Votante(int dni, string nombre, string password, string domicilio, string distrito) {
	this->dni=dni;
	this->nombre=nombre;
	this->password=password;
	this->domicilio=domicilio;
	this->distrito=distrito;
	this->listaDeEleccionesAnteriores=new list <EleccionAnterior*>;
}

Votante::~Votante() {
	list<EleccionAnterior*>::iterator it = listaDeEleccionesAnteriores->begin();
	while (it!=listaDeEleccionesAnteriores->end()) {
		delete (*it);
	}
	delete (listaDeEleccionesAnteriores);
}

void Votante::setNombre (string nombre) {
	this->nombre=nombre;
}
void Votante::setPassword (string password) {
	this->password=password;
}
void Votante::setDomicilio (string domicilio) {
	this->domicilio=domicilio;
}
void Votante::setDistrito (string distrito) {
	this->distrito=distrito;
}
void Votante::agregarEleccion (string fecha, string cargo) {
	EleccionAnterior* unaEleccionAnterior = new EleccionAnterior (fecha,cargo);
	listaDeEleccionesAnteriores->push_back(unaEleccionAnterior);
}
int Votante::getDNI () {
	return this->dni;
}
string Votante::getNombre () {
	return this->nombre;
}
string Votante::getPassword () {
	return this->password;
}
string Votante::getDomicilio () {
	return this->domicilio;
}
string Votante::getDistrito () {
	return this->distrito;
}
void Votante::verEleccionesAnteriores (){
	cout << "Elecciones Anteriores: " << endl;
	cout << "---------------------- " << endl;
	if (this->listaDeEleccionesAnteriores->size()==0)
		cout << "El votante no participo de ninguna eleccion a la fecha" << endl;
	else {
		list<EleccionAnterior*>::iterator it = this->listaDeEleccionesAnteriores->begin();
		while (it!=listaDeEleccionesAnteriores->end()) {
			cout << "Fecha: " << (*it)->getFecha() << "  Cargo: " << (*it)->getCargo() << endl;
			it++;
		}
	}
	cout << endl;
}

void Votante::verVotante() {
	cout << "Nombre: "    << this->nombre   << endl;
	cout << "Password: "  << this->password << endl;
	cout << "Domicilio: " << this->domicilio<< endl;
	cout << "Distrito: "  << this->distrito << endl;
	this->verEleccionesAnteriores ();
}

string* Votante::serializar(){

	cout << endl;
	cout << "Comienzo de serializado" << endl;

	stringstream buffer;
	int cantidadDeBytes;
	buffer.write((char*)&this->dni,TAM_INT);
	cantidadDeBytes   = this->nombre.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->nombre.c_str(),cantidadDeBytes);
	cantidadDeBytes   = this->password.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->password.c_str(),cantidadDeBytes);
	cantidadDeBytes   = this->domicilio.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->domicilio.c_str(),cantidadDeBytes);
	cantidadDeBytes   = this->distrito.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->distrito.c_str(),cantidadDeBytes);
	int tamanioDeLaListaDeElecciones= this->listaDeEleccionesAnteriores->size();
	buffer.write((char*)&tamanioDeLaListaDeElecciones,TAM_INT);
	list<EleccionAnterior*>:: iterator it = this->listaDeEleccionesAnteriores->begin();
	for (int i=0; i<tamanioDeLaListaDeElecciones; i++){
		cantidadDeBytes = ((*it)->getFecha()).size();
		buffer.write((char*)&cantidadDeBytes,TAM_INT);
		buffer.write((char*)((*it)->getFecha()).c_str(),cantidadDeBytes);
		cantidadDeBytes = ((*it)->getCargo()).size();
		buffer.write((char*)&cantidadDeBytes,TAM_INT);
		buffer.write((char*)((*it)->getCargo()).c_str(),cantidadDeBytes);
		it++;
	}
	string* datos = new string(buffer.str());
	cout << "Fin de serializado" << endl;
	cout << endl;
	return datos;
}

void Votante::deserializar(string * source){
	istringstream buffer (*source);
	int cantidadDeBytes;

//	hidrato el dni
    buffer.read((char*)&this->dni,TAM_INT);

//  hidrato el nombre
    buffer.read((char*)&cantidadDeBytes,TAM_INT);
    char* nombre = new char[cantidadDeBytes];
    buffer.read((char*)nombre,cantidadDeBytes);
    string* pasoAString = new string (nombre);
    this->nombre = *pasoAString;
    delete (nombre);
    delete (pasoAString);

//  hidrato el password
    buffer.read((char*)&cantidadDeBytes,TAM_INT);
    char* password = new char[cantidadDeBytes];
    buffer.read((char*)password,cantidadDeBytes);
    pasoAString = new string (password);
    this->password = *pasoAString;
    delete (password);
    delete (pasoAString);

//  hidrato el distrito
    buffer.read((char*)&cantidadDeBytes,TAM_INT);
    char* distrito = new char[cantidadDeBytes];
    buffer.read((char*)distrito,cantidadDeBytes);
    pasoAString = new string (distrito);
    this->distrito = *pasoAString;
    delete (distrito);
    delete (pasoAString);

//  hidrato el domicilio
    buffer.read((char*)&cantidadDeBytes,TAM_INT);
    char* domicilio = new char[cantidadDeBytes];
    buffer.read((char*)domicilio,cantidadDeBytes);
    pasoAString = new string (domicilio);
    this->domicilio = *pasoAString;
    delete (domicilio);
    delete (pasoAString);

//  hidrato la lista de elecciones anteriores
    int tamanioDeLaLista;
    buffer.read((char*)&tamanioDeLaLista,TAM_INT);
	for (int i=0; i<tamanioDeLaLista;i++){
		EleccionAnterior* unaEleccionAnterior = new EleccionAnterior();

//		hidrato la fecha de una Eleccion Anterior
		stringstream* bufferAuxiliar = new stringstream(NULL);
		buffer.read((char*)&cantidadDeBytes,TAM_INT);
		char* fechaEnBytes = new char[cantidadDeBytes];
		buffer.read(fechaEnBytes,cantidadDeBytes);
		bufferAuxiliar->write(fechaEnBytes,cantidadDeBytes);
		string fecha = bufferAuxiliar->str();
		unaEleccionAnterior->fecha=fecha;
		delete (bufferAuxiliar);
		delete (fechaEnBytes);

//		hidrato el cargo de la Eleccion Anterior
		bufferAuxiliar = new stringstream(NULL);
		buffer.read((char*)&cantidadDeBytes,TAM_INT);
		char* cargoEnBytes = new char[cantidadDeBytes];
		buffer.read(cargoEnBytes,cantidadDeBytes);
		bufferAuxiliar->write(cargoEnBytes,cantidadDeBytes);
		string cargo = bufferAuxiliar->str();
		unaEleccionAnterior->cargo=cargo;
		delete (cargoEnBytes);
		delete (bufferAuxiliar);

		this->listaDeEleccionesAnteriores->push_back(unaEleccionAnterior);
//		el delete de unaEleccionAnterior esta en el destructor
//		porque mi lista es lista de punteros a Eleccion Anterior
	}
}
