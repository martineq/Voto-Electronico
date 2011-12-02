/*
 * EncriptacionVotante.cpp
 *
 *  Created on: 16/11/2011
 *      Author: daniel
 */

#include "TestEncriptacionVotante.h"

TestEncriptacionVotante::TestEncriptacionVotante() {
	// TODO Auto-generated constructor stub

}

TestEncriptacionVotante::~TestEncriptacionVotante() {
	// TODO Auto-generated destructor stub
}

void TestEncriptacionVotante::principal() {
	cout << "Antes de generar votante"<<endl;
	Votante* unVotante = new Votante (5,"Daniel","Last","1","Hope");
	cout << "Se contruyo el votante" << endl;
	unVotante->verVotante();
	cout << "Se va a serializar el votante" << endl;
	RSA * rsa = new RSA(true);
	unVotante->setRSA(rsa);
	string* votanteSerializado = unVotante->serializar();
	delete unVotante;
	cout << "Se serializo el votante" << endl;
	cout << "Se va a deserializar el votante" << endl;
	unVotante = new Votante();
//	unVotante->verVotante();
	unVotante->setRSA(rsa);
	unVotante->deserializar(votanteSerializado);
	unVotante->verVotante();
	delete rsa;
}
