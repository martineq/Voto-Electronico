/*
 * ArchivoBloques.h
 *
 *  Created on: 21/09/2011
 *      Author: mart
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>


#ifndef ARCHIVOBLOQUES_H_
#define ARCHIVOBLOQUES_H_

class ArchivoBloques {

private:

	int* mem;
	int maxblocknum;
	int blocksize;
	int currmetadata;
	int currpos;
	int fd;
	char *path;

	// Están todas las funciones que había en C excepto <openblockfile()> y <getblock()>
	// que ahora son <ArchivoBloques()> (el constructor de la clase) y <obtenerBloque()> respectivamente

	//getblocksize() returns the block size of the file, this should be a public function
	int getblocksize();
	//newblockhandle() returns a new blockhandle which can either be obtained by growing the
	//file or by reusing an old but deleted block
	int newblockhandle();
	//delblockhandle() marks a block as deleted, by adding it to the current metadata file
	//in the current position + 1 or in the first block of a new metadata file if position*4 + 1
	//is larger than blocksize (blocksize is in chars and an int ocupies 4 chars)
	int delblockhandle(int blockhandle);
	//serializehead() saves the head of a block file, basically metadata
	int serializehead();
	//deserializehead() populates a filehandle struct from the metadata in the first block of a file
	int deserializehead();
	//newmetadatahandle() gets a new metadatafile by growing the file
	int newmetadatahandle();
	//delmetadatahandle() deletes an empty metadata file, i'm not sure whether it will ever be used
	int delmetadatahandle();
	//growfile() grows the file by 1 blocksize
	int growfile();
	//truncatefile() truncates a file by 1 blocksize
	int truncatefile();
	int *getdblock(int bh); //gets data block, wrapper to getblock
	int *getmblock(int bh); //gets metadata block, wrapper to getblock
	int retlastdeleted();


public:
	// <<Acá dejo los las funciones que se van a ver desde afuera>>
	// Si hace falta alguna otra después la vamos agregando

	// <<El constructor es el 'openblockfile()'>> que decía:
	//openblockfile() creates a new blockfile or opens an old one and populares a new filehandle
	//struct which should be freed after we're done with it, blocksize will be ignored if the file exists
	ArchivoBloques(char *path, int blocksize);
	// <<Es el 'getblock()'>> decía: returns a pointer to the block identified by <numeroBloque> (Antes devolvía int *).
	char *obtenerBloque(int numeroBloque);
	// Creo un nuevo bloque y devuelvo su posición en el archivo
	int crearNuevoBloque();
	// Borro un bloque, identificado por su posición en el archivo
	void liberarBloque(int numeroBloque);
	// Guarda un bloque de datos, en la posición <numeroBloque>
	void guardarBloque(int numeroBloque, char* datos);

	virtual ~ArchivoBloques();

};



#endif /* ARCHIVOBLOQUES_H_ */
