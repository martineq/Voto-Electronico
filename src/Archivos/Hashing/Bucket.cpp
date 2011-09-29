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
	cout << "HOLA!" << endl;
	cout << "Usted esta en el serializar de bucket" << endl;
	cout << "Esto es lo que ocurre paso a paso" << endl;
	stringstream buffer;
	int cantidadDeBytes;
	buffer.write((char*)&this->espacioLibre,TAM_INT);
	cout << "Carga del espacio libre en buffer" << endl;
	cout << "Espacio libre: " << this->espacioLibre << endl;
	buffer.write((char*)&this->tamanioDeDispersion,TAM_INT);
	cout << "Carga del tamanio de dispersion en buffer" << endl;
	cout << "Tamanio de dispersion: " << this->tamanioDeDispersion << endl;
	int cantidadDeRegistros= this->listaDeRegistros.size();
	buffer.write((char*)&cantidadDeRegistros,TAM_INT);
	cout << "Carga de la cantidad de registros en buffer" << endl;
	cout << "Cantidad de registros: " << cantidadDeRegistros << endl;
	cout << "Carga de registros en bufffer" << endl;
	for (list<Registro*>:: iterator it = this->listaDeRegistros.begin(); it != listaDeRegistros.end(); it++){
		cantidadDeBytes = ((*it)->getTamanio());
		buffer.write((char*)&cantidadDeBytes,TAM_INT);
		cout << "Carga del tamanio del registro en buffer" << endl;
		cout << "Tamanio del registro: " << cantidadDeBytes << endl;
		buffer.write(((*it)->serializar())->c_str(),cantidadDeBytes);
		cout << "Carga del registro en buffer" << endl;
	}
	cout << "Fin del serializado del bucket" << endl;
	cout << "Chauuu!!!" << endl;
	string* datos = new string(buffer.str());
	return datos;
}
void Bucket::deserializar(string* source){
	cout << "HOLA!" << endl;
	cout << "Usted esta en el deserializar de bucket" << endl;
	cout << "Esto es lo que ocurre paso a paso" << endl;
	istringstream buffer (*source);
	cout << "Carga del buffer" << endl;
	delete source;
	int cantidadDeBytes;

	//	hidrato el espacio libre
	buffer.read((char*)&this->espacioLibre,TAM_INT);
	cout << "Carga del espacio libre del bucket" << endl;
	cout << "Espacio libre: " << this->espacioLibre << endl;
	//	hidrato el tamanio de dispersion
	buffer.read((char*)&this->tamanioDeDispersion,TAM_INT);
	cout << "Carga del tamanio de dispersion" << endl;
	cout << "Tamanio De Dispersion: " << this->tamanioDeDispersion << endl;
	//	hidrato la lista de registros
	int tamanioDeLaLista;
	buffer.read((char*)&tamanioDeLaLista,TAM_INT);
	cout << "Carga de la cantidad de registros" << endl;
	cout << "Cantidad de registros: " << tamanioDeLaLista << endl;
	cout << "Carga de registros" << endl;
	for (int i=0; i<tamanioDeLaLista;i++){
		//hidrato el registro*
		stringstream* bufferAuxiliar = new stringstream;
		buffer.read((char*)&cantidadDeBytes,TAM_INT);
		cout << "Carga del tamanio del registro en el buffer auxiliar" << endl;
		cout << "Tamanio del registro actual: " << cantidadDeBytes << endl;
		char* registroSerializado = new char[cantidadDeBytes];
		buffer.read(registroSerializado,cantidadDeBytes);
		bufferAuxiliar->write(registroSerializado,cantidadDeBytes);
		cout << "Carga del registro serializado en el buffer auxiliar" << endl;
		string* registroADeserializar = new string(bufferAuxiliar->str());
//		CHAMUYOOOOOOOOOOOO
		Registro* unRegistro = new Registro(*registroADeserializar);
		cout << "Deserializando registro" << endl;
		unRegistro->deserializar(registroADeserializar);
		cout << "Registro deserializado" << endl;
		this->listaDeRegistros.push_back(unRegistro);
		cout << "Registro cargado" << endl;
		//delete unRegistro;
		delete bufferAuxiliar;
		delete []registroSerializado;
	}
	cout << "Chauuu!" << endl;
}
Bucket::~Bucket() {}
