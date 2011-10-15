#include "../EnBloques/ManejadorDeArchivo.h"
#include "./Bucket.h"
#include <iostream>
#include <vector>
#include <list>

#ifndef ARCHIVODECONTROL_H_
#define ARCHIVODECONTROL_H_

class ArchivoDeControl {
private:
	/*
	 * Contiene un archivo de control, de registros variables
	 * para funcionamiento del hashing.
	 */
	ManejadorDeArchivo*		archivo;

	/*
	 * Nombre del archivo pasado por parametro.
	 */
	string					nombreArchivo;

public:
	ArchivoDeControl(char* archivo);

	/*
	 * Serializa la tabla de Hash y la almacena en el archivo de registros
	 * variable.
	 */

	void persistirVector(vector<int>* tabla);

	/*
	 * Hidrata un vector desde el archivo de control.
	 */
	vector<int> hidratarVector();

	/*
	 * Serializa la lista de libres y la almacena en un archivo de registros
	 * variable.
	 */
	void persistirLista(list<int>* listaDeBucketsLibres);

	/*
	 * Hidrata una lista desde el archivo de configuracion.
	 */
	list<int> hidratarLista();

	/*
	 * Informa si el archivo está vacío.
	 */
	bool vacio();

	virtual ~ArchivoDeControl();
};

#endif /* ARCHIVODECONTROL_H_ */
