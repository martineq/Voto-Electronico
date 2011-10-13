#include "Lista.h"

Lista::Lista() {
	this->nombre="";
	this->fecha="";
	this->cargo="";
	this->cantidadDeVotos=0;
}

Lista::Lista(string nombre, string fecha, string cargo) {
	this->nombre=nombre;
	this->fecha=fecha;
	if (this->verificarCargo(cargo)) this->cargo=cargo;
	else cout << "ERROR CARGO INEXISTENTE" << endl;
	this->cantidadDeVotos=0;
}

bool Lista::verificarCargo(string cargo) {
	#warning "Debe buscarse si el cargo existe usando busqueda secuencial probablemente ya que son pocos cargos"
	return true;
}

Lista::~Lista() {
	// TODO Auto-generated destructor stub
}

string Lista::getNombre () {
	return nombre;
}
string Lista::getFecha () {
	return fecha;
}

int Lista::getTamanio(){
	int tamanioNombre = TAM_INT + this->nombre.size();
	int tamanioFecha = this->fecha.size(); //por default 8
	int tamanioCargo = TAM_INT + this->cargo.size();
	int tamanioCantVotos = sizeof(short int);
	return (tamanioNombre + tamanioFecha + tamanioCargo + tamanioCantVotos);
}

int Lista::getClave(){
	int c = 0;
	for (int i=0; i<this->fecha.length(); i++) {
		c += (int)this->fecha[i];
	}
	for (int i=0; i<this->cargo.length(); i++) {
		c += (int)this->cargo[i];
	}
	for (int i=0; i<this->nombre.length(); i++) {
		c += (int)this->nombre[i];
	}
	return c;
}

string Lista::getCargo () {
	return cargo;
}
short int Lista::getCantidadDeVotos () {
	return cantidadDeVotos;
}
void Lista::incrementarVotos () {
	this->cantidadDeVotos++;
}

string* Lista::serializar() {
	stringstream buffer;
	int cantidadDeBytes;
	cantidadDeBytes   = this->nombre.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->nombre.c_str(),cantidadDeBytes);
	buffer.write((char*)this->fecha.c_str(),cantidadDeBytes);
	cantidadDeBytes   = this->cargo.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->cargo.c_str(),cantidadDeBytes);
	buffer.write((char*)&this->cantidadDeVotos,TAM_SINT);
	string* datos = new string(buffer.str());
	return datos;
}

void Lista::deserializar(string* source) {
	int posicion=0;

//	hidrato la nombre
	stringstream tamanioDeNombre(source->substr(posicion,posicion+TAM_INT-1));
	int tamanio = tamanioDeNombre.get();
	posicion += TAM_INT;
	stringstream nombre(source->substr(posicion,posicion+tamanio-1));
	this->nombre = nombre.get();
	posicion += tamanio;

//	hidrato la fecha
	stringstream fecha(source->substr(posicion,posicion+TAM_FECHA-1));
	this->fecha = fecha.get();
	posicion += TAM_FECHA;

//	hidrato el cargo
	stringstream tamanioDeCargo(source->substr(posicion,posicion+TAM_INT-1));
	tamanio = tamanioDeCargo.get();
	posicion += TAM_INT;
	stringstream cargo(source->substr(posicion,posicion+tamanio-1));
	this->cargo = cargo.get();
	posicion += tamanio;

//	hidrato cantidad De Votos
	stringstream votos(source->substr(posicion,posicion+TAM_INT-1));
	this->cantidadDeVotos = votos.get();
	posicion += TAM_INT;
}

Entidad *Lista::duplicar()
{
	Lista* copia = new Lista();
	copia->cantidadDeVotos = this->cantidadDeVotos;
	copia->cargo = this->cargo;
	copia->fecha = this->fecha;
	copia->nombre = this->nombre;
	return copia;
}

NombreDeEntidad Lista::getNombreDeEntidad(){
	return tLista;
}

