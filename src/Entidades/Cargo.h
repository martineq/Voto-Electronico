/*
 * Cargo.h
 *
 *  Created on: 17/09/2011
 *      Author: lucas
 */

#ifndef CARGO_H_
#define CARGO_H_

#include <string>
#include <list>


using namespace std;

class Cargo {
private:
	string cargo;
	list<string> listaCargos;

public:
	Cargo();
	Cargo(string cargoPrincipal);
//	void modificarCargo(string nuevoCargo);
	string getCargo();
	bool agregarCargo(string subCargo);
	bool eliminarCargo(string subCargo);
	virtual ~Cargo();
};

#endif /* CARGO_H_ */
