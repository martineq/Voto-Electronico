/*
 * Pruebas.cpp
 *
 *  Created on: 17/09/2011
 *      Author: mart
 */

#include "Pruebas.h"

Pruebas::Pruebas() {

}

int Pruebas::holaMundo(){

    cout<<"||TP 1||\n--------\n\nHola Mundo!!!\n";
    // int i; for (i=0;i<argc;i++){ cout<<"\nParámetro ["<<i<<"]: "<<argv[i];  }
    cout<<"\n\nBueno, chau...\n";
    return 0;
}


int Pruebas::serializarCargo(){

	Cargo* cargo1 = new Cargo("Presidente   1");
	Cargo* cargo2 = new Cargo();
	list<string> listas1;
	list<string> listas2;

	cout << "Cargo: " << cargo1->getCargo() <<endl;
	cargo1->agregarCargo("Vicepresidente");
	cargo1->agregarCargo("Senador");
	listas1 = cargo1->devolverSubCargos();
	list<string>::iterator it1 = listas1.begin();
	while (it1 != listas1.end()){
		cout << "SubCargo: "<< (*it1) <<endl;
		it1++;
	}
	string* source = cargo1->serializar();

	cout <<endl<<endl<<endl;

	cout<<"Size blabla: "<<cargo2->devolverSubCargos().size()<<endl;
	cargo2->deserializar(source);
	cout << "Cargo 2: " << cargo2->getCargo() <<endl;
	listas2 = cargo2->devolverSubCargos();
	list<string>::iterator it2 = listas2.begin();
	cout << "Size lista 2: "<< listas2.size()<<endl;
	while (it2 != listas2.end()){
		cout << "SubCargo: "<< (*it2) <<endl;
		it2++;
	}

    cout<<"\nFin prueba: Serializar Cargo\n";

	cout << "Fin" <<endl;
    return 0;

}

int Pruebas::cargaVotante(){

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

Pruebas::~Pruebas() {

}
