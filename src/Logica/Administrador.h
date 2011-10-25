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
	list <Eleccion*> listaDeEleccionesDelVotante;
	list<Lista*> listaDeBoletas;
	int blancos;
	int novalidos;
	void mostrarEleccionesDelVotante (list<Eleccion*>);
	void abrirArchivoDePassword ();
	string* getString(vector<char> vect);
public:
	Administrador(string pathArchivo);
	bool acceder(string nombre,string password);
	Resultados altaHash (HashingExtensible*,Registro*);
	Resultados bajaHash(HashingExtensible* he,Registro* unRegistro);
	Resultados modificaHash(HashingExtensible* he,Registro* unRegistro);
	int altaArbol (bplustree*,Registro*);
	bool habilitarEleccion (Eleccion*);
	bool consultarEleccionesHabilitadasParaElVotante(Votante*);
	void getEleccionesHabilitadas();
	char sufragar(int,char);
	bool cargarListasDeEleccion(Eleccion*,bplustree*);
	int elegirBoleta(char);
	list <Eleccion*> getListaDeEleccionesHabilitadas();
	list <Eleccion*> getListaDeEleccionesDelVotante();
	list <Lista*> getListaDeBoletas();
	int modificaArbol(bplustree* arbolB,Registro* registro);
	int bajaArbol (bplustree* arbolB,Registro* registro);
	virtual ~Administrador();
	void destruir();
};




#endif /* ADMINISTRADOR_H_ */
