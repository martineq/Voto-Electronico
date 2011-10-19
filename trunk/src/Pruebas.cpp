#include "Pruebas.h"

Pruebas::Pruebas() {
}

Pruebas::~Pruebas() {
//	delete this->heVotante;
	delete this->heDistrito;
	delete this->heEleccion;
	delete this->heCandidato;
//	delete this->heLista;
	delete this->heCargo;
	remove ("archivoDeControlVotante.txt");
	remove ("archivoDeDatosVotante.txt");
	remove ("archivoDeControlDistrito.txt");
	remove ("archivoDeDatosDistrito.txt");
	remove ("archivoDeControlEleccion.txt");
	remove ("archivoDeDatosEleccion.txt");
	remove ("archivoDeControlCandidato.txt");
	remove ("archivoDeDatosCandidato.txt");
//	remove ("archivoDeControlLista.txt");
//	remove ("archivoDeDatosLista.txt");
	remove ("archivoDeControlCargo.txt");
	remove ("archivoDeDatosCargo.txt");
}

void Pruebas::iniciarRegistrosDePrueba(){
	this->distrito1 = new Distrito("Puerto Esperanza");
	this->distrito2 = new Distrito("Buenos Aires");
	this->distrito3 = new Distrito("Montecarlo");
	this->distrito4 = new Distrito("Eldorado");
	this->registroDistrito1 = new Registro(distrito1);
	this->registroDistrito2 = new Registro(distrito2);
	this->registroDistrito3 = new Registro(distrito3);
	this->registroDistrito4 = new Registro(distrito4);
	delete this->distrito1;
	delete this->distrito2;
	delete this->distrito3;
	delete this->distrito4;

	this->bucketVotante = new Bucket(0,128);
	cout << "El espacio libre es: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
	this->bucketDistrito->agregarRegistro(registroDistrito1);
	this->bucketDistrito->agregarRegistro(registroDistrito2);
	this->bucketDistrito->agregarRegistro(registroDistrito3);
	this->bucketDistrito->agregarRegistro(registroDistrito4);
}

void Pruebas::iniciarRegistrosDistrito(){

	Bucket* bucket = new Bucket(0,128);
	string distritos[] = {"Buenos Aires","Puerto Esperanza","Montecarlo","Eldorado"};

	for (int i=0; i < 4 ;i++){
		Distrito* distrito = new Distrito(distritos[i]);
		Registro* registro = new Registro(distrito);
		delete(distrito);

		bucket->agregarRegistro(registro);
		delete(registro);
	}

}

void Pruebas::pruebaAgregarRegistrosAlBucket(){
//	cout << endl;
//	cout << "Bienvenido a las pruebas de agregar registros a un bucket" << endl;
//	cout << "Observe y disfrute" << endl;
//	cout << "Iniciando prueba carga de cero" << endl;
//	this->iniciarRegistrosDePrueba();
//	cout << "Carga finalizada" << endl;
//	cout << "El espacio libre es: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//	cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//	if (bucketVotante->getCantidadDeRegistros()==4) cout << "Prueba OK" << endl;
//	else cout << "ERROR" << endl;
//	this->verContenidoBucketDistrito(this->bucketDistrito);
//	cout << "Iniciando prueba agregar un registro sin espacio libre" << endl;
//	cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//	Distrito* distrito5 = new Distrito("Obera");
//	Registro* registro5 = new Registro(distrito5);
//	cout << "Intentando carga de registro" << endl;
//	if (!this->bucketVotante->agregarRegistro(registro5)) {
//		cout << "No se pudo cargar el registro" << endl;
//		cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//		cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//		cout << "Prueba OK" << endl;
//	}
//	else cout << "ERROR" << endl;
//	cout << endl;
//	cout << "Iniciando prueba carga de registro luego de eliminar registros" << endl;
//	cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//	list<Registro*>::iterator it = this->bucketVotante->ubicarPrimero();
//	int clave = (*it)->obtenerClave();
//	cout << "Eliminando el primer registro" << endl;
//	this->bucketVotante->eliminarRegistro(clave);
//	cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//	cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//	cout << "El tamaño del registro nuevo es: " << registro5->getTamanio() << endl;
//	cout << "Intentando carga del registro" << endl;
//	if (this->bucketVotante->agregarRegistro(registro5)) {
//		cout << "El registro fue cargado" << endl;
//		cout << "Se elimino el primer registro Puerto Esperanza y se agrego Obera" << endl;
//		cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//		cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//		cout << "Prueba OK" << endl;
//	}
//	else cout << "ERROR" << endl;
//	this->verContenidoBucketDistrito(this->bucketDistrito);
//	cout << endl;
//	cout << "Iniciando prueba carga de registro con clave ya existente" << endl;
//	cout << "Se intenta agregar el registro Eldorado ya existente" << endl;
//	cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//	it = this->bucketVotante->ubicarPrimero();
//	clave = (*it)->obtenerClave();
//	this->bucketVotante->eliminarRegistro(clave);
//	it = this->bucketVotante->ubicarPrimero();
//	clave = (*it)->obtenerClave();
//	this->bucketVotante->eliminarRegistro(clave);
//	cout << "Se hizo espacio para el nuevo registro Eldorado" << endl;
//	cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//	Distrito* distrito6 = new Distrito("Eldorado");
//	Registro* registro6 = new Registro(distrito6);
//	cout << "Se intenta la carga del registro duplicado" << endl;
//	if (!this->bucketVotante->agregarRegistro(registro6)) {
//		cout << "El registro no fue cargado" << endl;
//		cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//		cout << "La prueba es exitosa porque el registro esta duplicado y no por no tener espacio" << endl;
//		cout << "Prueba OK" << endl;
//	}
//	else cout << "ERROR" << endl;
//	this->verContenidoBucketDistrito(this->bucketDistrito);
//	cout << endl;
//	cout << "Estas fueron todas las pruebas de agregar registros al bucket" << endl;
//	cout << "Gracias! Hasta luego" << endl;
//	delete distrito5;
//	delete registro5;
//	delete distrito6;
//	delete registro6;
//	delete this->registroDistrito1;
//	delete this->registroDistrito2;
//	delete this->registroDistrito3;
//	delete this->registroDistrito4;
}

void Pruebas::pruebaEliminarRegistrosDelBucket(){
//	cout << endl;
//	cout << "Bienvenido a las pruebas de eliminacion de registros en un bucket" << endl;
//	cout << "Observe y disfrute" << endl;
//	cout << "Prueba eliminar un registro con bucket vacio" << endl;
//	cout << "Intentando eliminar un registro" << endl;
//	Bucket* unBucket = new Bucket (0,128);
////	if (!unBucket->eliminarRegistro(8)) cout << "Prueba OK" << endl;
//	else cout << "ERROR" << endl;
//	delete unBucket;
//	cout << "Prueba eliminar el primer registro" << endl;
//	this->iniciarRegistrosDePrueba();
//	cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//	cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//	this->verContenidoBucketDistrito(this->bucketDistrito);
////	elimino el primer registro
//	list<Registro*>::iterator it = this->bucketVotante->ubicarPrimero();
//	int clave = (*it)->obtenerClave();
//	cout << "Eliminando el primer registro" << endl;
////	if (this->bucketVotante->eliminarRegistro(clave)) {
//		cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//		cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//		this->verContenidoBucketDistrito(this->bucketDistrito);
//		cout << "prueba OK" << endl;
//	}
//	else cout << "ERROR" << endl;
//	cout << endl;
//	cout << "Prueba eliminar un registro inexistente" << endl;
//	cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//	cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//	cout << "Intento de eliminar Resistencia" << endl;
//	it = this->bucketVotante->ubicarPrimero();
//	Distrito* distrito5 = new Distrito ("Resistencia");
//	Registro* registro5 = new Registro (distrito5);
//	clave = registro5->obtenerClave();
////	if (!this->bucketVotante->eliminarRegistro(clave)) {
//		cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//		cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//		this->verContenidoBucketDistrito(this->bucketDistrito);
//		cout << "prueba OK" << endl;
//	}
//	else cout << "ERROR" << endl;
//	cout << "Prueba eliminar un registro intermedio" << endl;
//	cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//	cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//	clave = this->registroDistrito3->obtenerClave();
//	cout << "intento eliminar Montecarlo" << endl;
//	if (this->bucketVotante->eliminarRegistro(clave)) {
//		cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//		cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//		this->verContenidoBucketDistrito(this->bucketDistrito);
//		cout << "prueba OK" << endl;
//	}
//	else cout << "ERROR" << endl;
//	cout << "Estas fueron todas las pruebas de eliminar registros del bucket" << endl;
//	cout << "Gracias! Hasta luego" << endl;
//	delete (distrito5);
//	delete (registro5);
//	delete this->registroDistrito1;
//	delete this->registroDistrito2;
//	delete this->registroDistrito3;
//	delete this->registroDistrito4;
}

void Pruebas::pruebaReemplazarRegistroEnBucket() {
//	//TODO
//	cout << endl;
//	cout << "Bienvenido a las pruebas de actualizacion de registros en un bucket" << endl;
//	cout << "Observe y disfrute" << endl;
//	this->votante1 = new Votante (1,"Daniel","","","");
//	this->votante2 = new Votante (2,"A","","","");
//	this->registroVotante1 = new Registro (votante1);
//	this->registroVotante2 = new Registro (votante2);
//	bucketVotante = new Bucket (0,128);
//	this->bucketVotante->agregarRegistro(registroVotante1);
//	this->bucketVotante->agregarRegistro(registroVotante2);
//	this->verContenidoBucketVotante(this->bucketVotante);
//	cout << "Se intentará reemplazar Daniel por Martin" << endl;
//	cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//	cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//	cout << "Inicio de reemplazo" << endl;
//	this->votante3 = new Votante (1,"Martin","","","");
//	this->registroVotante3 = new Registro (votante3);
//	if (this->bucketVotante->reemplazarRegistro(registroVotante3)){
//		cout << "Fin de reemplazo" << endl;
//		cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//		cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//		this->verContenidoBucketVotante(this->bucketVotante);
//		cout << "Prueba OK" << endl;
//	}
//	else cout << "ERROR" << endl;
//	cout << "Se intentara reemplazar un registro que no entre en el bucket" << endl;
//	cout << "Se intentara reemplazar el registro A con el registro Gonzalo" << endl;
//	this->votante4 = new Votante (2,"Gonzalo","","","");
//	this->registroVotante4 = new Registro (votante4);
//	cout << "Tamanio de registro A= " << this->registroVotante2->getTamanio() << endl;
//	cout << "Tamanio de registro Gonzalo= " << this->registroVotante4->getTamanio() << endl;
//	cout << "Inicio de reemplazo" << endl;
//	if (!bucketVotante->reemplazarRegistro(registroVotante4)) {
//		cout << "Fin de reemplazo" << endl;
//		cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//		cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//		this->verContenidoBucketVotante(this->bucketVotante);
//		cout << "Prueba OK" << endl;
//	}
//	else cout << "ERROR" << endl;
//	cout << "Se intentara un reemplazo con bucket vacio" << endl;
//	this->bucketVotante->eliminarRegistro(2);
//	this->bucketVotante->eliminarRegistro(1);
//	cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//	cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//	cout << "Inicio de reemplazo" << endl;
//	if (!bucketVotante->reemplazarRegistro(registroVotante4)) {
//		cout << "Fin de reemplazo" << endl;
//		cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//		cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//		this->verContenidoBucketVotante(this->bucketVotante);
//		cout << "Prueba OK" << endl;
//	}
//	else cout << "ERROR" << endl;
//	cout << endl;
//	cout << "Se intentara reemplazar un registro con clave inexistente" << endl;
//	Votante* votante5 = new Votante (3,"Celeste","","","");
//	Registro* registro5 = new Registro (votante5);
//	this->bucketVotante->agregarRegistro(registroVotante2);
//	this->verContenidoBucketVotante(this->bucketVotante);
//	cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//	cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//	cout << "Tamanio del registro a ingresar: " << this->registroVotante3->getTamanio() << endl;
//	cout << "De esta forma me aseguro que la prueba falle porque no esta el registro y no por espacio" << endl;
//	cout << "Inicio de reemplazo" << endl;
//	if (!bucketVotante->reemplazarRegistro(registro5)) {
//		cout << "Fin de reemplazo" << endl;
//		cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
//		cout << "Espacio libre: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
//		this->verContenidoBucketVotante(this->bucketVotante);
//		cout << "Prueba OK" << endl;
//	}
//	else cout << "ERROR" << endl;
//	cout << "Estas fueron todas las pruebas de actualizacion de registros de un bucket" << endl;
//	cout << "Gracias! Hasta luego" << endl;
//	delete this->votante1;
//	delete this->votante2;
//	delete this->votante3;
//	delete this->votante4;
//	delete votante5;
//	delete this->registroVotante1;
//	delete this->registroVotante2;
//	delete this->registroVotante3;
//	delete this->registroVotante4;
//	delete registro5;

}


void Pruebas::serializarDeserializarBucket(){
	cout << endl;
	cout << "Bienvenido a las pruebas de serializacion y deserializacion de un bucket" << endl;
	cout << "Observe y disfrute" << endl;
	cout << "Iniciando la carga del bucket" << endl;
	this->iniciarRegistrosDePrueba();
	cout << "Carga finalizada" << endl;
	cout << "El espacio libre es: " << this->bucketVotante->getEspacioLibre() << " Bytes" << endl;
	cout << "cantidad de registros en Bucket: " << this->bucketVotante->getCantidadDeRegistros() << endl;
	this->verContenidoBucketDistrito(this->bucketDistrito);
	cout << "Inicio serializado de bucket" << endl;
	string* bucketSerializado = this->bucketVotante->serializar();

//	===================================================================================
//	Pruebo si serializo bien
//	===================================================================================

	stringstream stream1(bucketSerializado->substr(0,3));
	int espacioLibre = stream1.get();
	if (espacioLibre==6) cout << "Serializado del espacio libre OK" << endl;
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
	if (tamanioDeRegistro==28) cout << "Serializado del tamanio De Registro1 OK" << endl;
	else cout << "Serializado del tamanio De Registro ERROR" << endl;

	cout << "Fin serializado de bucket" << endl;
	cout << "Inicio deserializado de bucket" << endl;

	delete (this->bucketVotante);
	this->bucketVotante = new Bucket(0,128);
	this->bucketVotante->deserializar(bucketSerializado);
	delete bucketSerializado;
	cout << "Fin deserializado de bucket" << endl;
	cout << "Si la serializacion fue correcta y la deserializacion tambien entonces usted debera ver los registros cargados inicialmente" << endl;
	this->verContenidoBucketDistrito(this->bucketDistrito);
	cout << "Estas fueron todas las pruebas de serializacion y deserializacion de un bucket" << endl;
	cout << "Gracias! Hasta luego" << endl;
	delete this->registroDistrito1;
	delete this->registroDistrito2;
	delete this->registroDistrito3;
	delete this->registroDistrito4;
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
	delete votante1;
	votante1 = new Votante ();
	cout << "Fin de serializado de Votante" << endl;
	cout << endl;
	cout << "Comienzo de deserializado de Votante" << endl;
	votante1->deserializar(datos);
	delete datos;
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
	delete datos;
	cout << "Fin de deserializado de Distrito" << endl;
	cout << "Distrito: " << unDistrito->getDistrito() << endl;
	delete unDistrito;
	cout << endl;
}

void Pruebas::serializarDeserializarLista() {
//	Probar incrementar el voto.
	Lista* unaLista = new Lista ("Lista 7","04071995","Jefe De Comuna");
	cout << endl;
	cout << "Comienzo de serializado de Lista" << endl;
	string* datos = unaLista->serializar();
	cout << "Fin de serializado de Lista" << endl;
	cout << endl;
	cout << "Comienzo de deserializado de Lista" << endl;
	unaLista->deserializar(datos);
	delete datos;
	cout << "Fin de deserializado de Lista" << endl;
	cout << endl;
	cout << "Lista: " << unaLista->getNombre() << endl;
	cout << "Fecha de eleccion: " << unaLista->getFecha() << endl;
	cout << "Cargo: " << unaLista->getCargo() << endl;
//	cout << "Votos: " << unaLista->getCantidadDeVotos() << endl;
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
	delete datos;
	cout << "Fin de deserializado de Eleccion" << endl;
	cout << endl;
	cout << "Fecha de eleccion: " << unaEleccion->getFecha() << endl;
	cout << "Cargo Principal: "   << unaEleccion->getCargo() << endl;
	cout << "Distritos: " << endl;
	cout << "----------"  << endl;
	list <Distrito> listaDeDistritos = unaEleccion->getLista();
	if (listaDeDistritos.size()==0) cout << "lista de distritos vacia" << endl;
	else {
		list <Distrito>::iterator it = listaDeDistritos.begin();
		while (it!=listaDeDistritos.end()) {
			cout << (*it).getDistrito() << endl;
			it++;
		}
	}
	delete unaEleccion;
}

void Pruebas::pruebaArchivoBloques(){
	string nombre ("ArchivoBloques.bin");
	string dat1 ("0123456789ABCDEF");
	string dat2 ("Datos Locos");
	string dat3 ("Soy Elvis El Rey");

	int tamanioDeBloque = 52;
	char* buf = new char[tamanioDeBloque];	// Mi bloque, instanciado en memoria, como si fuera un nodo, bucket, etc.-
	int nrr1,nrr2,nrr3,nrr4;
	nrr1=nrr2=nrr3=nrr4=99;
	ArchivoBloques *arch = new ArchivoBloques((char*)nombre.c_str(),tamanioDeBloque);

	arch->crearNuevoBloque(&nrr1);
	cout << "Los NRR's son: "<< nrr1<<", "<<nrr2<<", " << nrr3 <<endl;
	arch->crearNuevoBloque(&nrr2);
	cout << "Los NRR's son: "<< nrr1<<", "<<nrr2<<", " << nrr3 <<endl;
	arch->crearNuevoBloque(&nrr3);
	cout << "Los NRR's son: "<< nrr1<<", "<<nrr2<<", " << nrr3 <<endl;

	cout << "Pido el bloque del nrr: "<< nrr1 <<endl;
	arch->obtenerBloque(nrr1,buf);
	strcpy(buf,dat1.c_str());
	cout << "Guardo el dato: '"<< buf <<"' en el nrr: "<< nrr1 <<endl;
	arch->guardarBloque(nrr1,buf);
	cout << "Pido el bloque del nrr: "<< nrr2 <<endl;
	arch->obtenerBloque(nrr2,buf);
	strcpy(buf,dat2.c_str());
	cout << "Guardo el dato: '"<< buf <<"' en el nrr: "<< nrr2 <<endl;
	arch->guardarBloque(nrr2,buf);
	cout << "Pido el bloque del nrr: "<< nrr3 <<endl;
	arch->obtenerBloque(nrr3,buf);
	strcpy(buf,dat3.c_str());
	cout << "Guardo el dato: '"<< buf <<"' en el nrr: "<< nrr3 <<endl;
	arch->guardarBloque(nrr3,buf);

	cout << "Pido el bloque del nrr: "<< nrr1 <<endl;
	arch->obtenerBloque(nrr1,buf);
	cout << "El bloque tiene: "<< buf <<endl;
	cout << "Pido el bloque del nrr: "<< nrr2 <<endl;
	arch->obtenerBloque(nrr2,buf);
	cout << "El bloque tiene: "<< buf <<endl;
	cout << "Pido el bloque del nrr: "<< nrr3 <<endl;
	arch->obtenerBloque(nrr3,buf);
	cout << "El bloque tiene: "<< buf <<endl;

	cout << "Borro el bloque del nrr: "<< nrr1 <<endl;
	arch->borrarBloque(nrr1);
	arch->borrarBloque(nrr2);
	arch->borrarBloque(nrr3);

	cout << "Pido un bloque nuevo... "<<endl;
	arch->crearNuevoBloque(&nrr4);
	cout << "El bloque del nrr4 es: "<< nrr4 <<endl;
	cout << "Pido un bloque nuevo... "<<endl;
	arch->crearNuevoBloque(&nrr4);
	cout << "El bloque del nrr5 es: "<< nrr4 <<endl;
	cout << "Pido un bloque nuevo... "<<endl;
	arch->crearNuevoBloque(&nrr4);
	cout << "El bloque del nrr6 es: "<< nrr4 <<endl;
	cout << "Pido un bloque nuevo... "<<endl;
	arch->crearNuevoBloque(&nrr4);
	cout << "El bloque del nrr7 es: "<< nrr4 <<endl;
	cout << "Pido un bloque nuevo... "<<endl;
	arch->crearNuevoBloque(&nrr4);
	cout << "El bloque del nrr8 es: "<< nrr4 <<endl;
	cout << "Pido un bloque nuevo... "<<endl;
	arch->crearNuevoBloque(&nrr4);
	cout << "El bloque del nrr9 es: "<< nrr4 <<endl;

	arch->infoInts();
	delete[] buf;
	delete arch;
	cout << "\n------------\nSe acabó =D"<< endl;
}


void Pruebas::SerializarGuardarEnBloqueHidratar(){

	int dato1 = 99999;
	int dato2 = 88888;
	string dato3 = "Cadenita de text";
	string nombre ("BloqueSerializado.bin");
	stringstream buffer,stream;
	int leido1,leido2;
	string leido3;

	cout << "Datos A Serializar: "<<dato1<<" (int), " << dato2<<" (int), "<<dato3<<" (string)"<< endl;

//	Escribo en el StringStream
	buffer.write((char*)&dato1,sizeof(int));
	buffer.write((char*)&dato2,sizeof(int));
	buffer.write(dato3.c_str(),dato3.size());

//	Preparo el char* para guardarlo en un bloque
	string datos2( buffer.str() );
	char* cad = new char[datos2.size()];
	memcpy(cad,datos2.c_str(),datos2.size());
	cout << "Datos Serializados."<<endl;

//  Archivo en bloques: Guardo los datos.
	ArchivoBloques *arch = new ArchivoBloques((char*)nombre.c_str(),datos2.size());
	int nrr1;
	arch->crearNuevoBloque(&nrr1);
	arch->guardarBloque(nrr1,cad);
	delete[] cad;
	cout << "Datos guardados en disco."<<endl;

//  Archivo en bloques: Leo los datos.
	char* buf = new char[datos2.size()];
	arch->obtenerBloque(nrr1,buf);
	delete arch;
	cout << "Datos leidos disco."<<endl;

//	Escribo toda la cadena recuperada en un StringStream
	stream.write(buf,datos2.size());
	delete[] buf;
	string s = stream.str();
	cout <<"Datos Hidratados. Tamaño total hidratado: " <<s.size() << endl;

//	Leo de a uno las datos
	stream.read((char*)&leido1,sizeof(int));
	stream.read((char*)&leido2,sizeof(int));
	leido3 = (stream.str()).substr(8,19);

	cout << "Datos Hidratado: "<< leido1 << " (int), " << leido2 << " (int), " << leido3<<" (string)" << endl;
	cout << "\n------------\nSe acabó =D"<< endl;
}


void Pruebas::pruebaBMas(){

	 vector<char> v;
	 vector<char> tmp;
	 std::pair<vector<char>,std::string> gn;
	 bplustree b;
	 b.newtree("test",60);
	 v.push_back(1);
	 b.add("deloitte",v);
	 v.push_back(2);
	 b.add("nacho",v);
	 v.push_back(5);
	 b.add("this",v);
	 v.push_back(4);
	 b.add("vb",v);
	 v.push_back(5);
	 b.add("mama",v);
	 v.push_back(6);
	 b.add("eeee",v);
	 b.add("oiuy",v);
	 b.add("faffs",v);
	 b.add("fgfd",v);
	 b.add("faghgd",v);
	 b.add("ytytefe",v);
	 b.add("fsfsgfsff",v);
	 b.add("ytrefc",v);
	 b.add("rtyu",v);
	 b.add("aaaa",v);
	 b.add("bbbb",v);
	 b.add("cccc",v);
	 b.add("jjjj",v);
	 b.add("kkkkk",v);
	 b.add("llll",v);
	 b.add("mmmm",v);
	 b.add("nnnnn",v);
	 b.add("ooooo",v);
	 b.add("ppppppp",v);
	 b.add("rrrrrrr",v);
	 b.add("ssssssss",v);
	 b.add("tttttt",v);
	 b.add("uuuuuuu",v);
	 b.add("kkkkk",v);
	 b.add("dddd",v);
	 v.push_back(5);
	 b.modify("dddd",v);
	 tmp=b.search("aaaa");
	 b.del("faffs");
	 b.del("fgfd");
	 b.del("faghgd");
	 tmp=b.search("aaaa");
	 gn=b.getnext();
	 while(gn.second.size()!=0)
	 {
		 cout << gn.second << endl;
		 gn=b.getnext();
	 }
	 tmp=b.search("dddd");
	 for(int c=0;c< (int)tmp.size();c++)
		 cout << (int)tmp[c];
	 cout << endl;
}


void Pruebas::verContenidoBucketDistrito(Bucket* unBucket){
	if (unBucket->getCantidadDeRegistros()==0) cout << "BUCKET VACIO" << endl;
	else{
		cout << "Los registros cargados son:" << endl;
		list<Registro*>::iterator it = unBucket->ubicarPrimero();
		int n = unBucket->getCantidadDeRegistros();
		cout <<"El valor de N es: " << n << endl;
		for(int i = 0; i <n;i++ ){
			Registro* unRegistro = *it;
			Distrito* unDistrito = (Distrito*)unRegistro->getContenido();
			cout << "Distrito: " << unDistrito->getDistrito() << endl;
			delete unDistrito;
			it++;
		}
		cout << endl;
	}
}

void Pruebas::verContenidoBucketVotante(Bucket* unBucket){
	if (unBucket->getCantidadDeRegistros()==0) cout << "BUCKET VACIO" << endl;
	else{
		cout << "Los registros cargados son:" << endl;
		list<Registro*>::iterator it = unBucket->ubicarPrimero();
		int n = unBucket->getCantidadDeRegistros();
		for(int i = 0; i <n;i++ ){
			Registro* unRegistro = *it;
			Votante*  unVotante  = (Votante*)unRegistro->getContenido();
			unVotante->verVotante();
			delete unVotante;
			it++;
		}
		cout << endl;
	}
}

void Pruebas::verContenidoBucketEleccion(Bucket* unBucket) {
	if (unBucket->getCantidadDeRegistros()==0) cout << "BUCKET VACIO" << endl;
	else{
		cout << "Los registros cargados son:" << endl;
		list<Registro*>::iterator it = unBucket->ubicarPrimero();
		int n = unBucket->getCantidadDeRegistros();
		for(int i = 0; i <n;i++ ){
			Registro* unRegistro = *it;
			Eleccion* unaEleccion  = (Eleccion*)unRegistro->getContenido();
			cout << "Eleccion " << i+1 << endl;
			cout << "----------" << endl;
			cout << "Fecha: " << unaEleccion->getFecha() << endl;
			cout << "Cargo: " << unaEleccion->getCargo() << endl;
			cout << "Distritos habilitados: " << endl;
			list<Distrito> lista = unaEleccion->getLista();
			list<Distrito>::iterator itDistrito = lista.begin();
			int j=1;
			while (itDistrito != lista.end()){
				cout << "Distrito " << j << ": "<< (*itDistrito).getDistrito() <<endl;
				itDistrito++; j++;
			}
			delete unaEleccion;
			it++;
		}
		cout << endl;
	}
}

void Pruebas::verContenidoBucketCandidato(Bucket* unBucket){
	if (unBucket->getCantidadDeRegistros()==0) cout << "BUCKET VACIO" << endl;
	else{
		cout << "Los registros cargados son:" << endl;
		list<Registro*>::iterator it = unBucket->ubicarPrimero();
		int n = unBucket->getCantidadDeRegistros();
		cout <<"El valor de N es: " << n << endl;
		for(int i = 0; i <n;i++ ){
			Registro* unRegistro = *it;
			Candidato* unCandidato = (Candidato*)unRegistro->getContenido();
			unCandidato->verCandidato();
			delete unCandidato;
			it++;
		}
		cout << endl;
	}
}

void Pruebas::verContenidoBucketLista(Bucket* unBucket){
	if (unBucket->getCantidadDeRegistros()==0) cout << "BUCKET VACIO" << endl;
	else{
		cout << "Los registros cargados son:" << endl;
		list<Registro*>::iterator it = unBucket->ubicarPrimero();
		int n = unBucket->getCantidadDeRegistros();
		for(int i = 0; i <n;i++ ){
			Registro* unRegistro = *it;
			Lista*  unaLista  = (Lista*)unRegistro->getContenido();
			cout << "Lista " << i+1 << endl;
			cout << "Nombre: " << unaLista->getNombre() << endl;
			cout << "Fecha: " << unaLista->getFecha() << endl;
			cout << "Cargo: " << unaLista->getCargo() << endl;
//			cout << "Votos: " << unaLista->getCantidadDeVotos() << endl;
			cout << "----------" << endl;
			delete unaLista;
			it++;
		}
		cout << endl;
	}
}

void Pruebas::verContenidoBucketCargo(Bucket* unBucket){
	if (unBucket->getCantidadDeRegistros()==0) cout << "BUCKET VACIO" << endl;
	else{
		cout << "Los registros cargados son:" << endl;
		list<Registro*>::iterator it = unBucket->ubicarPrimero();
		int n = unBucket->getCantidadDeRegistros();
		for(int i = 0; i <n;i++ ){
			Registro* unRegistro = *it;
			Cargo* unCargo  = (Cargo*)unRegistro->getContenido();
			cout << "Cargo " << i << endl;
			cout << "-------" << endl;
			cout << "Cargo: " << unCargo->getCargo() << endl;
			list<string> lista = unCargo->devolverSubCargos();
			list<string>::iterator itCargo = lista.begin();
			int j=1;
			while (itCargo != lista.end()){
				cout << "Subcargo " << j << ": "<< (*itCargo) <<endl;
				itCargo++; j++;
			}
			delete unCargo;
			it++;
		}
		cout << endl;
	}
}


void Pruebas::iniciarVotantesParaIntegracion() {
	this->votante1 = new Votante(1,"Martin","m","","Recoleta");
	this->votante1->agregarEleccion ("19970701","Presidente");
	this->votante1->agregarEleccion ("19970701","Gobernador");
	this->votante2 = new Votante(2,"Lucas","l","","Recoleta");
	this->votante2->agregarEleccion ("19970701","Presidente");
	this->votante2->agregarEleccion ("19970701","Gobernador");
	this->votante3 = new Votante(3,"Daniel","d","","Recoleta");
	this->votante3->agregarEleccion ("19970701","Presidente");
	this->votante3->agregarEleccion ("19970701","Gobernador");
	this->registroVotante1 = new Registro(votante1);
	this->registroVotante2 = new Registro(votante2);
	this->registroVotante3 = new Registro(votante3);
	delete this->votante1;
	delete this->votante2;
	delete this->votante3;
	char archivoDeControl[]="archivoDeControlVotante.txt";
	char archivoDeDatos[]="archivoDeDatosVotante.txt";
	remove(archivoDeControl);
	remove(archivoDeDatos);
	this->heVotante = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos,archivoDeControl);
	if ( this->heVotante->agregarRegistro(registroVotante1) == operacionOK )
		cout << "Se agrego un votante1" << endl;
	else cout << "Error agregando votante1" << endl;
	if ( this->heVotante->agregarRegistro(registroVotante2) == operacionOK )
			cout << "Se agrego un votante2" << endl;
		else cout << "Error agregando votante2" << endl;
	if ( this->heVotante->agregarRegistro(registroVotante3) == operacionOK )
			cout << "Se agrego un votante3" << endl;
		else cout << "Error agregando votante3" << endl;

//	this->bucketVotante = new Bucket(0,454);
//	this->bucketVotante->agregarRegistro(registroVotante1);
//	this->bucketVotante->agregarRegistro(registroVotante2);
//	this->bucketVotante->agregarRegistro(registroVotante3);
}

void Pruebas::iniciarDistritosParaIntegracion(){
	this->distrito1 = new Distrito("Recoleta");
	this->distrito2 = new Distrito("Retiro");
	this->distrito3 = new Distrito("Mataderos");
	this->registroDistrito1 = new Registro(distrito1);
	this->registroDistrito2 = new Registro(distrito2);
	this->registroDistrito3 = new Registro(distrito3);
	delete this->distrito1;
	delete this->distrito2;
	delete this->distrito3;
	char archivoDeControl[]="archivoDeControlDistrito.txt";
	char archivoDeDatos[]="archivoDeDatosDistrito.txt";
	this->heDistrito = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos,archivoDeControl);
	if ( this->heDistrito->agregarRegistro(registroDistrito1) == operacionOK )
		cout << "Se agrego distrito1" << endl;
	else cout << "Error agregando distrito1" << endl;
	if ( this->heDistrito->agregarRegistro(registroDistrito2) == operacionOK )
		cout << "Se agrego un distrito2" << endl;
	else cout << "Error agregando distrito2" << endl;
	if ( this->heDistrito->agregarRegistro(registroDistrito3) == operacionOK )
		cout << "Se agrego un distrito3" << endl;
	else cout << "Error agregando distrito3" << endl;


//	this->bucketDistrito = new Bucket(0,256);
//	this->bucketDistrito->agregarRegistro(registroDistrito1);
//	this->bucketDistrito->agregarRegistro(registroDistrito2);
//	this->bucketDistrito->agregarRegistro(registroDistrito3);
}

void Pruebas::iniciarEleccionesParaIntegracion(){
	this->eleccion1 = new Eleccion("19970701","Presidente");
	this->eleccion1->agregarDistrito("Recoleta");
	this->eleccion1->agregarDistrito("Retiro");
	this->eleccion1->agregarDistrito("Mataderos");
	this->eleccion1->agregarDistrito("Colegiales");
	this->eleccion2 = new Eleccion("19970701","Gobernador");
	this->eleccion2->agregarDistrito("Recoleta");
	this->eleccion2->agregarDistrito("Retiro");
	this->eleccion2->agregarDistrito("Mataderos");
	this->eleccion2->agregarDistrito("Colegiales");
	this->eleccion3 = new Eleccion("19970702","Presidente");
	this->eleccion3->agregarDistrito("Recoleta");
	this->eleccion3->agregarDistrito("Retiro");
	this->eleccion3->agregarDistrito("Mataderos");
	this->eleccion3->agregarDistrito("Colegiales");
	this->registroEleccion1 = new Registro(eleccion1);
	this->registroEleccion2 = new Registro(eleccion2);
	this->registroEleccion3 = new Registro(eleccion3);
	delete this->eleccion1;
	delete this->eleccion2;
//	delete this->eleccion3;
	char archivoDeControl[]="archivoDeControlEleccion.txt";
	char archivoDeDatos[]="archivoDeDatosEleccion.txt";
	this->heEleccion = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos,archivoDeControl);
	if ( this->heEleccion->agregarRegistro(registroEleccion1) == operacionOK )
		cout << "Se agrego una eleccion" << endl;
	else cout << "Error agregando eleccion1" << endl;
	if ( this->heEleccion->agregarRegistro(registroEleccion2) == operacionOK )
		cout << "Se agrego una eleccion" << endl;
	else cout << "Error agregando eleccion2" << endl;
	if ( this->heEleccion->agregarRegistro(registroEleccion3) == operacionOK )
		cout << "Se agrego un eleccion" << endl;
	else cout << "Error agregando eleccion3" << endl;

//	this->bucketEleccion = new Bucket(0,450);
//	this->bucketEleccion->agregarRegistro(registroEleccion1);
//	this->bucketEleccion->agregarRegistro(registroEleccion2);
//	this->bucketEleccion->agregarRegistro(registroEleccion3);
}

void Pruebas::iniciarCandidatosParaIntegracion(){
	this->candidato1 = new Candidato("19970701","Presidente","Jaime",1);
	this->candidato2 = new Candidato("19970701","Gobernador","Cosme",2);
	this->candidato3 = new Candidato("19970702","Presidente","Juan",3);
	this->registroCandidato1 = new Registro(candidato1);
	this->registroCandidato2 = new Registro(candidato2);
	this->registroCandidato3 = new Registro(candidato3);
	delete this->candidato1;
	delete this->candidato2;
	delete this->candidato3;
	char archivoDeControl[]="archivoDeControlCandidato.txt";
	char archivoDeDatos[]="archivoDeDatosCandidato.txt";
	this->heCandidato = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos,archivoDeControl);
	if ( this->heCandidato->agregarRegistro(registroCandidato1) == operacionOK )
		cout << "Se agrego un candidato" << endl;
	else cout << "Error agregando candidato1" << endl;
	if ( this->heCandidato->agregarRegistro(registroCandidato2) == operacionOK )
		cout << "Se agrego un candidato" << endl;
	else cout << "Error agregando candidato2" << endl;
	if ( this->heCandidato->agregarRegistro(registroCandidato3) == operacionOK )
		cout << "Se agrego un candidato" << endl;
	else cout << "Error agregando candidato3" << endl;

//	this->bucketCandidato = new Bucket(0,204);
//	this->bucketCandidato->agregarRegistro(registroCandidato1);
//	this->bucketCandidato->agregarRegistro(registroCandidato2);
//	this->bucketCandidato->agregarRegistro(registroCandidato3);
}

void Pruebas::iniciarListasParaIntegracion(){
	this->lista1 = new Lista("UCR","19970701","Presidente");
	this->lista2 = new Lista("UCR","19970701","Gobernador");
	this->lista3 = new Lista("PJ","19970702","Presidente");
	this->registroLista1 = new Registro(lista1);
	this->registroLista2 = new Registro(lista2);
	this->registroLista3 = new Registro(lista3);
//	delete this->lista1;
//	delete this->lista2;
//	delete this->lista3;
	cout << "WHY" << endl;

	string* s_1 = lista1->serializar();

	Lista* lw1 = new Lista("","","");
	lw1->deserializar(s_1);
	lw1->verEntidad();
	delete s_1;

	cout << endl << endl;

	string* s2 = registroLista1->serializar();

	Registro* reg = new Registro();
	reg->deserializar(s2);
	reg->verContenido();

	bplustree arbolB;
	remove("arbolDeListas");
	arbolB.newtree("arbolDeListas",LONGITUD_BLOQUE);

	stringstream clave1;
	clave1 << registroLista1->obtenerClave();
	cout << "clave1 " << registroLista1->obtenerClave() << endl;
	cout << "clave1 comparada " << clave1.str() << endl;


	string* registroSerializado = registroLista1->serializar();
	vector<char> data1(registroSerializado->begin(), registroSerializado->end());
	cout << registroSerializado->size() << endl;


	arbolB.add(clave1.str(),data1);

	vector<char> vector1;

	vector1 = arbolB.search(clave1.str());

	if(data1.size() != vector1.size())
	{
		cout << "crap" << endl;
		return;
	}
	int sizeData1 = data1.size();
	for(int p=0; p< sizeData1; p++)
		if(data1[p]!=vector1[p])
		{
			cout << "more crap" << endl;
			return;
		}

	int sizeVector1 = vector1.size();

	string stringVector;
	for (int i= 0 ; i < sizeVector1;i++)
		stringVector.push_back(vector1[i]);

	if(stringVector.size() != registroSerializado->size())
		{
			cout << "crap" << endl;
			return;
		}
	int size2 = registroSerializado->size();
	for(int p=0 ; p < size2 ; p++)
		if(registroSerializado->at(p)!=stringVector.at(p))
		{
			cout << "more crap" << endl;
			return;
		}


	Registro* r1 = new Registro();
	r1->deserializar(&stringVector);
	r1->verContenido();

	delete r1;
	delete registroSerializado;

//	char archivoDeControl[]="archivoDeControlLista.txt";
//	char archivoDeDatos[]="archivoDeDatosLista.txt";
//	this->heLista = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos,archivoDeControl);
//	if ( this->heLista->agregarRegistro(registroLista1) == operacionOK )
//		cout << "Se agrego una lista" << endl;
//	else cout << "Error agregando lista1" << endl;
//	if ( this->heLista->agregarRegistro(registroLista2) == operacionOK )
//		cout << "Se agrego una lista" << endl;
//	else cout << "Error agregando lista2" << endl;
//	if ( this->heLista->agregarRegistro(registroLista3) == operacionOK )
//		cout << "Se agrego una lista" << endl;
//	else cout << "Error agregando listas3" << endl;

//	this->bucketLista = new Bucket(0,190);
//	cout << this->bucketLista->getEspacioLibre() << endl;
//	this->bucketLista->agregarRegistro(registroLista1);
//	cout << this->bucketLista->getEspacioLibre() << endl;
//	this->bucketLista->agregarRegistro(registroLista2);
//	cout << this->bucketLista->getEspacioLibre() << endl;
//	this->bucketLista->agregarRegistro(registroLista3);
//	cout << this->bucketLista->getEspacioLibre() << endl;
}

void Pruebas::iniciarCargosParaIntegracion() {
	this->cargo1 = new Cargo("Presidente");
	this->cargo1->agregarCargo("Vice Presidente");
	this->registroCargo1 = new Registro(cargo1);
	delete this->cargo1;
	char archivoDeControl[]="archivoDeControlCargo.txt";
	char archivoDeDatos[]="archivoDeDatosCargo.txt";
	this->heCargo = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos,archivoDeControl);
	if ( this->heCargo->agregarRegistro(registroCargo1) == operacionOK )
		cout << "Se agrego un cargo1" << endl;

//
//	this->bucketCargo = new Bucket(0,204);
//	this->bucketCargo->agregarRegistro(registroCargo1);
}

void Pruebas::cargarBaseDeDatos(Administrador administrador) {
	cout << "Inicio de carga de padron electoral" << endl;
	this->iniciarVotantesParaIntegracion();
	cout << "Se cargo el padron electoral" << endl;
	cout << "Se carga un votante nuevo" << endl;
	this->votante4 = new Votante(4,"Ignacio","i","","Recoleta");
	this->votante4->agregarEleccion ("19970701","Presidente");
	this->votante4->agregarEleccion ("19970701","Gobernador");
	this->registroVotante4 = new Registro(votante4);
	delete this->votante4;
	if (administrador.alta(this->heVotante,this->registroVotante4)==operacionOK )
		cout << "Se agrego un votante" << endl;
	else cout << "Error agregando votante4" << endl;
	heVotante->mostrarArchivoDeHash();
//	Anterior=============>
//	this->verContenidoBucketVotante(this->bucketVotante);
//	==============================


	cout << "Inicio de carga de distritos" << endl;
	this->iniciarDistritosParaIntegracion();
	this->distrito4 = new Distrito("Colegiales");
	this->registroDistrito4 = new Registro(distrito4);
	if (administrador.alta(this->heDistrito,this->registroDistrito4)==operacionOK )
		cout << "Se agrego un distrito4" << endl;
	else cout << "Error agregando distrito4" << endl;
	heDistrito->mostrarArchivoDeHash();

//	version anterior ===============>
//	if (administrador.alta(this->bucketDistrito,this->registroDistrito4)) cout << "Se cargo distrito nuevo" << endl;
//	else cout << "ERROR" << endl;
//	this->verContenidoBucketDistrito(this->bucketDistrito);
//	===============================

	cout << "Inicio de carga de Cargos posibles" << endl;
	this->iniciarCargosParaIntegracion();
	cout << "Fin de carga de Cargos posibles" << endl;
	this->cargo2 = new Cargo ("Gobernador");
	this->cargo2->agregarCargo("Vice Gobernador");
	this->registroCargo2 = new Registro(cargo2);
	if (administrador.alta(this->heCargo,this->registroCargo2)==operacionOK )
		cout << "Se agrego un cargo2" << endl;
	else cout << "Error agregando cargo2" << endl;
	heCargo->mostrarArchivoDeHash();

//	version anterior ===============>
//	if (administrador.alta(this->bucketCargo,this->registroCargo2)) cout << "Se un nuevo cargo para poder ser votado" << endl;
//	else cout << "ERROR" << endl;
//	this->verContenidoBucketCargo(this->bucketCargo);
//	=================================

	cout << "Inicio de carga de Elecciones pasadas" << endl;
	this->iniciarEleccionesParaIntegracion();
	cout << "Fin de carga de Elecciones pasadas" << endl;
	this->eleccion4 = new Eleccion ("19970702","Gobernador");
	this->eleccion4->agregarDistrito("Recoleta");
	this->eleccion4->agregarDistrito("Retiro");
	this->eleccion4->agregarDistrito("Mataderos");
	this->eleccion4->agregarDistrito("Colegiales");
	this->registroEleccion4 = new Registro(eleccion4);
	if (administrador.alta(this->heEleccion,this->registroEleccion4)==operacionOK )
		cout << "Se agrego una eleccion4" << endl;
	else cout << "Error agregando eleccion4" << endl;
	heEleccion->mostrarArchivoDeHash();

	//	version anterior ===============>
//	if (administrador.alta(this->bucketEleccion,this->registroEleccion4)) cout << "Se cargo eleccion nueva" << endl;
//	else cout << "ERROR" << endl;
//	this->verContenidoBucketEleccion(this->bucketEleccion);
//	=======================================

	cout << "Inicio de carga de Candidatos pasados" << endl;
	this->iniciarCandidatosParaIntegracion();
	cout << "Fin de carga de Elecciones pasadas" << endl;
	this->candidato4 = new Candidato ("19970702","Gobernador","VodkaTonic",4);
	this->registroCandidato4 = new Registro(candidato4);
	if (administrador.alta(this->heCandidato,this->registroCandidato4)==operacionOK )
		cout << "Se agrego un candidato4" << endl;
	else cout << "Error agregando candidato4" << endl;
	heCandidato->mostrarArchivoDeHash();

//	version anterior ===============>
//	if (administrador.alta(this->bucketCandidato,this->registroCandidato4)) cout << "Se cargo candidato nuevo" << endl;
//	else cout << "ERROR" << endl;
//	this->verContenidoBucketCandidato(this->bucketCandidato);
//	================================

	cout << "Inicio de carga de Listas de elecciones pasadas" << endl;
	this->iniciarListasParaIntegracion();
	cout << "Fin de carga de Listas de elecciones pasadas" << endl;


	this->lista4 = new Lista ("Socialista","19970702","Gobernador");
	this->registroLista4 = new Registro(lista4);
//	if (administrador.alta(this->heLista,this->registroLista4)==operacionOK )
//		cout << "Se agrego una Lista4" << endl;
//	else cout << "Error agregando lista4" << endl;

//	version anterior ===============>
//	if (administrador.alta(this->bucketLista,this->registroLista4)) cout << "Se cargo lista nueva" << endl;
//	else cout << "ERROR" << endl;
//	this->verContenidoBucketLista(this->bucketLista);
//    =========================================
}

void Pruebas::pruebaLog(){
//	FILE *archivo = fopen("texto","w+");
//	this->insertarTimestamp(archivo);
//	fputs (" Un votante ingreso al sistema",archivo);
//	sleep(10);
//	this->insertarTimestamp(archivo);
//	fputs (" Otro votante ingreso al sistema",archivo);
//	fclose (archivo);
//	Abrir y escribir al final texto
//	archivo = fopen("texto","a+");
//	fputs ("\n y espero que sea sensacional",archivo);
//	fclose (archivo);
}

void Pruebas::inicioDeSimulacion(Administrador administrador){
//	Se abre el Log
	Log log;
	log.abrir();
//	Inicio del sistema
//	El administrador habilita una eleccion valida que esta en el archivo de elecciones
	Eleccion* eleccionAHabilitar1 = new Eleccion ("19970702","Presidente");
	Eleccion* eleccionAHabilitar2 = new Eleccion ("19970702","Presidente");
	Eleccion* eleccionAHabilitar3 = new Eleccion ("19970702","Gobernador");
	Registro* registroAHabilitar1 = new Registro (eleccionAHabilitar1);
	Registro* registroAHabilitar2 = new Registro (eleccionAHabilitar2);
	Registro* registroAHabilitar3 = new Registro (eleccionAHabilitar3);
	administrador.habilitarEleccion((Eleccion*)(this->heEleccion->obtenerRegistro(registroAHabilitar1)->getContenido()));
	administrador.habilitarEleccion((Eleccion*)(this->heEleccion->obtenerRegistro(registroAHabilitar2)->getContenido()));
	administrador.habilitarEleccion((Eleccion*)(this->heEleccion->obtenerRegistro(registroAHabilitar3)->getContenido()));
	administrador.getEleccionesHabilitadas();
//	ingresa el votante1
	int numeroDeEleccion;
	int dni;
	char c;
	cout << endl;
	cout << "Bienvenido al sistema de voto electronico de los Gutierrez" << endl;
	cout << endl;
	bool ok=false;
	while (!ok) {
		cout << "Ingrese su DNI: " << endl;
		cin >> dni;
		cout << "Su dni es: " << dni << endl;
		while (!ok) {
			cout << "Presione ""S"" para confirmar, ""N"" para cancelar" << endl;
			cin >> c;
			if ((c=='s')||(c=='n')) ok=true;
			else cout << "Tecla no reconocida" << endl;
		}
		if (c=='n') ok=false;
	}
//	#warning "Hashea el dni en el archivo para ver si esta en el padron"
	Votante* votanteActual = new Votante(dni,"","","","");
	Registro* reg = new Registro(votanteActual);
	Registro* registroAuxiliar = this->heVotante->obtenerRegistro(reg);
	delete reg;
	if (!registroAuxiliar) {
		cout << "NO EXISTE EN EL PADRON" << endl;
		log.insertarMensajeConEntero(dni);
	}
	else {
		string mensaje= " Ingreso el votante: ";
		log.insertarMensajeConEntidad(((Votante*)registroAuxiliar->getContenido()),mensaje);
		cout << "Bienvenido " << ((Votante*)(registroAuxiliar->getContenido()))->getNombre() << endl;
		administrador.consultarEleccionesHabilitadasParaElVotante((Votante*)(registroAuxiliar->getContenido()));
		ok=false;
		while (!ok){
			cout << "Indique el numero de eleccion en la cual desea sufragar" << endl;
			int n;
			cin >> n;
			if (((n)<=((int)((administrador.getListaDeEleccionesHabilitadas()).size()))) && (c>0)) {
				while (!ok) {
					cout << "Usted eligio la eleccion " << n << endl;
					cout << "Si es correcto presione s sino n" << endl;
					numeroDeEleccion=n;
					cin >> c;
					if ((c=='s')||(c=='n')) ok=true;
					else cout << "Tecla incorrecta" << endl;
				}
				if (c=='s') ok=true;
				else ok=false;
			}
			else cout << "Numero invalido" << endl;
		}
//		hasheo la eleccion
		list<Eleccion*> listaHabilitadas= (administrador.getListaDeEleccionesHabilitadas());
		list<Eleccion*>::iterator itHabilitadas = listaHabilitadas.begin();
		for (int i=0;i<numeroDeEleccion-1;i++) itHabilitadas++;
		mensaje = "El votante participara en la eleccion: ";
		log.insertarMensajeConEntidad(*itHabilitadas,mensaje);
		ok=false;
		int boleta;
		administrador.cargarListasDeEleccion(*itHabilitadas,this->heLista);
		while (!ok) {
			while (!ok) {
				boleta = administrador.elegirBoleta(numeroDeEleccion,this->bucketLista);
				c=administrador.sufragar(boleta);
				if ((c=='s')||(c=='n')) ok=true;
				else cout << "Tecla no reconocida" << endl;
			}
			if (c=='n') ok=false;
		}
		list<Lista*> listaBoletas = administrador.getListaDeBoletas();
		list<Lista*>::iterator itBoletas = listaBoletas.begin();
		int size = listaBoletas.size();
		if ( boleta==size+1 ) {
			string mensaje="El votante voto en blanco ";
			log.insertarMensaje(mensaje);
		}
		else if ( boleta==size+2 ){
			string mensaje="El votante voto impugnado, nulo, etc ";
			log.insertarMensaje(mensaje);
		}
		else {
			//	me posiciono en la lista elegida de las opciones dadas
			for (int i=0; i< boleta-1;i++) itBoletas++;
			string mensaje="El votante voto lista: ";
			log.insertarMensajeConEntidad(*itBoletas,mensaje);
		}

//		INCREMENTAR CLASE CONTEO

	}
	log.cerrar();
	delete eleccionAHabilitar1;
	delete eleccionAHabilitar2;
	delete eleccionAHabilitar3;
	delete registroAHabilitar1;
	delete registroAHabilitar2;
	delete registroAHabilitar3;
	delete registroAuxiliar;
	delete votanteActual;
}

void Pruebas::pruebaDeSimulacionDePrograma () {
	string nombreDePrograma = ".//doc//password";
	Administrador administrador(nombreDePrograma);

//	intenta acceder al sistema con usuario incorrecto pero contraseña correcta
	if ((administrador.acceder("undomiel","1")) || (administrador.acceder("1","aragorn")) || (administrador.acceder("",""))) cout << "SEGURIDAD VIOLADA" << endl;

	if (administrador.acceder("undomiel","aragorn")) {
		cout << "INGRESO APROBADO" << endl;
		cout << "Bienvenido al sistama de gestion de elecciones" << endl;
		this->cargarBaseDeDatos(administrador);
		this->inicioDeSimulacion(administrador);
	}
	else cout << "ERROR EN EL NOMBRE DE USUARIO O PASSWORD" << endl;
	this->destruir();
}

void Pruebas::destruir() {
	delete votante4;
	delete distrito4;
	delete eleccion3;
	delete eleccion4;
	delete candidato4;
	delete lista4;
	delete cargo2;
	delete registroVotante1;
	delete registroVotante2;
	delete registroVotante3;
	delete registroVotante4;
	delete registroDistrito1;
	delete registroDistrito2;
	delete registroDistrito3;
	delete registroDistrito4;
	delete registroEleccion1;
	delete registroEleccion2;
	delete registroEleccion3;
	delete registroEleccion4;
	delete registroCandidato1;
	delete registroCandidato2;
	delete registroCandidato3;
	delete registroCandidato4;
	delete registroLista1;
	delete registroLista2;
	delete registroLista3;
	delete registroLista4;
	delete registroCargo1;
	delete registroCargo2;

}





int Pruebas::holaMundo(){

    cout<<"||TP 1||\n--------\n\nHola Mundo!!!\n";
    // int i; for (i=0;i<argc;i++){ cout<<"\nParámetro ["<<i<<"]: "<<argv[i];  }
    cout<<"\n\nBueno, chau...\n";
    return 0;
}
