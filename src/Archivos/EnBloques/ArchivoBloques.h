
// Código en C del Archivo en Bloques
// Luego va a ser pasado a C++

/* 
 * File:   blockmgnt.h
 * Author: nacho
 *
 * Created on September 20, 2011, 6:56 PM

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>



#ifndef BLOCKMGNT_H
#define	BLOCKMGNT_H

struct filehandle{
    int* mem;
    int maxblocknum;
    int blocksize;
    int currmetadata;
    int currpos;
    int fd;
    char *path;
 };



int getblocksize(struct filehandle *fh);
int *getblock(struct filehandle *fh, int bh);
int newblockhandle(struct filehandle *fh);
int delblockhandle(struct filehandle *fh, int blockhandle);
int openblockfile(struct filehandle * fh, char *path, int blocksize);
int serializehead(struct filehandle *fh);
int deserializehead(struct filehandle *fh);
int newmetadatahandle(struct filehandle *fh);
int delmetadatahandle(struct filehandle *fh);
int growfile(struct filehandle *fh);
int truncatefile(struct filehandle *fh);



#ifdef	__cplusplus
extern "C" {

#endif




#ifdef	__cplusplus
}
#endif

#endif	/* BLOCKMGNT_H */


