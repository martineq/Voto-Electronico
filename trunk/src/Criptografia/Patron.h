

#ifndef PATRON_H_
#define PATRON_H_

#include <string>
#include <list>

using std::string;
using std::list;

class Patron {
private:
	// almacena el patrón hallado.
	string palabra;

	// lista de distancias entre patrones recurrentes.
	list<int> listaDistancias;

public:

	// constructor del objeto, recibe el patrón en un string.
	Patron(string);

	// agrega una distancia a la lista de distancias.
	void agregarDistancia(int distancia);

	// devuelve el string correspondiente al patrón que caracteriza el objeto.
	string getPalabra();

	// devuelve el iterador al primer elemento de la lista de distancias.
	list<int>::iterator devolverDistancias();

	// devuelve true mientras el iterador pasado por parámetro no apunte al último elemento
	// de la lista.
	bool noEsUltimo(list<int>::iterator iterador);

	virtual ~Patron();
};

#endif /* PATRON_H_ */
