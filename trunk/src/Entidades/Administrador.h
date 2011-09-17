/*
 * Administrador.h
 *
 *  Created on: 17/09/2011
 *      Author: mart
 */

#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_

#include <string>
#include <list>

using namespace std;


class Administrador {
private:
	list<string> listaNombre;
	list<string> listapassword;

public:
	Administrador();
	Administrador(string nombre, string password);
	bool agregarAdministrador(string nombre, string password);
	bool eliminarAdministrador(string nombre, string password);
	bool acceder(string nombre,string password);
	virtual ~Administrador();
};




#endif /* ADMINISTRADOR_H_ */
