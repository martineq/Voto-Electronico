#include "TestMain.h"

void TestMain::ejecutar(){
	int fail = 0;
	int exito = 0;

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
//	testArchivoDeBuckets.testConteo();
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

//	Pruebas de votante aleatorio
//	TestVotanteAleatorio testVotanteAleatorio;
//	testVotanteAleatorio.crearArchivoDeVotantes();

//	Pruebas de simulacion de sistema de votacion
//	SimulacionSistema sistema(argc,argv);
//	sistema.main();

//	CRIPTOGRAFIA ************************************************ //

//	RSA

//	RSA rsa;
//	rsa.generarPyQ();
//	rsa.calcularN();
//	rsa.calcularPhi();
//	rsa.calcularE();
//	int numero = 46;
//	long long numeroEncriptado = rsa.encriptar(numero);
//	rsa.desencriptar(numeroEncriptado);
//	rsa.atacar();

//	Prueba encriptacion y desencriptacion de votante

//	TestEncriptacionVotante testRSAVotante;
//	testRSAVotante.principal();

//	Test Vigenere
	TestVigenere testVigenere;

	testVigenere.testCifrado()==0 ? exito++ : fail++;
	testVigenere.testEnBloques()==0 ? exito++ : fail++;
	testVigenere.testCifradoCadenaLarga()==0 ? exito++ : fail++;

//	Test Kasiski
	TestKasiski	testKasiski;
	testKasiski.testObtenerClaveDeVigenere()==0 ? exito++ : fail++;

//	Mensaje final

	if (fail != 0 )
		cout << "Fallaron: " << fail << " pruebas " << endl;
	else
		cout << "Todas las pruebas resultaron exitosas." << endl;

	cout << "Pasaron " << exito << " pruebas exitosamente." << endl;

}

TestMain::TestMain() {}
TestMain::~TestMain() {}

