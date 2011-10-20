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
#include "../Archivos/ArbolBMas/bplustree.h"
#include <stdio.h>
#include <fstream>
#include <sstream>


using namespace std;


class Administrador {
private:
	string nombre;		// Identificador
	string password;
	fstream*	archivo;
	list <Eleccion*> listaDeEleccionesHabilitadas;
	list<Lista*> listaDeBoletas;
	int blancos;
	int novalidos;
	bool verificarEleccion(Eleccion*);
	void mostrarEleccionesDelVotante (list<Eleccion*>);
	void abrirArchivoDePassword ();
	string* getString(vector<char> vect);
public:
	Administrador(string pathArchivo);
	bool acceder(string nombre,string password);
	Resultados altaHash (HashingExtensible*,Registro*);
	int altaArbol (bplustree*,Registro*);
	bool habilitarEleccion (Eleccion*);
	void consultarEleccionesHabilitadasParaElVotante(Votante*);
	void getEleccionesHabilitadas();
	char sufragar(int);
	void cargarListasDeEleccion(Eleccion*,bplustree*);
	int elegirBoleta(int, Bucket*);
	list <Eleccion*> getListaDeEleccionesHabilitadas();
	list <Lista*> getListaDeBoletas();
	virtual ~Administrador();
};




#endif /* ADMINISTRADOR_H_ */
