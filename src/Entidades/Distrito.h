#include "Entidad.h"

#ifndef DISTRITO_H_
#define DISTRITO_H_

class Distrito : public Entidad {

private:
	std::string distrito;

public:

	Distrito();

	Distrito(std::string distrito);

	std::string getDistrito();

	void setDistrito(std::string distrito);

	std::string* serializar();

	int getTamanio();

	int getClave();

	void deserializar(std::string* source);

	/*
	 * Realiza una copia del objeto de tipo Distrito.
	 */
	Entidad* duplicar();

	/*
	 * Instancia un Distrito a partir de un objeto serializado.
	 */
	static Entidad* hidratar(std::string* source);

	~Distrito();

};

#endif /* DISTRITO_H_ */

