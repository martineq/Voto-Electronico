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
#include <list>
#include <time.h>
#include <stdio.h>
#include "../Archivos/ArbolBMas/bplustree.h"
#include <string>
#include <iostream>
#include "../ClasesAuxiliares/Configuracion.h"
#include "AdministradorDeVotaciones.h"

using namespace std;

class InterfazAdministrador {
private:
	Configuracion* config;
	AdministradorDeVotaciones*	administradorDeConteo;
	int longitud;
	int longitudNodo;
	string rutaHash;
	string rutaArbol;
	bool mostrarMenuAdministrador(Administrador * administrador);
	void mostrarMenuDistritos(Administrador * administrador);
	void mostrarMenuVotantes(Administrador * administrador);
	void mostrarMenuElecciones(Administrador * administrador);
	void mostrarMenuCargos(Administrador * administrador);
	void mostrarMenuListas(Administrador * administrador);
	void mostrarMenuCandidatos(Administrador * administrador);
	void mostrarMenuInformes(Administrador * administrador);
	void habilitarElecciones(Administrador * administrador);
	int isANumber(string &cad);
	void imprimirRespuesta(Resultados res);
public:
	InterfazAdministrador(Configuracion* configuracion);
	void ingresoAdministrador(Administrador * administrador);
	virtual ~InterfazAdministrador();
};

#endif /* INTERFAZVOTANTE_H_ */
