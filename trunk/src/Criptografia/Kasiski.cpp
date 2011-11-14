/*
 * Kasiski.cpp
 *
 *  Created on: 13/11/2011
 *      Author: lucas
 */

#include "Kasiski.h"

Kasiski::Kasiski(string textoARomper) {
	this->textoCifrado = textoARomper;
	this->maximaLongitudPatron = 0;
}

int Kasiski::MCDDistancias(){
	list<Patron>::iterator it = this->listaPatrones.begin();
	int mcd = (*(it->devolverDistancias()));

	while (it != this->listaPatrones.end()){
		list<int>::iterator itInts = it->devolverDistancias();
		while (! it->esUltimo(itInts)){
			mcd = gcd(mcd,(*itInts));
			itInts++;
		}
		it++;
	}
	return mcd;
}

int Kasiski::gcd(int a, int b){
	if (b == 0) return a;
	return gcd(b, a%b);
}

bool Kasiski::noExiste(Patron patron){
	bool encontrado = false;
	list<Patron>::iterator it = this->listaPatrones.begin();
	while ((it != this->listaPatrones.end()) and (!encontrado)){
		if (patron.getPalabra() != it->getPalabra()){
			encontrado = true;
		}
	}
	return encontrado;
}

void Kasiski::listarPatrones(){
	int cantidadCharsComun = 3;
	unsigned int posicion = 0;
	unsigned int posicionUltimaOcurrencia = posicion;
	unsigned int posicionDesde = 3;
	string textoABuscar;
	string textoRestante;

	while (posicion < (this->textoCifrado.length() - 2)) {
		posicionUltimaOcurrencia = posicion;
		textoABuscar = this->textoCifrado.substr(posicion,cantidadCharsComun);
		Patron patron(textoABuscar);
		if (noExiste(patron)) {
			posicionDesde = posicion+cantidadCharsComun;
			while (posicionDesde < this->textoCifrado.length()){
				posicionDesde = this->textoCifrado.find(textoABuscar,posicionDesde);
				if (posicionDesde != string::npos){
					int diferencia = posicionDesde - posicionUltimaOcurrencia;
					posicionUltimaOcurrencia = posicionDesde;
					posicionDesde += cantidadCharsComun;
					patron.agregarDistancia(diferencia);
				}
			}
			if (posicionUltimaOcurrencia != posicion){
				this->listaPatrones.push_back(patron);
			}
		}
		posicion++;
	}
}

string Kasiski::romper(){
	this->listarPatrones();
	int mcd = this->MCDDistancias();
}
Kasiski::~Kasiski() {
	// TODO Auto-generated destructor stub
}
