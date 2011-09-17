#ifndef VOTANTE_H_
#define VOTANTE_H_

#include <list>
#include <string>
#include "Eleccion.h"
#include "EleccionAnterior.h"
#include <iostream>

using namespace std;

class Votante {
private:
	short int dni;
	string nombre;
	string password;
	string domicilio;
	string distrito;
	list <EleccionAnterior*>* listaDeEleccionesAnteriores;

public:
	Votante(short int dni, string nombre, string password, string domicilio, string distrito);
	virtual ~Votante();
	void setNombre (string nombre);
	void setPassword (string password);
	void setDomicilio (string domicilio);
	void setDistrito (string distrito);
	void agregarEleccion (Eleccion unaEleccion);
	string getNombre ();
	string getPassword ();
	string getDomicilio ();
	string getDistrito ();
	void getEleccionesAnteriores ();
};

#endif /* VOTANTE_H_ */
