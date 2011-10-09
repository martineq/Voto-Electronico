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
	int size = sizeof(int);
	int posicion = 0;

	if ( source->size() > 0 ){

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
		cout << "Deserializamos con exito" << endl;
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
}

Registro *Registro::duplicar(){
	NombreDeEntidad nombreDeLaEntidad = this->contenido->getNombreDeEntidad();
	Registro* registro = new Registro(nombreDeLaEntidad);
	registro->setContenido(this->contenido);
	registro->determinarClave();
	return registro;
}

Registro::~Registro()
{
	delete(this->contenido);
	this->contenido = NULL;
}
