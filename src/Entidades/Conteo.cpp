/*
 * Conteo.cpp
 *
 *  Created on: 08/10/2011
 *      Author: lucas
 */

#include "Conteo.h"

Conteo::Conteo() {
	fechaEleccion = "18991231";
	cargoEleccion = "";
	nombreLista = "";
	distrito = "";
	cantidadVotos = 0;
}

void Conteo::verEntidad(){
	cout << "Fecha Eleccion: "<< fechaEleccion << endl;
	cout << "Cargo eleccion: "<< cargoEleccion << endl;
	cout << "Nombre de lista: "<< nombreLista << endl;
	cout << "Distrito: "<< distrito << endl;
	cout << "Cantidad de votos: "<< cantidadVotos << endl;
}

Conteo::Conteo(string fecha,string cargo,string lista,string distrito){
	this->fechaEleccion = fecha;
	this->cargoEleccion = cargo;
	this->nombreLista = lista;
	this->distrito = distrito;
	this->cantidadVotos = 0;
}

unsigned long Conteo::getClave(){

	  string stringClave = this->fechaEleccion + this->cargoEleccion + this->nombreLista;
	  locale loc;                 // the "C" locale

	  const collate<char>& coll = use_facet<collate<char> >(loc);

	  unsigned long myhash = coll.hash(stringClave.data(),stringClave.data()+stringClave.length());

	  return myhash;

}

string Conteo::getFechaEleccion(){
	return this->fechaEleccion;
}

string Conteo::getCargoEleccion(){
	return this->cargoEleccion;
}

string Conteo::getLista(){
	return this->nombreLista;
}

string Conteo::getDistrito(){
	return this->distrito;
}

unsigned int Conteo::getCantidadVotos(){
	return this->cantidadVotos;
}

void Conteo::incrementarVotos(){
	this->cantidadVotos++;
}

void Conteo::decrementarVotos(){
	this->cantidadVotos--;
}
/*
 * Instancia un nuevo objeto, copia de actual.
 */
Entidad* Conteo::duplicar(){
	Conteo * conteoCopia = new Conteo();
	conteoCopia->cantidadVotos = this->cantidadVotos;
	conteoCopia->cargoEleccion = this->cargoEleccion;
	conteoCopia->distrito 	   = this->distrito;
	conteoCopia->fechaEleccion = this->fechaEleccion;
	conteoCopia->nombreLista   = this->nombreLista;
	return conteoCopia;
}

int Conteo::getTamanio(){
	int tamFecha    = TAM_INT + fechaEleccion.size();
	int tamCargo    = TAM_INT + cargoEleccion.size();
	int tamLista    = TAM_INT + nombreLista.size();
	int tamDistrito = TAM_INT + distrito.size();
	int tamVotos    = TAM_UNSINT;
	return (tamFecha + tamCargo + tamLista + tamDistrito + tamVotos);
}

string* Conteo::serializar(){
	stringstream streamDatos;
	int cantidadDeBytes;
	//Serializo cantidad de votos
	streamDatos.write((char*)&cantidadVotos,TAM_UNSINT);

	//Serializado cargo elección
	cantidadDeBytes = this->cargoEleccion.size();
	streamDatos.write((char*)&cantidadDeBytes,TAM_INT);
	streamDatos.write((char*)cargoEleccion.c_str(),cantidadDeBytes);

	//serializado distrito
	cantidadDeBytes = this->distrito.size();
	streamDatos.write((char*)&cantidadDeBytes,TAM_INT);
	streamDatos.write((char*)distrito.c_str(),cantidadDeBytes);

	//serializado nombreLista
	cantidadDeBytes = this->nombreLista.size();
	streamDatos.write((char*)&cantidadDeBytes,TAM_INT);
	streamDatos.write((char*)nombreLista.c_str(),cantidadDeBytes);

	//serializado fechaEleccion
	cantidadDeBytes = this->fechaEleccion.size();
	streamDatos.write((char*)&cantidadDeBytes,TAM_INT);
	streamDatos.write((char*)fechaEleccion.c_str(),cantidadDeBytes);

	return new string(streamDatos.str());

}

void Conteo::deserializar(string* source){

	Serializadora serializadora(source);

	cantidadVotos 	= serializadora.obtenerUnsignedInt();

	cargoEleccion	= serializadora.obtenerString();

	distrito 		= serializadora.obtenerString();

	nombreLista 	= serializadora.obtenerString();

	fechaEleccion 	= serializadora.obtenerString();
}

NombreDeEntidad Conteo::getNombreDeEntidad(){
	return tConteo;
}

void Conteo::imprimirConteo(){
	cout <<"Fecha de la elección: "<<this->fechaEleccion<<endl;
	cout <<"Cargo a votar: " << this->cargoEleccion<<endl;
	cout <<"Nombre de la lista: "<<this->nombreLista<<endl;
	cout <<"Distrito: "<<this->distrito<<endl;
	cout <<"Votos conseguidos: "<<this->cantidadVotos<<endl<<endl;
}


ResultadoComparacion Conteo::comparar(Entidad* entidad){
	if (entidad->getNombreDeEntidad() != tConteo){
		return comparacionInvalida;
	}
	Conteo* conteoNuevo = (Conteo*) entidad;
	int compararFecha = this->fechaEleccion.compare(conteoNuevo->fechaEleccion);
	int compararCargo = this->cargoEleccion.compare(conteoNuevo->cargoEleccion);
	int compararLista = this->nombreLista.compare(conteoNuevo->nombreLista);
	int compararDistrito = this->distrito.compare(conteoNuevo->distrito);

	if (compararFecha < 0){
		return menor;
	}
	if (compararFecha > 0){
		return mayor;
	}
	if (compararCargo < 0){
		return menor;
	}
	if (compararCargo > 0){
		return mayor;
	}
	if (compararLista < 0){
		return menor;
	}
	if (compararLista > 0){
		return mayor;
	}

	if ( compararDistrito < 0 )
		return menor;
	else if ( compararDistrito == 0 )
		return igual;
	else
		return mayor;

}


Conteo::~Conteo() {
	// TODO Auto-generated destructor stub
}
