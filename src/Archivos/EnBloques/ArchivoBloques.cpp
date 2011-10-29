/*
 * ArchivoBloques.cpp
 *
 *  Created on: 23/09/2011
 *      Author: mart
 */

#include "ArchivoBloques.h"

// Devuelve el tamaño de un bloque de Datos
int ArchivoBloques::getblocksize(){
    return (this->blocksize);
}

// Lee un sector del archivo de tamaño int, desde la posición <pos>
// y lo guarda donde apunta <dest>
void ArchivoBloques::leerTipoInt(int pos,int* dest){
	char* buf= new char[TAM_CAMPOS_CTRL]; 		// Preparo un buffer de tamaño int para obtener los datos
	this->archivo->posicionarse(pos);		// Voy a la posición <pos>
	this->archivo->leer(buf,TAM_CAMPOS_CTRL);	// Leo en archivo
	(*dest) = *(int*)buf;					// Guardo el valor en donde apunta <dest>
	delete[] buf;
}

// Guarda en un sector del archivo de tamaño int, desde la posición <pos>
// lo apuntado por <dest>
void ArchivoBloques::guardarTipoInt(int pos, int *dest){
	this->archivo->posicionarse(pos);
	this->archivo->escribir( (char*)dest,TAM_CAMPOS_CTRL);
	this->archivo->guardarBuffer();
}

// Devuelve un puntero al bloque de tipo <head>, CON la cabecera.
// Si el bloque no es de ese tipo devuelve cero
int ArchivoBloques::getblock(int nrr){
	if( (nrr<=(int)(TAM_CAMPOS_CTRL)) || (nrr > ( (this->maxblocknum-1) * this->blocksize ) + 1 ) ){
		cerr << "Se accedió a un bloque fuera de rango" << endl;
		return 0;	// Si estoy fuera del rango devuelvo 0
	}
    return nrr;
}

// Creo un bloque nuevo tipo <head> devolviendo su posición de bloque
// Devuelve un nrr al nuevo bloque de tipo <head>, con su cabecera formateada
int ArchivoBloques::newblock(){
    int posNuevo = retlastdeleted();								// Pongo en posNuevo la posición del bloque nuevo
    if (posNuevo == 0) posNuevo = growfile();						// Si no habia bloque borrado creo uno nuevo
    return posNuevo;
}

// delblock() marks a block as deleted, by adding it to the current metadata file
// in the current position + 1 or in the first block of a new metadata file if position*4 + 1
// is larger than blocksize (blocksize is in chars and an int ocupies 4 chars)
// Si el bloque a borrar se encuentra en la última posición del archivo, lo trunca del mismo
// ***Siempre se va a borrar un bloque de datos***
int ArchivoBloques::delblock(int nrrBorrado){

	if (nrrBorrado < this->blocksize) {
		cerr << "Archivo de Bloques >> Escritura ilegal en cabecera." << endl;
		exit(1);
	}
	// Si el bloque a borrar es el último del archivo, lo trunco.
	if ( nrrBorrado == ((this->blocksize) * (this->maxblocknum - 1)) ){
		truncarUltimoBloque();
		return 0;
	}
	// Este es el caso (A) donde no tengo bloque de metadata y agrego el 1ro o (B) el bloque actual está lleno
	if ( (this->currmetadata == 0) || (this->currpos) >= (this->blocksize)-(int)TAM_CAMPOS_CTRL ){
		int metadataAnterior = this->currmetadata;					// Me guardo el bloque de metadata anterior
		int nrrNuevo = growfile();									// Pido un NUEVO bloque de metadata
		this->currmetadata = nrrNuevo;
		this->currpos = (POSREL_1ER_BQLIBRE_MD - TAM_CAMPOS_CTRL );	// Con un 4 marco que está vacio (currpos=8, es el 1er dato)
		guardarTipoInt(nrrNuevo+(POSREL_BLOQANT_MD),&(metadataAnterior));// Guardo el bloque anterior
		guardarTipoInt(nrrNuevo+(POSREL_CURR_MD),&(this->currpos));
		serializehead();											// Gurado los datos en la cabecera
	}
	int nrrMetadata = getblock(this->currmetadata);
	int nuevaPos = (this->currpos) + (TAM_CAMPOS_CTRL);				// Obtengo la nueva posición actual
	guardarTipoInt(nrrMetadata+nuevaPos,&(nrrBorrado));				// Guardo el nuevo bloque libre en metadata
	guardarTipoInt(nrrMetadata+POSREL_CURR_MD,&(nuevaPos));			// Guardo la nuevaPos en el bloque de metadata
	this->currpos = nuevaPos;										// Actualizo en memoria
	return 0;
}

// Busca en metadata el último bloque borrado
int ArchivoBloques::retlastdeleted(){
	if ( (this->currmetadata)==0 ) return 0;						// Si no tengo metadata devuelvo cero
	int nrrMetadata = this->getblock(this->currmetadata);
	if (this->currpos < (int)(POSREL_1ER_BQLIBRE_MD) ){		// Si la pos es menor a 8 quiere decir que no hay mas bloques libres aquí
		int nuevoCurrMetadata;
		leerTipoInt(nrrMetadata + (POSREL_BLOQANT_MD),&(nuevoCurrMetadata));// Pido la posición del bq de HEAD_M anterior
		int bloqueNuevo = this->currmetadata;						// El bloque HEAD_M pasa a ser el bloque nuevo
		this->currmetadata = nuevoCurrMetadata;						// Voy al Bq de metadata anterior
		this->currpos = (this->blocksize)-(TAM_CAMPOS_CTRL); 		// Seteo en la posición mas alta, ya que el metadata anterior está lleno
		serializehead();											// Gurado los datos en la cabecera
		return bloqueNuevo;
	}
	int lastDeleted;											// Voy a la posición actual dentro del bloque HEAD_M
	leerTipoInt(nrrMetadata + (this->currpos),&(lastDeleted) );	// Pido la posición del bq de HEAD_M anterior
	int nuevaPos = (this->currpos)-(TAM_CAMPOS_CTRL);				// Obtengo la nueva posición actual restando un 4 bytes
	this->currpos = nuevaPos;										// Saco ese bloque de los 'libres', cambiando la pos
	guardarTipoInt(nrrMetadata+POSREL_CURR_MD,&(nuevaPos));			// Guardo la nuevaPos en el bloque de metadata
	serializehead();												// Gurado los datos en la cabecera
	return (lastDeleted);											// Devuelvo el número de bloque del último borrado
}

// Hago crecer el archivo un bloque con un bloque adicional
int ArchivoBloques::growfile(){
	this->archivo->posicionarseEnFin();
	int nrrNuevo = this->archivo->obtenerPosicionDeLectura();
	string bloque (blocksize, '\0');			// Creo un bloque con ceros
	this->archivo->escribir(bloque.c_str(),blocksize) ;
	this->maxblocknum+=1;
    serializehead();
	return nrrNuevo;
}

// obtenerCurrPos() Obtiene la posición actual dentro del metadata actual
// Supone que existe al menos un bloque con metadata
int ArchivoBloques::obtenerCurrPos(){
	if (this->currmetadata == 0) return 0;
	int nrrMetadata = getblock(this->currmetadata);
	int currPos;
	leerTipoInt(nrrMetadata + POSREL_CURR_MD,&(currPos));
	return currPos;
}

void ArchivoBloques::serializehead(){
	guardarTipoInt(POSREL_CURRMD_HEAD,&(this->currmetadata));
	guardarTipoInt(POSREL_MAXBLOQNUM_HEAD,&(this->maxblocknum));
}


void ArchivoBloques::deserializehead(){
	leerTipoInt(POSREL_CURRMD_HEAD,&(this->currmetadata));
	leerTipoInt(POSREL_MAXBLOQNUM_HEAD,&(this->maxblocknum));
}


void ArchivoBloques::truncarUltimoBloque(){

	if ( truncate(this->archivo->obtenerNombreArchivo().c_str(),(this->blocksize) * (this->maxblocknum - 1) ) == 0  ){
		this->maxblocknum = this->maxblocknum - 1;
		this->serializehead();
	}else{
		cerr << "Archivo de Bloques >> Error al truncar." << endl;
	}


}


///////////////////////////////////
////		Públic:			///////
///////////////////////////////////


ArchivoBloques::ArchivoBloques(char *path, int blocksize){

	if ( (blocksize) >= (MIN_BLOCK_SIZE) && ((blocksize%(TAM_CAMPOS_CTRL))==0) ){
		this->archivo = new ManejadorDeArchivo(path);

		if (archivo->obtenerTamArchivo() <= 0){		// Si el archivo está vacio inicialo los atributos en cero
			string bloque (blocksize, '\0');			// Creo un bloque con ceros
			char* buf = new char[blocksize];
			strcpy(buf,bloque.c_str());
			this->archivo->escribir(buf,blocksize) ;
			this->blocksize = blocksize;
			this->currmetadata = 0;
			this->currpos = 0;
			this->maxblocknum = 1;				// Lo pongo en 1 porque agrego el bloque cabecera
			guardarTipoInt(POSREL_BLOCKSIZE_HEAD,&(this->blocksize)); // Guardo en cabecera el blocksize
			this->serializehead();
			delete[] buf;
		}else{
			leerTipoInt(POSREL_BLOCKSIZE_HEAD,&(this->blocksize)); // Guardo de cabecera el blocksize
			if ( this->blocksize == blocksize ){
				this->deserializehead();
				this->blocksize = blocksize;
				if (this->currmetadata > 0) this->currpos = this->obtenerCurrPos();
				else this->currpos = 0;
			}else{
				cerr << "El archivo existente tiene un tamaño de bloque distinto al definido. Archivo NO iniciado. \nPrograma terminado."<<endl;
				exit(1);
			}
		}
	}else{
		if((blocksize%(TAM_CAMPOS_CTRL))!=0){
			cerr << "El bloque definido debe ser múltiplo de "<< (TAM_CAMPOS_CTRL) << endl;
		}
		if ( (blocksize) < (MIN_BLOCK_SIZE) ){
		cerr << "El bloque definido debe ser por lo menos de "<< (MIN_BLOCK_SIZE) << " bytes." << endl;
		}
		cerr << "Archivo NO creado. \nPrograma terminado." << endl;
		exit(1);
	}
}

void ArchivoBloques::obtenerBloque(int nrr, char *datos){
	this->archivo->posicionarse(nrr);
	this->archivo->leer(datos,this->blocksize);
}

void ArchivoBloques::crearNuevoBloque(int* pos){
	(*pos) = this->newblock();
}

void ArchivoBloques::borrarBloque(int nrr){
	this->delblock(nrr);
}

void ArchivoBloques::guardarBloque(int nrr, char *datos){
	this->archivo->posicionarse(nrr);
	this->archivo->escribir(datos,this->blocksize);
}

ArchivoBloques::~ArchivoBloques() {
	delete (this->archivo);
}
