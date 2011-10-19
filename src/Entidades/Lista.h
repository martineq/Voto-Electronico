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
	bool verificarCargo(string);
public:
	Lista();
	Lista(string nombre, string fecha, string cargo);
	void verEntidad();
	string getNombre ();
	string getFecha ();
	string getCargo ();
	int getTamanio();
	int getClave();
	virtual ~Lista();
	string* serializar();
	void deserializar (string*);
	ResultadoComparacion comparar(Entidad* entidad);

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
