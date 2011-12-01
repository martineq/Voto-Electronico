
#ifndef KASISKI_H
#define	KASISKI_H

#include <string>
#include <list>
#include "Patron.h"
#include "AnalizadorDeFrecuencias.h"

using std::string;
using std::list;

class Kasiski {
private:
    string 			claveEncontrada;
    int				mcd;
	list<Patron> 	listaPatrones;

	int gcd(int a, int b);
	bool noExiste(Patron patron);
	void agregarPatron(Patron patron, int posicion);

public:
	Kasiski();
	void generarPatrones(string*);
	void listarPatrones();
	int MCDDistancias();
	void analisisDeFrecuencias(string);
	string romper();
	~Kasiski();
};

#endif /* KASISKI_H_ */
