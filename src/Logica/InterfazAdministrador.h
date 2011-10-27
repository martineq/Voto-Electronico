/*
 * InterfazVotante.h
 *
 *  Created on: 21/10/2011
 *      Author: lucas
 */

#ifndef INTERFAZADMINISTRADOR_H_
#define INTERFAZADMINISTRADOR_H_

#include "../Entidades/Cargo.h"
#include "../Entidades/Votante.h"
#include "../Entidades/Distrito.h"
#include "../Entidades/Candidato.h"
#include "../Entidades/Lista.h"
#include "../Entidades/Eleccion.h"
#include "../Entidades/Conteo.h"
#include "../Entidades/Constantes.h"
#include "../ClasesAuxiliares/Log.h"
#include "../ClasesAuxiliares/CreadorVotante.h"
#include "../Logica/Administrador.h"
#include "../Archivos/Hashing/Bucket.h"
#include "../Archivos/Hashing/HashingExtensible.h"
#include "../Archivos/EnBloques/ArchivoBloques.h"
#include "../Archivos/ArbolBMas/bplustree.h"
#include "../Logica/AdministradorDeVotaciones.h"
#include "../ClasesAuxiliares/Configuracion.h"
#include "../../tests/SimulacionSistema.h"
#include "./AdministradorDeVotaciones.h";
#include "./NombresDeArchivosTemporales.h";
#include <list>
#include <time.h>
#include <iomanip>
#include <stdio.h>
#include <limits>
#include "../Archivos/ArbolBMas/bplustree.h"
#include <string>
#include <iostream>
#include "../ClasesAuxiliares/Configuracion.h"

using namespace std;

class InterfazAdministrador {
private:
	Configuracion* config;
	int longitud;
	int longitudNodo;
	string rutaHash;
	string rutaArbol;
	string* dummy;
	bool mostrarMenuAdministrador(Administrador * administrador);
	void mostrarMenuDistritos(Administrador * administrador);
	void mostrarMenuVotantes(Administrador * administrador);
	void mostrarMenuElecciones(Administrador * administrador);
	void mostrarMenuCargos(Administrador * administrador);
	void mostrarMenuListas(Administrador * administrador);
	void mostrarMenuCandidatos(Administrador * administrador);
	void mostrarMenuInformes(Administrador * administrador);
	void habilitarElecciones(Administrador * administrador);
	void comienzoVotacion(Administrador * administrador);
	int isANumber(string &cad);
	void imprimirRespuesta(Resultados res);
	string* getString(vector<char> vect);
	void verContenidoArbolListas (bplustree*);
	bool validarRespuesta();

public:
	InterfazAdministrador(Configuracion* configuracion);
	void ingresoAdministrador(Administrador * administrador);
	virtual ~InterfazAdministrador();
};

#endif /* INTERFAZVOTANTE_H_ */
