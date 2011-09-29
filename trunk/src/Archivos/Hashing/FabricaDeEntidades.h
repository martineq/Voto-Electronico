#ifndef FABRICADEENTIDADES_H_
#define FABRICADEENTIDADES_H_

#include "../../Entidades/Cargo.h"
#include "../../Entidades/Candidato.h"
#include "../../Entidades/Distrito.h"
#include "../../Entidades/Eleccion.h"
#include "../../Entidades/Lista.h"
#include "../../Entidades/Votante.h"

class FabricaDeEntidades {
public:
	FabricaDeEntidades();

	/*
	 * Crea una entidad a partir de un string que la identifica.
	 * La mimsa debe ser eliminada al dejar de utilizarse.
	 */
	Entidad* crearEntidad(NombreDeEntidad nombre);

	virtual ~FabricaDeEntidades();
};

#endif /* FABRICADEENTIDADES_H_ */
