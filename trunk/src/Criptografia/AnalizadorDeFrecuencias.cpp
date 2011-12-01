#include "AnalizadorDeFrecuencias.h"

AnalizadorDeFrecuencias::AnalizadorDeFrecuencias(int cantidadElementos) {
	this->listaDeFrecuencias.resize(cantidadElementos);
}

bool AnalizadorDeFrecuencias::incrementarFrecuencia(int posicion)
{
	supremo = false;

	bool resultado = false;
	if ( posicion >= 0 and posicion < (int)listaDeFrecuencias.size()){
		listaDeFrecuencias.at(posicion)++;
		resultado = true;
	}
	return resultado;
}

bool AnalizadorDeFrecuencias::existeSupremo()
{
	int maximo = 0;
	int repeticiones = 0;
	int size = this->listaDeFrecuencias.size();
	int i = 0;

	while ( i < size ){
		if ( maximo < listaDeFrecuencias.at(i) ){
			maximo = listaDeFrecuencias.at(i);
			repeticiones = 0;
		}
		else if ( maximo == listaDeFrecuencias.at(i) )
			repeticiones++;

		i++;
	}

	if ( repeticiones == 0 )
		supremo = true;

	return supremo;
}

int AnalizadorDeFrecuencias::posicionMaximaFrecuencia()
{
	int posicionMaximo = -1;

	if ( supremo == true ){

		int maximo = 0;
		int size = this->listaDeFrecuencias.size();
		int i = 0;

		while ( i < size ){
			if ( maximo < listaDeFrecuencias.at(i) ){
				maximo = listaDeFrecuencias.at(i);
				posicionMaximo = i;
			}
			i++;
		}
	}

	return posicionMaximo;
}

void AnalizadorDeFrecuencias::mostrarListaDeFrecuencias(){
	int size = listaDeFrecuencias.size();
	for(int i = 0; i < size; i++){
//		cout << listaDeFrecuencias.at(i) <<" ";
//		cout << i << "(" << listaDeFrecuencias.at(i) <<") ";
//		cout << (char) i << "@,";
		cout << i << " - " << (char)i << " (" << listaDeFrecuencias.at(i) << ") ";
	}
	cout << endl;
}

AnalizadorDeFrecuencias::~AnalizadorDeFrecuencias() {
	// TODO Auto-generated destructor stub
}

