#ifndef LISTA_H_
#define LISTA_H_

#include <string>
#include <iostream>
using namespace std;

class Lista {
private:
	string nombre;
	string fecha;
	string cargo;
	short int cantidadDeVotos;
public:
	Lista(string nombre, string fecha, string cargo);
	string getNombre ();
	string getFecha ();
	short int getCantidadDeVotos ();
	void incrementarVotos ();
	virtual ~Lista();
};

#endif /* LISTA_H_ */
