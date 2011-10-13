#ifndef LISTA_H_
#define LISTA_H_

#include <string>
#include <iostream>
#include "Entidad.h"
using namespace std;

class Lista : public Entidad {
private:
	string nombre;
	string fecha;
	string cargo;
	short int cantidadDeVotos;
	bool verificarCargo(string);
public:
	Lista();
	Lista(string nombre, string fecha, string cargo);
	string getNombre ();
	string getFecha ();
	string getCargo ();
	int getTamanio();
	int getClave();
	short int getCantidadDeVotos ();
	void incrementarVotos ();
	virtual ~Lista();
	string* serializar();
	void deserializar (string*);

	/*
	 * Instancia un nuevo objeto, copia de actual.
	 */
	Entidad* duplicar();

	/*
	 * Devuelve el tipo de la entidad instanciada.
	 */
	NombreDeEntidad getNombreDeEntidad();
};

#endif /* LISTA_H_ */
