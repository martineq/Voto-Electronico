#include "Entidad.h"
#include <iostream>
using namespace std;

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

	/*
	 * Devuelve el objeto serializado, si no tiene contenido, devuelve un string
	 * de dimension 0.
	 */
	std::string* serializar();

	/*
	 * Devuelve la dimension del objeto serializado, si no tiene distrito asignado,
	 * devuelve 0.
	 */
	int getTamanio();

	int getClave();

	void deserializar(std::string* source);

	/*
	 * Devuelve el nombre que identifica al objeto.
	 */
	NombreDeEntidad getNombreDeEntidad();

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

