/*
 * Bucket.cpp
 *
 *  Created on: 23/09/2011
 *      Author: lÑ#$dsa44
 */

#include "Bucket.h"

Bucket::Bucket(int tamanioDispersion){
	this->tamanioDeDispersion=tamanioDispersion;
	this->espacioLibre=LONGITUD_BLOQUE_PRUEBA;
//	this->espacioLibre=LONGITUD_BLOQUE;
}

Registro* Bucket::getRegistro(int clave){
	if (this->listaDeRegistros.empty()) return NULL;
	else {
		list<Registro*>::iterator it = this->listaDeRegistros.begin();
		while (it!=listaDeRegistros.end()) {
			int claveDeRegistroActual = (*it)->obtenerClave();
			if (claveDeRegistroActual==clave) return *it;
			it++;
		}
	}
	return NULL;
}

//devuelve el resultado de la operacion
bool Bucket::agregarRegistro(Registro* unRegistro){
	if (this->getRegistro(unRegistro->obtenerClave())!=NULL) return false;
	else
		if (unRegistro->getTamanio()>this->espacioLibre) return  false;
		else {
			this->listaDeRegistros.push_back(unRegistro);
			this->espacioLibre-=unRegistro->getTamanio();
			return true;
		}
}

bool Bucket::eliminarRegistro(int clave){
	if (this->listaDeRegistros.empty()) {
		cout << "ERROR: EL BUCKET ESTA VACIO" << endl;
		return false;
	}
	else {
		if (this->getRegistro(clave)==NULL) return false;
		else {
			list<Registro*>::iterator it = this->listaDeRegistros.begin();
			while (it!=listaDeRegistros.end()) {
				int claveDeRegistroActual = (*it)->obtenerClave();
				if (claveDeRegistroActual==clave) {
					this->espacioLibre+=(*it)->getTamanio();
					this->listaDeRegistros.erase (it);
					return true;
				}
				else it++;
			}
		}
	}
}

bool Bucket::reemplazarRegistro(Registro* unRegistro){
	if (this->listaDeRegistros.empty()) return false;
	else {
		int clave=unRegistro->obtenerClave();
		if (this->getRegistro(clave)==NULL) return false;
		else {
			Registro* registroAReemplazar = this->getRegistro(clave);
			if ((registroAReemplazar->getTamanio()+this->espacioLibre) > unRegistro->getTamanio()){
				this->eliminarRegistro(clave);
				this->agregarRegistro(unRegistro);
				return true;
			}
			else return false;
		}
	}
}

int Bucket::getEspacioLibre (){return this->espacioLibre;}
int Bucket::getTamanioDeDispersion (){return this->tamanioDeDispersion;}
int Bucket::getCantidadDeRegistros () {return this->listaDeRegistros.size();}
void Bucket::setTamanioDeDispersion (int tamanio){this->tamanioDeDispersion=tamanio;}
list<Registro*>::iterator Bucket::ubicarPrimero(){
	list<Registro*>::iterator it = this->listaDeRegistros.begin();
	return it;
}

string* Bucket::serializar(){
	stringstream buffer;
	int cantidadDeBytes;
	buffer.write((char*)&this->espacioLibre,TAM_INT);
	buffer.write((char*)&this->tamanioDeDispersion,TAM_INT);
	int tamanioDeLaListaDeRegistros= this->listaDeRegistros.size();
	buffer.write((char*)&tamanioDeLaListaDeRegistros,TAM_INT);
	for (list<Registro*>:: iterator it = this->listaDeRegistros.begin(); it != listaDeRegistros.end(); it++){
		cantidadDeBytes = ((*it)->getTamanio());
		buffer.write((char*)&cantidadDeBytes,TAM_INT);
		buffer.write(((*it)->serializar())->c_str(),TAM_INT);
	}
	string* datos = new string(buffer.str());
	return datos;
}
void Bucket::deserializar(string* source){
	istringstream buffer (*source);
	delete source;
	int cantidadDeBytes;

	//	hidrato el espacio libre
	buffer.read((char*)&this->espacioLibre,TAM_INT);
	//	hidrato el tamanio de dispersion
	buffer.read((char*)&this->tamanioDeDispersion,TAM_INT);
	int tamanioDeLaLista;
	buffer.read((char*)&tamanioDeLaLista,TAM_INT);
	for (int i=0; i<tamanioDeLaLista;i++){
		//hidrato el registro*
		stringstream* bufferAuxiliar = new stringstream;
		buffer.read((char*)&cantidadDeBytes,TAM_INT);
		char* registroSerializado = new char[cantidadDeBytes];
		buffer.read(registroSerializado,cantidadDeBytes);
		bufferAuxiliar->write(registroSerializado,cantidadDeBytes);
		string registroADeserializar = bufferAuxiliar->str();
		Registro* unRegistro;
		unRegistro->deserializar(&registroADeserializar);
		this->listaDeRegistros.push_back(unRegistro);
		delete bufferAuxiliar;
		delete []registroSerializado;
	}
}
Bucket::~Bucket() {}
