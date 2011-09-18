/*
 * Pruebas.cpp
 *
 *  Created on: 17/09/2011
 *      Author: mart
 */

#include "Pruebas.h"

Pruebas::Pruebas() {
	// TODO Auto-generated constructor stub
}

int Pruebas::holaMundo(){

    cout<<"||TP 1||\n--------\n\nHola Mundo!!!\n";

    cout << "Daniel Shlufman padron 88040 - Saludos!" << endl;
    cout << "Martín Eduardo Quiroz padron 86012 - Eclipse" << endl;

    // int i; for (i=0;i<argc;i++){ cout<<"\nParámetro ["<<i<<"]: "<<argv[i];  }

    cout<<"\n\nBueno, chau...\n";
    return 0;
}


int Pruebas::serializar(){

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



	cout << "Fin" <<endl;
    return 0;

}

Pruebas::~Pruebas() {
	// TODO Auto-generated destructor stub
}
