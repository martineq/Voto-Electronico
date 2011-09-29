#include "../Archivos/Hashing/Registro.h"
#include "../Entidades/Distrito.h"

#ifndef TEST_H_
#define TEST_H_

class Test {
public:
	Test();

	//	pruebas para serializar y deserializar
	void serializarDeserializarRegistro();

	virtual ~Test();
};

#endif /* TEST_H_ */
