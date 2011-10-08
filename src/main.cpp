#include <iostream>
#include <list>
#include "Pruebas.h"
#include "./ClasesDePrueba/Test.h"
using namespace std;

	/*
	 * Para probar en el main crear el código correspondiente
	 * en una función nueva dentro de la clase "Pruebas", para
	 * luego invocarlo con "prueba.<nombreDeLaPrueba>()".
	 */
int main(int argc,char* argv[]) {

//	Test test;
//	test.testArchivoDeBuckets();
//	test.serializarDeserializarRegistro();

//	Pruebas de Hashing!
//	test.pruebaAgregarRegistrosHashingExtensible();
//	test.testBucket();

	Pruebas* prueba = new Pruebas();


//	Pruebas de Bucket!
//	prueba->pruebaAgregarRegistrosAlBucket();
//	prueba->pruebaEliminarRegistrosDelBucket();
//	prueba->pruebaReemplazarRegistroEnBucket();
//	prueba->serializarDeserializarBucket();

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

	cout << "\n\n** EXITO! **" << endl;
	return 0;
}


