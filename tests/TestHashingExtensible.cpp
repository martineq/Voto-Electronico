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

	string distritos[] = {"Buenos Aires","Puerto Esperanza","Montecarlo","Eldorado"};
	for( int i=0;i < 4; i++ ){
		Distrito* distrito = new Distrito(distritos[i]);
		Registro* registro = new Registro(distrito);

		cout << endl << "Se intenta agregar "<< distrito->getDistrito() <<" al hashing" << endl;
		he->agregarRegistro(registro);

		delete distrito;
		delete registro;
	}

	cout << endl << endl << "Prueba obtener distrito: Buenos Aires" << endl;

	Registro* registroNuevo = he->obtenerRegistro(12);
	if ( registroNuevo != NULL ){
		Distrito* distrito = (Distrito*)registroNuevo->getContenido();
		cout << "Distrito: " << distrito->getDistrito() << endl;
		delete registroNuevo;
	}

	cout << endl << endl << "Prueba obtener distrito: Eldorado" << endl;

	registroNuevo = he->obtenerRegistro(8);
	if ( registroNuevo != NULL ){
		Distrito* distrito = (Distrito*)registroNuevo->getContenido();
		cout << "Distrito: " << distrito->getDistrito() << endl;
		delete registroNuevo;
	}

	cout << endl << endl << "Prueba obtener distrito: Montecarlo" << endl;

	registroNuevo = he->obtenerRegistro(10);
	if ( registroNuevo != NULL ){
		Distrito* distrito = (Distrito*)registroNuevo->getContenido();
		cout << "Distrito: " << distrito->getDistrito() << endl;
		delete registroNuevo;
	}

	cout << endl << endl << "Prueba obtener distrito: Puerto Esperanza" << endl;

	registroNuevo = he->obtenerRegistro(16);
	if ( registroNuevo != NULL ){
		Distrito* distrito = (Distrito*)registroNuevo->getContenido();
		cout << "Distrito: " << distrito->getDistrito() << endl;
		delete registroNuevo;
	}

	delete archivo;
	delete he;
}

TestHashingExtensible::~TestHashingExtensible() {
	// TODO Auto-generated destructor stub
}

