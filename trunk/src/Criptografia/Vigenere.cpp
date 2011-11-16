#include "Vigenere.h"

Vigenere::Vigenere(string clave){
	this->clave = clave;
	this->cardinalAlfabeto = 256;
	this->posicionCifrador = 0;
	this->posicionDescifrador = 0;
}

Vigenere::Vigenere(string clave,int cardinalAlfabeto){
	this->clave = clave;
	this->cardinalAlfabeto = cardinalAlfabeto;
	this->posicionCifrador = 0;
	this->posicionDescifrador = 0;
}

string* Vigenere::cifrar(string* mensaje){
	string* criptograma = NULL;
	int dimension = clave.size();

	if ( dimension > 0 ){
		unsigned int n = mensaje->size();

		criptograma = new string();

		for(unsigned int i = 0; i < n ; i++ ){
			criptograma->push_back( ( mensaje->at(i) + clave.at( posicionCifrador ) ) % cardinalAlfabeto );
			posicionCifrador = (posicionCifrador + 1 ) % dimension;
		}
	}
	return criptograma;
}

string* Vigenere::descifrar(string* criptograma){

	string* mensaje = NULL;
	int dimension = clave.size();

	if ( dimension > 0 ){
		unsigned int n = criptograma->size();

		mensaje = new string();

		for(unsigned int i = 0; i < n ; i++ ){
			mensaje->push_back( ( criptograma->at(i) - clave.at( i % dimension ) ) % cardinalAlfabeto );
			posicionDescifrador = (posicionDescifrador + 1 ) % dimension;
		}
	}
	return mensaje;
}

void Vigenere::reiniciarCifrador(){
	this->posicionCifrador = 0;
}

void Vigenere::reiniciarDescifrador(){
	this->posicionDescifrador = 0;
}

Vigenere::~Vigenere(){};
