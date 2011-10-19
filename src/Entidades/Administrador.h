/*
 * Administrador.h
 *
 *  Created on: 17/09/2011
 *      Author: mart
 */

#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

#include "../Archivos/Hashing/Bucket.h"
#include "../Archivos/Hashing/HashingExtensible.h"
#include "Eleccion.h"

using namespace std;


class Administrador {
private:
	string nombre;		// Identificador
	string password;
//	FILE* archivo;
	// archivo al estilo c++
	fstream*	archivo;
	list <Eleccion*> listaDeEleccionesHabilitadas;
	list<Lista*> listaDeBoletas;
	int blancos;
	int novalidos;
	bool verificarEleccion(Eleccion*);
	void mostrarEleccionesDelVotante (list<Eleccion*>);
	void abrirArchivoDePassword ();
public:
	Administrador(string pathArchivo);
	bool acceder(string nombre,string password);
	Resultados alta (HashingExtensible*,Registro*);
	bool habilitarEleccion (Eleccion*);
	void consultarEleccionesHabilitadasParaElVotante(Votante*);
	void getEleccionesHabilitadas();
	char sufragar(int);
	void cargarListasDeEleccion(Eleccion*,HashingExtensible*);
	int elegirBoleta(int, Bucket*);
	list <Eleccion*> getListaDeEleccionesHabilitadas();
	list <Lista*> getListaDeBoletas();
	virtual ~Administrador();
};




#endif /* ADMINISTRADOR_H_ */
