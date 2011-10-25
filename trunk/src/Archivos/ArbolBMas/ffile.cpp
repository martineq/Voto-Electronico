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
		return nrr;							// Devuelvo el numero de bloque "normalizado"
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

	if ( (int)vec.size() > cant ){
		cerr << "Error Interno: Tamaño de nodo mayor al permitido.\nPrograma Terminado." << endl;
		exit(1);
	}else{
		if( (int)vec.size() < cant ){
			// Si llego acá es porque el vector es menor del tamaño del bloque, pero igual lo copio.
			//cerr << "Precaución: Tamaño de nodo menor al permitido." << endl;
			cant = vec.size();
		}
	}

	cadena = vec.get_allocator().allocate(this->blocksize);	// Aloco cadena
	for (i=0; i<cant; i++) cadena[i]=vec[i];		// Copio los valores de vec en cadena
	for (i=cant; i<this->blocksize; i++) cadena[i]='\0';// Relleno con ceros el bloque, si es necesario
	this->arch->guardarBloque(bn,cadena);
	vec.get_allocator().deallocate(cadena,this->blocksize);	// Dealoco cadena
}


std::vector<char> ffile::getblock(int bn){

	// Archivo en disco físico:
	std::vector<char> vec;
	char* cadena;				// Variable temporal, se usa para leer de archivo
	int i;
	int cant = this->blocksize;

	cadena = vec.get_allocator().allocate(cant);		// Aloco cadena
	this->arch->obtenerBloque(bn,cadena);
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
		this->arch->borrarBloque(bn);
	}
	delete this->arch;
}
