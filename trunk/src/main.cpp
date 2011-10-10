#include <iostream>
#include <list>
#include "Pruebas.h"
#include "../tests/Test.h"
#include "../tests/TestArchivoBloques.h"
#include "../tests/TestArchivoDeBuckets.h"
#include "../tests/TestHashingExtensible.h"

using namespace std;

	/*
	 * Para probar en el main crear el código correspondiente
	 * en una función nueva dentro de la clase "Pruebas", para
	 * luego invocarlo con "prueba.<nombreDeLaPrueba>()".
	 */
int main(int argc,char* argv[]) {

	Pruebas* prueba = new Pruebas();

//	Pruebas de Bucket!
//	prueba->pruebaAgregarRegistrosAlBucket();
//	prueba->pruebaEliminarRegistrosDelBucket();
//	prueba->pruebaReemplazarRegistroEnBucket();
	prueba->serializarDeserializarBucket();

//  Pruebas de serializar y deserializar entidades!
//	prueba->serializarDeserializarCargo();
//	prueba->serializarDeserializarVotante();
//	prueba->serializarDeserializarDistrito();
//	prueba->serializarDeserializarLista();
//	prueba->serializarDeserializarEleccion();
//	prueba->serializarDeserializarCandidato();

//	Pruebas para el Archivo en Bloques:
//	prueba->pruebaArchivoBloques();

//  Prueba que funciona el eclipse!
//	prueba->holaMundo();

	delete (prueba);

//	Test test;
//	test.testStringstream();
//	test.testConvertir();
//	test.testArchivoDeBuckets();
//	test.serializarDeserializarRegistro();
//	test.testBucket();

//	Pruebas Archivo de Bloques
//	TestArchivoBloques ab;
//	ab.testObtenerBloque();

//	Pruebas Archivo de Buckets
//	TestArchivoDeBuckets testArchivoDeBuckets;
//	testArchivoDeBuckets.testAltaBajaDeBucketsEnArchivoDeBuckets();

//	Pruebas de Hashing!
//	TestHashingExtensible the;
//	the.testAgregarRegistros();

	cout << "\n\n** EXITO! **" << endl;
	return 0;
}


