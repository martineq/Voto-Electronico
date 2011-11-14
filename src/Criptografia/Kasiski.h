/*
 * Kasiski.h
 *
 *  Created on: 13/11/2011
 *      Author: lucas
 */

#ifndef KASISKI_H_
#define KASISKI_H_

#include <string>
#include <list>
#include "Patron.h"

using std::string;
using std::list;

class Kasiski {
private:
	string textoCifrado;
	list<Patron> listaPatrones;
	list<int> listaDistancias;
	int maximaLongitudPatron;

	int MCDDistancias();
	int gcd(int a, int b);
	bool noExiste(Patron patron);
	void agregarPatron(Patron patron, int posicion);
	void listarPatrones();
public:
	Kasiski(string);
	string romper();
	virtual ~Kasiski();
};

#endif /* KASISKI_H_ */
