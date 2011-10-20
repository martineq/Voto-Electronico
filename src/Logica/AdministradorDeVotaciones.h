#ifndef ADMINISTRADORDEVOTACIONES_H_
#define ADMINISTRADORDEVOTACIONES_H_

#include <string>
#include "../Archivos/ArbolBMas/bplustree.h"
#include "../Entidades/Eleccion.h"
#include "../Entidades/Conteo.h"

using std::string;

class AdministradorDeVotaciones {
private:
	bplustree	archivoDeConteo;


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
	void agregarConteo(Conteo* conteo);

	/*
	 * Devuelve 0 si se persistió el voto y 1 en caso contrario.
	 */
	void incrementarVoto(Eleccion* eleccion,string* nombreLista,string* distrito);

	virtual ~AdministradorDeVotaciones();
};

#endif /* ADMINISTRADORDEVOTACIONES_H_ */
