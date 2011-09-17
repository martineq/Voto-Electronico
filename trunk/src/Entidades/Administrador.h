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
	string nombre;
	string password;

public:
	Administrador();
	Administrador(string nombre, string password);
	bool acceder(string nombre,string password);
	virtual ~Administrador();
};




#endif /* ADMINISTRADOR_H_ */
