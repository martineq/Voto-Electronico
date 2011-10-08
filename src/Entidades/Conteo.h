/*
 * Conteo.h
 *
 *  Created on: 08/10/2011
 *      Author: lucas
 */
#include <string.h>

#ifndef CONTEO_H_
#define CONTEO_H_

#include "Entidad.h"

class Conteo: public Entidad {
private:
	string fechaEleccion;
	string cargoEleccion;
	string nombreLista;
	string distrito;
	unsigned int cantidadVotos;
public:
	Conteo();

	Conteo(string fecha,string cargo,string lista,string distrito);

	int getTamanio();

	int getClave();

	string getFechaEleccion();

	string getCargoEleccion();

	string getLista();

	unsigned int getCantidadVotos();

	void incrementarVotos();

	void decrementarVotos();
	/*
	 * Instancia un nuevo objeto, copia de actual.
	 */
	Entidad* duplicar();

	string* serializar();

	void deserializar(string*);

	NombreDeEntidad getNombreDeEntidad();

	virtual ~Conteo();
};

#endif /* CONTEO_H_ */
