#ifndef BUCKET_H_
#define BUCKET_H_

#define LONGITUD_BLOQUE_PRUEBA 100
#include <list>
#include "../../Entidades/Constantes.h"
#include "../../Entidades/Serializable.h"
#include "Registro.h"
#include <iostream>
using namespace std;

class Bucket : public Serializable {

private:
	int espacioLibre;
	int tamanioDeDispersion;
	list<Registro*> listaDeRegistros;

	void imprimirMetadata();
public:
	Bucket(int);
	//devuelve el resultado de la operacion
	bool agregarRegistro(Registro*);
	bool eliminarRegistro(int);
	bool reemplazarRegistro(Registro*);
	Registro* getRegistro(int);
	int getEspacioLibre ();
	int getTamanioDeDispersion ();
	int getCantidadDeRegistros ();
	void  setTamanioDeDispersion (int);
	list<Registro*>::iterator ubicarPrimero();
	string* serializar();
	void deserializar(string*);
	~Bucket();
};

#endif /* BUCKET_H_ */
