#ifndef BUCKET_H_
#define BUCKET_H_

#include <string>
#include <iostream>
#include "../../Entidades/Serializable.h"
#include "InterpreteDeRegistro.h"
using namespace std;


class Bucket : public Serializable{
private:
	int espacioLibre;
	list<InterpreteDeRegistro> listaRegistros;
	InterpreteDeRegistro* interprete;

public:
	Bucket();

	Bucket(int tamanioDispersion, InterpreteDeRegistro* tipoInterprete);

	string* obtenerRegistro(int clave);

	//devuelve el resultado de la operación
	int agregarRegistro(string* bytes);

	int modificarRegistro(string* bytes);

	int eliminarRegistro(int clave);

	int getEspacioLibre ();

	int getTamanioDeDispersion ();

	void setTamanioDeDispersion (int tamanio);

	InterpreteDeRegistro* getInterprete();

	void* setInterprete(InterpreteDeRegistro* tipoInterprete);

	string* ubicarPrimero();

	bool siguiente();

	string* getActual();

	string* serializar();

	void deserializar(string* source);

	~Bucket();
};

#endif /* BUCKET_H_ */
