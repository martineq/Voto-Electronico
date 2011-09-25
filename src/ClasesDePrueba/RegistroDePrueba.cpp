#include "RegistroDePrueba.h"



RegistroDePrueba::RegistroDePrueba(Entidad* entidad)
{
	this->contenido = entidad;
}



int RegistroDePrueba::obtenerClave()
{
}



Entidad *RegistroDePrueba::getContenido()
{
	return this->contenido;
}



std::string *RegistroDePrueba::serializar()
{
	return this->contenido->serializar();
}



void RegistroDePrueba::deserializar(std::string *source)
{
	this->contenido->deserializar(source);
}



RegistroDePrueba::~RegistroDePrueba()
{
}

