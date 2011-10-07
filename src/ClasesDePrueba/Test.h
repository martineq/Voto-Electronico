#include "../Archivos/Hashing/Registro.h"
#include "../Archivos/Hashing/ArchivoDeBuckets.h"
#include "../Archivos/Hashing/HashingExtensible.h"
#include "../Archivos/Hashing/Bucket.h"
#include "../Entidades/Distrito.h"

#ifndef TEST_H_
#define TEST_H_

class Test {
public:
	Test();

	//	pruebas para serializar y deserializar
	void serializarDeserializarRegistro();
	void pruebaAgregarRegistrosHashingExtensible();
	void testBucket();
	void testArchivoDeBuckets();
	virtual ~Test();
};

#endif /* TEST_H_ */
