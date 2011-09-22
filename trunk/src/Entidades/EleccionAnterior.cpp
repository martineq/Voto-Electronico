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

string EleccionAnterior::getFecha () {
	return this->fecha;
}

string EleccionAnterior::getCargo () {
	return this->cargo;
}
