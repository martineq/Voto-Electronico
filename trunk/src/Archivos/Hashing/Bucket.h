#ifndef BUCKET_H_
#define BUCKET_H_

#include <string>
#include <iostream>
#include <list>
#include "../../Entidades/Serializable.h"
#include "../Registro.h"



using namespace std;

class Bucket : public Serializable {

private:
	int espacioLibre;
	list<Registro*> listaRegistros;
	Registro* registro;

public:
	Bucket();

	Bucket(int tamanioDispersion, Registro* tipoInterprete);

	Registro* obtenerRegistro(int clave);

	//devuelve el resultado de la operación
	int agregarRegistro(string* bytes);

	int modificarRegistro(string* bytes);

	int eliminarRegistro(int clave);

	int getEspacioLibre ();

	int getTamanioDeDispersion ();

	void setTamanioDeDispersion (int tamanio);

	Registro* getInterprete();

	void setInterprete(Registro* tipoInterprete);

	string* ubicarPrimero();

	bool siguiente();

	string* getActual();

	string* serializar();

	void deserializar(string* source);

	~Bucket();
};

#endif /* BUCKET_H_ */
