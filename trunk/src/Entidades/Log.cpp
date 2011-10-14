/*
 * Log.cpp
 *
 *  Created on: 14/10/2011
 *      Author: daniel
 */

#include "Log.h"

Log::Log() {
	// TODO Auto-generated constructor stub

}

Log::~Log() {
	// TODO Auto-generated destructor stub
}

void Log::abrir(){
	this->archivo = fopen("texto","w+");
}

void Log::cerrar(){
	fclose(this->archivo);
}

string Log::convertIntToString(int dni){
	string s;
	stringstream out;
	out << dni;
	s = out.str();
	return s;
}
void Log::insertarTimestamp(){
	time_t rawtime1;
	struct tm * timeinfo;
	time ( &rawtime1 );
	timeinfo = localtime ( &rawtime1 );
	string hora = asctime (timeinfo);
	string horaAux= hora.substr(0,hora.length()-1);
	fputs ("\n[",this->archivo);
	fputs (&horaAux[0],this->archivo);
	fputs ("]",this->archivo);
}

void Log::insertarMensaje(string mensaje){
	this->insertarTimestamp();
	fputs (&mensaje[0],this->archivo);
}

void Log::insertarMensajeConEntero(int dni) {
	this->insertarTimestamp();
	fputs (" Intento ingresar el votante con DNI: ",this->archivo);
	string s = this->convertIntToString(dni);
	fputs (&s[0],this->archivo);
	fputs (" pero no esta en el padron.",this->archivo);
}

void Log::insertarVotante(Votante* votante,string mensaje){
	this->insertarTimestamp();
	fputs (&mensaje[0],this->archivo);
	fputs ("\n Nombre: ", this->archivo);
	fputs (&(votante->getNombre()[0]),this->archivo);
	string s = this->convertIntToString(votante->getDNI());
	fputs ("\n DNI: ",this->archivo);
	fputs (&s[0],this->archivo);
	fputs ("\n Domicilio: ",this->archivo);
	fputs (&(votante->getDomicilio()[0]),this->archivo);
	fputs ("\n Distrito: ",this->archivo);
	fputs (&(votante->getDistrito()[0]),this->archivo);
}

void Log::insertarEleccion(Eleccion* eleccion,string mensaje){
	this->insertarTimestamp();
	fputs (&mensaje[0],this->archivo);
	fputs ("\n Fecha: ", this->archivo);
	fputs (&(eleccion->getFecha()[0]),this->archivo);
	fputs ("\n Cargo Principal: ",this->archivo);
	fputs (&(eleccion->getCargo()[0]),this->archivo);
}

void Log::insertarLista(Lista* lista,string mensaje){
	this->insertarTimestamp();
	fputs (&mensaje[0],this->archivo);
	fputs ("\n Nombre: ", this->archivo);
	fputs (&(lista->getNombre()[0]),this->archivo);
}

void Log::insertarMensajeConEntidad(Entidad* entidad,string mensaje){
	NombreDeEntidad nombre = entidad->getNombreDeEntidad();
	if (nombre==tEleccion) cout << "hukgyfjiuhojiuhyftdg" << endl;
	switch(nombre){
	case tVotante:
		this->insertarVotante((Votante*)entidad,mensaje);
		break;
	case tEleccion:
		this->insertarEleccion((Eleccion*)entidad,mensaje);
		break;
	case tLista:
		this->insertarLista((Lista*)entidad,mensaje);
		break;
	}
}
