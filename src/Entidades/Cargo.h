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
#include "Constantes.h"

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
	virtual ~Cargo();

	string* serializar();
	void deserializar(string * source);

};

#endif /* CARGO_H_ */
