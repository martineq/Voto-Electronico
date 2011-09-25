#ifndef REGISTRODISTRITO_H_
#define REGISTRODISTRITO_H_

#include "../Registro.h"
#include "../../../Entidades/Distrito.h"

class RegistroDistrito: public Registro {

private:
	/*
	 * Realiza el cálculo para obtener la clave a partir del ID del distrito.
	 */
	int determinarClave();

public:

	/*
	 * Instancia un objeto sin contenido ni clave.
	 */
	RegistroDistrito();

	/*
	 * Instancia un objeto registro distrito.
	 */
	RegistroDistrito(Entidad* entidad);

	/*
	 * Deserializa el objeto pasado por parámetro.
	 */
	void deserializar(std::string* source);

	/*
	 * Agrega o sobreescribe el contenido del registro
	 */
	void setContenido(Entidad* entidad);


	static Registro* hidratar(std::string* source);

	~RegistroDistrito();

};

#endif /* REGISTRODISTRITO_H_ */
