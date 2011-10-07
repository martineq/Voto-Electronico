#include "Registro.h"

Registro::Registro()
{
	this->clave = 0;
	this->contenido = NULL;
}

Registro::Registro(Entidad *entidad)
{
	this->contenido = entidad->duplicar();
	this->determinarClave();
}

Registro::Registro(NombreDeEntidad nombreDeEntidad)
{
	FabricaDeEntidades* fabrica = new FabricaDeEntidades();
	this->contenido = fabrica->crearEntidad(nombreDeEntidad);
	delete (fabrica);
}

/*
 * El método realiza el cálculo de la clave modificando el atributo de la clase
 * debe ser invocado luego de modificar el contenido.
 */
void Registro::determinarClave()
{
	this->clave = this->contenido->getClave();
}


int Registro::getTamanio()
{
	int size = 0;

	size += 4;									// tamanio del tipo de entidad
	size += 4;									// tamanio de la entidad
	size += this->contenido->getTamanio();		// tamanio de la entidad serializada

	return size;
}

std::string *Registro::serializar()
{
	stringstream buffer;

	int entidad = this->getContenido()->getNombreDeEntidad();
	buffer.write((char*)&entidad,TAM_INT);

	int tamanioEntidad = this->getContenido()->getTamanio();
	buffer.write((char*)&tamanioEntidad,TAM_INT);

	string entidadSerializada = *(this->getContenido()->serializar());
	buffer.write(entidadSerializada.c_str(),tamanioEntidad);

	string* s = new string(buffer.str());
	return s;
}

Entidad *Registro::getContenido()
{
	return this->contenido->duplicar();
}

int Registro::obtenerClave(){
	if ( this->contenido == NULL )
		throw "Contenido inexistente";

	return this->clave;
}

void Registro::deserializar(std::string *source){
	int size = sizeof(int);
	int posicion = 0;

	cout << endl << "Bienvenido al deserializar de Registro" << endl;
	stringstream bufferNombreDeEntidad(source->substr(posicion,posicion+size-1));
	cout << "Obtuvimos el nombre de la entidad serializado" << endl;
	NombreDeEntidad nombreDeEntidad = (NombreDeEntidad)bufferNombreDeEntidad.get();
	cout << "La entidad es: " << nombreDeEntidad << endl;
	posicion += size;

	stringstream bufferTamanioEntidad(source->substr(posicion,posicion+size-1));
	cout << "Obtuvimos el tamanio de la entidad serializado" << endl;
	int tamanioEntidad = bufferTamanioEntidad.get();
	cout << "El tamanio de la entidad es: " << tamanioEntidad << endl;

	posicion += size;

	string entidadSerializada = source->substr(posicion,posicion+tamanioEntidad-1);
	cout << "Obtuvimos la entidad serializada y la vamos a deserializar" << endl;

	FabricaDeEntidades fabrica;
	Entidad* nuevoContenido = fabrica.crearEntidad(nombreDeEntidad);
	cout << "Instanciamos su entidad" << endl;
	cout << "Deserializando" << endl;
	nuevoContenido->deserializar(&entidadSerializada);
	cout << "Deserializamos con exito" << endl;
	this->setContenido(nuevoContenido);
	cout << "Cargamos la entidad al registro" << endl << endl;

}

void Registro::setContenido(Entidad *entidad)
{
	if ( this->contenido != NULL )
		delete this->contenido;

	this->contenido = entidad->duplicar();
}

Registro *Registro::duplicar()
{
	NombreDeEntidad nombre = this->getContenido()->getNombreDeEntidad();
	Registro* registro = new Registro(nombre);
	registro->setContenido(this->getContenido());
	return registro;
}

Registro::~Registro()
{
	delete(this->contenido);
	this->contenido = NULL;
}
