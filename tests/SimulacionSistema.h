/*
 * SimulacionSistema.h
 *
 *  Created on: 20/10/2011
 *      Author: daniel
 */

#ifndef SIMULACIONSISTEMA_H_
#define SIMULACIONSISTEMA_H_

#include "../src/Entidades/Cargo.h"
#include "../src/Entidades/Votante.h"
#include "../src/Entidades/Distrito.h"
#include "../src/Entidades/Candidato.h"
#include "../src/Entidades/Lista.h"
#include "../src/Entidades/Eleccion.h"
#include "../src/Entidades/Conteo.h"
#include "../src/Entidades/Constantes.h"
#include "../src/Auxiliares/Log.h"
#include "../src/Logica/Administrador.h"
#include "../src/Archivos/Hashing/Bucket.h"
#include "../src/Archivos/Hashing/HashingExtensible.h"
#include "../src/Archivos/EnBloques/ArchivoBloques.h"
#include "../src/Archivos/ArbolBMas/bplustree.h"
#include "../src/Logica/AdministradorDeVotaciones.h"
#include <list>
#include <time.h>
#include <stdio.h>
#include "../src/Archivos/ArbolBMas/bplustree.h"
#include <string>
#include <iostream>

using namespace std;


class SimulacionSistema {
private:
	Votante* votante1;
	Votante* votante2;
	Votante* votante3;
	Votante* votante4;
	Distrito* distrito1;
	Distrito* distrito2;
	Distrito* distrito3;
	Distrito* distrito4;
	Eleccion* eleccion1;
	Eleccion* eleccion2;
	Eleccion* eleccion3;
	Eleccion* eleccion4;
	Candidato* candidato1;
	Candidato* candidato2;
	Candidato* candidato3;
	Candidato* candidato4;
	Lista* lista1;
	Lista* lista2;
	Lista* lista3;
	Lista* lista4;
	Cargo* cargo1;
	Cargo* cargo2;
	Registro* registroVotante1;
	Registro* registroVotante2;
	Registro* registroVotante3;
	Registro* registroVotante4;
	Registro* registroDistrito1;
	Registro* registroDistrito2;
	Registro* registroDistrito3;
	Registro* registroDistrito4;
	Registro* registroEleccion1;
	Registro* registroEleccion2;
	Registro* registroEleccion3;
	Registro* registroEleccion4;
	Registro* registroCandidato1;
	Registro* registroCandidato2;
	Registro* registroCandidato3;
	Registro* registroCandidato4;
	Registro* registroLista1;
	Registro* registroLista2;
	Registro* registroLista3;
	Registro* registroLista4;
	Registro* registroCargo1;
	Registro* registroCargo2;
	HashingExtensible* heVotante;
	HashingExtensible* heDistrito;
	HashingExtensible* heEleccion;
	HashingExtensible* heCandidato;
	HashingExtensible* heLista;
	HashingExtensible* heCargo;
	bplustree* arbolB;
	string* getString(vector<char>);
	void agregarBoletaAlArbol(Registro*);
	void habilitarElecciones(Administrador* administrador);
	void iniciarEleccionesParaIntegracion();
	void iniciarVotantesParaIntegracion();
	void iniciarDistritosParaIntegracion();
	void iniciarCandidatosParaIntegracion();
	void iniciarListasParaIntegracion();
	void iniciarCargosParaIntegracion();
	void verContenidoArbolListas();
public:
	SimulacionSistema();
	~SimulacionSistema();
	void cargarBaseDeDatos(Administrador*);
	bool inicioDeSimulacion(Administrador*);
	void destruir();
	void main ();
};

#endif /* SIMULACIONSISTEMA_H_ */
