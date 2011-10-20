#ifndef BUCKET_H_
#define BUCKET_H_

#define LONGITUD_BLOQUE_PRUEBA 128
#include <list>
#include "../../Entidades/Constantes.h"
#include "../../Entidades/Serializable.h"
#include "../../Auxiliares/Serializadora.h"
#include "Registro.h"
#include <iostream>
using namespace std;

class Bucket : public Serializable {

private:
	int espacioLibre;
	int tamanioDeDispersion;
	list<Registro*> listaDeRegistros;
	Registro* consultarRegistro(Registro*);
public:
	Bucket(int,int);
	//devuelve el resultado de la operacion
	bool agregarRegistro(Registro*);
	bool eliminarRegistro(Registro*);
	bool reemplazarRegistro(Registro*);
	Registro* getRegistro(Registro*);
	int getEspacioLibre ();
	int getTamanioDeDispersion ();
	int getCantidadDeRegistros ();
	void  setTamanioDeDispersion (int);
	void mostarClavesDeBucket();
	list<Registro*>::iterator ubicarPrimero();
	string* serializar();
	void deserializar(string*);
	void mostarBucket();
	void verInfoBucket();
	~Bucket();
};

#endif /* BUCKET_H_ */
