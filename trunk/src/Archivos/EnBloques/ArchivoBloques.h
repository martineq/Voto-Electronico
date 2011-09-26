/*
 * ArchivoBloques.h
 *
 *  Created on: 21/09/2011
 *      Author: mart
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include "ManejadorDeArchivo.h"

#ifndef ARCHIVOBLOQUES_H_
#define ARCHIVOBLOQUES_H_

// Acá defino los 2 tipos de cabeceras, el tipo 'R' no hace falta definirlo
// porque siempre se encuentran registrados detro de los bloques de metadata y
// el tipo 'H' tampoco hace falta porque es único y siempre se encuentra al inicio.
#define	HEAD_D 1
#define	HEAD_M 2

class ArchivoBloques {

private:

	//Nueva variable
	ManejadorDeArchivo* archivo;

	int* mem;        //this is the memory in which the file is mapped
	int maxblocknum;  //this is the number of blocks in my file, it counts everything, deleted blocks, metadata blocks, head
	int blocksize;    //this is the block size of the file (in bytes), incluye todos los campos de control
	int currmetadata; //this points to the current metadata block in use
	int currpos;      //this points to the current position in the metadata block
	int fd; 		  //this is the file descriptor pointing to my file
	char *path;  	  //this is the path to the file

	// Están todas las funciones que había en C excepto <openblockfile()> y <getblock()>
	// que ahora son <ArchivoBloques()> (el constructor de la clase) y <obtenerBloque()> respectivamente

	//getblocksize() returns the block size of the file, this should be a public function
	int getblocksize();
	//getblock() returns a nrr to the block, or 0 if there is an error
	int getblock(int nrr,int head);
	//newblock() returns a new blockhandle which can either be obtained by growing the
	//file or by reusing an old but deleted block
	int newblock(int head);
	//delblock() marks a block as deleted, by adding it to the current metadata file
	//in the current position + 1 or in the first block of a new metadata file if position*4 + 1
	//is larger than blocksize (blocksize is in chars and an int ocupies 4 chars)
	int delblock(int nrrBorrado);
	// retlastdeleted() Busca en metadata el último bloque borrado
	int retlastdeleted();
	//growfile() grows the file by 1 blocksize
	int growfile();
	//serializehead() saves the head of a block file, basically metadata
	void serializehead();
	//deserializehead() populates a filehandle struct from the metadata in the first block of a file
	void deserializehead();
	//truncatefile() truncates a file by 1 blocksize
	void truncatefile();
	// obtenerCurrPos() Obtiene la posición actual dentro del metadata actual
	int obtenerCurrPos();
	// Lee un sector del archivo de tamaño int, desde la posición <pos>
	// y lo guarda donde apunta <dest>
	void leerTipoInt(int pos,int* dest);
	// Guarda en un sector del archivo de tamaño int, desde la posición <pos>
	// lo apuntado por <dest>
	void guardarTipoInt(int pos,int* dest);

public:
	// <<Acá dejo los las funciones que se van a ver desde afuera>>
	// Si hace falta alguna otra después la vamos agregando

	// <<El constructor es el 'openblockfile()'>> que decía:
	//openblockfile() creates a new blockfile or opens an old one and populares a new filehandle
	//struct which should be freed after we're done with it, blocksize will be ignored if the file exists
	ArchivoBloques();
	ArchivoBloques(char *path, int blocksize);
	// Devuelve un bloque (de datos)
	char *obtenerBloque(int nrr);
	// Creo un nuevo bloque y devuelvo su puntero, además de su posición relativa en archivo
	char *crearNuevoBloque(int* nrr);
	// Borro un bloque, identificado por su posición en el archivo
	void liberarBloque(int nrr);
	// Guarda un bloque de datos, en la posición <numeroBloque>
	void guardarBloque(int nrr, char* datos);

	virtual ~ArchivoBloques();

};



#endif /* ARCHIVOBLOQUES_H_ */
