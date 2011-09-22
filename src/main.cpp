#include <iostream>
#include <list>
#include "Pruebas.h"

using namespace std;

int main(int argc,char* argv[])
{
	Pruebas prueba;

	//prueba.holaMundo();
	prueba.serializar();
	Votante* votante1 = new Votante (32299496,"Daniel Shlufman","32299496","San Juan 124","Recoleta");
	votante1->agregarEleccion("271011","Presidente");
	votante1->agregarEleccion("100297","Gobernador");
	votante1->agregarEleccion("221199","Intendente");
	votante1->agregarEleccion("160500","Diputado Nacional");
	votante1->agregarEleccion("190603","Diputado Provincial");
	votante1->agregarEleccion("040705","Senador");
	votante1->agregarEleccion("040705","Jefe De Comuna");
	string* datos = votante1->serializar();
	votante1->deserializar(datos);
	votante1->verVotante();
	delete (votante1);


	cout << "Sonrie la vida es bella" << endl;
	return 0;

}

