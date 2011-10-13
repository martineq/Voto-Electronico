#include "../src/Archivos/Hashing/Registro.h"
#include "../src/Archivos/Hashing/ArchivoDeBuckets.h"
#include "../src/Archivos/Hashing/HashingExtensible.h"
#include "../src/Archivos/Hashing/Bucket.h"
#include "../src/Entidades/Distrito.h"

#ifndef TEST_H_
#define TEST_H_

class Test {
public:
	Test();

	//	pruebas para serializar y deserializar
	void testStringstream();
	void testConvertir();
	void serializarDeserializarRegistro();
	void testBucket();
	virtual ~Test();
};

#endif /* TEST_H_ */
