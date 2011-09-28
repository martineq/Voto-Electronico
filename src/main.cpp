#include <iostream>
#include <list>
#include "Pruebas.h"
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
	prueba->pruebaReemplazarRegistroEnBucket();
//	prueba->serializarBucket();
//	prueba->deserializarBucket();

//	Pruebas de Hashing!
//	prueba->pruebaAgregarRegistrosHashingExtensible();

//  Pruebas de serializar y deserializar entidades!
//	prueba->serializarDeserializarCargo();
//	prueba->serializarDeserializarVotante();
//	prueba->serializarDeserializarDistrito();
//	prueba->serializarDeserializarLista();
//	prueba->serializarDeserializarEleccion();
//	prueba->serializarDeserializarCandidato();

//  Prueba que funciona el eclipse!
//	prueba->holaMundo();

	delete prueba;
	return 0;
}


