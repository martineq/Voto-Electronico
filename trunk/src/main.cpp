#include "./Logica/InterfazAdministrador.h"
#include "./ClasesAuxiliares/Configuracion.h"

#include "../tests/TestMain.h"


#include <iostream>
using std::cout;
using std::endl;

int main(int argc,const char* argv[]) {

//	Pruebas del programa

//	TestMain mainTest;
//	mainTest.ejecutar();

//	TestEncriptacionVotante test;
//	test.principal();

//	Programa Principal

	Configuracion* conf = new Configuracion(argc,argv);
	Administrador* administrador = new Administrador(conf->pathPassword());

	InterfazAdministrador* interfaz = new InterfazAdministrador(conf);
	interfaz->ingresoAdministrador(administrador);

	delete conf;
	delete administrador;
	delete interfaz;

	cout << "\n** EXITO! **" << endl;
	return 0;
}

