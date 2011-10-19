#include "Registro.h"

Registro::Registro()
{
	this->clave = -1;
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
	if ( this->contenido != NULL )
		this->clave = this->contenido->getClave();
	else
		this->clave = -1;
}


int Registro::getTamanio()
{
	int size = 0;

	if ( this->contenido != NULL ){

		size += 4;									// tamanio del tipo de entidad
		size += 4;									// tamanio de la entidad
		size += this->contenido->getTamanio();		// tamanio de la entidad serializada

	}
	return size;
}

Entidad *Registro::getContenido(){
	Entidad* entidad = NULL;
	if (this->contenido != NULL)
		entidad = this->contenido->duplicar();
	return entidad;
}

int Registro::obtenerClave(){
	return this->clave;
}

std::string *Registro::serializar()
{
	stringstream buffer;

	if (this->contenido != NULL){

		int entidad = this->contenido->getNombreDeEntidad();
		buffer.write((char*)&entidad,TAM_INT);

		int tamanioEntidad = this->contenido->getTamanio();
		buffer.write((char*)&tamanioEntidad,TAM_INT);

		string* contenidoSerializado = this->contenido->serializar();
		buffer.write(contenidoSerializado->c_str(),tamanioEntidad);
		delete contenidoSerializado;
	}

	return new string(buffer.str());
}

void Registro::deserializar(std::string *source){

	if ( source->size() > 0 ){

		Serializadora serializadora(source);

		NombreDeEntidad nombreDeEntidad = (NombreDeEntidad)serializadora.obtenerInt();

		string* entidadSerializada = serializadora.obtenerStringPointer();

		FabricaDeEntidades fabrica;
		Entidad* nuevoContenido = fabrica.crearEntidad(nombreDeEntidad);
		nuevoContenido->deserializar(entidadSerializada);

		delete entidadSerializada;
//		cout << "Deserializamos con exito" << endl;
		this->setContenido(nuevoContenido);
		delete nuevoContenido;

	}else{
		cout << "No se pudo deserealizar el registro pues el tamaño de la fuente es nula." << endl;
	}
}

void Registro::setContenido(Entidad *entidad)
{
	if ( this->contenido != NULL )
		delete this->contenido;

	this->contenido = entidad->duplicar();
	this->determinarClave();
}

Registro *Registro::duplicar(){
	NombreDeEntidad nombre = this->contenido->getNombreDeEntidad();
	Registro* registro = new Registro(nombre);
	registro->setContenido(this->contenido);
	registro->determinarClave();
	return registro;
}

ResultadoComparacion Registro::comparar(Registro *registroMuestra)
{
	return contenido->comparar(registroMuestra->contenido);
}

void Registro::verContenido()
{
	if (contenido != NULL)
		contenido->verEntidad();
	else
		cout << "Contenido vacio" << endl;
}

Registro::~Registro()
{
//	cout << "destruyo Registro" << endl;
	delete(this->contenido);
	this->contenido = NULL;
}
