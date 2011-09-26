#ifndef REGISTRODISTRITO_H_
#define REGISTRODISTRITO_H_

#include "../Registro.h"
#include "../../../Entidades/Distrito.h"

class RegistroDistrito: public Registro {

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

	/*
	 * Instancia un objeto del tipo RegistroDistrito a partir
	 * de otra instancia.
	 */
	Registro* duplicar();

	/*
	 * Instancia un objeto del tipo RegistroDistrito a partir
	 * de un objeto serializado
	 */
	static Registro* hidratar(std::string* source);

	~RegistroDistrito();
};

#endif /* REGISTRODISTRITO_H_ */
