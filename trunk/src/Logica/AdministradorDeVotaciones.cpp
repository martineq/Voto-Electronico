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

	string indiceDistrito = pathArchivo;
	indiceDistrito += "_distrito";

	cout << "indice secundario: " << indiceDistrito << endl;

	indiceSecundarioDistrito.newtree(indiceDistrito,dimensionBloque);
}

int AdministradorDeVotaciones::agregarConteoAlIndicePorDistrito(Conteo* conteo){
	string clave = "";

	clave += conteo->getDistrito();
	clave += conteo->getFechaEleccion();
	clave += conteo->getLista();
	clave += conteo->getCargoEleccion();

	conteo->verEntidad();
	string* conteoSerializado = conteo->serializar();

	vector<char> resultado = archivoDeConteo.search(clave);
	if ( resultado.size() == 0 ){
		cout << "size: " << conteoSerializado->size() << endl;

		vector<char> data(conteoSerializado->begin(),conteoSerializado->end());
		delete conteoSerializado;

		archivoDeConteo.add(clave,data);

		// agrego el contenido al indice secundario distrito

		return 0;
	}else{
		cout << "******* agregado fallo ***************" << endl;
		return 1;
	}

}

void AdministradorDeVotaciones::abrirArchivoDeConteo(string pathArchivo)
{
//	archivoDeConteo.opentree(pathArchivo);
//	indiceSecundarioDistrito();
}

string* AdministradorDeVotaciones::getString(vector<char> vect){
	string* s = new string();
	vector<char>::iterator it = vect.begin();
	while( it != vect.end() ){
		s->push_back(*it);
		it++;
	}
	return s;
}

int AdministradorDeVotaciones::agregarConteo(Conteo *conteo)
{
	string clave = "";

	clave  = conteo->getFechaEleccion();
	clave += conteo->getDistrito();
	clave += conteo->getLista();
	clave += conteo->getCargoEleccion();

	conteo->verEntidad();
	string* conteoSerializado = conteo->serializar();

	vector<char> resultado = archivoDeConteo.search(clave);
	if ( resultado.size() == 0 ){
		cout << "size: " << conteoSerializado->size() << endl;

		vector<char> data(conteoSerializado->begin(),conteoSerializado->end());
		delete conteoSerializado;

		archivoDeConteo.add(clave,data);

		// agrego el contenido al indice secundario distrito

		return 0;
	}else{
		cout << "******* agregado fallo ***************" << endl;
		return 1;
	}
}

void AdministradorDeVotaciones::incrementarVoto(Eleccion *eleccion, string *nombreLista, string *distrito)
{
	string clave;

	clave  = eleccion->getFecha();
	clave += *distrito;
	clave += *nombreLista;
	clave += eleccion->getCargo();

	vector<char> result = archivoDeConteo.search(clave);

	if (result.size() != 0){

		string* conteoSerializado = getString(result);

		Conteo* conteo = new Conteo("","","","");
		conteo->deserializar(conteoSerializado);
		conteo->verEntidad();
		conteo->incrementarVotos();
		delete conteoSerializado;

		conteoSerializado = conteo->serializar();

		vector<char> vectorSerializado(conteoSerializado->begin(),conteoSerializado->end());
		archivoDeConteo.modify(clave,vectorSerializado);

		delete conteo;
		delete conteoSerializado;
	}else
		cout << "size==0" << endl;
}

void AdministradorDeVotaciones::mostrarArchivo(){
	string* conteoSerializado = getString( archivoDeConteo.search("") );

	pair<vector<char>,string> par=archivoDeConteo.getnext();
	while( par.second.size() != 0 ) {

		conteoSerializado = getString( par.first );
		Conteo* conteo = new Conteo("","","","");
		conteo->deserializar(conteoSerializado);
		delete conteoSerializado;

		conteo->verEntidad();
		delete conteo;
		cout << endl;
		par=archivoDeConteo.getnext();
	}
}

AdministradorDeVotaciones::~AdministradorDeVotaciones() {
	// TODO Auto-generated destructor stub
}

