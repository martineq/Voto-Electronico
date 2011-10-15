#include "TestHashingExtensible.h"

HashingExtensible* TestHashingExtensible::inicializarArchivosDePrueba(){
	int dimensionBucket = 128;
	char nombreDeArchivo[] = "he.bin";
	char archivoConfiguracion[] = "conf.bin";
	remove(nombreDeArchivo);
	remove(archivoConfiguracion);
	HashingExtensible* he = new HashingExtensible(dimensionBucket,nombreDeArchivo,archivoConfiguracion);
	return he;
}

HashingExtensible* TestHashingExtensible::inicializarArchivosDePruebaSinBorrarExistentes(){
	int dimensionBucket = 128;
	char nombreDeArchivo[] = "he.bin";
	char archivoConfiguracion[] = "conf.bin";
	HashingExtensible* he = new HashingExtensible(dimensionBucket,nombreDeArchivo,archivoConfiguracion);
	return he;
}

TestHashingExtensible::TestHashingExtensible() {
	// TODO Auto-generated constructor stub

}

void TestHashingExtensible::verContenidoBucketDistrito(Bucket* bucket){
	if (bucket->getCantidadDeRegistros()==0) cout << "BUCKET VACIO" << endl;
	else{
		cout << "Los registros cargados son:" << endl;
		list<Registro*>::iterator it = bucket->ubicarPrimero();
		int n = bucket->getCantidadDeRegistros();
		cout <<"El valor de N es: " << n << endl;
		for(int i = 0; i <n;i++ ){
			Registro* unRegistro = *it;
			Distrito* unDistrito = (Distrito*)unRegistro->getContenido();
			string s = unDistrito->getDistrito();
			cout << "Distrito: " << s << endl;
			delete unDistrito;
			it++;
		}
		cout << endl;
	}
}

void TestHashingExtensible::testAgregarRegistros1(){
	HashingExtensible* he = inicializarArchivosDePrueba();

	string distritos[] = {"Buenos Aires","Puerto Esperanza","Montecarlo","Eldorado","Pekin","Santiago del Estero","Marseille","Washington DC","Edinburgo","Amsterdam","Madrid","Brasilia","Mexico DF","Santiago de Compostela","Atenas","San Francisco","Cupertino","San Diego","Las Vegas","Mendoza","Corrientes","San Fernando del Valle de Catamarca","San Martin de los Andes","Valeria del Mar","Resistencia","San Salvador de Jujuy"};
	for( int i=0;i < 26 ; i++ ){
		Distrito* distrito = new Distrito(distritos[i]);
		Registro* registro = new Registro(distrito);

		if (distrito->getDistrito() == "Valeria del Mar")
			cout << "stop";

		cout << endl << "** Se intenta agregar "<< distrito->getDistrito() <<" al hashing" << endl;
		if ( he->agregarRegistro(registro) == operacionOK )
			cout << "OPERACION EXITOSA" << endl;
		else
			cout << "OPERACION FALLO" << endl;

		he->mostrarArchivoDeHash();

		delete distrito;
		delete registro;
	}

	he->mostrarArchivoDeHash();

	delete he;
}

void TestHashingExtensible::testAgregarRegistros2(){
	HashingExtensible* he = inicializarArchivosDePrueba();

	string distritos[] = {"Buenos Aires","Puerto Esperanza","Montecarlo","Eldorado","Pekin","Santiago del Estero","Marseille","Washington DC","Edinburgo","Amsterdam","Madrid","Brasilia","Mexico DF","Santiago de Compostela","Atenas","San Francisco","Cupertino","San Diego","Las Vegas","Mendoza","Corrientes","San Fernando del Valle de Catamarca","San Martin de los Andes","Valeria del Mar","Resistencia","San Salvador de Jujuy"};
	for( int i=0;i < 26 ; i++ ){
		Distrito* distrito = new Distrito(distritos[i]);
		Registro* registro = new Registro(distrito);

		if (distrito->getDistrito() == "Valeria del Mar")
			cout << "stop";

		cout << endl << "** Se intenta agregar "<< distrito->getDistrito() <<" al hashing" << endl;
		if ( he->agregarRegistro(registro) == operacionOK )
			cout << "OPERACION EXITOSA" << endl;
		else
			cout << "OPERACION FALLO" << endl;

		he->mostrarArchivoDeHash();

		delete distrito;
		delete registro;
	}


	// Prueba de obtención de registros
	Distrito* distrito;
	Registro* registro;

	cout << endl << endl << "Prueba obtener distrito: Buenos Aires" << endl;
	distrito = new Distrito("Buenos Aires");
	registro = he->obtenerRegistro(distrito->getClave());
	delete distrito;

	if ( registro != NULL ){
		distrito = (Distrito*)registro->getContenido();
		cout << "Distrito: " << distrito->getDistrito() << endl;
		delete distrito;
		delete registro;
	}

	cout << endl << endl << "Prueba obtener distrito: Eldorado" << endl;

	distrito = new Distrito("Eldorado");
	registro = he->obtenerRegistro(distrito->getClave());
	delete distrito;

	if ( registro != NULL ){
		distrito = (Distrito*)registro->getContenido();
		cout << "Distrito: " << distrito->getDistrito() << endl;
		delete distrito;
		delete registro;
	}

	cout << endl << endl << "Prueba obtener distrito: Montecarlo" << endl;

	distrito = new Distrito("Montecarlo");
	registro = he->obtenerRegistro(distrito->getClave());
	delete distrito;

	if ( registro != NULL ){
		distrito = (Distrito*)registro->getContenido();
		cout << "Distrito: " << distrito->getDistrito() << endl;
		delete distrito;
		delete registro;
	}

	cout << endl << endl << "Prueba obtener distrito: Puerto Esperanza" << endl;

	distrito = new Distrito("Puerto Esperanza");
	registro = he->obtenerRegistro(distrito->getClave());
	delete distrito;

	if ( registro != NULL ){
		distrito = (Distrito*)registro->getContenido();
		cout << "Distrito: " << distrito->getDistrito() << endl;
		delete distrito;
		delete registro;
	}

	cout << endl << endl << "Prueba obtener distrito: San Fernando del Valle de Catamarca" << endl;
	distrito = new Distrito("San Fernando del Valle de Catamarca");
	registro = he->obtenerRegistro(distrito->getClave());
	delete distrito;

	if ( registro != NULL ){
		distrito = (Distrito*)registro->getContenido();
		cout << "Distrito: " << distrito->getDistrito() << endl;
		delete distrito;
		delete registro;
	}

	cout << endl << endl << "Prueba obtener distrito: Amsterdam" << endl;
	distrito = new Distrito("Amsterdam");
	registro = he->obtenerRegistro(distrito->getClave());
	delete distrito;

	if ( registro != NULL ){
		distrito = (Distrito*)registro->getContenido();
		cout << "Distrito: " << distrito->getDistrito() << endl;
		delete distrito;
		delete registro;
	}
	cout << "Este el caso de la clave duplicada, busca por clave y es Marseille y no Amsterdam la almacenada." << endl;


	cout << endl << endl << "Prueba obtener distrito: Roma" << endl;
	distrito = new Distrito("Roma");
	registro = he->obtenerRegistro(distrito->getClave());
	delete distrito;
	if ( registro != NULL ){
		distrito = (Distrito*)registro->getContenido();
		cout << "Distrito: " << distrito->getDistrito() << endl;
		delete distrito;
		delete registro;
	}else{
		cout << "Este distrito no fue agregado, por lo que no debe encontrarse." << endl;
	}

	delete he;
}

void TestHashingExtensible::testObtenerRegistro()
{
	HashingExtensible* he = inicializarArchivosDePrueba();

	cout << "Prueba 1 - ";
	if ( he->obtenerRegistro(12) == NULL )
	cout << " OK " <<endl; else cout << " ERROR "<<endl;

	cout << "Prueba 2 - ";
	if ( he->obtenerRegistro(-12) == NULL )
	cout << " OK " <<endl; else cout << " ERROR "<<endl;

	delete he;
}

void TestHashingExtensible::cargarRegistros(HashingExtensible* he){
	string distritos[] = {"Buenos Aires","Puerto Esperanza","Montecarlo","Eldorado","Pekin","Santiago del Estero","Marseille","Washington DC","Edinburgo","Amsterdam","Madrid","Brasilia","Mexico DF","Santiago de Compostela","Atenas","San Francisco","Cupertino","San Diego","Las Vegas","Mendoza","Corrientes","San Fernando del Valle de Catamarca","San Martin de los Andes","Valeria del Mar","Resistencia","San Salvador de Jujuy"};
	for( int i=0;i < 26 ; i++ ){
		Distrito* distrito = new Distrito(distritos[i]);
		Registro* registro = new Registro(distrito);

		cout << endl << "** Se intenta agregar "<< distrito->getDistrito() <<" al hashing" << endl;
		if ( he->agregarRegistro(registro) == operacionOK )
			cout << "OPERACION EXITOSA" << endl;
		else
			cout << "OPERACION FALLO" << endl;

		delete distrito;
		delete registro;
	}
}

void TestHashingExtensible::testEliminarRegistrosYBucketSinReducirTabladeHash(){
	HashingExtensible* he = inicializarArchivosDePrueba();
	this->cargarRegistros(he);
	he->mostrarArchivoDeHash();

	cout << endl << endl << "** INICIO DE ELIMINACION DE REGISTROS *****" << endl;

	Distrito* distrito;

	distrito = new Distrito("Buenos Aires");
	cout << endl << "Se intenta eliminar el registro "<< distrito->getDistrito() << endl;
	if ( he->eliminarRegistro(distrito->getClave()) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	distrito = new Distrito("Puerto Esperanza");
	cout << endl << "Se intenta eliminar el registro "<< distrito->getDistrito() << endl;

	if ( he->eliminarRegistro(distrito->getClave()) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	distrito = new Distrito("Montecarlo");
	cout << endl << "Se intenta eliminar el registro "<< distrito->getDistrito() << endl;

	if ( he->eliminarRegistro(distrito->getClave()) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	distrito = new Distrito("Atenas");
	cout << endl << "Se intenta eliminar el registro "<< distrito->getDistrito() << endl;

	if ( he->eliminarRegistro(distrito->getClave()) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	distrito = new Distrito("Buenos Aires");
	cout << endl << "Se intenta obtener el registro "<< distrito->getDistrito() << endl;

	if ( he->obtenerRegistro(distrito->getClave()) == NULL )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;


	cout << endl << "Se muestra el archivo de HASH " << endl;
	he->mostrarArchivoDeHash();

	delete he;
}

void TestHashingExtensible::testEliminarRegistrosReduciendoTablaDehash()
{
	HashingExtensible* he = inicializarArchivosDePrueba();

	this->cargarRegistros(he);
	he->mostrarArchivoDeHash();

	cout << endl << endl << "** INICIO DE ELIMINACION DE REGISTROS *****" << endl;

	Distrito* distrito;

	distrito = new Distrito("Santiago del Estero");
	cout << endl << "Se intenta eliminar el registro "<< distrito->getDistrito() << endl;
	if ( he->eliminarRegistro(distrito->getClave()) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	cout << endl << "Se muestra el archivo de HASH " << endl;
	he->mostrarArchivoDeHash();

	distrito = new Distrito("San Fernando del Valle de Catamarca");
	cout << endl << "Se intenta eliminar el registro "<< distrito->getDistrito() << endl;
	if ( he->eliminarRegistro(distrito->getClave()) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	cout << endl << "Se muestra el archivo de HASH " << endl;
	he->mostrarArchivoDeHash();

	distrito = new Distrito("Resistencia");
	cout << endl << "Se intenta eliminar el registro "<< distrito->getDistrito() << endl;
	if ( he->eliminarRegistro(distrito->getClave()) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	cout << endl << "Se muestra el archivo de HASH " << endl;
	he->mostrarArchivoDeHash();

	distrito = new Distrito("Resistencia");
	cout << endl << "Se intenta obtener el registro "<< distrito->getDistrito() << endl;
	if ( he->obtenerRegistro(distrito->getClave()) == NULL )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	cout << endl << "Se muestra el archivo de HASH " << endl;
	he->mostrarArchivoDeHash();

	distrito = new Distrito("Mendoza");
	cout << endl << "Se intenta eliminar el registro "<< distrito->getDistrito() << endl;
	if ( he->eliminarRegistro(distrito->getClave()) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	cout << endl << "Se muestra el archivo de HASH " << endl;
	he->mostrarArchivoDeHash();

	delete he;
}

void TestHashingExtensible::testEliminarRegistro()
{
	HashingExtensible* he = inicializarArchivosDePrueba();

	Distrito* distrito = new Distrito("Buenos Aires");
	Registro* registro = new Registro(distrito);

	cout << endl << "** Se intenta agregar "<< distrito->getDistrito() <<" al hashing" << endl;
	if ( he->agregarRegistro(registro) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;

	delete distrito;
	delete registro;

	he->mostrarArchivoDeHash();

	cout << endl << "Se intenta eliminar al registro Buenos Aires" << endl;
	distrito = new Distrito("Buenos Aires");
	int clave = distrito->getClave();
	if ( he->eliminarRegistro(clave) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	he->mostrarArchivoDeHash();

	cout << endl << "Se intenta acceder al registro Buenos Aires" << endl;
	distrito = new Distrito("Buenos Aires");
	if ( he->obtenerRegistro(distrito->getClave()) == NULL )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	he->mostrarArchivoDeHash();

	cout << "se reintenta la operacion." << endl;

	distrito = new Distrito("Buenos Aires");
	registro = new Registro(distrito);

	cout << endl << "** Se intenta agregar "<< distrito->getDistrito() <<" al hashing" << endl;
	if ( he->agregarRegistro(registro) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;

	delete distrito;
	delete registro;

	he->mostrarArchivoDeHash();

	distrito = new Distrito("Puerto Esperanza");
	registro = new Registro(distrito);

	cout << endl << "** Se intenta agregar "<< distrito->getDistrito() <<" al hashing" << endl;
	if ( he->agregarRegistro(registro) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;

	delete distrito;
	delete registro;

	he->mostrarArchivoDeHash();

	distrito = new Distrito("Madrid");
	registro = new Registro(distrito);

	cout << endl << "** Se intenta agregar "<< distrito->getDistrito() <<" al hashing" << endl;
	if ( he->agregarRegistro(registro) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;

	delete distrito;
	delete registro;

	he->mostrarArchivoDeHash();

	distrito = new Distrito("Montevideo");
	registro = new Registro(distrito);

	cout << endl << "** Se intenta agregar "<< distrito->getDistrito() <<" al hashing" << endl;
	if ( he->agregarRegistro(registro) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;

	delete distrito;
	delete registro;

	he->mostrarArchivoDeHash();

	distrito = new Distrito("Londres");
	registro = new Registro(distrito);

	cout << endl << "** Se intenta agregar "<< distrito->getDistrito() <<" al hashing" << endl;
	if ( he->agregarRegistro(registro) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;

	delete distrito;
	delete registro;

	he->mostrarArchivoDeHash();

	cout << endl << "Se intenta eliminar al registro Buenos Aires" << endl;
	distrito = new Distrito("Buenos Aires");
	clave = distrito->getClave();
	if ( he->eliminarRegistro(clave) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	he->mostrarArchivoDeHash();


	cout << endl << "Se intenta acceder al registro Buenos Aires" << endl;
	distrito = new Distrito("Buenos Aires");
	if ( he->obtenerRegistro(distrito->getClave()) == NULL )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	he->mostrarArchivoDeHash();

	cout << endl << "Se intenta eliminar al registro Montevideo" << endl;
	distrito = new Distrito("Montevideo");
	clave = distrito->getClave();
	if ( he->eliminarRegistro(clave) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	he->mostrarArchivoDeHash();

	cout << endl << "Se intenta eliminar al registro Puerto Esperanza" << endl;
	distrito = new Distrito("Puerto Esperanza");
	clave = distrito->getClave();
	if ( he->eliminarRegistro(clave) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	he->mostrarArchivoDeHash();

	cout << "FIN TEST" << endl;

	delete he;
}

void TestHashingExtensible::testModificarRegistroInexistente()
{
	HashingExtensible* he = inicializarArchivosDePrueba();

	Distrito* distrito = new Distrito("Ciudad Autonoma de Buenos Aires");
	Registro* registro = new Registro(distrito);

	cout << endl << "Se intenta modificar un registro inexistente" << endl;
	if ( he->modificarRegistro(registro) == registroInexistente )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;

	delete registro;
	delete distrito;

	this->cargarRegistros(he);
	he->mostrarArchivoDeHash();

	distrito = new Distrito("Ciudad Autonoma de Buenos Aires");
	registro = new Registro(distrito);

	cout << endl << "Se intenta modificar un registro inexistente" << endl;
	if ( he->modificarRegistro(registro) == registroInexistente )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;

	delete registro;
	delete distrito;

	delete he;
}

void TestHashingExtensible::testModificarRegistroExistente()
{
	HashingExtensible* he = inicializarArchivosDePrueba();

	Distrito* distrito;
	Registro* registro;

	this->cargarRegistros(he);
	he->mostrarArchivoDeHash();

	cout << endl << "Se intenta acceder al registro Marseille" << endl;

	distrito = new Distrito("Marseille");
	registro = he->obtenerRegistro(distrito->getClave());
	delete distrito;

	if ( registro != NULL ){
		cout << "OPERACION EXITOSA" << endl;
		distrito = (Distrito*)registro->getContenido();
		cout << "Se obtuvo el distrito: " << distrito->getDistrito() << endl;
	}else
		cout << "OPERACION FALLO" << endl;

	delete registro;
	delete distrito;

	distrito = new Distrito("Amsterdam");
	registro = new Registro(distrito);

	cout << endl << "Se intenta modificar un registro" << endl;
	if ( he->modificarRegistro(registro) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;

	delete registro;
	delete distrito;

	//he->mostrarArchivoDeHash();

	cout << endl << "Se intenta acceder al registro Amsterdam" << endl;
	distrito = new Distrito("Amsterdam");
	registro = he->obtenerRegistro(distrito->getClave());
	delete distrito;
	if ( registro != NULL ){
		cout << "OPERACION EXITOSA" << endl;
		distrito = (Distrito*)registro->getContenido();
		cout << "Se obtuvo el distrito: " << distrito->getDistrito() << endl;
	}else
		cout << "OPERACION FALLO" << endl;

	delete registro;
	delete distrito;

	delete he;
}

void TestHashingExtensible::testModificarRegistroConRedispersion()
{
	int dimensionBucket = 384;
	char nombreDeArchivo[] = "he.bin";
	char archivoConfiguracion[] = "conf.bin";
	remove(nombreDeArchivo);
	remove(archivoConfiguracion);
	HashingExtensible* he = new HashingExtensible(dimensionBucket,nombreDeArchivo,archivoConfiguracion);

	for(int i= 0;i<5;i++){
		cout << endl << endl << "Votante: " << i << endl;
		Votante* v = new Votante(i,"nombre","password","domicilio","distrito");
		Registro* r = new Registro(v);
		delete v;
		if (i == 4)
			cout << "stop" << endl;
		he->agregarRegistro(r);
		delete r;

		he->mostrarArchivoDeHash();

	}

	delete he;
}

void TestHashingExtensible::testCargarYmostrarContenidoDelArchivo()
{
	HashingExtensible* he = inicializarArchivosDePruebaSinBorrarExistentes();

	he->mostrarArchivoDeHash();

	delete he;
}

void TestHashingExtensible::testSimple(){
		HashingExtensible* he = inicializarArchivosDePrueba();

		string vect[]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
		for(int i= 0;i<26;i++){
			cout << "DISTRITO: " << vect[i] << endl;
			Distrito* d = new Distrito(vect[i]);
			Registro* r = new Registro(d);
			he->agregarRegistro(r);

			he->mostrarArchivoDeHash();
			delete r;
			delete d;
		}

		for(int i=0;i<26;i++){
			cout << "DISTRITO: " << vect[i] << endl;
			Distrito* d = new Distrito(vect[i]);
			he->eliminarRegistro(d->getClave());

			he->mostrarArchivoDeHash();
			delete d;

		}

		for(int i= 0;i<26;i++){
			cout << "DISTRITO: " << vect[i] << endl;
			Distrito* d = new Distrito(vect[i]);
			Registro* r = new Registro(d);
			he->agregarRegistro(r);

			he->mostrarArchivoDeHash();
			delete r;
			delete d;
		}

		delete he;
}

TestHashingExtensible::~TestHashingExtensible() {
}
