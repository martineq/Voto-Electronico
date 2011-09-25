#include "Registro.h"

/*
 * El método realiza el cálculo de la clave modificando el atributo de la clase
 * debe ser invocado luego de modificar el contenido.
 */
void Registro::determinarClave(){
	this->clave = this->contenido->getClave();
}


int Registro::getTamanio(){
	return this->contenido->getTamanio();
}

std::string *Registro::serializar()
{
	return this->contenido->serializar();
}

Entidad *Registro::getContenido()
{
	return this->contenido;
}

int Registro::obtenerClave(){
	if ( this->contenido == NULL )
		throw "Contenido inexistente";

	return this->clave;
}

Registro::~Registro()
{
	delete(this->contenido);
	this->contenido = NULL;
}
