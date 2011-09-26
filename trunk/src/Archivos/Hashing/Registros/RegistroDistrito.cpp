#include "RegistroDistrito.h"

RegistroDistrito::RegistroDistrito()
{
	this->contenido = NULL;
}

RegistroDistrito::RegistroDistrito(Entidad *entidad)
{

	#warning	"No se duplica la entidad";
	//this->contenido = entidad->duplicar();
	this->contenido = entidad;
	this->determinarClave();
}

void RegistroDistrito::deserializar(std::string *source)
{
	if ( this->contenido != NULL )
		delete(this->contenido);

	Distrito* distrito = new Distrito();
	distrito->deserializar(source);
	this->contenido = distrito;

	// Realizo el cálculo de la nueva clave.
	this->determinarClave();
}


void RegistroDistrito::setContenido(Entidad* entidad){
	if ( this->contenido != NULL )
		delete(this->contenido);

	#warning	"No se duplica la entidad";
	//this->contenido = entidad->duplicar();
	this->contenido = entidad;
	// Realizo el cálculo de la nueva clave.
	this->determinarClave();
}


RegistroDistrito::~RegistroDistrito(){
	delete(this->contenido);
}

Registro* RegistroDistrito::duplicar(){

	Registro* nuevoRegistro = new RegistroDistrito();
	nuevoRegistro->setContenido(this->contenido);
	return nuevoRegistro;
}

/*
 * Hidrata el objeto, devolviendo una instancia de tipo RegistroDistrito.
 */
Registro* RegistroDistrito::hidratar(std::string *source){
	RegistroDistrito* registro = new RegistroDistrito();
	registro->deserializar(source);

	// Realizo el cálculo de la nueva clave.
	registro->determinarClave();

	return (Registro*)registro;
}
