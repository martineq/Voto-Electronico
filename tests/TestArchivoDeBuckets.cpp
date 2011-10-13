#include "TestArchivoDeBuckets.h"

Bucket* TestArchivoDeBuckets::crearBucket1(){
	Bucket* bucket = new Bucket(LONGITUD_BLOQUE_PRUEBA,0);
	string distritos[] = {"Buenos Aires","Puerto Esperanza","Bahia Blancaaaaa","ushuaia"};

	for (int i=0; i < 4 ;i++){
		Distrito* distrito = new Distrito(distritos[i]);
		Registro* registro = new Registro(distrito);
		delete(distrito);

		bucket->agregarRegistro(registro);
		delete(registro);
	}

	return bucket;
}

Bucket* TestArchivoDeBuckets::crearBucket2(){
	Bucket* bucket = new Bucket(LONGITUD_BLOQUE_PRUEBA,0);
	string distritos[] = {"Montevideo","San Francisco","Paris","Londres"};

	for (int i=0; i < 4 ;i++){
		Distrito* distrito = new Distrito(distritos[i]);
		Registro* registro = new Registro(distrito);
		delete(distrito);

		bucket->agregarRegistro(registro);
		delete(registro);
	}
	return bucket;
}

Bucket* TestArchivoDeBuckets::crearBucket3(){
	Bucket* bucket = new Bucket(LONGITUD_BLOQUE_PRUEBA,0);
	string distritos[] = {"Moscu","Auckland","Canberra","Puerto Moresby"};

	for (int i=0; i < 4 ;i++){
		Distrito* distrito = new Distrito(distritos[i]);
		Registro* registro = new Registro(distrito);
		delete(distrito);

		bucket->agregarRegistro(registro);
		delete(registro);
	}
	return bucket;
}

Bucket* TestArchivoDeBuckets::crearBucket4(){
	Bucket* bucket = new Bucket(LONGITUD_BLOQUE_PRUEBA,0);
	string distritos[] = {"Washington","Nueva York","Roma","Atenas"};

	for (int i=0; i < 4 ;i++){
		Distrito* distrito = new Distrito(distritos[i]);
		Registro* registro = new Registro(distrito);
		delete(distrito);

		bucket->agregarRegistro(registro);
		delete(registro);
	}
	return bucket;
}

Bucket* TestArchivoDeBuckets::crearBucket5(){
	Bucket* bucket = new Bucket(LONGITUD_BLOQUE_PRUEBA,0);
	string distritos[] = {"Copenhague","Marseille","Viena","Praga"};

	for (int i=0; i < 4 ;i++){
		Distrito* distrito = new Distrito(distritos[i]);
		Registro* registro = new Registro(distrito);
		delete(distrito);

		bucket->agregarRegistro(registro);
		delete(registro);
	}
	return bucket;
}

void TestArchivoDeBuckets::mostrarBucket(ArchivoDeBuckets* archivo,int numeroDeBucket){
	Bucket* bucketNuevo = archivo->obtenerBucket(numeroDeBucket);

	string* serializacion = bucketNuevo->serializar();
	cout << "bucketSerializado "<< serializacion->size() << endl;
	delete serializacion;

	int cantRegistros = bucketNuevo->getCantidadDeRegistros();

	list<Registro*>::iterator it = bucketNuevo->ubicarPrimero();
	for(int i =0; i < cantRegistros;i++){
		Registro* registro = *it;
		Distrito* d = (Distrito*)registro->getContenido();
		cout << d->getDistrito() << endl;
		delete d;
		it++;
	}

	delete bucketNuevo;
}

TestArchivoDeBuckets::TestArchivoDeBuckets()
{
}

void TestArchivoDeBuckets::testAgregarDistrito(Bucket* bucket,string lugar){
	Distrito* distrito = new Distrito(lugar);
	Registro* registro = new Registro(distrito);

	if ( !bucket->agregarRegistro(registro) )
		cout << "No se pudo agregar el registro en el bucket." << endl;

	delete distrito;
	delete registro;
}

void TestArchivoDeBuckets::testObtenerBucketFallas(){
	Bucket* bucket;
	int nB;
	int nB1;
	int nB2;
	int nB4;
	char nombreDelArchivo[]= "Archivo.bin";
	remove(nombreDelArchivo);
	int numero = LONGITUD_BLOQUE_PRUEBA;

	ArchivoDeBuckets* archivo = new ArchivoDeBuckets(nombreDelArchivo,numero);

	cout << "** Carga de Bucket" << endl;
	Bucket* bucketValido = new Bucket(0,numero);
	testAgregarDistrito(bucketValido,"Buenos Aires");
	nB = archivo->guardarBucket(bucketValido);

	cout << "** Carga de Bucket" << endl;
	Bucket* bucketValido2 = new Bucket(0,numero);
	testAgregarDistrito(bucketValido,"Puerto Esperanza");
	nB1 = archivo->guardarBucket(bucketValido);

	cout << "** Carga de Bucket" << endl;
	Bucket* bucketValido3 = new Bucket(0,numero);
	testAgregarDistrito(bucketValido,"Montecarlo");
	nB2 = archivo->guardarBucket(bucketValido);

	cout << endl << endl << "INICIO DE PRUEBAS" << endl << endl;

	bucket = archivo->obtenerBucket(-1);
	if ( bucket==NULL )
		cout << "Prueba 1 - OK" << endl;
	else
		cout << "Prueba 1 - FALLO" << endl;

	bucket = archivo->obtenerBucket(100);
	if ( bucket==NULL )
		cout << "Prueba 2 - OK" << endl;
	else
		cout << "Prueba 2 - FALLO" << endl;

	bucket = NULL;

	if ( archivo->bucketDisponible(-100) == bucketNoDisponible )
		cout << "Prueba 3 - OK" << endl;
	else
		cout << "Prueba 3 - FALLO" << endl;

	if ( archivo->bucketDisponible(100) == bucketNoDisponible )
		cout << "Prueba 4 - OK" << endl;
	else
		cout << "Prueba 4 - FALLO" << endl;

	if ( archivo->liberarBucket(-100) == bucketNoDisponible )
		cout << "Prueba 5 - OK" << endl;
	else
		cout << "Prueba 5 - FALLO" << endl;

	if ( archivo->liberarBucket(100) == bucketNoDisponible )
		cout << "Prueba 6 - OK" << endl;
	else
		cout << "Prueba 6 - FALLO" << endl;

	if ( archivo->guardarBucket(bucket) == bucketNULO )
		cout << "Prueba 7 - OK" << endl;
	else
		cout << "Prueba 7 - FALLO" << endl;

	if ( archivo->modificarBucket(18,bucket) == bucketNULO )
		cout << "Prueba 8 - OK" << endl;
	else
		cout << "Prueba 8 - FALLO" << endl;

	if ( archivo->modificarBucket(-100,bucketValido) == bucketNoDisponible )
		cout << "Prueba 9 - OK" << endl;
	else
		cout << "Prueba 9 - FALLO" << endl;

	if ( archivo->modificarBucket(100,bucketValido) == bucketNoDisponible )
		cout << "Prueba 10 - OK" << endl;
	else
		cout << "Prueba 10 - FALLO" << endl;

	cout << "Prueba 11 -";
	if ( archivo->bucketDisponible(nB) == bucketEnUso )
		cout << " OK" << endl;
	else
		cout << " FALLO" << endl;

	cout << "Prueba 12 -";
	if ( archivo->liberarBucket(nB) == operacionOK )
		cout << " OK" << endl;
	else
		cout << " FALLO" << endl;

	cout << "Prueba 13 -";
	if ( archivo->bucketDisponible(nB) == bucketLibre )
		cout << " OK" << endl;
	else
		cout << " FALLO" << endl;

	cout << "Prueba 14 -";
	if ( archivo->modificarBucket(nB,bucketValido2) == bucketLibre )
		cout << " OK" << endl;
	else
		cout << " FALLO" << endl;

	cout << "Prueba 15 -";
	if ( archivo->obtenerBucket(nB) == NULL )
		cout << " OK" << endl;
	else
		cout << " FALLO" << endl;

	archivo->liberarBucket(nB2);

	cout << "Prueba 16 -";
	if ( archivo->bucketDisponible(nB2) == bucketNoDisponible )
		cout << " OK" << endl;
	else
		cout << " FALLO" << endl;

	archivo->liberarBucket(nB1);

	cout << "Prueba 17 -";
	if ( archivo->bucketDisponible(nB1) == bucketNoDisponible )
		cout << " OK" << endl;
	else
		cout << " FALLO" << endl;

	cout << "Prueba 18 -";
	if ( archivo->liberarBucket(nB) == bucketLibre )
		cout << " OK" << endl;
	else
		cout << " FALLO" << endl;

	cout << "** Carga de Bucket" << endl;
	Bucket* bucketValido4 = new Bucket(0,numero);
	testAgregarDistrito(bucketValido,"Hong Kong");
	nB4 = archivo->guardarBucket(bucketValido);

	cout << nB4 << endl;

	delete bucketValido4;
	delete bucketValido;
	delete bucketValido2;
	delete bucketValido3;
	delete archivo;
}

void TestArchivoDeBuckets::testAccesoADisco(){
	Bucket* bucket;
	int nB;

	char nombreDelArchivo[]= "Archivo.bin";
	remove(nombreDelArchivo);
	int numero = LONGITUD_BLOQUE_PRUEBA;

	ArchivoDeBuckets* archivo = new ArchivoDeBuckets(nombreDelArchivo,numero);

	string distritos[] = {"Copenhague","Marseille","Viena","Praga"};

	bucket	= new Bucket(0,numero);

	testAgregarDistrito(bucket,distritos[0]);
	nB = archivo->guardarBucket(bucket);
	delete bucket;

	bucket = archivo->obtenerBucket(nB);

	if ( bucket ){

		testAgregarDistrito(bucket,distritos[1]);
		archivo->modificarBucket(nB,bucket);
		delete bucket;
	}

	bucket = archivo->obtenerBucket(nB);
	if ( bucket ){

		testAgregarDistrito(bucket,distritos[2]);
		archivo->modificarBucket(nB,bucket);
		delete bucket;
	}

	bucket = archivo->obtenerBucket(nB);
	if ( bucket ){

		testAgregarDistrito(bucket,distritos[3]);
		archivo->modificarBucket(nB,bucket);
		delete bucket;
	}

	mostrarBucket(archivo,nB);

	delete archivo;
}

void TestArchivoDeBuckets::testAltaBajaDeBucketsEnArchivoDeBuckets(){
	char nombreDelArchivo[]= "Archivo.bin";
	remove(nombreDelArchivo);
	int numero = LONGITUD_BLOQUE_PRUEBA;

	ArchivoDeBuckets* archivo = new ArchivoDeBuckets(nombreDelArchivo,numero);

	Bucket* bucket = this->crearBucket1();
	int numeroDeBucket1 = archivo->guardarBucket(bucket);
	delete bucket;

	bucket = this->crearBucket2();
	int numeroDeBucket2 = archivo->guardarBucket(bucket);
	delete bucket;

	bucket = this->crearBucket3();
	int numeroDeBucket3 = archivo->guardarBucket(bucket);
	delete bucket;

	bucket = this->crearBucket4();
	int numeroDeBucket4 = archivo->guardarBucket(bucket);
	delete bucket;

	archivo->liberarBucket(numeroDeBucket2);

	bucket = this->crearBucket5();
	int numeroDeBucket5 = archivo->guardarBucket(bucket);
	delete bucket;

	cout << endl ;

	cout << "Se muesta el bucket de la posicion: " << numeroDeBucket1 << endl;
	this->mostrarBucket(archivo,numeroDeBucket1);

	cout << "Se muesta el bucket de la posicion: " << numeroDeBucket3 << endl;
	this->mostrarBucket(archivo,numeroDeBucket3);

	cout << "Se muesta el bucket de la posicion: " << numeroDeBucket4 << endl;
	this->mostrarBucket(archivo,numeroDeBucket4);

	cout << "Se muesta el bucket de la posicion: " << numeroDeBucket5 << endl;
	this->mostrarBucket(archivo,numeroDeBucket5);

	delete archivo;
}


void TestArchivoDeBuckets::testAgotamiento(){
	char nombreDelArchivo[]= "Archivo.bin";
	remove(nombreDelArchivo);
	int numero = LONGITUD_BLOQUE_PRUEBA;
	int nb;
	int nb2;
	Distrito* d;
	ArchivoDeBuckets* archivo = new ArchivoDeBuckets(nombreDelArchivo,numero);

	for (int i = 0; i < 10000; i++){
		if (i == 5000)
			d = new Distrito("B");
		else
			d = new Distrito("A");

		Registro* r = new Registro(d);
		Bucket* b = new Bucket(0,numero);
		b->agregarRegistro(r);

		if (i==5000)
			nb = archivo->guardarBucket(b);
		else
			nb2 = archivo->guardarBucket(b);

		cout << "Bloque (" << i << ") almacenado en posicion :" << nb2 << endl;

		delete b;
		delete r;
		delete d;
	}

	cout << nb << endl;

	Bucket* buc = archivo->obtenerBucket(nb);
	cout << "cant regs" << buc->getCantidadDeRegistros() << endl;
	list<Registro*>::iterator it = buc->ubicarPrimero();
	Registro* reg = *it;
	Distrito* dis = (Distrito*)reg->getContenido();
	cout << "distrito: " << dis->getDistrito() << endl;
	delete archivo;
}

void TestArchivoDeBuckets::testLecturaEscrituraDeBuckets(){
	char nombreDelArchivo[]= "Archivo.bin";
	remove(nombreDelArchivo);
	int numero = LONGITUD_BLOQUE_PRUEBA;

	ArchivoDeBuckets* archivo = new ArchivoDeBuckets(nombreDelArchivo,numero);

	Distrito* distrito = new Distrito("Buenos Aires");
	string* serializacion = distrito->serializar();
	cout << "longitud: "<< serializacion->size() << endl;
	delete serializacion;

	Registro* registro = new Registro(distrito);
	serializacion = registro->serializar();
	cout << "longitud: "<< serializacion->size() << endl;
	delete serializacion;

	delete distrito;

	Bucket* bucket = new Bucket(0,numero);
	serializacion = bucket->serializar();
	cout << "longitud: "<< serializacion->size() << endl;
	delete serializacion;

	bucket->agregarRegistro(registro);
	serializacion = bucket->serializar();
	cout << "longitud: "<< serializacion->size() << endl;
	delete serializacion;

	delete registro;

	int numeroDeBucket1 = archivo->guardarBucket(bucket);
	delete bucket;

	bucket = archivo->obtenerBucket(numeroDeBucket1);

	distrito = new Distrito("Puerto Esperanza");
	serializacion = distrito->serializar();
	cout << "longitud: "<< serializacion->size() << endl;
	delete serializacion;

	registro = new Registro(distrito);
	serializacion = registro->serializar();
	cout << "longitud: "<< serializacion->size() << endl;
	delete serializacion;

	delete distrito;

	bucket->agregarRegistro(registro);
	serializacion = bucket->serializar();
	cout << "longitud: "<< serializacion->size() << endl;
	delete serializacion;

	delete registro;

	numeroDeBucket1 = archivo->guardarBucket(bucket);
	delete bucket;

	cout << "Se muesta el bucket de la posicion: " << numeroDeBucket1 << endl;
	this->mostrarBucket(archivo,numeroDeBucket1);

	delete archivo;
}
TestArchivoDeBuckets::~TestArchivoDeBuckets()
{
}


