/*
 * Eleccion.cpp
 *
 *  Created on: 17/09/2011
 *      Author: martin
 */

#include "Eleccion.h"
using namespace std;
Eleccion::Eleccion() {
	this->fecha = "";
	this->cargoPrincipal = "";

}

Eleccion::Eleccion(string fecha,string cargoPrincipal){
	this->fecha 		= fecha;
	this->cargoPrincipal= cargoPrincipal;
}

int Eleccion::getTamanio(){
	int tamanioFecha = this->fecha.size(); //por default es 8
	int tamanioCargoPrincipal = TAM_INT + this->cargoPrincipal.size();
	int tamanioListaDistritos = TAM_INT; // este tam_int es la cantidad de distritos
	list<Distrito>::iterator it = this->distritos.begin();
	while (it != this->distritos.end()){
		tamanioListaDistritos = it->getTamanio();
	}
	return (tamanioFecha + tamanioCargoPrincipal + tamanioListaDistritos);

}

int Eleccion::getClave(){
	return 0;
}

string Eleccion::getFecha(){
	return this->fecha;
}

void Eleccion::setFecha(string fecha){
	this->fecha = fecha;
}

string Eleccion::getCargo(){
	return this->cargoPrincipal;
}

void Eleccion::setCargo(string cargoPrincipal){
	this->cargoPrincipal = cargoPrincipal;
}

bool Eleccion::agregarDistrito(Distrito distrito){
	bool encontrado = false;
	list<Distrito>::iterator iterador = this->distritos.begin();
	while (iterador != this->distritos.end() and (!encontrado)){
		if ((iterador->getDistrito()).compare(distrito.getDistrito()) == 0){
			encontrado = true;
		}
		iterador++;
	}
	if (!encontrado){
		this->distritos.push_back(distrito);
	}
	return (!encontrado); //devuelve el resultado de la inserción
}

bool Eleccion::eliminarDistrito(Distrito distrito){
	bool encontrado = false;
	list<Distrito>::iterator iterador = this->distritos.begin();
	while( iterador != this->distritos.end() and !encontrado ){
		if( (iterador->getDistrito().compare(distrito.getDistrito()))==0){
			encontrado = true;
			this->distritos.erase(iterador);
		}
		iterador++;
	}
	return (!encontrado); //devuelve el resultado de la inserción
}

list<Distrito> Eleccion::getLista(){
	return this->distritos;
}

list<Distrito>::iterator Eleccion::obtenerIterador(){
	list<Distrito>::iterator iterador = this->distritos.begin();
	return iterador;
}


Entidad *Eleccion::duplicar()
{
	Eleccion* copia = new Eleccion();
	copia->cargoPrincipal = this->cargoPrincipal;
	copia->fecha = this->fecha;
	list<Distrito>::iterator it = this->distritos.begin();
	while (it != this->distritos.end()){
		copia->agregarDistrito(*it);
	}
	return copia;

}

Eleccion::~Eleccion() {
	// TODO Auto-generated destructor stub
}

string* Eleccion::serializar() {
	stringstream buffer;
	int cantidadDeBytes;
	cantidadDeBytes   = this->fecha.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->fecha.c_str(),cantidadDeBytes);
	cantidadDeBytes   = this->cargoPrincipal.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->cargoPrincipal.c_str(),cantidadDeBytes);
	int tamanioDeListaDeDistritos = this->distritos.size();
	buffer.write((char*)&tamanioDeListaDeDistritos,TAM_INT);
	list<Distrito>::iterator it = this->distritos.begin();
	for (int i=0; i<tamanioDeListaDeDistritos; i++) {
		cantidadDeBytes = ((*it).getDistrito()).size();
		buffer.write((char*)&cantidadDeBytes,TAM_INT);
		buffer.write((char*)((*it).getDistrito()).c_str(),cantidadDeBytes);
		it++;
	}
	string* datos = new string(buffer.str());
	return datos;
}

void Eleccion::deserializar(string* source) {
	istringstream buffer (*source);
	delete source;
	int cantidadDeBytes;

//	hidrato la fecha
    buffer.read((char*)&cantidadDeBytes,TAM_INT);
    char* fechaSerializada = new char[cantidadDeBytes];
    buffer.read((char*)fechaSerializada,cantidadDeBytes);
    string* pasoAString = new string (fechaSerializada);
    this->fecha = *pasoAString;
    delete []fechaSerializada;
    delete pasoAString;

//  hidrato el cargo principal
    buffer.read((char*)&cantidadDeBytes,TAM_INT);
    char* cargoPrincipalSerializado = new char[cantidadDeBytes];
    buffer.read((char*)cargoPrincipalSerializado,cantidadDeBytes);
    pasoAString = new string (cargoPrincipalSerializado);
    this->cargoPrincipal = *pasoAString;
    delete []cargoPrincipalSerializado;
    delete pasoAString;

//  hidrato la lista de distritos
    int tamanioDeLaLista;
    buffer.read((char*)&tamanioDeLaLista,TAM_INT);
    for (int i=0; i<tamanioDeLaLista;i++){
    	stringstream* bufferAuxiliar = new stringstream;
    	buffer.read((char*)&cantidadDeBytes,TAM_INT);
    	char* distritoSerializado = new char[cantidadDeBytes];
    	buffer.read(distritoSerializado,cantidadDeBytes);
    	bufferAuxiliar->write(distritoSerializado,cantidadDeBytes);
    	Distrito unDistrito(bufferAuxiliar->str());
    	this->distritos.push_back(unDistrito);
    	delete bufferAuxiliar;
    	delete []distritoSerializado;
    }
}

NombreDeEntidad Eleccion::getNombreDeEntidad(){
	return tEleccion;
}

