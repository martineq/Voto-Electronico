#include "Pruebas.h"

Pruebas::Pruebas() {

}


Pruebas::~Pruebas() {
	delete (bucket);
}

void Pruebas::serializarDeserializarRegistro(){
	Distrito* d = new Distrito("Buenos Aires");
	Registro* r = new Registro(d->getNombreDeEntidad());
	r->setContenido(d);
	string registroSerializado = *(r->serializar());
	//delete (r);

	Registro* r2 = new Registro(registroSerializado);
	Distrito* d2 = (Distrito*)r2->getContenido();
	std::cout << d2->getDistrito() << std::endl;
	delete(r2);
}

void Pruebas::iniciarRegistrosDistrito(){
	this->distrito1 = new Distrito("Puerto Esperanza");
	this->distrito2 = new Distrito("Buenos Aires");
	this->distrito3 = new Distrito("Montecarlo");
	this->distrito4 = new Distrito("Eldorado");
	this->registro1 = new Registro(distrito1);
	this->registro2 = new Registro(distrito2);
	this->registro3 = new Registro(distrito3);
	this->registro4 = new Registro(distrito4);
	this->bucket = new Bucket(0);
	cout << "El espacio libre es: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	this->bucket->agregarRegistro(registro1);
	this->bucket->agregarRegistro(registro2);
	this->bucket->agregarRegistro(registro3);
	this->bucket->agregarRegistro(registro4);
}

void Pruebas::verContenidoBucketDistrito(){
	if (this->bucket->getCantidadDeRegistros()==0) cout << "BUCKET VACIO" << endl;
	else{
		cout << "Los registros cargados son:" << endl;
		list<Registro*>::iterator it = this->bucket->ubicarPrimero();
		int n = bucket->getCantidadDeRegistros();
		cout <<"El valor de N es: " << n << endl;
		for(int i = 0; i <n;i++ ){
			Registro* unRegistro = *it;
			Distrito* unDistrito = (Distrito*)unRegistro->getContenido();
			cout << "Distrito: " << unDistrito->getDistrito() << endl;
			it++;
		}
		cout << endl;
	}
}

void Pruebas::verContenidoBucketVotante(){
	if (this->bucket->getCantidadDeRegistros()==0) cout << "BUCKET VACIO" << endl;
	else{
		cout << "Los registros cargados son:" << endl;
		list<Registro*>::iterator it = this->bucket->ubicarPrimero();
		int n = bucket->getCantidadDeRegistros();
		for(int i = 0; i <n;i++ ){
			Registro* unRegistro = *it;
			Votante*  unVotante  = (Votante*)unRegistro->getContenido();
			unVotante->verVotante();
			it++;
		}
		cout << endl;
	}
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
	this->verContenidoBucketDistrito();
	cout << "Iniciando prueba agregar un registro sin espacio libre" << endl;
	cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	Distrito* distrito5 = new Distrito("Obera");
	Registro* registro5 = new Registro(distrito5);
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
	this->verContenidoBucketDistrito();
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
	Registro* registro6 = new Registro(distrito6);
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
	delete this->distrito1;
	delete this->distrito2;
	delete this->distrito3;
	delete this->distrito4;
	delete this->registro1;
	delete this->registro2;
	delete this->registro3;
	delete this->registro4;
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
	this->verContenidoBucketDistrito();
//	elimino el primer registro
	list<Registro*>::iterator it = this->bucket->ubicarPrimero();
	int clave = (*it)->obtenerClave();
	cout << "Eliminando el primer registro" << endl;
	if (this->bucket->eliminarRegistro(clave)) {
		cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
		cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
		this->verContenidoBucketDistrito();
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
	Registro* registro5 = new Registro (distrito5);
	clave = registro5->obtenerClave();
	if (!this->bucket->eliminarRegistro(clave)) {
		cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
		cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
		this->verContenidoBucketDistrito();
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
		this->verContenidoBucketDistrito();
		cout << "prueba OK" << endl;
	}
	else cout << "ERROR" << endl;
	cout << "Estas fueron todas las pruebas de eliminar registros del bucket" << endl;
	cout << "Gracias! Hasta luego" << endl;
	delete (distrito5);
	delete (registro5);
	delete this->distrito1;
	delete this->distrito2;
	delete this->distrito3;
	delete this->distrito4;
	delete this->registro1;
	delete this->registro2;
	delete this->registro3;
	delete this->registro4;
}

void Pruebas::pruebaReemplazarRegistroEnBucket() {
	//TODO
	cout << endl;
	cout << "Bienvenido a las pruebas de actualizacion de registros en un bucket" << endl;
	cout << "Observe y disfrute" << endl;
	Votante* votante1 = new Votante (1,"Daniel","","","");//40bytes
	Votante* votante2 = new Votante (2,"A","","","");//30bytes
	this->registro1 = new Registro (votante1);
	this->registro2 = new Registro (votante2);
	bucket = new Bucket (0);
	this->bucket->agregarRegistro(registro1);
	this->bucket->agregarRegistro(registro2);
	this->verContenidoBucketVotante();
	cout << "Se intentará reemplazar Daniel por Martin" << endl;
	cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
	cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	cout << "Inicio de reemplazo" << endl;
	Votante* votante3 = new Votante (1,"Martin","","","");//40bytes
	this->registro3 = new Registro (votante3);
	if (this->bucket->reemplazarRegistro(registro3)){
		cout << "Fin de reemplazo" << endl;
		cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
		cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
		this->verContenidoBucketVotante();
		cout << "Prueba OK" << endl;
	}
	else cout << "ERROR" << endl;
	cout << "Se intentara reemplazar un registro que no entre en el bucket" << endl;
	cout << "Se intentara reemplazar el registro A con el registro Gonzalo" << endl;
	Votante* votante4 = new Votante (2,"Gonzalo","","","");//42bytes
	this->registro4 = new Registro (votante4);
	cout << "Tamanio de registro A= " << this->registro2->getTamanio() << endl;
	cout << "Tamanio de registro Gonzalo= " << this->registro4->getTamanio() << endl;
	cout << "Inicio de reemplazo" << endl;
	if (!bucket->reemplazarRegistro(registro4)) {
		cout << "Fin de reemplazo" << endl;
		cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
		cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
		this->verContenidoBucketVotante();
		cout << "Prueba OK" << endl;
	}
	else cout << "ERROR" << endl;
	cout << "Se intentara un reemplazo con bucket vacio" << endl;
	this->bucket->eliminarRegistro(2);
	this->bucket->eliminarRegistro(1);
	cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
	cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	cout << "Inicio de reemplazo" << endl;
	if (!bucket->reemplazarRegistro(registro4)) {
		cout << "Fin de reemplazo" << endl;
		cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
		cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
		this->verContenidoBucketVotante();
		cout << "Prueba OK" << endl;
	}
	else cout << "ERROR" << endl;
	cout << endl;
	cout << "Se intentara reemplazar un registro con clave inexistente" << endl;
	Votante* votante5 = new Votante (3,"Celeste","","","");
	Registro* registro5 = new Registro (votante5);
	this->bucket->agregarRegistro(registro2);
	this->verContenidoBucketVotante();
	cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
	cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	cout << "Tamanio del registro a ingresar: " << this->registro3->getTamanio() << endl;
	cout << "De esta forma me aseguro que la prueba falle porque no esta el registro y no por espacio" << endl;
	cout << "Inicio de reemplazo" << endl;
	if (!bucket->reemplazarRegistro(registro5)) {
		cout << "Fin de reemplazo" << endl;
		cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
		cout << "Espacio libre: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
		this->verContenidoBucketVotante();
		cout << "Prueba OK" << endl;
	}
	else cout << "ERROR" << endl;
	delete votante1;
	delete votante2;
	delete votante3;
	delete votante4;
	delete votante5;
	delete this->registro1;
	delete this->registro2;
	delete this->registro3;
	delete this->registro4;
	delete registro5;
	cout << "Estas fueron todas las pruebas de actualizacion de registros de un bucket" << endl;
	cout << "Gracias! Hasta luego" << endl;
}


void Pruebas::serializarDeserializarBucket(){
	cout << endl;
	cout << "Bienvenido a las pruebas de serializacion y deserializacion de un bucket" << endl;
	cout << "Observe y disfrute" << endl;
	cout << "Iniciando la carga del bucket" << endl;
	this->iniciarRegistrosDistrito();
	cout << "Carga finalizada" << endl;
	cout << "El espacio libre es: " << this->bucket->getEspacioLibre() << " Bytes" << endl;
	cout << "cantidad de registros en Bucket: " << this->bucket->getCantidadDeRegistros() << endl;
	this->verContenidoBucketDistrito();
	cout << "Inicio serializado de bucket" << endl;
	string* bucketSerializado = this->bucket->serializar();
//	Pruebo si serializo bien
	stringstream stream1(bucketSerializado->substr(0,3));
	int espacioLibre = stream1.get();
	if (espacioLibre==8) cout << "Serializado del espacio libre OK" << endl;
	else cout << "Serializado del espacio libre ERROR" << endl;

	stringstream stream2(bucketSerializado->substr(4,7));
	int tamanioDeDispersion = stream2.get();
	if (tamanioDeDispersion==0) cout << "Serializado del tamanio De Dispersion OK" << endl;
	else cout << "Serializado del tamanio De Dispersion ERROR" << endl;

	stringstream stream3(bucketSerializado->substr(8,11));
	int cantidadDeRegistros = stream3.get();
	if (cantidadDeRegistros==4) cout << "Serializado del cantidad De Registros OK" << endl;
	else cout << "Serializado del cantidad De Registros ERROR" << endl;

	stringstream stream4(bucketSerializado->substr(12,15));
	int tamanioDeRegistro = stream4.get();
	if (tamanioDeRegistro==20) cout << "Serializado del tamanio De Registro1 OK" << endl;
	else cout << "Serializado del tamanio De Registro1 ERROR" << endl;

	cout << "Fin serializado de bucket" << endl;
	cout << "Inicio deserializado de bucket" << endl;
	this->bucket->deserializar(bucketSerializado);
	cout << "Fin deserializado de bucket" << endl;
	cout << "Si la serializacion fue correcta y la deserializacion tambien entonces usted debera ver los registros cargados inicialmente" << endl;
	this->verContenidoBucketDistrito();
	cout << "Estas fueron todas las pruebas de serializacion y deserializacion de un bucket" << endl;
	cout << "Gracias! Hasta luego" << endl;
	delete this->distrito1;
	delete this->distrito2;
	delete this->distrito3;
	delete this->distrito4;
	delete this->registro1;
	delete this->registro2;
	delete this->registro3;
	delete this->registro4;
}

void Pruebas::pruebaAgregarRegistrosHashingExtensible(){
	this->iniciarRegistrosDistrito();
	ArchivoDeBuckets* archivo = new ArchivoDeBuckets();
	HashingExtensible* he = new HashingExtensible(archivo);
	he->agregarRegistro(this->registro1);
	he->agregarRegistro(this->registro2);
	he->agregarRegistro(this->registro3);
	he->agregarRegistro(this->registro4);
	this->bucket = he->obtenerBucket(0);
	cout << "cantidad de registrosen Bucket: " << bucket->getCantidadDeRegistros() << endl;
	list<Registro*>::iterator it = this->bucket->ubicarPrimero();
	int n = this->bucket->getCantidadDeRegistros();
	for(int i = 0; i <n;i++ ){
		Registro* unRegistro = *it;
		Distrito* unDistrito = (Distrito*)unRegistro->getContenido();
		cout << "Distrito: " << unDistrito->getDistrito() << endl;
		it++;
	}

	delete(archivo);
	delete(he);
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