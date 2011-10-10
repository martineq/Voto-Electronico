/*
 * Bucket.cpp
 *
 *  Created on: 23/09/2011
 *      Author: lÑ#$dsa44
 */

#include "Bucket.h"

Bucket::Bucket(int tamanioDispersion,int tamanioDeBucket){
	this->tamanioDeDispersion=tamanioDispersion;
	this->espacioLibre=tamanioDeBucket-12;
//	this->espacioLibre=LONGITUD_BLOQUE;
}

Registro* Bucket::getRegistro(int clave){
	if (this->listaDeRegistros.empty()) return NULL;
	else {
		list<Registro*>::iterator it = this->listaDeRegistros.begin();
		while (it!=listaDeRegistros.end()) {
			int claveDeRegistroActual = (*it)->obtenerClave();
			if (claveDeRegistroActual==clave) {
				Registro* unRegistro = (*it)->duplicar();
				return unRegistro;
			}
			it++;
		}
	}
	return NULL;
}

Registro* Bucket::consultarRegistro(int clave){
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
	if (this->consultarRegistro(unRegistro->obtenerClave())!=NULL) return false;
	else
		if ((unRegistro->getTamanio()+TAM_INT)>this->espacioLibre) return  false;
		else {
			Registro* registro = unRegistro->duplicar();
			this->listaDeRegistros.push_back(registro);
			this->espacioLibre-= (unRegistro->getTamanio()+TAM_INT);
			return true;
		}
}

bool Bucket::eliminarRegistro(int clave){
	if (this->listaDeRegistros.empty()) {
		cout << "ERROR: EL BUCKET ESTA VACIO" << endl;
		return false;
	}
	else {
		if (this->consultarRegistro(clave)==NULL) return false;
		else {
			list<Registro*>::iterator it = this->listaDeRegistros.begin();
			while (it!=listaDeRegistros.end()) {
				int claveDeRegistroActual = (*it)->obtenerClave();
				if (claveDeRegistroActual==clave) {
					this->espacioLibre+=((*it)->getTamanio()+TAM_INT);
					delete *it;
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
		if (this->consultarRegistro(clave)==NULL) return false;
		else {
			Registro* registroAReemplazar = this->consultarRegistro(clave);
			if ((registroAReemplazar->getTamanio()+this->espacioLibre) >= unRegistro->getTamanio()){
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
	cout << endl << "Usted esta en el serializar de bucket" << endl;

	stringstream buffer;
	int cantidadDeBytes;

	cout << "Comienza la carga de elementos en buffer." << endl;

	buffer.write((char*)&this->espacioLibre,TAM_INT);
	cout << "Se cargo el espacio libre: " << this->espacioLibre << endl;

	buffer.write((char*)&this->tamanioDeDispersion,TAM_INT);
	cout << "Se cargo el tamanio de dispersion: " << this->tamanioDeDispersion << endl;

	int cantidadDeRegistros= this->listaDeRegistros.size();
	buffer.write((char*)&cantidadDeRegistros,TAM_INT);
	cout << "Se cargo la cantidad de registros: " << cantidadDeRegistros << endl;

	for (list<Registro*>:: iterator it = this->listaDeRegistros.begin(); it != listaDeRegistros.end(); it++){

		cantidadDeBytes = ((*it)->getTamanio());
		buffer.write((char*)&cantidadDeBytes,TAM_INT);
		cout << "Se cargo el tamanio de un registro: " << cantidadDeBytes << endl;

		string* registroSerializado = (*it)->serializar();
		buffer.write(registroSerializado->c_str(),cantidadDeBytes);
		delete registroSerializado;

	}
	cout << "Fin del serializado del bucket" << endl << endl;
	string* datos = new string(buffer.str());
	return datos;
}
void Bucket::deserializar(string* bufferSerializado){
	cout << endl << "Usted esta en el deserializar de bucket" << endl;
	if (bufferSerializado->size()==0) cout << "No se pudo hidratar el Bucket pues la fuente es nula" << endl;
	else {
		int posicion=0;

		//	hidrato el espacio libre
		stringstream espacioLibre (bufferSerializado->substr(posicion,posicion+TAM_INT-1));
		posicion+=TAM_INT;
		this->espacioLibre = espacioLibre.get();
		cout << "Se cargo el espacio libre: " << this->espacioLibre << endl;

		//	hidrato el tamanio de dispersion
		stringstream tamanioDeDispersion (bufferSerializado->substr(posicion,posicion+TAM_INT-1));
		posicion+=TAM_INT;
		this->tamanioDeDispersion = tamanioDeDispersion.get();
		cout << "Se cargo el tamanio de dispersion: " << this->tamanioDeDispersion << endl;

		//	hidrato la lista de registros
		stringstream cantidadDeRegistros (bufferSerializado->substr(posicion,posicion+TAM_INT-1));
		posicion+=TAM_INT;
		int tamanioDeLaLista = cantidadDeRegistros.get();
		cout << "Se cargo la cantidad de registros: " << tamanioDeLaLista << endl;

		cout << "Carga de registros" << endl;
		for (int i=0; i<tamanioDeLaLista;i++){
			//hidrato el registro
			stringstream tamanioDeRegistroHidratado (bufferSerializado->substr(posicion,posicion+TAM_INT-1));
			posicion+=TAM_INT;
			int tamanioDeRegistro = tamanioDeRegistroHidratado.get();
			cout << "Se cargo el tamanio de un registro: " << tamanioDeRegistro << endl;
			stringstream registroAHidratar (bufferSerializado->substr(posicion,posicion+tamanioDeRegistro-1));
			posicion+=tamanioDeRegistro;
			Registro* unRegistro = new Registro();
			cout << "Deserializando registro" << endl;
			string* source = new string (registroAHidratar.str());
			unRegistro->deserializar(source);
			delete source;
			cout << "Registro deserializado" << endl;
			this->listaDeRegistros.push_back(unRegistro);
			cout << "Registro cargado" << endl;
		}
		cout << "Chauuu!" << endl;
	}
}
Bucket::~Bucket() {
	for (list<Registro*>:: iterator it = this->listaDeRegistros.begin(); it != listaDeRegistros.end(); it++){
		delete *it;
	}
}
