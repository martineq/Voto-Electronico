/*
 * ArchivoBloques.cpp
 *
 *  Created on: 23/09/2011
 *      Author: mart
 */

#include "ArchivoBloques.h"


ArchivoBloques::ArchivoBloques(char *path, int blocksize){
	// Es el 'openblockfile()' de C
}

int ArchivoBloques::delmetadatahandle(){
	return 0;
}

int ArchivoBloques::serializehead(){
	return 0;
}

int ArchivoBloques::getblocksize(){
	return 0;
}

int *ArchivoBloques::getdblock(int bh){
	return 0;
}

int ArchivoBloques::delblockhandle(int blockhandle){
	return 0;
}

int ArchivoBloques::newmetadatahandle(){
	return 0;
}

int ArchivoBloques::newblockhandle(){
	return 0;
}


int *ArchivoBloques::getmblock(int bh){
	return 0;
}

void ArchivoBloques::guardarBloque(int numeroBloque, char *datos){

}

char *ArchivoBloques::obtenerBloque(int numeroBloque){
	// Es el 'getblock()' de C
	return 0;
}

int ArchivoBloques::growfile(){
	return 0;
}

int ArchivoBloques::truncatefile(){
	return 0;
}

int ArchivoBloques::retlastdeleted(){
	return 0;
}

int ArchivoBloques::deserializehead(){
	return 0;
}

void ArchivoBloques::liberarBloque(int numeroBloque){

}

int ArchivoBloques::crearNuevoBloque(){
	return 0;
}

ArchivoBloques::~ArchivoBloques() {

}
