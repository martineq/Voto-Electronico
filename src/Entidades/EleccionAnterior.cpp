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
	int tamanioFecha = this->fecha.size(); //por default es 8
	int tamanioCargo = TAM_INT + this->cargo.size();
	return (tamanioFecha + tamanioCargo);
}

string EleccionAnterior::getFecha () {
	return this->fecha;
}

string EleccionAnterior::getCargo () {
	return this->cargo;
}
