#include "RegistroVotante.h"

RegistroVotante::RegistroVotante() {
	this->contenido = new Votante();
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

