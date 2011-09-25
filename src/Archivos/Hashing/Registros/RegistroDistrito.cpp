#include "RegistroDistrito.h"

RegistroDistrito::RegistroDistrito()
{
	this->contenido = NULL;
}

RegistroDistrito::RegistroDistrito(Entidad *entidad)
{
	#warning "Falta copiar la entidad en el distrito."

	this->contenido = entidad;
}

int RegistroDistrito::determinarClave(){
	Distrito* distrito = (Distrito)this->contenido;

	#warning "Esta solución es sólo para poder realizar pruebas, no es la definitiva."

	return distrito->getDistrito().size();
}

void RegistroDistrito::deserializar(std::string *source)
{
	if ( this->contenido != NULL )
		delete(this->contenido);

	Distrito* distrito = new Distrito();
	distrito->deserializar(source);
	this->contenido = distrito;
}

void RegistroDistrito::setContenido(Entidad* entidad){
	if ( this->contenido != NULL )
		delete(this->contenido);

	#warning "Falta copiar la entidad en el distrito."

	this->contenido = entidad;
}

static Registro *RegistroDistrito::hidratar(std::string *source)
{
	Distrito *distrito = new Distrito();
	distrito->deserializar(source);
	this->contenido = distrito;

	return this;
}



RegistroDistrito::~RegistroDistrito()
{
	delete(this->contenido);
}

