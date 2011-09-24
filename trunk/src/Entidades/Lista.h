#ifndef LISTA_H_
#define LISTA_H_

#include <string>
#include <iostream>
#include "Entidad.h"
#include "Constantes.h"
using namespace std;

class Lista : public Entidad {
private:
	string nombre;
	string fecha;
	string cargo;
	short int cantidadDeVotos;
public:
	Lista(string nombre, string fecha, string cargo);
	string getNombre ();
	string getFecha ();
	string getCargo ();
	short int getCantidadDeVotos ();
	void incrementarVotos ();
	virtual ~Lista();
	string* serializar();
	void deserializar (string*);
};

#endif /* LISTA_H_ */
