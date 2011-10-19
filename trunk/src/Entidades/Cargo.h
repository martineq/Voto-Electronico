#ifndef CARGO_H_
#define CARGO_H_

#include <iostream>
#include <list>
#include "Entidad.h"

using namespace std;

class Cargo : public Entidad {
private:
	string cargo;
	list<string> listaCargos;

public:
	Cargo();
	Cargo(string cargoPrincipal);
//	void modificarCargo(string nuevoCargo);
	string getCargo();
	bool agregarCargo(string subCargo);
	list<string> devolverSubCargos();
	bool eliminarCargo(string subCargo);
	int getTamanio();
	int getClave();
	void verEntidad();
	virtual ~Cargo();

	string* serializar();
	void deserializar(string * source);

	/*
	 * Devuelve el resultado de comparar la actual entidad con otra.
	 * Los resultados posibles son mayor, menor, igual o comparacionInvalida.
	 * El resultado es respecto del patrón.
	 * Por ejemplo: sean A y B dos entidades, entonces
	 * A->comparar(B) devuelve "mayor" si A es mayor a "B".
	 */
	ResultadoComparacion comparar(Entidad* entidad);

	/*
	 * Instancia un nuevo objeto, copia de actual.
	 */
	Entidad* duplicar();

	/*
	 * Devuelve el tipo de la entidad instanciada.
	 */
	NombreDeEntidad getNombreDeEntidad();

};

#endif /* CARGO_H_ */
