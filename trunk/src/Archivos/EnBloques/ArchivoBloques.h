/*
 * ArchivoBloques.h
 *
 *  Created on: 21/09/2011
 *      Author: mart
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "ManejadorDeArchivo.h"

#ifndef ARCHIVOBLOQUES_H_
#define ARCHIVOBLOQUES_H_

#define TAM_CAMPOS_CTRL sizeof(int)  //Tamaño de campos de control para el funcionamiento (Debe ser potencia de 2)
#define MIN_CAMPOS_CTRL 4  //Cantidad mínima de campos de control para el funcionamiento (Debe ser potencia de 2)
#define POSREL_CURRMD_HEAD (0*TAM_CAMPOS_CTRL)		// Posición relativa del campo de ctrl currMD dentro del Bq HEAD
#define POSREL_MAXBLOQNUM_HEAD (1*TAM_CAMPOS_CTRL)// Posición relativa del campo de ctrl maxblocknum dentro del Bq HEAD
#define POSREL_BLOCKSIZE_HEAD (2*TAM_CAMPOS_CTRL)// Posición relativa del campo de ctrl Blocksize dentro del Bq HEAD
#define POSREL_BLOQANT_MD (0*TAM_CAMPOS_CTRL)// Posición relativa del campo de ctrl BqAnterior dentro del Bq METADATA
#define POSREL_CURR_MD (1*TAM_CAMPOS_CTRL)		// Posición relativa del campo de ctrl currPos dentro del Bq METADATA
#define POSREL_1ER_BQLIBRE_MD (2*TAM_CAMPOS_CTRL)// Posición relativa del 1er bloue libre dentro del Bq METADATA


class ArchivoBloques {

private:

	ManejadorDeArchivo* archivo; // Maneja lo respectivo al acceso a disco.-
	int* mem;        //this is the memory in which the file is mapped
	int maxblocknum;  //this is the number of blocks in my file, it counts everything, deleted blocks, metadata blocks, head
	int blocksize;    //this is the block size of the file (in bytes), incluye todos los campos de control
	int currmetadata; //this points to the current metadata block in use
	int currpos;      //this points to the current position in the metadata block

	//getblocksize() returns the block size of the file, this should be a public function
	int getblocksize();
	//getblock() returns a nrr to the block, or 0 if there is an error
	int getblock(int nrr);
	//newblock() returns a new blockhandle which can either be obtained by growing the
	//file or by reusing an old but deleted block
	int newblock();
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

	ArchivoBloques();
	ArchivoBloques(char *path, int blocksize);
	// Devuelve un bloque (de datos), según la posición <nrr> dada
	void obtenerBloque(int nrr, char *datos);
	// Creo un nuevo bloque y devuelvo su posición relativa en archivo
	void crearNuevoBloque(int* nrr);
	// Borro un bloque, identificado por su posición en el archivo
	void borrarBloque(int nrr);
	// Guarda un bloque de datos, en la posición <numeroBloque>
	void guardarBloque(int nrr, char* datos);
	void cerrarArchivo();

	//Muestra TODO_ el contenido del archivo en intervalos de Ints (en paquetes de a 4 Bytes)
	// Una vez usada, bórrese! =D
	void infoInts();

	virtual ~ArchivoBloques();

};



#endif /* ARCHIVOBLOQUES_H_ */
