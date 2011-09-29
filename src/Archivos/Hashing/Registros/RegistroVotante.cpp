#include "RegistroVotante.h"

RegistroVotante::RegistroVotante(){
	this->contenido = NULL;
}

RegistroVotante::RegistroVotante(Entidad *entidad) {
	this->contenido = entidad;
	this->determinarClave();
}

void RegistroVotante::setContenido(Entidad* entidad){
	if ( this->contenido != NULL )
		delete(this->contenido);

//	#warning	"No se duplica la entidad";
	//this->contenido = entidad->duplicar();
	this->contenido = entidad;
	// Realizo el cálculo de la nueva clave.
	this->determinarClave();
}

Entidad* RegistroVotante::getContenido(){
	return this->contenido;
}

Registro* RegistroVotante::duplicar(){

	Registro* nuevoRegistro = new RegistroVotante();
	nuevoRegistro->setContenido(this->contenido);
	return nuevoRegistro;
}

void RegistroVotante::deserializar(std::string *source)
{
	if ( this->contenido != NULL )
		delete(this->contenido);

	Votante* unVotante = new Votante();
	unVotante->deserializar(source);
	this->contenido = unVotante;

	// Realizo el cálculo de la nueva clave.
	this->determinarClave();
}

/*
 * Hidrata el objeto, devolviendo una instancia de tipo RegistroVotante.
 */
Registro* RegistroVotante::hidratar(std::string *source){
	RegistroVotante* unRegistro = new RegistroVotante();
	unRegistro->deserializar(source);

	// Realizo el cálculo de la nueva clave.
	unRegistro->determinarClave();

	return (Registro*) unRegistro;
}

RegistroVotante::~RegistroVotante() {
	delete(this->contenido);
}

