#include "TestHashingExtensible.h"

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
			cout << "Distrito: " << unDistrito->getDistrito() << endl;
			delete unDistrito;
			it++;
		}
		cout << endl;
	}
}

void TestHashingExtensible::testAgregarRegistros(){

	int dimensionBucket = 128;
	char nombreDeArchivo[] = "he.bin";
	remove(nombreDeArchivo);
	ArchivoDeBuckets* archivo = new ArchivoDeBuckets(nombreDeArchivo,dimensionBucket);
	HashingExtensible* he = new HashingExtensible(archivo);

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


	delete archivo;
	delete he;
}

void TestHashingExtensible::testObtenerRegistro()
{
	int dimensionBucket = 128;
	char nombreDeArchivo[] = "he.bin";
	remove(nombreDeArchivo);
	ArchivoDeBuckets* archivo = new ArchivoDeBuckets(nombreDeArchivo,dimensionBucket);
	HashingExtensible* he = new HashingExtensible(archivo);

	cout << "Prueba 1 - ";
	if ( he->obtenerRegistro(12) == NULL )
	cout << " OK " <<endl; else cout << " ERROR "<<endl;

	cout << "Prueba 2 - ";
	if ( he->obtenerRegistro(-12) == NULL )
	cout << " OK " <<endl; else cout << " ERROR "<<endl;

	delete archivo;
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
	int dimensionBucket = 128;
	char nombreDeArchivo[] = "he.bin";
	remove(nombreDeArchivo);
	ArchivoDeBuckets* archivo = new ArchivoDeBuckets(nombreDeArchivo,dimensionBucket);
	HashingExtensible* he = new HashingExtensible(archivo);

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

	delete archivo;
	delete he;
}

void TestHashingExtensible::testEliminarRegistrosReduciendoTablaDehash()
{
	int dimensionBucket = 128;
	char nombreDeArchivo[] = "he.bin";
	remove(nombreDeArchivo);
	ArchivoDeBuckets* archivo = new ArchivoDeBuckets(nombreDeArchivo,dimensionBucket);
	HashingExtensible* he = new HashingExtensible(archivo);

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

	distrito = new Distrito("San Fernando del Valle de Catamarca");
	cout << endl << "Se intenta eliminar el registro "<< distrito->getDistrito() << endl;
	if ( he->eliminarRegistro(distrito->getClave()) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	distrito = new Distrito("Resistencia");
	cout << endl << "Se intenta eliminar el registro "<< distrito->getDistrito() << endl;
	if ( he->eliminarRegistro(distrito->getClave()) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	distrito = new Distrito("Resistencia");
	cout << endl << "Se intenta obtener el registro "<< distrito->getDistrito() << endl;
	if ( he->obtenerRegistro(distrito->getClave()) == NULL )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;


	cout << endl << "Se muestra el archivo de HASH " << endl;
	he->mostrarArchivoDeHash();

	delete archivo;
	delete he;
}

void TestHashingExtensible::testEliminarRegistro()
{
	int dimensionBucket = 128;
	char nombreDeArchivo[] = "he.bin";
	remove(nombreDeArchivo);
	ArchivoDeBuckets* archivo = new ArchivoDeBuckets(nombreDeArchivo,dimensionBucket);
	HashingExtensible* he = new HashingExtensible(archivo);

	Distrito* distrito = new Distrito("Buenos Aires");
	Registro* registro = new Registro(distrito);

	cout << endl << "** Se intenta agregar "<< distrito->getDistrito() <<" al hashing" << endl;
	if ( he->agregarRegistro(registro) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;

	delete distrito;
	delete registro;

	cout << endl << "Se intenta eliminar al registro Buenos Aires" << endl;
	distrito = new Distrito("Buenos Aires");
	if ( he->eliminarRegistro(distrito->getClave()) == operacionOK )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;


	cout << endl << "Se intenta acceder al registro Buenos Aires" << endl;
	distrito = new Distrito("Buenos Aires");
	if ( he->obtenerRegistro(distrito->getClave()) == NULL )
		cout << "OPERACION EXITOSA" << endl;
	else
		cout << "OPERACION FALLO" << endl;
	delete distrito;

	delete archivo;
	delete he;
}

void TestHashingExtensible::testModificarRegistroInexistente()
{
	int dimensionBucket = 128;
	char nombreDeArchivo[] = "he.bin";
	remove(nombreDeArchivo);
	ArchivoDeBuckets* archivo = new ArchivoDeBuckets(nombreDeArchivo,dimensionBucket);
	HashingExtensible* he = new HashingExtensible(archivo);

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



	delete archivo;
	delete he;
}

void TestHashingExtensible::testModificarRegistroExistente()
{
	int dimensionBucket = 128;
	char nombreDeArchivo[] = "he.bin";
	remove(nombreDeArchivo);
	ArchivoDeBuckets* archivo = new ArchivoDeBuckets(nombreDeArchivo,dimensionBucket);
	HashingExtensible* he = new HashingExtensible(archivo);

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

	delete archivo;
	delete he;
}

void TestHashingExtensible::testModificarRegistroConRedispersion()
{
}

TestHashingExtensible::~TestHashingExtensible() {
	// TODO Auto-generated destructor stub
}
