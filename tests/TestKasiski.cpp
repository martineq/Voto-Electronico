#include "TestKasiski.h"

int TestKasiski::testObtenerClaveDeVigenere(){

	string clave = "ABCD";
	Vigenere* vigenere = new Vigenere(clave,256);

	Constitucion constitucion;
	string mensaje = constitucion.getTexto();

	string* criptograma = vigenere->cifrar(&mensaje);

	Kasiski ka;
	string key;
	key = ka.getkey(*criptograma);
	cout <<"Key: "<<key<<endl;

	string* mensajeDescifrado = vigenere->descifrar(criptograma);
	int resultado = mensajeDescifrado->compare(mensaje);

	if (resultado != 0)
		cout << "testVigenere.testKasiski: FALLO" << endl;

	delete criptograma;
	delete mensajeDescifrado;
	delete vigenere;

	return resultado;
}

TestKasiski::TestKasiski() {}
TestKasiski::~TestKasiski() {}

