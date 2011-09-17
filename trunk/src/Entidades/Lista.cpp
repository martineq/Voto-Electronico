#include "Lista.h"

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
short int Lista::getCantidadDeVotos () {
	return cantidadDeVotos;
}
void Lista::incrementarVotos () {
	this->cantidadDeVotos++;
}
