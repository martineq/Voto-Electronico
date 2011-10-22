#ifndef SERIALIZADORA_H_
#define SERIALIZADORA_H_

#include <string>
#include <sstream>
#include <iostream>
#include "../Entidades/Constantes.h"

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

class Serializadora {
private:

	stringstream*	stream;
public:
	/*
	 * Instancia para serializar
	 */
	Serializadora();

	/*
	 * Instancia para deserializar.
	 */
	Serializadora(string* stringSerializado);

	/*
	 * Agrega un int al stream.
	 */
	void agregarInt(int valor);

	/*
	 * Agrega un short int al stream.
	 */
	void agregarShortInt(short int valor);

	/*
	 * Agrega un string al stream.
	 */
	void agregarString(string* cadena);

	/*
	 * Devuelve el resultado de la serializacion.
	 */
	string* obtenerSerializacion();

	/*
	 * Devuelve un int.
	 */
	int		obtenerInt();

	/*
	 * Obtiene un short int del stream.
	 */
	short int obtenerShortInt();

	/*
	 * Devuelve un string, debe ser liberado luego de ser usado.
	 */
	string*	obtenerStringPointer();

	/*
	 * Devuelve un string.
	 */
	string	obtenerString();

	virtual ~Serializadora();
};

#endif /* SERIALIZADORA_H_ */
