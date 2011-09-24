#ifndef VOTANTE_H_
#define VOTANTE_H_

#include <list>
#include <string>
#include "Eleccion.h"
#include "EleccionAnterior.h"
#include <iostream>
#include "Entidad.h"
#include "Constantes.h"

using namespace std;

class Votante : public Entidad {
private:
	int dni;
	string nombre;
	string password;
	string domicilio;
	string distrito;
	list <EleccionAnterior*>* listaDeEleccionesAnteriores;
	void verEleccionesAnteriores ();

public:
	Votante(int dni, string nombre, string password, string domicilio, string distrito);
	virtual ~Votante();
	void setNombre (string);
	void setPassword (string);
	void setDomicilio (string);
	void setDistrito (string);
	void agregarEleccion (string,string);
	void deserializar (string* source);
	void verVotante ();
	int getDNI ();
	string getNombre ();
	string getPassword ();
	string getDomicilio ();
	string getDistrito ();
	string* serializar();
};

#endif /* VOTANTE_H_ */
