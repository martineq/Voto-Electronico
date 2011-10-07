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
//			this->listaDeRegistros.push_back(unRegistro);
			Registro* registro = unRegistro->duplicar();
			this->listaDeRegistros.push_back(registro);
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

		buffer.write(((*it)->serializar())->c_str(),cantidadDeBytes);
		cout << "Se cargo el registro en buffer: " << *((*it)->serializar()) << endl;

	}
	cout << "Fin del serializado del bucket" << endl << endl;
	string* datos = new string(buffer.str());
	return datos;
}
void Bucket::deserializar(string* source){

	cout << endl << "Usted esta en el deserializar de bucket" << endl;

	istringstream buffer (*source);
	cout << "Carga del buffer" << endl;
	delete source;
	int cantidadDeBytes;

	//	hidrato el espacio libre
	buffer.read((char*)&this->espacioLibre,TAM_INT);
	cout << "Se cargo el espacio libre: " << this->espacioLibre << endl;

	//	hidrato el tamanio de dispersion
	buffer.read((char*)&this->tamanioDeDispersion,TAM_INT);
	cout << "Se cargo el tamanio de dispersion: " << this->tamanioDeDispersion << endl;

	//	hidrato la lista de registros
	int tamanioDeLaLista;
	buffer.read((char*)&tamanioDeLaLista,TAM_INT);
	cout << "Se cargo la cantidad de registros: " << tamanioDeLaLista << endl;

	cout << "Carga de registros" << endl;
	for (int i=0; i<tamanioDeLaLista;i++){
		//hidrato el registro*
		stringstream* bufferAuxiliar = new stringstream;
		buffer.read((char*)&cantidadDeBytes,TAM_INT);
		cout << "Se cargo el tamanio de un registro: " << cantidadDeBytes << endl;

		char* registroSerializado = new char[cantidadDeBytes];
		buffer.read(registroSerializado,cantidadDeBytes);
		bufferAuxiliar->write(registroSerializado,cantidadDeBytes);

		string* registroADeserializar = new string(bufferAuxiliar->str());
		cout << "Se cargo el registro en buffer: " << *registroSerializado << endl;
		cout << "Se cargo el registro en buffer: " << *registroADeserializar << endl;

		Registro* unRegistro = new Registro();
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
