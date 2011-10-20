/*
 * AdministradorDeVotaciones.cpp
 *
 *  Created on: 20/10/2011
 *      Author: martin
 */

#include "AdministradorDeVotaciones.h"

AdministradorDeVotaciones::AdministradorDeVotaciones() {
}

void AdministradorDeVotaciones::nuevoArchivoDeConteo(string pathArchivo, int dimensionBloque)
{
	archivoDeConteo.newtree(pathArchivo,dimensionBloque);
}

void AdministradorDeVotaciones::abrirArchivoDeConteo(string pathArchivo)
{
	#warning "no funciona"
	//archivoDeConteo.opentree(pathArchivo);
}

void AdministradorDeVotaciones::agregarConteo(Conteo *conteo)
{
	string clave;

	clave  = conteo->getFechaEleccion();
	clave += conteo->getDistrito();
	clave += conteo->getLista();
	clave += conteo->getCargoEleccion();

	string* conteoSerializado = conteo->serializar();
	vector<char> data(conteoSerializado->begin(),conteoSerializado->end());
	delete conteoSerializado;

	archivoDeConteo.add(clave,data);
}

void AdministradorDeVotaciones::incrementarVoto(Eleccion *eleccion, string *nombreLista, string *distrito)
{
	string clave;

	clave  = eleccion->getFecha();
	clave += *distrito;
	clave += *nombreLista;
	clave += eleccion->getCargo();

	vector<char> result = archivoDeConteo.search(clave);

	if (result.size() != 0)
		cout << "size!=0" << endl;
	else
		cout << "size==0" << endl;
}

AdministradorDeVotaciones::~AdministradorDeVotaciones() {
	// TODO Auto-generated destructor stub
}

