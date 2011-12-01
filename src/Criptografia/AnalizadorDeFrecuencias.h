#ifndef ANALIZADORDEFRECUENCIAS_H_
#define ANALIZADORDEFRECUENCIAS_H_

#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

class AnalizadorDeFrecuencias {
private:
	vector<int>		listaDeFrecuencias;
	bool			supremo;

public:
	AnalizadorDeFrecuencias(int cantidadElementos);

	bool incrementarFrecuencia(int posicion);

	bool existeSupremo();

	int posicionMaximaFrecuencia();

	void mostrarListaDeFrecuencias();

	virtual ~AnalizadorDeFrecuencias();
};

#endif /* ANALIZADORDEFRECUENCIAS_H_ */
