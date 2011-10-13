#ifndef TESTARCHIVOBLOQUES_H_
#define TESTARCHIVOBLOQUES_H_

#include "../logica/Archivos/EnBloques/ArchivoBloques.h"

class TestArchivoBloques{

public:

	void testObtenerBloque()
	{

		char nombreDeArchivo[] = "archivoBloques.bin";
		int dimensionBloque = 100;

		remove(nombreDeArchivo);
		ArchivoBloques* archivo = new ArchivoBloques(nombreDeArchivo,dimensionBloque);

		char bucket1[] = "Buenos Aires";

		int nrr;
		archivo->crearNuevoBloque(&nrr);
		archivo->guardarBloque(nrr,bucket1);

		char* bucket2 = new char[dimensionBloque];

		cout << endl << "test 1 obtener bloque válido" << endl;

		archivo->obtenerBloque(nrr,bucket2);

		cout << bucket2 << endl;

		delete[] bucket2;

		cout << endl << "test 2 creamos 3 nuevos bloques en el archivo y luego eliminamos 1 y lo volvemos a acceder";

		char bucket5[] = "Puerto Esperanza";

		archivo->crearNuevoBloque(&nrr);
		archivo->guardarBloque(nrr,bucket5);

		cout << endl << bucket5 << " en nrr: " << nrr <<endl;

		char bucket6[] = "Bahia Blancaaa";

		int nrr6;
		archivo->crearNuevoBloque(&nrr6);
		archivo->guardarBloque(nrr6,bucket6);

		cout << endl << bucket6 << " en nrr: " << nrr6 <<endl;

		char bucket7[] = "Usuahia";

		archivo->crearNuevoBloque(&nrr);
		archivo->guardarBloque(nrr,bucket7);

		cout << endl << bucket7 << " en nrr: " << nrr <<endl;

		archivo->borrarBloque(nrr6);

		cout << endl << "se elimino el bloque de " << bucket6 << " liberando el nrr: " << nrr6 << endl;

		char bucket8[] = "Montevideo";

		archivo->crearNuevoBloque(&nrr);
		archivo->guardarBloque(nrr,bucket8);

		cout << endl << bucket8 << " en nrr: " << nrr <<endl;

		cout << endl << "test 3 obtener un bloque que fue liberado" << endl;

		archivo->borrarBloque(nrr);
		cout << endl << "se elimino el bloque de " << bucket8 << " liberando el nrr: " << nrr << endl;

		char* bucket9 = new char[dimensionBloque];
		archivo->obtenerBloque(nrr,bucket9);

		cout << bucket9 << endl;
		delete[] bucket9;

		cout << endl << "test 4 obtener bloque invalido por exceso" << endl;

		nrr = 10000;
		char* bucket3 = new char[dimensionBloque];
		archivo->obtenerBloque(nrr,bucket3);
		cout << bucket3 << endl;

		delete bucket3;

		cout << endl << "test 5 obtener bloque invalido con valores negativos" << endl;

		nrr = -10000;
		char* bucket4 = new char[dimensionBloque];
		archivo->obtenerBloque(nrr,bucket3);

		cout << bucket4 << endl;

		delete bucket4;

		delete archivo;




	}

	void testCrearNuevoBloque()
	{
		// TODO: Implement testCrearNuevoBloque() function.
	}

	void testBorrarBloque()
	{
		// TODO: Implement testBorrarBloque() function.
	}

	void testGuardarBloque()
	{
		// TODO: Implement testGuardarBloque() function.
	}

	void testCerrarArchivo()
	{
		// TODO: Implement testCerrarArchivo() function.
	}

	void testInfoInts()
	{
		// TODO: Implement testInfoInts() function.
	}

};

#endif /*TESTARCHIVOBLOQUES_H_*/
