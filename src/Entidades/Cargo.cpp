#include "Cargo.h"

Cargo::Cargo() {
	this->cargo = "";
}

Cargo::Cargo(string cargoPrincipal){
	this->cargo = cargoPrincipal;
}

/*
void Cargo::modificarCargo(string nuevoCargo){
	this->Cargo = nuevoCargo;
}*/

string Cargo::getCargo(){
	return this->cargo;
}

list<string> Cargo::devolverSubCargos(){
	return this->listaCargos;
}

bool Cargo::agregarCargo(string subCargo){
	bool repetido = false;
	list<string>::iterator it = this->listaCargos.begin();
	while (it != this->listaCargos.end() and (!repetido)){
		if (it->compare(subCargo) == 0){
			repetido = true;
		}
		it++;
	}
	if (!repetido){
		this->listaCargos.push_back(subCargo);
	}
	return (!repetido); //devuelve el resultado de la inserción
}

bool Cargo::eliminarCargo(string subCargo){
	bool existeCargo = false;
	list<string>::iterator it = this->listaCargos.begin();
	while (it != this->listaCargos.end() and (!existeCargo)){
		if (it->compare(subCargo) == 0){
			existeCargo = true;
			this->listaCargos.erase(it);
		}
		it++;
	}
	return existeCargo;
}

int Cargo::getTamanio(){

	int tamanioCargo = TAM_INT + this->cargo.size();
	int tamanioLista = TAM_INT + this->listaCargos.size();
	list<string>::iterator it = this->listaCargos.begin();
	while (it != this->listaCargos.end()){
		tamanioLista += TAM_INT + it->size();
		it++;
	}

	return (tamanioCargo + tamanioLista);
}

unsigned long Cargo::getClave(){
//	int size = cargo.length();
//	int c = 0;
//	for (int i=0; i < size; i++) {
//		c += (int)this->cargo[i];
//	}
//	return c;

	locale loc;                 // the "C" locale

    const collate<char>& coll = use_facet<collate<char> >(loc);

	unsigned long myhash = coll.hash(this->cargo.data(),this->cargo.data()+this->cargo.length());

	return myhash;

}


Cargo::~Cargo() {
	this->listaCargos.clear();
}



string* Cargo::serializar(){

	Serializadora serializadora;

	serializadora.agregarString(&cargo);

	int cantidadCargos = listaCargos.size();

	serializadora.agregarInt(cantidadCargos);

	list<string>::iterator it = listaCargos.begin();
	for(int i = 0; i < cantidadCargos; i++){
		string subcargo = *it;
		serializadora.agregarString(&subcargo);
		it++;
	}

	return serializadora.obtenerSerializacion();

}

void Cargo::deserializar(string * source){

	Serializadora serializadora(source);

	cargo = serializadora.obtenerString();

	int cantidadCargos = serializadora.obtenerInt();

	for(int i=0; i< cantidadCargos; i++)
		this->agregarCargo(serializadora.obtenerString());
}

ResultadoComparacion Cargo::comparar(Entidad *entidad)
{
	ResultadoComparacion resultado = comparacionInvalida;

	if ( tCargo == entidad->getNombreDeEntidad() ){

		int r = cargo.compare(((Cargo*)entidad)->cargo);

		resultado = mayor;

		if ( r == 0 )
			resultado = igual;

		else if ( r < 0 )
			resultado = menor;
	}
	return resultado;
}

Entidad *Cargo::duplicar()
{
	Cargo * copia = new Cargo();
	copia->cargo = this->cargo;
	list<string>::iterator it = this->listaCargos.begin();
	while (it != this->listaCargos.end()){
		copia->agregarCargo(*it);
		it++;
	}
	return copia;
}

void Cargo::verEntidad(){
	cout << "Cargo Principal: " << cargo;
	list<string>::iterator it = listaCargos.begin();
	while(it != listaCargos.end()){
		cout << "Subcargo: "<< *it;
		it++;
	}
}

NombreDeEntidad Cargo::getNombreDeEntidad(){
	return tCargo;
}
