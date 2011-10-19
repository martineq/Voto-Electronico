#ifndef DISTRITO_H_
#define DISTRITO_H_

#include "Entidad.h"
#include <iostream>
#include "../Auxiliares/ResultadoComparacion.h"

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

	void verEntidad();

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
	 * Devuelve el resultado de comparar la actual entidad con otra.
	 * Los resultados posibles son mayor, menor, igual o comparacionInvalida.
	 * El resultado es respecto del patrón.
	 * Por ejemplo: sean A y B dos entidades, entonces
	 * A->comparar(B) devuelve "mayor" si A es mayor a "B".
	 */
	ResultadoComparacion comparar(Entidad* entidad);

	/*
	 * Instancia un Distrito a partir de un objeto serializado.
	 */
	static Entidad* hidratar(std::string* source);

	virtual ~Distrito();

};

#endif /* DISTRITO_H_ */

