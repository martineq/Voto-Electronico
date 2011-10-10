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
			cout << "Creamos una entidad Candidato" << endl;
			break;
		case tCargo:
			entidad = (Entidad*) new Cargo();
			cout << "Creamos una entidad Cargo" << endl;
			break;
		case tDistrito:
			entidad = (Entidad*) new Distrito();
			cout << "Creamos una entidad Distrito" << endl;
			break;
		case tEleccion:
			entidad = (Entidad*) new Eleccion();
			cout << "Creamos una entidad Eleccion" << endl;
			break;
		case tLista:
			entidad = (Entidad*) new Lista();
			cout << "Creamos una entidad Lista" << endl;
			break;
		case tVotante:
			entidad = (Entidad*) new Votante();
			cout << "Creamos una entidad Votante" << endl;
			break;
		case tConteo:
			entidad = (Entidad*) new Conteo();
			cout << "Creamos una entidad Conteo" << endl;
			break;
	}
	return entidad;
}

FabricaDeEntidades::~FabricaDeEntidades() {
	// TODO Auto-generated destructor stub
}

