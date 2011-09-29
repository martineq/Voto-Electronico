#include "FabricaDeEntidades.h"

FabricaDeEntidades::FabricaDeEntidades() {
	// TODO Auto-generated constructor stub

}

Entidad *FabricaDeEntidades::crearEntidad(NombreDeEntidad nombre)
{
	Entidad* entidad;
	switch(nombre){
		case tCandidato:
			entidad = (Entidad*)new Candidato();
			break;
		case tCargo:
			entidad = (Entidad*) new Cargo();
			break;
		case tDistrito:
			entidad = (Entidad*) new Distrito();
			break;
		case tEleccion:
			entidad = (Entidad*) new Eleccion();
			break;
		case tLista:
			entidad = (Entidad*) new Lista();
			break;
		case tVotante:
			entidad = (Entidad*) new Votante();
			break;
	}
	return entidad;
}

FabricaDeEntidades::~FabricaDeEntidades() {
	// TODO Auto-generated destructor stub
}

