/*
 * Test.cpp
 *
 *  Created on: 29/09/2011
 *      Author: lÑ#$dsa44
 */

#include "Test.h"
#include <string>
#include <cstring>
#include <cstdio>

Test::Test() {
	// TODO Auto-generated constructor stub

}


std::string* charToString(char* cadena,int tamanio){
	std::string* nuevoString = new std::string(cadena);
	return nuevoString;
}

char* stringToChar(std::string* cadena){

	int numero = cadena->size();
	char* nuevaCadena = new char[numero+1];

	for(int i = 0; i < numero ; i++){
		nuevaCadena[i]=cadena->at(i);
	}
	nuevaCadena[numero] = '\0';

	return nuevaCadena;
}

void Test::testStringstream(){

	int espacioLibre = 15;
	int tamanioDeDispersion = 400;
	string cadena = "Buenos Aires";

	stringstream buffer;

	cout << buffer << endl;

	buffer.write((char*)&espacioLibre,TAM_INT);
	cout << "tamanio de int " << TAM_INT << endl;
	cout << "Se cargo el espacio libre: " << (char)espacioLibre << endl;

	buffer.write((char*)&tamanioDeDispersion,TAM_INT);
	cout << "Se cargo el tamanio de dispersion: " << (char)tamanioDeDispersion << endl;

	buffer.write(cadena.c_str(),cadena.size());
	cout << "Se cargo el registro en buffer: " << cadena << endl;

	string* datos2 = new string( buffer.str() );

	cout << *datos2 << " string serializado " << endl;
	char* cad = new char[datos2->size()];
	memcpy(cad,datos2->c_str(),datos2->size());


	stringstream stream;
	stream.write(cad,datos2->size());

	string s = stream.str();
	cout << s << " inversa "<< endl;
	cout << s.size() << endl;


	int a;
	stream.read((char*)&a,4);
	cout << a << endl;


	int b;
	stream.read((char*)&b,4);
	cout << b << endl;

	string s2 = (stream.str()).substr(8,19);
	cout << s2 << endl;

	delete(datos2);

	cout << "FIN" << endl;

}


void Test::testConvertir(){
	string* cadena = new string("Buenos Aires");

	char* nuevaCadena = stringToChar(cadena);

	cout << nuevaCadena << endl;

	char* iterador = nuevaCadena;
	int size = 0;
	while (*iterador != '\0'){
		cout << *iterador;
		iterador++;
		size++;
	}

	delete cadena;

	string* nuevoString = charToString(nuevaCadena,size);

	cout << endl << "nuevoString: " << *nuevoString << endl;

	delete nuevaCadena;
	delete nuevoString;
}


void Test::serializarDeserializarRegistro()
{
	Distrito* d = new Distrito("Buenos Aires");
	Registro* r = new Registro(d);
	delete(d);

	string* registroSerializado = r->serializar();
	delete r;

	Registro *prueba = new Registro();
	prueba->deserializar(registroSerializado);
	delete registroSerializado;

	Distrito* d2 = (Distrito*)prueba->getContenido();
	delete(prueba);

	std::cout << d2->getDistrito() << std::endl;
	delete(d2);
}

void Test::pruebaAgregarRegistrosHashingExtensible(){
	ArchivoDeBuckets* archivo = new ArchivoDeBuckets("archiv.bin",50);

	HashingExtensible* he = new HashingExtensible(archivo);

	string distritos[] = {"Buenos Aires","Puerto Esperanza","Bahia Blancaaaaa","ushuaia"};

	for (int i=0; i < 4 ;i++){
		Distrito* distrito = new Distrito(distritos[i]);
		Registro* registro = new Registro(distrito);

		cout << "Se agrega un registro al hashing" << endl;
		he->agregarRegistro(registro);
		delete(distrito);
		delete(registro);
	}

	Bucket* bucket = he->obtenerBucket(0);
	cout << "cantidad de registrosen Bucket: " << bucket->getCantidadDeRegistros() << endl;
	list<Registro*>::iterator it = bucket->ubicarPrimero();
	int n = bucket->getCantidadDeRegistros();
	for(int i = 0; i <n;i++ ){
		Registro* unRegistro = *it;
		Distrito* unDistrito = (Distrito*)unRegistro->getContenido();
		cout << "Distrito: " << unDistrito->getDistrito() << endl;
		it++;
	}

	delete(archivo);
	delete(he);
}

void Test::testBucket(){
	Bucket* bucket = new Bucket(0);
	string distritos[] = {"Buenos Aires","Puerto Esperanza","Bahia Blancaaaaa","ushuaia"};

	for (int i=0; i < 4 ;i++){
		Distrito* distrito = new Distrito(distritos[i]);
		Registro* registro = new Registro(distrito);
		delete(distrito);

		bucket->agregarRegistro(registro);
		delete(registro);
	}

	string* bucketSerializado = bucket->serializar();
	delete bucket;

	Bucket* bucketNuevo = new Bucket(0);
	bucketNuevo->deserializar(bucketSerializado);

	int cantRegistros = bucket->getCantidadDeRegistros();

	list<Registro*>::iterator it = bucket->ubicarPrimero();
	for(int i =0; i <cantRegistros;i++){
		Registro* registro = *it;
		Distrito* d = (Distrito*)registro->getContenido();
		cout << d->getDistrito() << endl;
		delete d;
		it++;
	}

	delete bucketNuevo;
}

void Test::testArchivoDeBuckets(){
	Bucket* bucket = new Bucket(0);
	string distritos[] = {"Buenos Aires","Puerto Esperanza","Bahia Blancaaaaa","ushuaia"};

	for (int i=0; i < 4 ;i++){
		Distrito* distrito = new Distrito(distritos[i]);
		Registro* registro = new Registro(distrito);
		delete(distrito);

		bucket->agregarRegistro(registro);
		delete(registro);
	}

	std::remove("Archivo.bin");
	ArchivoDeBuckets* archivo = new ArchivoDeBuckets("Archivo.bin",100);
	int numeroDeBucket = archivo->guardarBucket(bucket);
	delete bucket;

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
		delete archivo;
}

Test::~Test() {
	// TODO Auto-generated destructor stub
}

