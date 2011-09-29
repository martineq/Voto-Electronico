#ifndef VOTANTE_H_
#define VOTANTE_H_

#include <list>
#include <string>
#include "Eleccion.h"
#include "EleccionAnterior.h"
#include <iostream>
#include "Entidad.h"

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
	Votante();
	Votante(int dni, string nombre, string password, string domicilio, string distrito);
	virtual ~Votante();
	void setNombre (string);
	void setPassword (string);
	void setDomicilio (string);
	void setDistrito (string);
	void agregarEleccion (string,string);
	int  getTamanio();
	int getClave();
	void deserializar (string* source);
	void verVotante ();
	int getDNI ();
	string getNombre ();
	string getPassword ();
	string getDomicilio ();
	string getDistrito ();
	string* serializar();

	/*
	 * Instancia un nuevo objeto, copia de actual.
	 */
	Entidad* duplicar();

	/*
	 * Devuelve el tipo de la entidad instanciada.
	 */
	NombreDeEntidad getNombreDeEntidad();
};

#endif /* VOTANTE_H_ */
