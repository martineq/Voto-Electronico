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
//	this->espacioLibre=LONGITUD_BLOQUE;  // LONGITUD_BLOQUE Ya no se usa mas!!!
}

Registro* Bucket::getRegistro(Registro* registro){
	if (this->listaDeRegistros.empty()) return NULL;
	else {
		list<Registro*>::iterator it = this->listaDeRegistros.begin();
		while (it!=listaDeRegistros.end()) {
			if ( (*it)->comparar(registro) == igual ) {
				Registro* unRegistro = (*it)->duplicar();
				return unRegistro;
			}
			it++;
		}
	}
	return NULL;
}

Registro* Bucket::consultarRegistro(Registro* registro){
	if (this->listaDeRegistros.empty()) return NULL;
	else {
		list<Registro*>::iterator it = this->listaDeRegistros.begin();
		while (it!=listaDeRegistros.end()) {
			if ( (*it)->comparar(registro) == igual ) return *it;
			it++;
		}
	}
	return NULL;
}

//devuelve el resultado de la operacion
bool Bucket::agregarRegistro(Registro* unRegistro){
	if (this->consultarRegistro(unRegistro)!=NULL) return false;
	else
		if ((unRegistro->getTamanio()+TAM_INT)>this->espacioLibre) return  false;
		else {
			Registro* registro = unRegistro->duplicar();
			this->listaDeRegistros.push_back(registro);
			this->espacioLibre-= (unRegistro->getTamanio()+TAM_INT);
			return true;
		}
}

bool Bucket::eliminarRegistro(Registro* registro){
	if (this->listaDeRegistros.empty()) {
		cout << "ERROR: EL BUCKET ESTA VACIO" << endl;
		return false;
	}
	else {
		if (this->consultarRegistro(registro)==NULL) return false;
		else {
			list<Registro*>::iterator it = this->listaDeRegistros.begin();
			while (it!=listaDeRegistros.end()) {
				if ( (*it)->comparar(registro) == igual ) {
					this->espacioLibre+=((*it)->getTamanio()+TAM_INT);
					delete *it;
					this->listaDeRegistros.erase (it);
					return true;
				}
				else it++;
			}
			return false;
		}
	}
}

bool Bucket::reemplazarRegistro(Registro* unRegistro){
	if (this->listaDeRegistros.empty()) return false;
	else {
		if (this->consultarRegistro(unRegistro)==NULL) return false;
		else {
			Registro* registroAReemplazar = this->consultarRegistro(unRegistro);
			if ((registroAReemplazar->getTamanio()+this->espacioLibre) >= unRegistro->getTamanio()){
				this->eliminarRegistro(unRegistro);
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
	//cout << endl << "Usted esta en el serializar de bucket" << endl;

	stringstream buffer;
	int cantidadDeBytes;

	//cout << "Comienza la carga de elementos en buffer." << endl;

	buffer.write((char*)&this->espacioLibre,TAM_INT);
	//cout << "Se cargo el espacio libre: " << this->espacioLibre << endl;

	buffer.write((char*)&this->tamanioDeDispersion,TAM_INT);
	//cout << "Se cargo el tamanio de dispersion: " << this->tamanioDeDispersion << endl;

	int cantidadDeRegistros= this->listaDeRegistros.size();
	buffer.write((char*)&cantidadDeRegistros,TAM_INT);
	//cout << "Se cargo la cantidad de registros: " << cantidadDeRegistros << endl;

	for (list<Registro*>:: iterator it = this->listaDeRegistros.begin(); it != listaDeRegistros.end(); it++){

		cantidadDeBytes = ((*it)->getTamanio());
		buffer.write((char*)&cantidadDeBytes,TAM_INT);
		//cout << "Se cargo el tamanio de un registro: " << cantidadDeBytes << endl;

		string* registroSerializado = (*it)->serializar();
		buffer.write(registroSerializado->c_str(),cantidadDeBytes);
		delete registroSerializado;

	}
	//cout << "Fin del serializado del bucket" << endl << endl;
	string* datos = new string(buffer.str());
	return datos;
}
void Bucket::deserializar(string* bufferSerializado){
	//cout << endl << "Usted esta en el deserializar de bucket" << endl;
	if (bufferSerializado->size()==0) cout << "No se pudo hidratar el Bucket pues la fuente es nula" << endl;
	else {

		Serializadora serializadora(bufferSerializado);

		//	hidrato el espacio libre
		espacioLibre = serializadora.obtenerInt();
//		cout << "Se cargo el espacio libre: " << this->espacioLibre << endl;

		//	hidrato el tamanio de dispersion
		tamanioDeDispersion = serializadora.obtenerInt();
//		cout << "Se cargo el tamanio de dispersion: " << this->tamanioDeDispersion << endl;

		//	hidrato la lista de registros
		int tamanioDeLaLista = serializadora.obtenerInt();
//		cout << "Se cargo la cantidad de registros: " << tamanioDeLaLista << endl;

		//cout << "Carga de registros" << endl;
		for (int i=0; i<tamanioDeLaLista;i++){

			string* registroSerializado = serializadora.obtenerStringPointer();

			//hidrato el registro
			Registro* unRegistro = new Registro();
			unRegistro->deserializar(registroSerializado);

			delete registroSerializado;

			this->listaDeRegistros.push_back(unRegistro);
		}
	}
}
void Bucket::mostarClavesDeBucket()
{
	cout <<"Contenido del bucket: ";
	list<Registro*>::iterator it = this->listaDeRegistros.begin();
	while( it != listaDeRegistros.end()){
		cout << " " << (*it)->obtenerClave();
		it++;
	}
	cout << endl;
}

void Bucket::verInfoBucket(){
	cout << "Contenido del bucket: "<<endl;
	cout << " - Espacio libre: " << espacioLibre << endl;
	cout << " - Tamanio de Dispersion: " << tamanioDeDispersion << endl;
	int cantidadRegistros = listaDeRegistros.size();
	cout << " - Cantidad de registros: " << cantidadRegistros << endl;
}

void Bucket::mostarBucket(){
	verInfoBucket();

	list<Registro*>::iterator it = this->listaDeRegistros.begin();
	int i = 1;
	while( it != listaDeRegistros.end()){
		cout << "Contenido del registro " << i++ <<endl;
		(*it)->verContenido();
		it++;
	}
	cout << endl;
}

Bucket::~Bucket() {
	for (list<Registro*>:: iterator it = this->listaDeRegistros.begin(); it != listaDeRegistros.end(); it++)
		delete *it;
}
