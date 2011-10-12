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
#include <iostream>

using namespace std;

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

	string getDistrito();

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

	void imprimirConteo();

	virtual ~Conteo();
};

#endif /* CONTEO_H_ */
