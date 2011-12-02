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
#include "../ClasesAuxiliares/Configuracion.h"
#include "../Logica/Administrador.h"
#include "../Logica/AdministradorDeVotaciones.h"
#include "../Archivos/Hashing/Bucket.h"
#include "../Archivos/Hashing/HashingExtensible.h"
#include "../Archivos/EnBloques/ArchivoBloques.h"
#include "../Archivos/ArbolBMas/bplustree.h"
#include "../Archivos/EnBloques/ManejadorDeArchivo.h"
#include "../Criptografia/RSA.h"
#include "../../tests/SimulacionSistema.h"
#include "./AdministradorDeVotaciones.h"
#include <list>
#include <ctime>
#include <iomanip>
#include <limits>
#include "../Archivos/ArbolBMas/bplustree.h"
#include <string>
#include <iostream>
#include "../ClasesAuxiliares/Configuracion.h"
#include "NombresDeArchivosTemporales.h"
#include "../Criptografia/Kasiski.h"
#include "../Criptografia/Vigenere.h"

using namespace std;

class InterfazAdministrador {
private:
	Configuracion* config;
	AdministradorDeVotaciones * administradorDeConteo;
	int longitud;
	int longitudNodo;
	bool	votoAutomatizado;
	string rutaHash;
	string rutaArbol;
	string* dummy;
	streambuf*		backup;
	stringstream*	stream;
	RSA* rsa;

	bool mostrarMenuAdministrador(Administrador * administrador);
	void mostrarMenuDistritos(Administrador * administrador);
	void mostrarMenuVotantes(Administrador * administrador);
	void mostrarMenuElecciones(Administrador * administrador);
	void mostrarMenuCargos(Administrador * administrador);
	void mostrarMenuListas(Administrador * administrador);
	void mostrarMenuCandidatos(Administrador * administrador);
	void mostrarMenuInformes(Administrador * administrador);
	void mostrarMenuVotacionAutomatica(Administrador * administrador);
	void mostrarMenuCriptoanalisis(Administrador * administrador);
	void atacarRSA();
	void habilitarElecciones(Administrador * administrador);
	void comienzoVotacion(Administrador * administrador);
	int isANumber(string &cad);
	void imprimirRespuesta(Resultados res);
	string* getString(vector<char> vect);
	void cargarArchivoDeConteo(Eleccion* eleccion,Administrador* administrador);
	void verContenidoArbolListas (bplustree*);
	void criptoanalizarInforme(string informe);
public:
	InterfazAdministrador(Configuracion* configuracion);
	void ingresoAdministrador(Administrador * administrador);
	virtual ~InterfazAdministrador();
};

#endif /* INTERFAZVOTANTE_H_ */
