/*
 * Candidato.h
 *
 *  Created on: 17/09/2011
 *      Author: mart
 */

#ifndef CANDIDATO_H_
#define CANDIDATO_H_
//Candidato ( ( (lista)ie, (votante)ie, (cargo)ie)i )
//Candidato ( (fecha),(cargo),(nombre),(dni), (cargo) )

#include "Entidad.h"
#include <string>
#include <list>
#include <iostream>

using namespace std;

class Candidato : public Entidad{

private:
	string fecha;		//Identificador
	string cargo;		//Identificador
	string nombre;		//Identificador
	int dni;			//Identificador

public:
	Candidato();
	Candidato(string fecha, string cargo, string nombre, int dni);
	void verEntidad();
	void verCandidato ();
	int getTamanio();
	unsigned long getClave();
	string* serializar();
	void deserializar(string*);
	virtual ~Candidato();


	/*
	 * Instancia un nuevo objeto, copia de actual.
	 */
	Entidad* duplicar();

	/*
	 * Devuelve el tipo de la entidad instanciada.
	 */
	NombreDeEntidad getNombreDeEntidad();

	ResultadoComparacion comparar(Entidad* entidad);

};

#endif /* CANDIDATO_H_ */
