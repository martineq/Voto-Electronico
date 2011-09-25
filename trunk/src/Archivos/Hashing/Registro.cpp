#include "Registro.h"

int Registro::getTamanioRegistro(){
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
