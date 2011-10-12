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

Conteo::Conteo(string fecha,string cargo,string lista,string distrito){
	this->fechaEleccion = fecha;
	this->cargoEleccion = cargo;
	this->nombreLista = lista;
	this->distrito = distrito;
	this->cantidadVotos = 0;
}

int Conteo::getTamanio(){
	int tamFecha    = this->fechaEleccion.length(); //por default siempre es 8
	int tamCargo    = TAM_INT + this->cargoEleccion.length();
	int tamLista    = TAM_INT + this->nombreLista.length();
	int tamDistrito = TAM_INT + this->distrito.length();
	int tamVotos    = TAM_INT;
	return (tamFecha + tamCargo + tamLista + tamDistrito + tamVotos);
}

int Conteo::getClave(){
	return 0;
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

	//serializado fechaEleccion
	cantidadDeBytes = this->fechaEleccion.size();
	streamDatos.write((char*)fechaEleccion.c_str(),cantidadDeBytes);

	//serializado nombreLista
	cantidadDeBytes = this->nombreLista.size();
	streamDatos.write((char*)&cantidadDeBytes,TAM_INT);
	streamDatos.write((char*)nombreLista.c_str(),cantidadDeBytes);


	string* datos = new string(streamDatos.str());
	return datos;

}

void Conteo::deserializar(string* source){
	istringstream streamDatos(*source);
	stringstream * miString = new stringstream();
	int cantidadDeBytes;

	//deserializo cantidad de votos
	streamDatos.read((char*)&cantidadVotos,TAM_UNSINT);

	//Deserializado cargo elección
	streamDatos.read((char*)&cantidadDeBytes,TAM_INT);
    char* cargoChar = new char[cantidadDeBytes];
    streamDatos.read((char*)cargoChar,cantidadDeBytes);
    miString->write(cargoChar,cantidadDeBytes);
    string cargoString = miString->str();
    this->cargoEleccion = cargoString;
    delete []cargoChar;
    delete miString;

    //Deserializado distrito
	streamDatos.read((char*)&cantidadDeBytes,TAM_INT);
    char* distritoChar = new char[cantidadDeBytes];
    miString = new stringstream();
    streamDatos.read((char*)distritoChar,cantidadDeBytes);
    miString->write(distritoChar,cantidadDeBytes);
    string distritoString = miString->str();
    this->distrito = distritoString;
    delete []distritoChar;
    delete miString;

    //Deserializado fecha elección
    cantidadDeBytes = TAM_FECHA;
    char* fechaChar = new char[cantidadDeBytes];
    miString = new stringstream();
    streamDatos.read((char*)fechaChar,cantidadDeBytes);
    miString->write(fechaChar,cantidadDeBytes);
    string fechaString = miString->str();
    this->fechaEleccion = fechaString;
    delete []fechaChar;
    delete miString;

    //Deserializado nombre lista
	streamDatos.read((char*)&cantidadDeBytes,TAM_INT);
    char* listaChar = new char[cantidadDeBytes];
    miString = new stringstream();
    streamDatos.read((char*)listaChar,cantidadDeBytes);
    miString->write(listaChar,cantidadDeBytes);
    string listaString = miString->str();
    this->nombreLista = listaString;
    delete []listaChar;
    delete miString;
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



Conteo::~Conteo() {
	// TODO Auto-generated destructor stub
}
