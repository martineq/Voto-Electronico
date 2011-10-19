#include "ffile.h"


ffile::ffile(string p, int bs){
	this->path = p;
	this->blocksize=bs;
	this->arch = new ArchivoBloques((char*)(this->path).c_str(),this->blocksize);
}


int ffile::newblock(){

	// Archivo en disco físico:
	int bn;
	if(q.size()==0){
		int nrr;
		this->arch->crearNuevoBloque(&nrr);
		this->ind.push_back(nrr);			// Agrego el nrr del nuevo bloque al índice
		return this->ind.size()-1;			// Devuelvo el numero de bloque "normalizado"
	}
	bn = this->q.back();
	this->q.pop_back();

	return bn;
}


// Se usa en el árbol
void ffile::setblock(std::vector<char> vec, int bn){

	// Archivo en disco físico:
	char* cadena;					// Variable temporal, se usa para guardar en archivo
	int i;
	int cant = this->blocksize;

	if ( vec.size() > cant ){
		cerr << "Error Interno: Tamaño de nodo mayor al permitido.\nPrograma Terminado." << endl;
		exit(1);
	}else{
		if( vec.size() < cant ){
			// Si llego acá es porque el vector es menor del tamaño del bloque, pero igual lo copio.
			//cerr << "Precaución: Tamaño de nodo menor al permitido." << endl;
			cant = vec.size();
		}
	}

	cadena = vec.get_allocator().allocate(cant);	// Aloco cadena
	for (i=0; i<cant; i++) cadena[i]=vec[i];		// Copio los valores de vec en cadena
	this->arch->guardarBloque(this->ind[bn],cadena);
	vec.get_allocator().deallocate(cadena,cant);	// Dealoco cadena
}


std::vector<char> ffile::getblock(int bn){

	// Archivo en disco físico:
	std::vector<char> vec;
	char* cadena;				// Variable temporal, se usa para leer de archivo
	int i;
	int cant = this->blocksize;

	cadena = vec.get_allocator().allocate(cant);		// Aloco cadena
	this->arch->obtenerBloque(this->ind[bn],cadena);
	for (i=0; i<cant; i++) vec.push_back(cadena[i]);	// Copio los valores de cadena en vec
	vec.get_allocator().deallocate(cadena,cant);		// Dealoco cadena y me quedo con el vec

	return vec;
}


void ffile::delblock(int bn){
	this->q.push_back(bn);
}


int ffile::getblocksize(){
	return this->blocksize;
}


ffile::~ffile(){
	// Destruyo el objeto. Si quedaron bloques en la lista de borrados
	// los mando a borrar. Esto es para no persistir un archivo de configuración.
	if(q.size()>0){
		int bn = this->q.back();
		this->q.pop_back();
		this->arch->borrarBloque(this->ind[bn]);
	}
	delete this->arch;
}
