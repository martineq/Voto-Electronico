/*
 * Test.cpp
 *
 *  Created on: 29/09/2011
 *      Author: lÑ#$dsa44
 */

#include "Test.h"
#include <string>
#include <cstdio>

Test::Test() {
	// TODO Auto-generated constructor stub

}

void Test::serializarDeserializarRegistro()
{
	Distrito* d = new Distrito("Buenos Aires");
	Registro* r = new Registro(d);
	delete(d);

	string* registroSerializado = r->serializar();
	delete (r);

	Registro *prueba = new Registro();
	prueba->deserializar(registroSerializado);

	Distrito* d2 = (Distrito*)prueba->getContenido();
	std::cout << d2->getDistrito() << std::endl;

	delete(prueba);
	delete(d2);
}

Test::~Test() {
	// TODO Auto-generated destructor stub
}

