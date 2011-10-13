/*
 * Administrador.h
 *
 *  Created on: 17/09/2011
 *      Author: mart
 */

#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_

#include <string>
#include "../Archivos/Hashing/Bucket.h"
#include "Eleccion.h"
#include <list>
#include <iostream>

using namespace std;


class Administrador {
private:
	string nombre;		// Identificador
	string password;
	list <Eleccion*> listaDeEleccionesHabilitadas;
	list<Lista*> listaDeBoletas;
	int blancos;
	int novalidos;
	bool verificarEleccion(Eleccion*);
	void mostrarEleccionesDelVotante (list<Eleccion*>);
public:
	Administrador();
	Administrador(string nombre, string password);
	bool acceder(string nombre,string password);
	bool alta (Bucket*,Registro*);
	bool habilitarEleccion (Eleccion*);
	void consultarEleccionesHabilitadasParaElVotante(Votante*);
	void getEleccionesHabilitadas();
	char sufragar(int);
	int mostrarListasDeEleccion(int,Bucket*);
	list <Eleccion*> getListaDeEleccionesHabilitadas();
	virtual ~Administrador();
};




#endif /* ADMINISTRADOR_H_ */
