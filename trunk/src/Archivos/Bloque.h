/*
 * Bloque.h // MANEJADOR DE REGISTROS
 *
 *  Created on: 22/09/2011
 *      Author: martin
 */

#include <string>

using std::string;

#ifndef BLOQUE_H_
#define BLOQUE_H_

class Bloque {
private:
	int			espacioDisponible;
	int			tamanioBloque;
	string*		espacioUsado;

protected:
	virtual int cantidadDeRegistrosAlmacenados();

public:
	Bloque(){};

	virtual string* obtenerRegistro(int clave)= 0;

	//devuelve el resultado de la operación
	virtual int agregarRegistro(int size,int clave,string* bytes)= 0;

	virtual int modificarRegistro(int clave,string* bytes)= 0;

	virtual int eliminarRegistro(int clave)= 0;

	virtual ~Bloque();
};

#endif /* BLOQUE_H_ */
