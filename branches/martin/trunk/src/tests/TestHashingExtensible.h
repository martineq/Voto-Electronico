#include "../logica/Archivos/Hashing/HashingExtensible.h"
#include "../logica/Archivos/Hashing/ArchivoDeBuckets.h"
#include "../logica/Archivos/Hashing/Bucket.h"
#include "../logica/Archivos/Hashing/Registro.h"
#include "../logica/Entidades/Distrito.h"

#ifndef TESTHASHINGEXTENSIBLE_H_
#define TESTHASHINGEXTENSIBLE_H_

class TestHashingExtensible {
private:
	void verContenidoBucketDistrito(Bucket* bucket);
	void cargarRegistros(HashingExtensible* he);
public:
	TestHashingExtensible();
	void testAgregarRegistros();
	void testObtenerRegistro();
	void testEliminarRegistro();
	void testEliminarRegistrosReduciendoTablaDehash();
	void testEliminarRegistrosYBucketSinReducirTabladeHash();
	void testModificarRegistroInexistente();
	void testModificarRegistroExistente();
	void testModificarRegistroConRedispersion();
	virtual ~TestHashingExtensible();
};

#endif /* TESTHASHINGEXTENSIBLE_H_ */
