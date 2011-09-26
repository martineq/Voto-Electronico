/*
 * ArchivoBloques.cpp
 *
 *  Created on: 23/09/2011
 *      Author: mart
 */

#include "ArchivoBloques.h"

// Devuelve el tamaño de un bloque de Datos
int ArchivoBloques::getblocksize(){
    return (this->blocksize - (sizeof(int)) );
}

// Lee un sector del archivo de tamaño int, desde la posición <pos>
// y lo guarda donde apunta <dest>
void ArchivoBloques::leerTipoInt(int pos,int* dest){
	char* buf= new char[sizeof(int)]; 		// Preparo un buffer de tamaño int para obtener los datos
	this->archivo->posicionarse(pos);		// Voy a la posición <pos>
	this->archivo->leer(buf,sizeof(int));	// Leo en archivo
	(*dest) = *(int*)buf;					// Guardo el valor en donde apunta <dest>
	delete[] buf;
}

// Guarda en un sector del archivo de tamaño int, desde la posición <pos>
// lo apuntado por <dest>
void ArchivoBloques::guardarTipoInt(int pos, int *dest){
	this->archivo->posicionarse(pos);
	this->archivo->escribir( (char*)dest,sizeof(int));
	this->archivo->guardarBuffer();
}

//Ejemplo de uso:
//guardarTipoInt(0,&(this->currmetadata));
//leerTipoInt(0,&(this->currmetadata));

//////Podría llegar a ser para afuera
// Devuelve un puntero al bloque de tipo <head>, CON la cabecera.
// Si el bloque no es de ese tipo devuelve cero
int ArchivoBloques::getblock(int nrr, int head){
	if( (nrr<=((int)sizeof(int))) || (nrr > (this->maxblocknum * this->blocksize) ) ) return 0;	// Si estoy fuera del rango devuelvo 0
    int filehead;
    leerTipoInt(nrr,&(filehead));					// Obtengo la cabecera en filehead
    if (filehead==head) return nrr;					// Devuelvo el bloque con la cabecera
    return 0;
}

// Creo un bloque nuevo tipo <head> devolviendo su posición de bloque
// Devuelve un nrr al nuevo bloque de tipo <head>, con su cabecera formateada
int ArchivoBloques::newblock(int head){
    int posNuevo = retlastdeleted();								// Pongo en posNuevo la posición del bloque nuevo
    if (posNuevo == 0) posNuevo = growfile();						// Si no habia bloque borrado creo uno nuevo
    guardarTipoInt(posNuevo+0*sizeof(int),&(head));					// Escribo su cabecera
    return posNuevo;
}

//delblock() marks a block as deleted, by adding it to the current metadata file
//in the current position + 1 or in the first block of a new metadata file if position*4 + 1
//is larger than blocksize (blocksize is in chars and an int ocupies 4 chars)
//***Supongo que siempre se va a borrar un bloque de datos***
int ArchivoBloques::delblock(int nrrBorrado){
	 // Este es el caso (A) donde no tengo bloque de metadata y agrego el 1ro o (B) el bloque actual está lleno
	if ( (this->currmetadata == 0) || (this->currpos) >= (this->blocksize)-(sizeof(int)) ){
		int metadataAnterior = this->currmetadata;					// Me guardo el bloque de metadata anterior
		int nrrNuevo = newblock(HEAD_M);							// Pido un nuevo bloque de metadata
		this->currmetadata = nrrNuevo;
		this->currpos = 2*sizeof(int);								// Con un 8 marco que está vacio (currpos=8, 3° int)
		guardarTipoInt(nrrNuevo+(1*sizeof(int)),&(metadataAnterior));// Guardo el bloque anterior
		guardarTipoInt(nrrNuevo+(2*sizeof(int)),&(this->currpos));
		serializehead();											// Gurado los datos en la cabecera
	}
	int nrrMetadata = getblock(this->currmetadata,HEAD_M);
	int nuevaPos = (this->currpos) + (sizeof(int));					// Obtengo la nueva posición actual
	guardarTipoInt(nrrMetadata+nuevaPos,&(nrrBorrado));				// Guardo el nuevo bloque libre en metadata
	guardarTipoInt(nrrMetadata+2*sizeof(int),&(nuevaPos));			// Guardo la nuevaPos en el bloque de metadata
	this->currpos = nuevaPos;										// Actualizo en memoria

   return 0;

}

// Busca en metadata el último bloque borrado
int ArchivoBloques::retlastdeleted(){
	if ( (this->currmetadata)==0 ) return 0;						// Si no tengo metadata devuelvo cero
	int nrrMetadata = this->getblock(this->currmetadata,HEAD_M);
	if (this->currpos < (3*(int)sizeof(int)) ){		// Si la pos es menor a 12 quiere decir que no hay mas bloques libres aquí
		int nuevoCurrMetadata;
		leerTipoInt(nrrMetadata + (sizeof(int)),&(nuevoCurrMetadata));// Pido la posición del bq de HEAD_M anterior
		int bloqueNuevo = this->currmetadata;						// El bloque HEAD_M pasa a ser el bloque nuevo
		this->currmetadata = nuevoCurrMetadata;						// Voy al Bq de metadata anterior
		this->currpos = (this->blocksize)-(sizeof(int)); // Seteo en la posición mas alta, ya que el metadata anterior está lleno
		serializehead();											// Gurado los datos en la cabecera
		return bloqueNuevo;
	}
	int lastDeleted;						// Voy a la posición actual dentro del bloque HEAD_M
	leerTipoInt(nrrMetadata + (this->currpos),&(lastDeleted) );	// Pido la posición del bq de HEAD_M anterior
	int nuevaPos = (this->currpos)-(sizeof(int));					// Obtengo la nueva posición actual restando un 4 bytes
	this->currpos = nuevaPos;										// Saco ese bloque de los 'libres', cambiando la pos
	guardarTipoInt(nrrMetadata+2*sizeof(int),&(nuevaPos));			// Guardo la nuevaPos en el bloque de metadata
	serializehead();												// Gurado los datos en la cabecera
	return (lastDeleted);											// Devuelvo el número de bloque del último borrado
}

// Hago crecer el archivo un bloque con un bloque adicional
int ArchivoBloques::growfile(){
	this->archivo->posicionarseEnFin();
	int nrrNuevo = this->archivo->obtenerPosicionDeLectura();
	char* bloqueNuevo= new char[this->blocksize]; 		// Preparo un buffer de tamaño int para obtener los datos
	this->archivo->escribir(bloqueNuevo,this->blocksize);
    this->maxblocknum+=1;
    serializehead();
	return nrrNuevo;
}

// obtenerCurrPos() Obtiene la posición actual dentro del metadata actual
// Supone que existe al menos un bloque con metadata
int ArchivoBloques::obtenerCurrPos(){
	int nrr = getblock(this->currmetadata,HEAD_M);
	int currPos;
	leerTipoInt(nrr + (sizeof(int)),&(currPos));	// Pido la currPos en el bq de HEAD_M actual
	return currPos;
}

void ArchivoBloques::serializehead(){
	puts("Acá pincha 1");
	guardarTipoInt(0,&(this->currmetadata));
	guardarTipoInt(1,&(this->maxblocknum));
	puts("Acá pincha 2");
}


void ArchivoBloques::deserializehead(){
	leerTipoInt(0,&(this->currmetadata));
	leerTipoInt(1,&(this->maxblocknum));
}


void ArchivoBloques::truncatefile(){
    struct stat statbuf;
    int *mem;
    munmap((void*)this->mem, statbuf.st_size);
    if (fstat (this->fd,&statbuf) < 0){
        perror("cannot stat file");
        std::cout << "cannot stat file\n";
    }

    lseek(this->fd,(statbuf.st_size) - (this->blocksize) ,SEEK_END);
    write(this->fd,"",sizeof(char));
    if ( (void*)(mem = (int*)mmap (0,statbuf.st_size - this->blocksize, PROT_READ | PROT_WRITE, MAP_SHARED, this->fd, 0)) == (caddr_t) -1){
       perror("mmap error for output\n");
       std::cout << "mmap error for output\n";
    }
    this->mem=mem;
    this->maxblocknum-=1;
    serializehead();
}

///////////////////////////////////
////		Públic:			///////
///////////////////////////////////

ArchivoBloques::ArchivoBloques(){

}

ArchivoBloques::ArchivoBloques(char *path, int blocksize){

	//////////////////
	///  Lo nuevo  ///
	//////////////////

	this->archivo = new ManejadorDeArchivo();
	archivo->abrir(path);

	if (archivo->obtenerTamArchivo() <= 0){		// Si el archivo está vacio inicialo loa atributos en cero
		puts("Archivo Nuevo");
		string bloque (blocksize, '0');			// Creo un bloque con ceros
		this->archivo->escribir(bloque.c_str(),blocksize) ;
		this->blocksize = blocksize+1;		// Ver si va el +1
		this->currmetadata = 0;
		this->currpos = 0;
		this->maxblocknum = 0;
		this->fd = 0;						// El file descriptor seguramente no lo voy a tener que usar mas
		this->serializehead();
	}else{
		puts("Archivo existente");
		this->blocksize=blocksize+1;		// Ver si va el +1
		this->deserializehead();
		if (this->currmetadata > 0) this->currpos = this->obtenerCurrPos();
		else this->currpos = 0;
	}
	this->path = (char*)(this->archivo->obtenerNombreArchivo()).c_str();
}

char *ArchivoBloques::obtenerBloque(int nrr){
	this->archivo->posicionarse(nrr);
	char* buf= new char[this->blocksize - (sizeof(int))];
	this->archivo->leer(buf,this->blocksize - (sizeof(int)));
	return buf;
}

char *ArchivoBloques::crearNuevoBloque(int* pos){
	int nrr = this->newblock(HEAD_D);
	this->archivo->posicionarse(nrr + (sizeof(int)) );			// El "+4" es para sacar la cabecera 'D'
	char* buf= new char[this->blocksize - (sizeof(int))];
	this->archivo->leer(buf,this->blocksize - (sizeof(int)));
	(*pos) = nrr + (sizeof(int));
	return buf;
}

void ArchivoBloques::liberarBloque(int nrr){
	this->delblock(nrr - (sizeof(int)));
}

void ArchivoBloques::guardarBloque(int nrr, char *datos){

	this->archivo->posicionarse(nrr);
	this->archivo->escribir(datos, this->blocksize - (sizeof(int)) );

}


ArchivoBloques::~ArchivoBloques() {

}
