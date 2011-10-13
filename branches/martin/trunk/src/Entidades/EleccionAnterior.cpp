#include "EleccionAnterior.h"

EleccionAnterior::EleccionAnterior(string fecha, string cargo) {
	this->fecha=fecha;
	this->cargo=cargo;
}

EleccionAnterior::EleccionAnterior() {
	;
}

EleccionAnterior::~EleccionAnterior() {

}

int EleccionAnterior::getTamanio(){
	int tamanioCargo = this->cargo.size();
	return (TAM_FECHA + TAM_INT + tamanioCargo);
}

string EleccionAnterior::getFecha () {
	return this->fecha;
}

string EleccionAnterior::getCargo () {
	return this->cargo;
}

EleccionAnterior* EleccionAnterior::duplicar(){
	EleccionAnterior* copia = new EleccionAnterior();
	copia->cargo = this->cargo;
	copia->fecha = this->fecha;
	return copia;
}
