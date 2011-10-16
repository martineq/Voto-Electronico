/*
 * CreadorVotante.cpp
 *
 *  Created on: 10/10/2011
 *      Author: lucas
 */

#include "CreadorVotante.h"
//#include "../doc/Nombres.txt"
#include <stdlib.h>
#include <time.h>

CreadorVotante::CreadorVotante() {
	// TODO Auto-generated constructor stub

}

string CreadorVotante::getNombre(){
	string linea;
    fstream archivo;
    archivo.open ("./trunk/doc/Nombres.txt", ios::in);
    int cantLineas = this->getCantLineas("./trunk/doc/Nombres.txt");
    if (archivo.is_open()) {
       int cont = 0;
       srand ( time(NULL) );
       int pos = rand() % cantLineas;
       while ( archivo.good() and (cont < pos))
       {
    	   cont = cont + 1;
    	   getline(archivo,linea);
       }
       cout <<"Nombre elegido: "<<linea<<endl;
       archivo.close();
    }
     return linea;

}


string CreadorVotante::getApellido(){
	string linea;
    fstream archivo;
    int cantLineas = this->getCantLineas("./trunk/doc/Apellidos.txt");
    archivo.open ("./trunk/doc/Apellidos.txt", ios::in);
    if (archivo.is_open()) {
       int cont = 0;
       srand ( time(NULL) );
       int pos = rand() % cantLineas;
       while ( archivo.good() and (cont < pos))
       {
    	   cont++;
    	   getline(archivo,linea);
       }
       cout <<"Apellido elegido: "<<linea<<endl;
       archivo.close();
    }
     return linea;
}

int CreadorVotante::getDNI(){
    srand ( time(NULL) );
    int pos = rand() % 40000000;
    cout << "DNI: "<<pos<<endl;
   return pos;
}

string CreadorVotante::getDistrito(){
	string linea;
    fstream archivo;
    int cantLineas = this->getCantLineas("./trunk/doc/Distritos.txt");
    archivo.open ("./trunk/doc/Distritos.txt", ios::in);
    if (archivo.is_open()) {
       int cont = 0;
       srand ( time(NULL) );
       int pos = rand() % cantLineas;
       while ( archivo.good() and (cont < pos))
       {
    	   cont = cont + 1;
    	   getline(archivo,linea);
       }
       cout <<"Distrito elegido: "<<linea<<endl;
       archivo.close();
    }
     return linea;

}

string CreadorVotante::getDomicilio(){
	string linea;
    fstream archivo;
    stringstream miString;
    int cantLineas = this->getCantLineas("./trunk/doc/Domicilios.txt");
    archivo.open ("./trunk/doc/Domicilios.txt", ios::in);
    if (archivo.is_open()) {
       int cont = 0;
       srand ( time(NULL) );
       int pos = rand() % cantLineas;
       while ( archivo.good() and (cont < pos))
       {
    	   cont = cont + 1;
    	   getline(archivo,linea);
       }
       int altura = rand() % 5000;
       miString << altura;
       linea = linea+" "+miString.str();
       cout <<"Domicilio elegido: "<<linea<<endl;
       archivo.close();
    }
     return linea;
}

string CreadorVotante::getClave(){
    stringstream miString;
    string passString;
    srand ( time(NULL) );
    int password = rand() % 10000;
    miString << password;
    passString = miString.str();
    while (passString.size() < 4) {
    	passString = "0"+passString;
    }

    cout << "Password: "<<passString<<endl;
    return passString;
}

int CreadorVotante::getCantLineas(string path){
    int cantLineas = 0;
    string linea;
    fstream archivo;
    archivo.open (path.c_str(), ios::in);
    while (archivo.good()){
    	getline(archivo,linea);
    	cantLineas++;
    }
    archivo.close();
    return cantLineas;
}

Votante* CreadorVotante::crearVotante(){
	string nombre = this->getNombre();
	string apellido = this->getApellido();
	int dni = this->getDNI();
	string distrito = this->getDistrito();
	string domicilio = this->getDomicilio();
	string password = this->getClave();
	Votante* votante = new Votante(dni, nombre+" "+apellido, password, domicilio, distrito);
	return votante;
}

CreadorVotante::~CreadorVotante() {
	// TODO Auto-generated destructor stub
}
