#include "Votante.h"


Votante::Votante(){
	this->dni = 0;
	this->listaDeEleccionesAnteriores=new list <EleccionAnterior*>;
	this->rsa = NULL;
}

Votante::Votante(int dni, string nombre, string password, string domicilio, string distrito) {
	this->dni=dni;
	this->nombre=nombre;
	this->password=password;
	this->domicilio=domicilio;
	this->distrito=distrito;
	this->listaDeEleccionesAnteriores=new list <EleccionAnterior*>;
	this->rsa = NULL;
}

Votante::~Votante() {
	list<EleccionAnterior*>::iterator it = listaDeEleccionesAnteriores->begin();
	while (it!=listaDeEleccionesAnteriores->end()) {
		delete *it;
		it++;
	}
	delete (listaDeEleccionesAnteriores);
	delete this->rsa;
}

void Votante::setNombre (string nombre) {
	this->nombre=nombre;
}

void Votante::setPassword (string password) {
	this->password=password;
}

void Votante::setDomicilio (string domicilio) {
	this->domicilio=domicilio;
}
void Votante::setDistrito (string distrito) {
	this->distrito=distrito;
}

bool Votante::agregarEleccion (string fecha, string cargo) {
	EleccionAnterior* unaEleccionAnterior = new EleccionAnterior (fecha,cargo);
	list <EleccionAnterior*>::iterator it = listaDeEleccionesAnteriores->begin();
	while (it!=listaDeEleccionesAnteriores->end()) {
		EleccionAnterior* eleccionAnterior= new EleccionAnterior((*it)->getFecha(),(*it)->getCargo());
		if ((unaEleccionAnterior->getFecha()==eleccionAnterior->getFecha())&&(unaEleccionAnterior->getCargo()==eleccionAnterior->getCargo())){
			cout << "ERROR: EL VOTANTE YA PARTICIPO EN ESTA ELECCION" << endl;
			delete unaEleccionAnterior;
			delete eleccionAnterior;
			return false;
		}
		delete eleccionAnterior;
		it++;
	}
	listaDeEleccionesAnteriores->push_back(unaEleccionAnterior);
	return true;
}

int  Votante::getTamanio(){
//	int tamanioDni = TAM_INT;
//	int tamanioNombre = TAM_INT + this->nombre.size();
//	int tamanioPassword = TAM_INT + this->password.size();
//	int tamanioDomicilio = TAM_INT + this->domicilio.size();
//	int tamanioDistrito = TAM_INT + this->distrito.size();
//	int tamanioEleccionesAnteriores = TAM_INT; //tamaño de ver cantidad de elementos
//	list<EleccionAnterior*>::iterator it = this->listaDeEleccionesAnteriores->begin();
//	while (it != this->listaDeEleccionesAnteriores->end()){
//		tamanioEleccionesAnteriores += (*it)->getTamanio();
//		it++;
//	}
//
//	return (tamanioDni + tamanioNombre + tamanioNombre + tamanioPassword + tamanioDomicilio +
//			tamanioDistrito + tamanioEleccionesAnteriores);
//	cout << "Tamanio votante encriptado: "<<this->tamanio<<endl;
	string* encriptado = this->serializar();
	delete encriptado;
	return (this->tamanio);
}

unsigned long Votante::getClave(){
	return this->dni;
}

list <EleccionAnterior*>* Votante::getListaDeEleccionesAnteriores () {
	return this->listaDeEleccionesAnteriores;
}

int Votante::getDNI () {
	return this->dni;
}
string Votante::getNombre () {
	return this->nombre;
}
string Votante::getPassword () {
	return this->password;
}
string Votante::getDomicilio () {
	return this->domicilio;
}
string Votante::getDistrito () {
	return this->distrito;
}
void Votante::verEleccionesAnteriores (){
	cout << "Elecciones Anteriores: " << endl;
	cout << "---------------------- " << endl;
	if (this->listaDeEleccionesAnteriores->size()==0)
		cout << "El votante no participo de ninguna eleccion a la fecha" << endl;
	else {
		list<EleccionAnterior*>::iterator it = this->listaDeEleccionesAnteriores->begin();
		while (it!=listaDeEleccionesAnteriores->end()) {
			cout << "Fecha: " << (*it)->getFecha() << "  Cargo: " << (*it)->getCargo() << endl;
			it++;
		}
	}
	cout << endl;
}

void Votante::verVotante() {
	cout << " - Nombre: "    << this->nombre   << endl;
	cout << " - DNI: "       << this->dni      << endl;
	cout << " - Password: "  << this->password << endl;
	cout << " - Domicilio: " << this->domicilio<< endl;
	cout << " - Distrito: "  << this->distrito << endl;
	this->verEleccionesAnteriores ();
}

void Votante::setRSA(RSA * rsa){
	this->rsa = rsa->duplicar();
}


string* Votante::serializar(){
	stringstream buffer;
	int cantidadDeBytes;
	buffer.write((char*)&this->dni,TAM_INT);
	cantidadDeBytes   = this->nombre.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->nombre.c_str(),cantidadDeBytes);
	cantidadDeBytes   = this->password.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->password.c_str(),cantidadDeBytes);
	cantidadDeBytes   = this->domicilio.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->domicilio.c_str(),cantidadDeBytes);
	cantidadDeBytes   = this->distrito.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->distrito.c_str(),cantidadDeBytes);
	int tamanioDeLaListaDeElecciones= this->listaDeEleccionesAnteriores->size();
	buffer.write((char*)&tamanioDeLaListaDeElecciones,TAM_INT);
	list<EleccionAnterior*>:: iterator it = this->listaDeEleccionesAnteriores->begin();
	for (int i=0; i<tamanioDeLaListaDeElecciones; i++){
		cantidadDeBytes = ((*it)->getFecha()).size();
		buffer.write((char*)&cantidadDeBytes,TAM_INT);
		buffer.write((char*)((*it)->getFecha()).c_str(),cantidadDeBytes);
		cantidadDeBytes = ((*it)->getCargo()).size();
		buffer.write((char*)&cantidadDeBytes,TAM_INT);
		buffer.write((char*)((*it)->getCargo()).c_str(),cantidadDeBytes);
		it++;
	}
	string strNuevo = this->rsa->encriptar(buffer.str());
//	cout << "StrNuevo.size(): "<<strNuevo.size()<<endl;
	this->tamanio = (int)strNuevo.size();
//	cout << "Tamanio: "<<this->tamanio<<endl;
	return new string(strNuevo);
//	return new string(buffer.str());
}

void Votante::deserializar(string* source){
	ManejadorDeArchivo manejador ("clavePrivada.txt");
	this->rsa = new RSA();
	long long* numero = new long long;
	manejador.posicionarse(0);
	char* buf= new char[sizeof(long long)]; 		// Preparo un buffer de tamaño int para obtener los datos		// Voy a la posición <pos>
	manejador.leer(buf,sizeof(long long));	// Leo en archivo
	(*numero) = *(long long*)buf;					// Guardo el valor en donde apunta <dest>
	delete[] buf;
	this->rsa->setD(*numero);
	char* buf2= new char[sizeof(long long)]; 		// Preparo un buffer de tamaño int para obtener los datos		// Voy a la posición <pos>
	manejador.leer(buf2,sizeof(long long));	// Leo en archivo
	(*numero) = *(long long*)buf2;					// Guardo el valor en donde apunta <dest>
	delete[] buf2;
	this->rsa->setN(*numero);


	char* buf3= new char[sizeof(long long)]; 		// Preparo un buffer de tamaño int para obtener los datos		// Voy a la posición <pos>
	manejador.leer(buf3,sizeof(long long));	// Leo en archivo
	(*numero) = *(long long*)buf3;					// Guardo el valor en donde apunta <dest>
	delete[] buf3;
	this->rsa->setE(*numero);
	delete numero;
//
//	cout << "D: "<<this->rsa->getD()<<endl;
//	cout << "N: "<<this->rsa->getN()<<endl;
//	cout << "E: "<<this->rsa->getE()<<endl;
//	char trulala;
//	cin >> trulala;
//
//
//	cout << "this->rsa->getN();= " << this->rsa->getN() << endl;
//	cout << "this->rsa->getD();= " << this->rsa->getD() << endl;

	istringstream buffer ( this->rsa->desencriptar(*source));

//	istringstream buffer(*source);
	stringstream * miString;
	int cantidadDeBytes;

//	hidrato el dni
    buffer.read((char*)&this->dni,TAM_INT);
    cout << "DNI: "<<this->dni<<endl;
//  hidrato el nombre
    buffer.read((char*)&cantidadDeBytes,TAM_INT);
    char* nombreSerializado = new char[cantidadDeBytes];
    buffer.read((char*)nombreSerializado,cantidadDeBytes);
    miString = new stringstream();
    miString->write(nombreSerializado,cantidadDeBytes);
    string* pasoAString = new string(miString->str());
    this->nombre = *pasoAString;
    delete []nombreSerializado;
    delete pasoAString;
    delete miString;

    cout << "Nombre: "<<this->nombre<<endl;
//  hidrato el password
    buffer.read((char*)&cantidadDeBytes,TAM_INT);
//    cout << "CantBytes: "<<cantidadDeBytes<<endl;
    char* passwordSerializado = new char[cantidadDeBytes];
    buffer.read((char*)passwordSerializado,cantidadDeBytes);
    miString = new stringstream();
    miString->write(passwordSerializado,cantidadDeBytes);
    pasoAString = new string (miString->str());
    this->password = *pasoAString;
    delete [] passwordSerializado;
    delete pasoAString;
    delete miString;

//  hidrato el domicilio
    buffer.read((char*)&cantidadDeBytes,TAM_INT);
    char* domicilioSerializado = new char[cantidadDeBytes];
    buffer.read((char*)domicilioSerializado,cantidadDeBytes);
    miString = new stringstream();
    miString->write(domicilioSerializado,cantidadDeBytes);
    pasoAString = new string (miString->str());
    this->domicilio = *pasoAString;
    delete []domicilioSerializado;
    delete pasoAString;
    delete miString;

//  hidrato el distritoYayiiiY
    buffer.read((char*)&cantidadDeBytes,TAM_INT);
    char* distritoSerializado = new char[cantidadDeBytes];
    buffer.read((char*)distritoSerializado,cantidadDeBytes);
    miString = new stringstream();
    miString->write(distritoSerializado,cantidadDeBytes);
    pasoAString = new string (miString->str());
    this->distrito = *pasoAString;
    delete []distritoSerializado;
    delete pasoAString;
    delete miString;

//  hidrato la lista de elecciones anteriores
    int tamanioDeLaLista;
    buffer.read((char*)&tamanioDeLaLista,TAM_INT);
    for (int i=0; i<tamanioDeLaLista;i++){
//		hidrato la fecha de una Eleccion Anterior
		stringstream* bufferAuxiliar = new stringstream;
		buffer.read((char*)&cantidadDeBytes,TAM_INT);
		char* fechaSerializada = new char[cantidadDeBytes];
		buffer.read(fechaSerializada,cantidadDeBytes);
		bufferAuxiliar->write(fechaSerializada,cantidadDeBytes);
		string fecha = bufferAuxiliar->str();
		delete bufferAuxiliar;
		delete []fechaSerializada;

//		hidrato el cargo de la Eleccion Anterior
		bufferAuxiliar = new stringstream;
		buffer.read((char*)&cantidadDeBytes,TAM_INT);
		char* cargoEnBytes = new char[cantidadDeBytes];
		buffer.read(cargoEnBytes,cantidadDeBytes);
		bufferAuxiliar->write(cargoEnBytes,cantidadDeBytes);
		string cargo = bufferAuxiliar->str();
		delete []cargoEnBytes;
		delete bufferAuxiliar;

		EleccionAnterior* unaEleccionAnterior = new EleccionAnterior(fecha,cargo);
		this->listaDeEleccionesAnteriores->push_back(unaEleccionAnterior);
//		cout << "salgo"<<endl;
//		el delete de unaEleccionAnterior esta en el destructor
//		porque mi lista es lista de punteros a Eleccion Anterior
	}
}

ResultadoComparacion Votante::comparar(Entidad *entidad)
{
	ResultadoComparacion resultado = comparacionInvalida;

	if ( tVotante == entidad->getNombreDeEntidad() ){

		int r = dni-(((Votante*)entidad)->dni);

		resultado = mayor;

		if ( r == 0 )
			resultado = igual;

		else if ( r < 0 )
			resultado = menor;
	}
	return resultado;
}

Entidad *Votante::duplicar()
{
	Votante* copia = new Votante();
	copia->distrito = this->distrito;
	copia->dni = this->dni;
	copia->domicilio = this->domicilio;
	copia->nombre = this->nombre;
	copia->password = this->password;
	copia->rsa = this->rsa->duplicar();
	copia->tamanio = this->tamanio;
	list<EleccionAnterior*>::iterator it = this->listaDeEleccionesAnteriores->begin();
	while (it != this->listaDeEleccionesAnteriores->end()){
		copia->agregarEleccion((*it)->getFecha(),(*it)->getCargo());
		it++;
	}
	return copia;
}

void Votante::verEntidad()
{
	this->verVotante();
}

NombreDeEntidad Votante::getNombreDeEntidad(){
	return tVotante;
}
