/*
 * InterfazVotante.h
 *
 *  Created on: 21/10/2011
 *      Author: lucas
 */

#ifndef INTERFAZADMINISTRADOR_H_
#define INTERFAZADMINISTRADOR_H_

#include "../src/Entidades/Cargo.h"
#include "../src/Entidades/Votante.h"
#include "../src/Entidades/Distrito.h"
#include "../src/Entidades/Candidato.h"
#include "../src/Entidades/Lista.h"
#include "../src/Entidades/Eleccion.h"
#include "../src/Entidades/Conteo.h"
#include "../src/Entidades/Constantes.h"
#include "../src/ClasesAuxiliares/Log.h"
#include "../src/ClasesAuxiliares/CreadorVotante.h"
#include "../src/Logica/Administrador.h"
#include "../src/Archivos/Hashing/Bucket.h"
#include "../src/Archivos/Hashing/HashingExtensible.h"
#include "../src/Archivos/EnBloques/ArchivoBloques.h"
#include "../src/Archivos/ArbolBMas/bplustree.h"
#include "../src/Logica/AdministradorDeVotaciones.h"
#include "../src/ClasesAuxiliares/Configuracion.h"
#include <list>
#include <time.h>
#include <stdio.h>
#include "../src/Archivos/ArbolBMas/bplustree.h"
#include <string>
#include <iostream>
#include "../src/ClasesAuxiliares/Configuracion.h"

using namespace std;

class InterfazAdministrador {
private:
	Configuracion* config;
	int longitud;
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
	int isANumber(string &cad);
	void imprimirRespuesta(Resultados res);
public:
	InterfazAdministrador(int argc, const char** argv );
	void ingresoAdministrador();
	virtual ~InterfazAdministrador();
};

#endif /* INTERFAZVOTANTE_H_ */
