#include <iostream>
#include <list>
#include "../tests/Pruebas.h"
#include "../tests/SimulacionSistema.h"
#include "../tests/TestHashingExtensible.h"
#include "./Logica/InterfazAdministrador.h"
#include "./ClasesAuxiliares/Configuracion.h"


using namespace std;

	/*
	 * Para probar en el main crear el código correspondiente
	 * en una función nueva dentro de la clase "Pruebas", para
	 * luego invocarlo con "prueba.<nombreDeLaPrueba>()".
	 */
int main(int argc,const char* argv[]) {

//	Pruebas* prueba = new Pruebas();

//	Pruebas de Bucket!
//	prueba->pruebaAgregarRegistrosAlBucket();
//	prueba->pruebaEliminarRegistrosDelBucket();
//	prueba->pruebaReemplazarRegistroEnBucket();
//	prueba->serializarDeserializarBucket();

//  Pruebas de serializar y deserializar entidades!
//	prueba->serializarDeserializarVotante();
//	prueba->serializarDeserializarDistrito();
//	prueba->serializarDeserializarCargo();
//	prueba->serializarDeserializarCandidato();
//	prueba->serializarDeserializarLista();
//	prueba->serializarDeserializarEleccion();

//	Pruebas para el Archivo en Bloques:
//	prueba->pruebaArchivoBloques();
//	prueba->SerializarGuardarEnBloqueHidratar();

//	Pruebas para el Árbol B+:
//	prueba->pruebaBMas();
//	prueba->pruebaBMasCarga(); // No usar esta por ahora.
//	prueba->pruebaBMasAuto();

//	pruebas para argumentos y archivo de configuración
//	prueba->pruebaConfiguracion(argc,argv);

//  Prueba que funciona el eclipse!
//	prueba->holaMundo();

//	delete (prueba);

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
//	testArchivoDeBuckets.testVotante();
//	testArchivoDeBuckets.testCargo();
//	testArchivoDeBuckets.tests();
//	testArchivoDeBuckets.testLecturaEscrituraDeBuckets();
//	testArchivoDeBuckets.testAltaBajaDeBucketsEnArchivoDeBuckets();

//	Pruebas de Hashing!
//	TestHashingExtensible the;
//	the.testAgregarRegistros1();
//	the.testCargarYmostrarContenidoDelArchivo();
//	the.testAgregarRegistros2();
//	the.testObtenerRegistro();
//	the.testEliminarRegistro();
//	the.testEliminarRegistrosReduciendoTablaDehash();
//	the.testEliminarRegistrosYBucketSinReducirTabladeHash();
//	the.testModificarRegistroInexistente();
//	the.testModificarRegistroExistente();
//	the.testModificarRegistroConRedispersion();
//	the.testSimple();

//	Pruebas de simulacion de sistema
//	SimulacionSistema sistema(argc,argv);
//	sistema.main();

//	Pruebas de interfaz

	Configuracion* conf = new Configuracion(argc,argv);

	string pathPassword = conf->pathPassword() + ".bin";

	Administrador* administrador = new Administrador(pathPassword);

	InterfazAdministrador* interfaz = new InterfazAdministrador(conf);
	interfaz->ingresoAdministrador(administrador);

	delete conf;
	delete administrador;
	delete interfaz;
	return 0;
}

