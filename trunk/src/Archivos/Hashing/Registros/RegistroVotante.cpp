#include "RegistroVotante.h"

RegistroVotante::RegistroVotante(Entidad *entidad) {
	this->contenido = entidad;
	this->determinarClave();
}

int RegistroVotante::obtenerClave(){
	//TODO
	return 0;
}

Entidad* RegistroVotante::getContenido(){
	return this->contenido;
}

string* RegistroVotante::serializar(){

}

void RegistroVotante::deserializar(string * source){

}


RegistroVotante::~RegistroVotante() {
	// TODO Auto-generated destructor stub
}

