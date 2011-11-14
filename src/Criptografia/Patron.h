

#ifndef PATRON_H_
#define PATRON_H_

#include <string>
#include <list>

using std::string;
using std::list;

class Patron {
private:
	string palabra;
	list<int> listaDistancias;
public:
	Patron(string);
	void agregarDistancia(int distancia);
	string getPalabra();
	list<int>::iterator devolverDistancias();
	bool esUltimo(list<int>::iterator iterador);
	virtual ~Patron();
};

#endif /* PATRON_H_ */
