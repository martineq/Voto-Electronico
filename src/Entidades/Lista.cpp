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
	int tamanioFecha 	= TAM_INT;
	int tamanioNombre 	= TAM_INT + this->nombre.size();
	int tamanioCargo	= TAM_INT + this->cargo.size();
	int tamanioCantVotos= sizeof(short int);
	return (tamanioNombre + tamanioFecha + tamanioCargo + tamanioCantVotos);
}

int Lista::getClave(){
	int c = 0;

	int size = fecha.length();
	for (int i=0; i< size; i++)
		c += (int)this->fecha[i];

	size = cargo.length();
	for (int i=0; i< size ; i++)
		c += (int)this->cargo[i];

	size = nombre.length();
	for (int i=0; i< size ; i++)
		c += (int)this->nombre[i];

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

	int fechaInt;

	Serializadora serializadora;
	stringstream fechaStream (fecha);
	fechaStream >> fechaInt;

	serializadora.agregarInt(fechaInt);
	serializadora.agregarString(&nombre);
	serializadora.agregarString(&cargo);
	serializadora.agregarShortInt(cantidadDeVotos);

	return serializadora.obtenerSerializacion();
}

void Lista::deserializar(string* source) {

	Serializadora serializadora(source);

	stringstream fechaStream;
	fechaStream << serializadora.obtenerInt();

	fecha  = fechaStream.str();
	nombre = serializadora.obtenerString();
	cargo  = serializadora.obtenerString();
	cantidadDeVotos = serializadora.obtenerShortInt();

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

