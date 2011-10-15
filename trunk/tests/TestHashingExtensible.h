#include <iostream>
#include <string>
#include "../src/Archivos/Hashing/HashingExtensible.h"
#include "../src/Archivos/Hashing/ArchivoDeBuckets.h"
#include "../src/Archivos/Hashing/Bucket.h"
#include "../src/Archivos/Hashing/Registro.h"
#include "../src/Entidades/Votante.h"
#include "../src/Entidades/Distrito.h"

#ifndef TESTHASHINGEXTENSIBLE_H_
#define TESTHASHINGEXTENSIBLE_H_

class TestHashingExtensible {
private:
	HashingExtensible* inicializarArchivosDePrueba();
	HashingExtensible* inicializarArchivosDePruebaSinBorrarExistentes();
	void verContenidoBucketDistrito(Bucket* bucket);
	void cargarRegistros(HashingExtensible* he);

public:
	TestHashingExtensible();
	void testSimple();
	void testAgregarRegistros1();
	void testAgregarRegistros2();
	void testObtenerRegistro();
	void testEliminarRegistro();
	void testEliminarRegistrosReduciendoTablaDehash();
	void testEliminarRegistrosYBucketSinReducirTabladeHash();
	void testModificarRegistroInexistente();
	void testModificarRegistroExistente();
	void testModificarRegistroConRedispersion();
	void testCargarYmostrarContenidoDelArchivo();
	virtual ~TestHashingExtensible();
};

#endif /* TESTHASHINGEXTENSIBLE_H_ */
