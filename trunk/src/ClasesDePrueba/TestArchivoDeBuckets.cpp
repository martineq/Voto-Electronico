#include "TestArchivoDeBuckets.h"

Bucket* TestArchivoDeBuckets::crearBucket1(){
	Bucket* bucket = new Bucket(0);
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
	Bucket* bucket = new Bucket(0);
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
	Bucket* bucket = new Bucket(0);
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
	Bucket* bucket = new Bucket(0);
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
	Bucket* bucket = new Bucket(0);
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

	int cantRegistros = bucketNuevo->getCantidadDeRegistros();

	list<Registro*>::iterator it = bucketNuevo->ubicarPrimero();
	for(int i =0; i <cantRegistros;i++){
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

void TestArchivoDeBuckets::testAltaBajaDeBucketsEnArchivoDeBuckets(){
	std::remove("Archivo.bin");
	ArchivoDeBuckets* archivo = new ArchivoDeBuckets("Archivo.bin",100);

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

	cout << "El siguiente bucket fue borrado, verificar comportamiento" << endl;
	cout << "Se muesta el bucket de la posicion: " << numeroDeBucket2 << endl;
	this->mostrarBucket(archivo,numeroDeBucket2);
	delete archivo;
}

TestArchivoDeBuckets::~TestArchivoDeBuckets()
{
}


