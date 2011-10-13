#ifndef TESTREGISTRODISTRITO_H_
#define TESTREGISTRODISTRITO_H_

#include "../logica/Archivos/Hashing/Registro.h"
#include "../logica/Entidades/Distrito.h"
#include "../logica/Entidades/NombreDeEntidad.h"

class TestRegistroDistrito{

public:

	void testDeserializar()
	{
		string ciudad = "Buenos Aires";
		int sizeCiudad = ciudad.size();
		Distrito* distrito = new Distrito(ciudad);
		Registro* registro = new Registro(distrito);

		string* distritoSerializado = distrito->serializar();
		delete distrito;

		string* s = registro->serializar();
		delete registro;

		Registro* nuevoRegistro = new Registro();
		nuevoRegistro->deserializar(s);

//		TS_ASSERT_EQUALS(nuevoRegistro->obtenerClave(),sizeCiudad);

		Entidad* entidad = nuevoRegistro->getContenido();
		string* entidadSerializada = entidad->serializar();

//		TS_ASSERT_EQUALS(*entidadSerializada,*distritoSerializado);

		delete nuevoRegistro;
		delete entidad;
		delete entidadSerializada;
		delete distritoSerializado;
		delete s;
	}

	void testSetContenido()
	{
		// TODO: Implement testSetContenido() function.
	}

	void testDuplicar()
	{
		// TODO: Implement testDuplicar() function.
	}

	void testGetTamanio()
	{
		// TODO: Implement testGetTamanio() function.
	}

	void testObtenerClave()
	{
		// TODO: Implement testObtenerClave() function.
	}

	void testSerializar()
	{
		string ciudad = "Buenos Aires";
		int sizeCiudad = ciudad.size();
		Distrito* distrito = new Distrito(ciudad);
		Registro* registro = new Registro(distrito);

		string* distritoSerializado = distrito->serializar();
		int		dimensionDistritoSerializado = distrito->getTamanio();
		delete distrito;


		string* s = registro->serializar();
		delete registro;

		stringstream streamTipoEntidad(s->substr(0,3));
		int tipoEntidad = streamTipoEntidad.get();
//		TS_ASSERT_EQUALS(tipoEntidad,tDistrito);

		stringstream streamLongitudRegistro(s->substr(4,7));
		int longitudRegistro = streamLongitudRegistro.get();
//		TS_ASSERT_EQUALS(longitudRegistro,dimensionDistritoSerializado);

//		TS_ASSERT_EQUALS(s->substr(8,8+sizeCiudad-1),*distritoSerializado);

		delete s;
		delete distritoSerializado;
	}

	void testGetContenido()
	{
		// TODO: Implement testGetContenido() function.
	}

};

#endif /*TESTREGISTRODISTRITO_H_*/
