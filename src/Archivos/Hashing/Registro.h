

using namespace std;

#ifndef REGISTRO_H_
#define REGISTRO_H_

#include <string>
#include "../../Entidades/Serializable.h"
#include "../../Entidades/Entidad.h"
#include "FuncionHashing.h"



class Registro : public Serializable {
protected:
	Entidad* contenido;
	FuncionHashing* funcion;

public:
	Registro();

	// ID es el identificador del registro del archivo
	// clave = hash(ID)
	// devuelve la clave
	virtual int obtenerClave() = 0;

	virtual Entidad* getContenido() = 0;

	int getTamanio();

	void setContenido(Entidad* entidad) {
		this->contenido = entidad;
	}

	virtual ~Registro();
};

#endif /* REGISTRO_H_ */
