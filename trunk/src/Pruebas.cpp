#include "Pruebas.h"

Pruebas::Pruebas() {

}

Pruebas::~Pruebas() {
	delete this->distrito1,this->distrito2,this->distrito3,this->distrito4;
	delete this->registro1,this->registro2,this->registro3,this->registro4;
	delete (bucket);
}

void Pruebas::iniciarRegistrosDistrito(){
	this->distrito1 = new Distrito("Puerto Esperanza");
	this->distrito2 = new Distrito("Buenos Aires");
	this->distrito3 = new Distrito("Montecarlo");
	this->distrito4 = new Distrito("Eldorado");
	this->registro1 = new RegistroDistrito(distrito1);
	this->registro2 = new RegistroDistrito(distrito2);
	this->registro3 = new RegistroDistrito(distrito3);
	this->registro4 = new RegistroDistrito(distrito4);
	this->bucket = new Bucket(0);
	cout << "El espacio libre es: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	this->bucket->agregarRegistro(registro1);
	this->bucket->agregarRegistro(registro2);
	this->bucket->agregarRegistro(registro3);
	this->bucket->agregarRegistro(registro4);
}

void Pruebas::verContenidoBucket(){
	cout << "Los registros cargados son:" << endl;
	list<Registro*>::iterator it = bucket->ubicarPrimero();
	int n = bucket->getCantidadDeRegistros();
	for(int i = 0; i <n;i++ ){
		Registro* unRegistro = *it;
		Distrito* unDistrito = (Distrito*)unRegistro->getContenido();
		cout << "Distrito: " << unDistrito->getDistrito() << endl;
		it++;
	}
	cout << endl;
}

void Pruebas::pruebaAgregarRegistrosAlBucket(){
	cout << endl;
	cout << "Bienvenido a las pruebas de agregar registros a un bucket" << endl;
	cout << "Observe y disfrute" << endl;
	cout << "Iniciando prueba carga de cero" << endl;
	this->iniciarRegistrosDistrito();
	cout << "Carga finalizada" << endl;
	cout << "El espacio libre es: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
	if (bucket->getCantidadDeRegistros()==4) cout << "Prueba OK" << endl;
	else cout << "ERROR" << endl;
	this->verContenidoBucket();
	cout << "Iniciando prueba agregar un registro sin espacio libre" << endl;
	cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	Distrito* distrito5 = new Distrito("Obera");
	Registro* registro5 = new RegistroDistrito(distrito5);
	cout << "Intentando carga de registro" << endl;
	if (!this->bucket->agregarRegistro(registro5)) {
		cout << "No se pudo cargar el registro" << endl;
		cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
		cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
		cout << "Prueba OK" << endl;
	}
	else cout << "ERROR" << endl;
	cout << endl;
	cout << "Iniciando prueba carga de registro luego de eliminar registros" << endl;
	cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	list<Registro*>::iterator it = this->bucket->ubicarPrimero();
	int clave = (*it)->obtenerClave();
	cout << "Eliminando el primer registro" << endl;
	this->bucket->eliminarRegistro(clave);
	cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
	cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	cout << "El tamaño del registro nuevo es: " << registro5->getTamanio() << endl;
	cout << "Intentando carga del registro" << endl;
	if (this->bucket->agregarRegistro(registro5)) {
		cout << "El registro fue cargado" << endl;
		cout << "Se elimino el primer registro Puerto Esperanza y se agrego Obera" << endl;
		cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
		cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
		cout << "Prueba OK" << endl;
	}
	else cout << "ERROR" << endl;
	this->verContenidoBucket();
	cout << "Iniciando prueba carga de registro con clave ya existente" << endl;
	cout << "Se intenta agregar el registro Obera ya existente" << endl;
	cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	it = this->bucket->ubicarPrimero();
	clave = (*it)->obtenerClave();
	this->bucket->eliminarRegistro(clave);
	it = this->bucket->ubicarPrimero();
	clave = (*it)->obtenerClave();
	this->bucket->eliminarRegistro(clave);
	cout << "Se hizo espacio para el nuevo registro Obera" << endl;
	cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	Distrito* distrito6 = new Distrito("Obera");
	Registro* registro6 = new RegistroDistrito(distrito6);
	cout << "Se intenta la carga del registro duplicado" << endl;
	if (!this->bucket->agregarRegistro(registro6)) {
		cout << "El registro no fue cargado" << endl;
		cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
		cout << "La prueba es exitosa porque el registro esta duplicado y no por no tener espacio" << endl;
		cout << "Prueba OK" << endl;
	}
	else cout << "ERROR" << endl;
	cout << endl;
	cout << "Estas fueron todas las pruebas de agregar registros al bucket" << endl;
	cout << "Gracias! Hasta luego" << endl;
	delete distrito5;
	delete registro5;
	delete distrito6;
	delete registro6;
}

void Pruebas::pruebaEliminarRegistrosDelBucket(){
	cout << endl;
	cout << "Bienvenido a las pruebas de eliminacion de registros en un bucket" << endl;
	cout << "Observe y disfrute" << endl;
	cout << "Prueba eliminar un registro con bucket vacio" << endl;
	cout << "Intentando eliminar un registro" << endl;
	Bucket* unBucket = new Bucket (0);
	if (!unBucket->eliminarRegistro(8)) cout << "Prueba OK" << endl;
	else cout << "ERROR" << endl;
	delete unBucket;
	cout << "Prueba eliminar el primer registro" << endl;
	this->iniciarRegistrosDistrito();
	cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
	cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	this->verContenidoBucket();
//	elimino el primer registro
	list<Registro*>::iterator it = this->bucket->ubicarPrimero();
	int clave = (*it)->obtenerClave();
	cout << "Eliminando el primer registro" << endl;
	if (this->bucket->eliminarRegistro(clave)) {
		cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
		cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
		this->verContenidoBucket();
		cout << "prueba OK" << endl;
	}
	else cout << "ERROR" << endl;
	cout << endl;
	cout << "Prueba eliminar un registro inexistente" << endl;
	cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
	cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	cout << "Intento de eliminar Resistencia" << endl;
	it = this->bucket->ubicarPrimero();
	Distrito* distrito5 = new Distrito ("Resistencia");
	Registro* registro5 = new RegistroDistrito (distrito5);
	clave = registro5->obtenerClave();
	if (!this->bucket->eliminarRegistro(clave)) {
		cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
		cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
		this->verContenidoBucket();
		cout << "prueba OK" << endl;
	}
	else cout << "ERROR" << endl;
	cout << "Prueba eliminar un registro intermedio" << endl;
	cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
	cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	clave = this->registro3->obtenerClave();
	cout << "intento eliminar Montecarlo" << endl;
	if (this->bucket->eliminarRegistro(clave)) {
		cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
		cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
		this->verContenidoBucket();
		cout << "prueba OK" << endl;
	}
	else cout << "ERROR" << endl;
	delete (distrito5);
	delete (registro5);
	cout << "Estas fueron todas las pruebas de eliminar registros del bucket" << endl;
	cout << "Gracias! Hasta luego" << endl;

}

void Pruebas::pruebaReemplazarRegistroEnBucket() {
	//TODO
	cout << endl;
	cout << "Bienvenido a las pruebas de actualizacion de registros en un bucket" << endl;
	cout << "Observe y disfrute" << endl;
	Votante* votante1 = new Votante (1,"Daniel","","","");
	Votante* votante2 = new Votante (2,"Adrian","","","");
	Votante* votante3 = new Votante (3,"Martin","","","");
	Votante* votante4 = new Votante (4,"Gonzalo","","","");
//	this->registro1 = new RegistroVotante (votante1);
//	this->registro2 = new RegistroVotante (votante2);
//	this->registro3 = new RegistroVotante (votante3);
//	this->registro4 = new RegistroVotante (votante4);
//	cout << "Tamanio de los 4 votantes= " << registro1->getTamanio()+
//			registro2->getTamanio()+registro3->getTamanio()+registro4->getTamanio() << endl;
//	Pruebas:
//	que al reemplazar no entre
//	que quiera reemplazar con la lista vacia
//	que quiera reemplazar un registro inexistente

	delete (votante1,votante2,votante3,votante4);
//	delete (registro1,registro2,registro3,registro4);
	cout << "Estas fueron todas las pruebas de actualizacion de registros de un bucket" << endl;
	cout << "Gracias! Hasta luego" << endl;
}


void Pruebas::serializarBucket(){
	cout << endl;
	cout << "Bienvenido a las pruebas de serializacion de un bucket" << endl;
	cout << "Observe y disfrute" << endl;
	cout << "Estas fueron todas las pruebas de serializacion de un bucket" << endl;
	cout << "Gracias! Hasta luego" << endl;
}

void Pruebas::deserializarBucket(){
	cout << endl;
	cout << "Bienvenido a las pruebas de deserializacion de un bucket" << endl;
	cout << "Observe y disfrute" << endl;
	cout << "Estas fueron todas las pruebas de deserializacion de un bucket" << endl;
	cout << "Gracias! Hasta luego" << endl;
}

void Pruebas::pruebaAgregarRegistrosHashingExtensible(){

        ArchivoDeBuckets* archivo = new ArchivoDeBuckets();
        HashingExtensible* he = new HashingExtensible(archivo);

        Distrito* distrito = new Distrito("1");
        RegistroDistrito* registro = new RegistroDistrito(distrito);

        Distrito* distrito2 = new Distrito("12");
        RegistroDistrito* registro2 = new RegistroDistrito(distrito2);

        Distrito* distrito3 = new Distrito("3");
        RegistroDistrito* registro3 = new RegistroDistrito(distrito3);

        he->agregarRegistro(registro);
        he->agregarRegistro(registro2);
        he->agregarRegistro(registro3);


        delete(archivo);
        delete(he);
        delete(distrito);
        delete(registro);
        delete(distrito2);
        delete(registro2);
        delete(distrito3);
        delete(registro3);

}


int Pruebas::serializarDeserializarCargo(){
	Cargo* cargo1 = new Cargo("Presidente   1");
	Cargo* cargo2 = new Cargo();
	list<string> listas1;
	list<string> listas2;

	cout << "Cargo: " << cargo1->getCargo() <<endl;
	cargo1->agregarCargo("Vicepresidente");
	cargo1->agregarCargo("Senador");
	listas1 = cargo1->devolverSubCargos();
	list<string>::iterator it1 = listas1.begin();
	while (it1 != listas1.end()){
		cout << "SubCargo: "<< (*it1) <<endl;
		it1++;
	}

	cout << endl;
	cout << "Comienzo serializado de Cargo" << endl;
	string* source = cargo1->serializar();
	cout << "Fin serializado de Cargo" << endl;
	cout << endl;


	cout << "Comienzo deserializado de Cargo" << endl;
	cargo2->deserializar(source);
	cout << "Fin deserializado de Cargo" << endl;
	cout << endl;
	cout<<"Size blabla: "<<cargo2->devolverSubCargos().size()<<endl;
	cout << "Cargo 2: " << cargo2->getCargo() <<endl;
	listas2 = cargo2->devolverSubCargos();
	list<string>::iterator it2 = listas2.begin();
	cout << "Size lista 2: "<< listas2.size()<<endl;
	while (it2 != listas2.end()){
		cout << "SubCargo: "<< (*it2) <<endl;
		it2++;
	}
	delete cargo1;
	delete cargo2;
	return 0;
}

void Pruebas::serializarDeserializarVotante(){
	Votante* votante1 = new Votante (32299496,"Daniel Shlufman","32299496","San Juan 124","Recoleta");
	votante1->agregarEleccion("271011","Presidente");
	votante1->agregarEleccion("100297","Gobernador");
	votante1->agregarEleccion("221199","Intendente");
	votante1->agregarEleccion("160500","Diputado Nacional");
	votante1->agregarEleccion("190603","Diputado Provincial");
	votante1->agregarEleccion("040705","Senador");
	votante1->agregarEleccion("040705","Jefe De Comuna");
	cout << endl;
	cout << "Comienzo de serializado de Votante" << endl;
	string* datos = votante1->serializar();
	cout << "Fin de serializado de Votante" << endl;
	cout << endl;
	cout << "Comienzo de deserializado de Votante" << endl;
	votante1->deserializar(datos);
	cout << "Fin de deserializado de Votante" << endl;
	cout << endl;
	votante1->verVotante();
	delete votante1;
}

void Pruebas::serializarDeserializarDistrito(){
	Distrito* unDistrito = new Distrito ("Puerto Esperanza");
	cout << endl;
	cout << "Comienzo de serializado de Distrito" << endl;
	string* datos = unDistrito->serializar();
	cout << "Fin de serializado de Distrito" << endl;
	cout << endl;
	cout << "Comienzo de deserializado de Distrito" << endl;
	unDistrito->deserializar(datos);
	cout << "Fin de deserializado de Distrito" << endl;
	cout << "Distrito: " << unDistrito->getDistrito() << endl;
	delete unDistrito;
	cout << endl;
}

void Pruebas::serializarDeserializarLista() {
//	Probar incrementar el voto.
	Lista* unaLista = new Lista ("Lista 7","040795","Jefe De Comuna");
	cout << endl;
	cout << "Comienzo de serializado de Lista" << endl;
	string* datos = unaLista->serializar();
	cout << "Fin de serializado de Lista" << endl;
	cout << endl;
	cout << "Comienzo de deserializado de Lista" << endl;
	unaLista->deserializar(datos);
	cout << "Fin de deserializado de Lista" << endl;
	cout << endl;
	cout << "Lista: " << unaLista->getNombre() << endl;
	cout << "Fecha de eleccion: " << unaLista->getFecha() << endl;
	cout << "Cargo: " << unaLista->getCargo() << endl;
	cout << "Votos: " << unaLista->getCantidadDeVotos() << endl;
	delete unaLista;
}

void Pruebas::serializarDeserializarCandidato(){
	Candidato* unCandidato = new Candidato ("040795","Jefe De Comuna","Osvaldo Basan",11554234);
	cout << endl;
	cout << "Comienzo de serializado de Candidato" << endl;
	string* datos = unCandidato->serializar();
	cout << "Fin de serializado de Candidato" << endl;
	cout << endl;
	cout << "Comienzo de deserializado de Candidato" << endl;
	unCandidato->deserializar(datos);
	cout << "Fin de deserializado de Candidato" << endl;
	cout << endl;
	unCandidato->verCandidato();
	delete unCandidato;
}

void Pruebas::serializarDeserializarEleccion(){
	Eleccion* unaEleccion = new Eleccion ("040795","Jefe De Comuna");
	cout << endl;
	cout << "Comienzo de serializado de Eleccion" << endl;
	string* datos = unaEleccion->serializar();
	cout << "Fin de serializado de Eleccion" << endl;
	cout << endl;
	cout << "Comienzo de deserializado de Eleccion" << endl;
	unaEleccion->deserializar(datos);
	cout << "Fin de deserializado de Eleccion" << endl;
	cout << endl;
	cout << "Fecha de eleccion: " << unaEleccion->getFecha() << endl;
	cout << "Cargo Principal: "   << unaEleccion->getCargo() << endl;
	cout << "Distritos: " << endl;
	cout << "----------"  << endl;
	list <Distrito> listaDeDistritos = unaEleccion->getLista();
	list <Distrito>::iterator it = listaDeDistritos.begin();
	while (it!=listaDeDistritos.end()) {
		cout << (*it).getDistrito() << endl;
		it++;
	}
	delete unaEleccion;
}

int Pruebas::holaMundo(){

    cout<<"||TP 1||\n--------\n\nHola Mundo!!!\n";
    // int i; for (i=0;i<argc;i++){ cout<<"\nParámetro ["<<i<<"]: "<<argv[i];  }
    cout<<"\n\nBueno, chau...\n";
    return 0;
}
