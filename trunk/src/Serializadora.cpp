/*
 * Serializadora.cpp
 *
 *  Created on: 15/10/2011
 *      Author: martin
 */

#include "Serializadora.h"

Serializadora::Serializadora() {
	stream = new stringstream();
}

Serializadora::Serializadora(string *stringSerializado)
{
	stream = new stringstream(*stringSerializado);
}

void Serializadora::agregarInt(int valor)
{
	stream->write((char*)&valor,TAM_INT);
}

void Serializadora::agregarString(string* cadena)
{
	int size = cadena->size();
	agregarInt(size);
	stream->write((char*)cadena->c_str(),size);
}

string *Serializadora::obtenerSerializacion()
{
	return new string(stream->str());
}

int Serializadora::obtenerInt()
{
	int valor;
	stream->read((char*)&valor,TAM_INT);
	return valor;
}

string *Serializadora::obtenerStringPointer()
{
	int size = obtenerInt();
	char* aux = new char[size];
	stream->read(aux,size);
	stringstream abc;
	abc.write(aux,size);
	string* cadena = new string(abc.str());
	delete aux;
	return cadena;
}

string Serializadora::obtenerString()
{
	int size = obtenerInt();
	char* aux = new char[size];
	stream->read(aux,size);
	stringstream abc;
	abc.write(aux,size);
	delete aux;
	return abc.str();
}

void Serializadora::agregarShortInt(short int valor)
{
	stream->write((char*)&valor,TAM_SINT);
}

short int Serializadora::obtenerShortInt()
{
	short int valor;
	stream->read((char*)&valor,TAM_SINT);
	return valor;
}

Serializadora::~Serializadora() {
	delete stream;
}

