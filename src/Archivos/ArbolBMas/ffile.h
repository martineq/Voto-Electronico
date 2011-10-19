#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "../EnBloques/ArchivoBloques.h"

using namespace std;

class ffile{

private:
	ArchivoBloques* arch;			// Archivo de bloques (en disco)
	string path;					// Ruta del archivo.
	int blocksize;					// Tamaño de bloque.
	vector<std::vector<char> > v;	// Simula un archivo con un vector y cada "vector<char>" es un bloque.
	vector<int> q;					// Lista de elementos borrados.
	vector<int> ind;				// Índice para el árbol. De esta forma los bloques se numeran 0,1,2,3...n.

	void newfile(string p, int bs);

public:
	ffile(string p, int bs);
	~ffile();
	int newblock();
	int getblocksize();
	std::vector<char> getblock(int bn);
	void setblock(std::vector<char> vec,int bn);
	void delblock(int bn);

};

