/*
 * Test.cpp
 *
 *  Created on: 29/09/2011
 *      Author: lÑ#$dsa44
 */

#include "Test.h"
#include <string>
#include <cstdio>

Test::Test() {
	// TODO Auto-generated constructor stub

}

void Test::serializarDeserializarRegistro()
{
	Distrito* d = new Distrito("Buenos Aires");
	Registro* r = new Registro(d);
	delete(d);

	string* registroSerializado = r->serializar();
	delete (r);

	Registro *prueba = new Registro();
	prueba->deserializar(registroSerializado);

	Distrito* d2 = (Distrito*)prueba->getContenido();
	std::cout << d2->getDistrito() << std::endl;

	delete(prueba);
	delete(d2);
}

void Test::pruebaAgregarRegistrosHashingExtensible(){
	ArchivoDeBuckets* archivo = new ArchivoDeBuckets("archiv.bin",50);

	HashingExtensible* he = new HashingExtensible(archivo);

	string distritos[] = {"Buenos Aires","Puerto Esperanza","Bahia Blancaaaaa","ushuaia"};

	for (int i=0; i < 4 ;i++){
		Distrito* distrito = new Distrito(distritos[i]);
		Registro* registro = new Registro(distrito);

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

Test::~Test() {
	// TODO Auto-generated destructor stub
}

