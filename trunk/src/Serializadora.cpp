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
	stream->write((char*)&valor,sizeof(int));
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
	stream->read((char*)&valor,sizeof(int));
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

Serializadora::~Serializadora() {
	delete stream;
}

