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
	if (this->verificarCargo(cargoPrincipal))	this->cargoPrincipal= cargoPrincipal;
	else cout << "NO EXISTE ESE CARGO HABILITADO" << endl;
}

int Eleccion::getTamanio(){
	int tamanioFecha = TAM_FECHA; //por default es 8
	int tamanioCargoPrincipal = TAM_INT + this->cargoPrincipal.size();
	int tamanioListaDistritos = TAM_INT; // este tam_int es la cantidad de distritos
	list<Distrito>::iterator it = this->distritos.begin();
	while (it != this->distritos.end()){
		tamanioListaDistritos += (TAM_INT +  it->getTamanio());
		it++;
		it++;
	}
	return (tamanioFecha + tamanioCargoPrincipal + tamanioListaDistritos);
}

int Eleccion::getClave(){
	int c = 0;
	for (int i=0; i<this->fecha.length(); i++) {
		c += (int)this->fecha[i];
	}
	for (int i=0; i<this->cargoPrincipal.length(); i++) {
		c += (int)this->cargoPrincipal[i];
	}
	return c;
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
	if (this->verificarCargo(cargoPrincipal)) this->cargoPrincipal = cargoPrincipal;
	else cout << "CARGO NO EXISTENTE" << endl;
}

bool Eleccion::agregarDistrito(string nombre){
	Distrito unDistrito (nombre);
	list<Distrito>::iterator iterador = this->distritos.begin();
	while (iterador != this->distritos.end()){
		if ((iterador->getDistrito()).compare(unDistrito.getDistrito()) == 0){
			return false;
		}
		iterador++;
	}
	if (this->verificarDistrito(nombre)) {
		this->distritos.push_back(unDistrito);
		return true;
	}
	return false;
}

bool Eleccion::verificarDistrito(string cargo) {
	#warning "Debe buscarse si el distrito existe usando hashing"
	return true;
}

bool Eleccion::verificarCargo(string cargo) {
	#warning "Debe buscarse si el cargo existe usando busqueda secuencial probablemente ya que son pocos cargos"
	return true;
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


Entidad *Eleccion::duplicar(){
	Eleccion* copia = new Eleccion();
	copia->cargoPrincipal = this->cargoPrincipal;
	copia->fecha = this->fecha;
	list<Distrito>::iterator it = this->distritos.begin();
	while (it != this->distritos.end()){
		copia->agregarDistrito(it->getDistrito());
		it++;
	}
	return copia;

}

Eleccion::~Eleccion() {
	// TODO Auto-generated destructor stub
}

string* Eleccion::serializar() {
	stringstream buffer;
	int cantidadDeBytes;
	buffer.write((char*)this->fecha.c_str(),TAM_FECHA);
	cantidadDeBytes   = this->cargoPrincipal.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->cargoPrincipal.c_str(),cantidadDeBytes);
	int tamanioDeListaDeDistritos = this->distritos.size();
	buffer.write((char*)&tamanioDeListaDeDistritos,TAM_INT);

	list<Distrito>::iterator it = this->distritos.begin();
	for (int i=0; i<tamanioDeListaDeDistritos; i++) {
		cantidadDeBytes = (*it).getTamanio();
		buffer.write((char*)&cantidadDeBytes,TAM_INT);
		string* distritoSerializado = (*it).serializar();
		buffer.write((char*)distritoSerializado->c_str(),cantidadDeBytes);
		delete distritoSerializado;
		it++;
	}
	string* datos = new string(buffer.str());
	return datos;
}

void Eleccion::deserializar(string* source) {
	int posicion=0;

//	hidrato la fecha
	stringstream fecha(source->substr(posicion,posicion+TAM_FECHA-1));
	this->fecha = fecha.get();
	posicion += TAM_FECHA;

//  hidrato el cargo principal
	stringstream tamanioDeCargoPrincipal(source->substr(posicion,posicion+TAM_INT-1));
	int tamanio = tamanioDeCargoPrincipal.get();
	posicion += TAM_INT;
	stringstream nombre(source->substr(posicion,posicion+tamanio-1));
	this->cargoPrincipal = nombre.get();
	posicion += tamanio;

 //  hidrato la lista de distritos
	stringstream tamanioLista(source->substr(posicion,posicion+TAM_INT-1));
	tamanio = tamanioLista.get();
	posicion += TAM_INT;
    for (int i=0; i<tamanio;i++){
    	stringstream tamanioDelDistrito (source->substr(posicion,posicion+TAM_INT-1));
    	tamanio = tamanioDelDistrito.get();
    	posicion += TAM_INT;
    	stringstream unDistrito (source->substr(posicion,posicion+tamanio-1));
    	Distrito distrito;
    	string str = unDistrito.str();
    	distrito.deserializar(&str);
    	this->distritos.push_back(distrito);
    	posicion += tamanio;
    }
}

NombreDeEntidad Eleccion::getNombreDeEntidad(){
	return tEleccion;
}

