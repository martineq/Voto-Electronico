#include "Lista.h"

Lista::Lista() {
	this->nombre="";
	this->fecha="";
	this->cargo="";
}

void Lista::verEntidad(){
	cout << "Nombre: "<<nombre << endl;
	cout << "Fecha: "<<fecha << endl;
	cout << "Cargo: "<<cargo << endl;
}

Lista::Lista(string nombre, string fecha, string cargo) {
	this->nombre=nombre;
	this->fecha=fecha;
	if (this->verificarCargo(cargo)) this->cargo=cargo;
	else cout << "ERROR CARGO INEXISTENTE" << endl;
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
	int tamanioFecha 	= TAM_INT + this->fecha.size();
	int tamanioNombre 	= TAM_INT + this->nombre.size();
	int tamanioCargo	= TAM_INT + this->cargo.size();
	return (tamanioNombre + tamanioFecha + tamanioCargo);
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

string* Lista::serializar() {

	Serializadora serializadora;

	serializadora.agregarString(&fecha);
	serializadora.agregarString(&nombre);
	serializadora.agregarString(&cargo);

	return serializadora.obtenerSerializacion();
}

void Lista::deserializar(string* source) {

	Serializadora serializadora(source);

	fecha  = serializadora.obtenerString();
	nombre = serializadora.obtenerString();
	cargo  = serializadora.obtenerString();

}

Entidad *Lista::duplicar(){

	Lista* copia = new Lista();
	copia->cargo = this->cargo;
	copia->fecha = this->fecha;
	copia->nombre = this->nombre;
	return copia;
}

NombreDeEntidad Lista::getNombreDeEntidad(){
	return tLista;

}

ResultadoComparacion Lista::comparar(Entidad* entidad){
	if ( tLista != entidad->getNombreDeEntidad() ){
		return comparacionInvalida;
	}
	Lista* listaNueva = (Lista*) entidad;
	int compararFecha = this->fecha.compare(listaNueva->fecha);
	int compararCargo = this->cargo.compare(listaNueva->cargo);
	int compararLista = this->nombre.compare(listaNueva->nombre);
	if (compararFecha < 0){
		return menor;
	}
	if (compararFecha > 0){
		return mayor;
	}
	if (compararCargo < 0){
		return menor;
	}
	if (compararCargo > 0){
		return mayor;
	}
	if (compararLista < 0){
		return menor;
	}
	if (compararLista > 0){
		return mayor;
	}
	return igual;

}
