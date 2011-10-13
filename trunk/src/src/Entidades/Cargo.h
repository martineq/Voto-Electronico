/*
 * Cargo.h
 *
 *  Created on: 17/09/2011
 *      Author: lucas
 */

#ifndef CARGO_H_
#define CARGO_H_



#include <iostream>
#include <list>
#include "Entidad.h"


using namespace std;

class Cargo : public Entidad {
private:
	string cargo;
	list<string> listaCargos;

public:
	Cargo();
	Cargo(string cargoPrincipal);
//	void modificarCargo(string nuevoCargo);
	string getCargo();
	bool agregarCargo(string subCargo);
	list<string> devolverSubCargos();
	bool eliminarCargo(string subCargo);
	int getTamanio();
	int getClave();
	virtual ~Cargo();

	string* serializar();
	void deserializar(string * source);

	/*
	 * Instancia un nuevo objeto, copia de actual.
	 */
	Entidad* duplicar();

	/*
	 * Devuelve el tipo de la entidad instanciada.
	 */
	NombreDeEntidad getNombreDeEntidad();

};

#endif /* CARGO_H_ */
