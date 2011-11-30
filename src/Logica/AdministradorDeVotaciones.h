#ifndef ADMINISTRADORDEVOTACIONES_H_
#define ADMINISTRADORDEVOTACIONES_H_

#include <string>
#include <iomanip>
#include "../Archivos/ArbolBMas/bplustree.h"
#include "../Entidades/Eleccion.h"
#include "../Entidades/Conteo.h"
#include "../Archivos/Hashing/Registro.h"
#include "../Archivos/Hashing/HashingExtensible.h"
#include "../Criptografia/Vigenere.h"
#include "../Archivos/EnBloques/ManejadorDeArchivo.h"

using std::string;

class AdministradorDeVotaciones {
private:
	bplustree			archivoDeConteo;

	bplustree			indiceSecundario;
    string				pathInformePorEleccion;
    string				pathInformePorDistrito;
    string				pathInformePorLista;

    string				claveParaEleccion;
    string				claveParaDistrito;
    string				claveParaLista;

    /*
	 * Devuelve un string a partir de un string.
	 */
    string *getString(vector<char> vect);
    /*
	 * Agrega elementos conteo al indice secundario.
	 */
    int agregarConteoAlIndicePorDistrito(Conteo *conteo);
    /*
	 * Obtiene la clave del ínfice pricipal.
	 */
    string obtenerClavePrincipal(Conteo *conteo);
    /*
	 * Obtiene la clave del índice secundario.
	 */
    string obtenerClaveSecundaria(Conteo *conteo);

    void guardarStringEnArchivo(string* s,ManejadorDeArchivo* m);

public:
    AdministradorDeVotaciones();
    /*
	 * Crea un nuevo archivo de conteo.
	 */
    void nuevoArchivoDeConteo(string pathArchivo, string pathArchivoSecundario, int dimensionBloque);
    /*
	 * Abre un archivo de conteo.
	 */
    void abrirArchivoDeConteo(string pathArchivo, string pathArchivoSecundario, int dimensionBloque);
    /*
	 * Devuelve 0 si lo agregó correctamente.
	 */
    int agregarConteo(Conteo *conteo);
    /*
	 * Agrega la eleccion al archivo de conteo, necesita el arbol de listas, que
	 * contiene el nombre de la eleccion.
	 */
    bool cargarEleccionEnArchivoDeConteo(Eleccion *eleccion, bplustree *arbolB);
    /*
	 * Devuelve 0 si se persistió el voto y 1 en caso contrario.
	 */
    void incrementarVoto(Eleccion *eleccion, string *nombreLista, string *distrito);
    /*
	 * Genera un informe mostrando el resultado de resultados de
	 * cada lista de esa eleccion.
	 */
    void generarInformePorEleccion(Eleccion *eleccion);
    /*
	 * Genera un informe mostrando los cargos y el resultado
	 * de una lista particular.
	 */
    void generarInformePorLista(Lista *lista, HashingExtensible *heCargo);
    /*
	 * Genera un informe mostrando el resultado del ganador
	 * de una eleccion.
	 */
    void generarInformePorDistrito(Distrito *distrio);
    /*
	 * Ver Archivo de conteo.
	 */
    void mostrarArchivoPrincipal();
    /*
	 * Ver el archivo secundario.
	 */
    void mostrarArchivoSecundario();
    /*
	 * Muestra el archivo de conteo en formato tabla.
	 */
    void mostrarArchivoPrincipalEnFormatoTabla();
    /*
	 * Muesta el archivo de conteo ordenado por distrito.
	 */
    void mostrarArchivoPrincipalEnFormatoTablaOrdenadoPorClaveSecundaria();
    ~AdministradorDeVotaciones();
    bplustree getArchivoDeConteo() const;
    bplustree getIndiceSecundario() const;
    string getPathInformePorDistrito() const;
    string getPathInformePorEleccion() const;
    string getPathInformePorLista() const;
    void setArchivoDeConteo(bplustree archivoDeConteo);
    void setIndiceSecundario(bplustree indiceSecundario);
    void setPathInformePorDistrito(string pathInformePorDistrito);
    void setPathInformePorEleccion(string pathInformePorEleccion);
    void setPathInformePorLista(string pathInformePorLista);
    void setClaveParaDistrito(string claveParaDistrito);
    void setClaveParaEleccion(string claveParaEleccion);
    void setClaveParaLista(string claveParaLista);
};

#endif /* ADMINISTRADORDEVOTACIONES_H_ */
