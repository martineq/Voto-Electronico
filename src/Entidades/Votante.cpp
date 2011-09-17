#include "Votante.h"

Votante::Votante(short int dni, string nombre, string password, string domicilio, string distrito) {
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
void Votante::agregarEleccion (Eleccion unaEleccion) {
	string fecha=unaEleccion.getFecha();
	string cargo=unaEleccion.getCargo();
	EleccionAnterior* unaEleccionAnterior = new EleccionAnterior (fecha,cargo);
	listaDeEleccionesAnteriores->push_back(unaEleccionAnterior);
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
void Votante::getEleccionesAnteriores (){
	list<EleccionAnterior*>::iterator it = listaDeEleccionesAnteriores->begin();
	while (it!=listaDeEleccionesAnteriores->end()) {
		cout << "Fecha: " << (*it)->getFecha() << "  Cargo: " << (*it)->getCargo() << endl;
	}
}
