/*
 * CreadorVotante.cpp
 *
 *  Created on: 10/10/2011
 *      Author: lucas
 */

#include "CreadorVotante.h"
//#include "../doc/Nombres.txt"
#include <stdlib.h>
#include <ctime>

CreadorVotante::CreadorVotante(int seed) {
    semilla = seed;
}

string CreadorVotante::getNombre(string path){
    string linea;
    fstream archivo;
    archivo.open (path.c_str(), ios::in);
    int cantLineas = this->getCantLineas(path.c_str());
    if (archivo.is_open()) {
       int cont = 0;
       int pos = (rand() % cantLineas) + 1;
       while ( archivo.good() and (cont < pos))
       {
           cont = cont + 1;
           getline(archivo,linea);
       }
       archivo.close();
    }
    else{
//        cout << "Pucha no esta"<<endl;
    }
     return linea;

}


string CreadorVotante::getApellido(string path){
    string linea;
    fstream archivo;
    int cantLineas = this->getCantLineas(path.c_str());
    archivo.open (path.c_str(), ios::in);
    if (archivo.is_open()) {
       int cont = 0;
       int pos = (rand() % cantLineas) + 1;
       while ( archivo.good() and (cont < pos))
       {
           cont++;
           getline(archivo,linea);
       }
       archivo.close();
    }
     return linea;
}

int CreadorVotante::getDNI(){
//    int pos = (rand() % 40000000)+1;
	int pos = semilla;
   return pos;
}

string CreadorVotante::getDistrito(string path){
    string linea;
    fstream archivo;
    int cantLineas = this->getCantLineas(path.c_str());
    archivo.open (path.c_str(), ios::in);
    if (archivo.is_open()) {
       int cont = 0;
       int pos = (rand() % cantLineas) + 1;
       while ( archivo.good() and (cont < pos))
       {
           cont = cont + 1;
           getline(archivo,linea);
       }
       archivo.close();
    }
     return linea;

}

string CreadorVotante::getDomicilio(string path){
    string linea;
    fstream archivo;
    stringstream miString;
    int cantLineas = this->getCantLineas(path.c_str());
    archivo.open (path.c_str(), ios::in);
    if (archivo.is_open()) {
       int cont = 0;
       int pos = ( rand() % cantLineas) + 1;
       while ( archivo.good() and (cont < pos))
       {
           cont = cont + 1;
           getline(archivo,linea);
       }
       int altura = rand() % 5000;
       miString << altura;
       linea = linea+" "+miString.str();
       archivo.close();
    }
     return linea;
}

string CreadorVotante::getClave(){
    stringstream miString;
    string passString;
    int password = rand() % 10000;
    miString << password;
    passString = miString.str();
    while (passString.size() < 4) {
        passString = "0"+passString;
    }


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

Votante* CreadorVotante::crearVotante(Configuracion* configuracion){
    srand ( semilla );
    string path;

    string nombre = this->getNombre(configuracion->pathNombres());

    string apellido = this->getApellido(configuracion->pathApellidos());

    int dni = this->getDNI();

    string distrito = this->getDistrito(configuracion->pathDistritos());

    string domicilio = this->getDomicilio(configuracion->pathDomicilios());

    string password = this->getClave();
    Votante* votante = new Votante(dni, nombre+" "+apellido, password, domicilio, distrito);
    return votante;
}

Votante* CreadorVotante::crearVotante(Configuracion* configuracion, RSA* rsa){
    srand ( semilla );
    string path;

    string nombre = this->getNombre(configuracion->pathNombres());

    string apellido = this->getApellido(configuracion->pathApellidos());

    int dni = this->getDNI();

    string distrito = this->getDistrito(configuracion->pathDistritos());

    string domicilio = this->getDomicilio(configuracion->pathDomicilios());

    string password = this->getClave();
    Votante* votante = new Votante(dni, nombre+" "+apellido, password, domicilio, distrito);
    votante->setRSA(rsa->duplicar());
    return votante;
}

CreadorVotante::~CreadorVotante() {
    // TODO Auto-generated destructor stub
}
