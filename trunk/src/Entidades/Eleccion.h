/*
 * Eleccion.h
 *
 *  Created on: 17/09/2011
 *      Author: martin
 */

#include <list>
#include <string>
#include "Distrito.h"
#include "Serializable.h"
#include "Cargo.h"

#ifndef ELECCION_H_
#define ELECCION_H_

class Eleccion
//: public Serializable{
{
private:
	string			fecha;				// identificador
	string			cargoPrincipal;		// identificador
	list<Distrito>	distritos;

public:
	Eleccion();

	Eleccion(string fecha,string cargoPrincipal);

	string getFecha();

	void setFecha(string fecha);

	string getCargo();

	void setCargo(string cargoPrincipal);

	bool agregarDistrito(Distrito distrito);

	bool eliminarDistrito(Distrito distrito);

	list<Distrito>::iterator obtenerIterador();

	list<Distrito> getLista();

	~Eleccion();

	//std::string* serializar(){}

	//void deserializar(std::string* source) {}

};

#endif /* ELECCION_H_ */
