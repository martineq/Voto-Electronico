#include "../src/Archivos/Hashing/HashingExtensible.h"
#include "../src/Archivos/Hashing/ArchivoDeBuckets.h"
#include "../src/Archivos/Hashing/Bucket.h"
#include "../src/Archivos/Hashing/Registro.h"
#include "../src/Entidades/Distrito.h"

#ifndef TESTHASHINGEXTENSIBLE_H_
#define TESTHASHINGEXTENSIBLE_H_

class TestHashingExtensible {
private:
	void verContenidoBucketDistrito(Bucket* bucket);

public:
	TestHashingExtensible();
	void testAgregarRegistros();
	void testObtenerRegistro();
	virtual ~TestHashingExtensible();
};

#endif /* TESTHASHINGEXTENSIBLE_H_ */
