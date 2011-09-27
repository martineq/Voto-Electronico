#ifndef TESTDISTRITO_H_
#define TESTDISTRITO_H_

#include <iostream>
#include <sstream>
#include <string>
#include <cxxtest/TestSuite.h>

#include "../src/Entidades/Distrito.h"

class testDistrito : public CxxTest::TestSuite
{
public:

	void testSerializar()
	{
		std::string ba = "Buenos Aires";
		Distrito* d = new Distrito(ba);
		std::string* s = d->serializar();

		std::stringstream stream(s->substr(0,3));
		int cantidad = stream.get();
		int size = ba.size();
		TS_ASSERT_EQUALS(cantidad,size);

		std::string s1 = s->substr(4,12);
		TS_ASSERT_EQUALS(s1,"Buenos Aires");
	}


	void testDeserializar()
	{
		// TODO: Implement testDeserializar() function.
	}

	void testGetTamanio(){
		Distrito* d = new Distrito("Buenos Aires");
		int size = d->getTamanio();
		int sizeSerializado = d->serializar()->size();
		TS_ASSERT_EQUALS(size,sizeSerializado);
	}

	void testDuplicar()
	{
		Distrito* d = new Distrito("Buenos Aires");
		Distrito* b = (Distrito*)d->duplicar();

		std::string stringB = *(b->serializar());

		int size = b->serializar()->size();
		TS_ASSERT_EQUALS(size,16);

		std::stringstream stream(b->serializar()->substr(0,3));
		int cantidad = stream.get();
		TS_ASSERT_EQUALS(cantidad,12);
		TS_ASSERT_EQUALS(b->serializar()->substr(4,16),"Buenos Aires");

		delete d;
		delete b;
	}

	void testHidratar()
	{
		Distrito* d = new Distrito("Buenos Aires");
		std::string* s = d->serializar();
		delete d;

		Distrito* b = (Distrito*)Distrito::hidratar(s);
		TS_ASSERT_EQUALS(d->getDistrito(),"Buenos Aires");
		delete b;
	}

};

#endif /*TESTDISTRITO_H_*/
