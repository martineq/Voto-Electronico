#include "Registro.h"

Registro::Registro(string registroSerializado){
	this->deserializar(&registroSerializado);
	this->determinarClave();
}

Registro::Registro(Entidad *entidad)
{

	#warning	"No se duplica la entidad";
	//this->contenido = entidad->duplicar();
	this->contenido = entidad;
	this->determinarClave();
}

Registro::Registro(NombreDeEntidad nombreDeEntidad){

	FabricaDeEntidades* fabrica = new FabricaDeEntidades();
	this->contenido = fabrica->crearEntidad(nombreDeEntidad);
	delete (fabrica);
}

/*
 * El método realiza el cálculo de la clave modificando el atributo de la clase
 * debe ser invocado luego de modificar el contenido.
 */
void Registro::determinarClave(){
	this->clave = this->contenido->getClave();
}


int Registro::getTamanio(){
	return this->contenido->getTamanio();
}

std::string *Registro::serializar(){

	#warning	"Faltaría agregar la serializacion del tipo de datos";
	stringstream buffer;

	int entidad = this->getContenido()->getNombreDeEntidad();
	buffer.write((char*)&entidad,TAM_INT);

	int tamanioEntidad = this->getContenido()->getTamanio();
	buffer.write((char*)&tamanioEntidad,TAM_INT);

	string entidadSerializada = *(this->getContenido()->serializar());
	buffer.write((char*)entidadSerializada.c_str(),tamanioEntidad);

	string* s = new string(buffer.str());
	return s;
}

Entidad *Registro::getContenido()
{
	return this->contenido;
}

int Registro::obtenerClave(){
	if ( this->contenido == NULL )
		throw "Contenido inexistente";

	return this->clave;
}

void Registro::deserializar(std::string *source)
{
	int size = sizeof(int);
	int posicion = 0;

	stringstream bufferNombreDeEntidad(source->substr(posicion,posicion+size-1));
	NombreDeEntidad nombreDeEntidad = (NombreDeEntidad)bufferNombreDeEntidad.get();

	posicion += size;

	stringstream bufferTamanioEntidad(source->substr(posicion,posicion+size-1));
	int tamanioEntidad = bufferTamanioEntidad.get();

	posicion += size;

	string entidadSerializada = source->substr(posicion,posicion+tamanioEntidad-1);

	FabricaDeEntidades fabrica;
	Entidad* nuevoContenido = fabrica.crearEntidad(nombreDeEntidad);

	nuevoContenido->deserializar(&entidadSerializada);

	Distrito* d = (Distrito*)nuevoContenido;

	cout << d->getDistrito() << endl;

	this->setContenido(nuevoContenido);

}

void Registro::setContenido(Entidad *entidad)
{
	if ( this->contenido != NULL )
		delete this->contenido;

	#warning "acá debería duplicarse";
	this->contenido = entidad;
}

Registro *Registro::duplicar()
{
	NombreDeEntidad nombre = this->getContenido()->getNombreDeEntidad();
	Registro* registro = new Registro(nombre);
	registro->setContenido(registro->getContenido());
	return registro;
}

Registro::~Registro()
{
	delete(this->contenido);
	this->contenido = NULL;
}
