#include "Patron.h"

Patron::Patron(string palabra) {
	this->palabra = palabra;
}

void Patron::agregarDistancia(int distancia){
	this->listaDistancias.push_back(distancia);
}

string Patron::getPalabra(){
	return this->palabra;
}

list<int>::iterator Patron::devolverDistancias(){
	return this->listaDistancias.begin();
}

bool Patron::noEsUltimo(list<int>::iterator iterador){
	return (this->listaDistancias.end() != iterador);
}


Patron::~Patron() {
	// TODO Auto-generated destructor stub
}
