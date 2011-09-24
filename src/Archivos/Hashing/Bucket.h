#ifndef BUCKET_H_
#define BUCKET_H_

#include <string>
#include <iostream>
#include "../../Entidades/Serializable.h"
using namespace std;


class Bucket : public Serializable{
public:
	Bucket();

	Bucket(int tamanioDispersion);

	string* obtenerRegistro(int clave);

	//devuelve el resultado de la operación
	int agregarRegistro(int size,int clave,string* bytes);

	int modificarRegistro(int clave,string* bytes);

	int eliminarRegistro(int clave);

	int getEspacioLibre ();

	int getTamanioDeDispersion ();

	void duplicarTamanioDeDispersion ();

	std::string* serializar();

	void deserializar(std::string* source);

	~Bucket();
};

#endif /* BUCKET_H_ */
