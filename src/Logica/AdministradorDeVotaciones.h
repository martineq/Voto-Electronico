#ifndef ADMINISTRADORDEVOTACIONES_H_
#define ADMINISTRADORDEVOTACIONES_H_

#include <string>
#include "../Archivos/ArbolBMas/bplustree.h"
#include "../Entidades/Eleccion.h"
#include "../Entidades/Conteo.h"
#include "../Archivos/Hashing/Registro.h"

using std::string;

class AdministradorDeVotaciones {
private:
	bplustree			archivoDeConteo;

	bplustree			indiceSecundarioDistrito;

	/*
	 * Devuelve un string a partir de un string.
	 */
	string* getString(vector<char> vect);


	/*
	 * Agrega elementos conteo al indice secundario.
	 */
	int agregarConteoAlIndicePorDistrito(Conteo* conteo);



public:
	AdministradorDeVotaciones();

	/*
	 * Crea un nuevo archivo de conteo.
	 */
	void nuevoArchivoDeConteo(string pathArchivo,int dimensionBloque);

	/*
	 * Abre un archivo de conteo.
	 */
	void abrirArchivoDeConteo(string pathArchivo);

	/*
	 * Devuelve 0 si lo agregó correctamente.
	 */
	int agregarConteo(Conteo* conteo);

	/*
	 * Devuelve 0 si se persistió el voto y 1 en caso contrario.
	 */
	void incrementarVoto(Eleccion* eleccion,string* nombreLista,string* distrito);

	/*
	 * Ver Archivo de conteo.
	 */
	void mostrarArchivo();

	virtual ~AdministradorDeVotaciones();
};

#endif /* ADMINISTRADORDEVOTACIONES_H_ */
