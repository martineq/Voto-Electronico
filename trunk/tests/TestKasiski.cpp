#include "TestKasiski.h"

int TestKasiski::testObtenerClaveDeVigenere(){

	string clave = "abFgi";

	Vigenere* vigenere = new Vigenere(clave,256);

	Constitucion constitucion;
	string mensaje = constitucion.getTexto();
//	string mensaje = "PBVRQVICADSKAZSDETSJPSIEDBGGMPSLRPWRZPWYEDSDEZDRDPCRCPQMNPWKUBZVSFNVRDMTIPWUEQVVCBOVNUEDIFQLONMWNUVRSEIKAZYEACEYEDSETFPHLBHGUZESOMEHLBXVAEEPUZELISEVEFWHUNMCLPQPMBRRNBPVIZMTIBVVEZIDANSJAMTJOKMDODSELPWIUFOZMQMVNFOHASESRJWRSFQCOTWVMBJGRPWVSUEXINQRSJEUEMGGRBDGNNILAGSJIDSVSUEEINTGRUEETFGGMPORDFOGTSSTOSEQOZTGRRYVLPWJIFWXOTGGRPQRRJSKETXRNBLZETGGNEMUOTXJATORVJHRSFHVNUEJIBCHASEHEUEUOTIEFFGYATGGMPIKTBWUEZENIEEU.";

	string* criptograma = vigenere->cifrar(&mensaje);

	Kasiski ka;
	string key;

//	ka.analisisDeFrecuencias(mensaje);

	ka.generarPatrones(criptograma);
//	ka.listarPatrones();
	cout << ka.MCDDistancias() << endl;
	ka.analisisDeFrecuencias(*criptograma);
	key = ka.romper();

	cout << key << endl;

	int resultado = clave.compare(key);

	if (resultado != 0)
		cout << "testKasiski.testObtenerClaveDeVigenere: FALLO" << endl;

	delete criptograma;
	delete vigenere;

	return resultado;
}

TestKasiski::TestKasiski() {}
TestKasiski::~TestKasiski() {}

