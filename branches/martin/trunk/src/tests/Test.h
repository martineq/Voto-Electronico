#include "../logica/Archivos/Hashing/Registro.h"
#include "../logica/Archivos/Hashing/ArchivoDeBuckets.h"
#include "../logica/Archivos/Hashing/HashingExtensible.h"
#include "../logica/Archivos/Hashing/Bucket.h"
#include "../logica/Entidades/Distrito.h"

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
