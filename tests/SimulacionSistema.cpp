/*
 * SimulacionSistema.cpp
 *
 *  Created on: 20/10/2011
 *      Author: daniel
 */

#include "SimulacionSistema.h"

SimulacionSistema::SimulacionSistema(){}

SimulacionSistema::~SimulacionSistema(){
	//		delete votante4;
	//			delete registroVotante1;
	//			delete registroVotante2;
	//			delete registroVotante3;
	//			delete registroVotante4;
	delete distrito4;
	delete eleccion4;
	delete candidato4;
	delete lista4;
	delete cargo2;
	delete registroDistrito1;
	delete registroDistrito2;
	delete registroDistrito3;
	delete registroDistrito4;
	delete registroEleccion1;
	delete registroEleccion2;
	delete registroEleccion3;
	delete registroEleccion4;
	delete registroCandidato1;
	delete registroCandidato2;
	delete registroCandidato3;
	delete registroCandidato4;
	delete registroLista1;
	delete registroLista2;
	delete registroLista3;
	delete registroLista4;
	delete registroCargo1;
	delete registroCargo2;
	delete this->heVotante;
	delete this->heDistrito;
	delete this->heEleccion;
	delete this->heCandidato;
	delete this->heCargo;
	delete this->arbolB;
//	remove ("archivoDeControlVotante.txt");
//	remove ("archivoDeDatosVotante.txt");
//	remove ("archivoDeControlDistrito.txt");
//	remove ("archivoDeDatosDistrito.txt");
//	remove ("archivoDeControlEleccion.txt");
//	remove ("archivoDeDatosEleccion.txt");
//	remove ("archivoDeControlCandidato.txt");
//	remove ("archivoDeDatosCandidato.txt");
//	remove ("archivoDeControlCargo.txt");
//	remove ("archivoDeDatosCargo.txt");
	remove ("arbolDeListas");
}

void SimulacionSistema::cargarArchivoDeConteo(Administrador* administrador,AdministradorDeVotaciones* administradorDeConteo)
{
	//Busco en la lista de elecciones habilitadas

	list<Eleccion*> eleccionesHabilitadas = (administrador->getListaDeEleccionesHabilitadas());
	list<Eleccion*>::iterator itEleccion = eleccionesHabilitadas.begin();
	while( itEleccion != eleccionesHabilitadas.end()){

		Conteo* conteo;

		string clave;
		clave  = (*itEleccion)->getFecha();
		clave += (*itEleccion)->getCargo();

		vector<char> result = arbolB->search(clave);

		bool buscarSiguienteLista = true;
		while ( buscarSiguienteLista == true ){

			pair<vector<char>,string> map = arbolB->getnext();

			if ( map.first.size() != 0 ){

				string* registroSerializado = getString(map.first);

				Registro* registro = new Registro();
				registro->deserializar(registroSerializado);
				delete registroSerializado;

				Lista* lista = (Lista*)registro->getContenido();
				delete registro;

				if ( lista != NULL ){

					if ( lista->getFecha() == (*itEleccion)->getFecha() &&
						 lista->getCargo() == (*itEleccion)->getCargo() ){

						// Recorro los distritos de la eleccion habilitada
						list<Distrito>::iterator itDistrito = (*itEleccion)->obtenerIterador();
						while( !(*itEleccion)->ultimo(itDistrito) ){
							conteo = new Conteo(lista->getFecha(),lista->getCargo(),lista->getNombre(),(*itDistrito).getDistrito());

							cout << endl <<"Se agrega un registro al archivo de conteo" << endl;
							conteo->verEntidad();

							administradorDeConteo->agregarConteo(conteo);
							delete conteo;

							itDistrito++;
						}

					}else
						buscarSiguienteLista = false;

					delete lista;
				}
			}
		}
		itEleccion++;
	}
}

void SimulacionSistema::iniciarVotantesParaIntegracion() {
	this->votante1 = new Votante(1,"Martin","m","","Chaco");
	this->votante1->agregarEleccion ("19970701","Presidente");
	this->votante1->agregarEleccion ("19970701","Gobernador");
	this->votante2 = new Votante(2,"Lucas","l","","Misiones");
	this->votante2->agregarEleccion ("19970701","Presidente");
	this->votante2->agregarEleccion ("19970701","Gobernador");
	this->votante3 = new Votante(3,"Daniel","d","","Formosa");
	this->votante3->agregarEleccion ("19970701","Presidente");
	this->votante3->agregarEleccion ("19970701","Gobernador");
	this->registroVotante1 = new Registro(votante1);
	this->registroVotante2 = new Registro(votante2);
	this->registroVotante3 = new Registro(votante3);

	char archivoDeControl[]="archivoDeControlVotante.txt";
	char archivoDeDatos[]="archivoDeDatosVotante.txt";
	remove(archivoDeControl);
	remove(archivoDeDatos);
	this->heVotante = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos,archivoDeControl);
	if ( this->heVotante->agregarRegistro(registroVotante1) == operacionOK )
		cout << "Se agrego un votante1" << endl;
	else cout << "Error agregando votante1" << endl;
	if ( this->heVotante->agregarRegistro(registroVotante2) == operacionOK )
			cout << "Se agrego un votante2" << endl;
		else cout << "Error agregando votante2" << endl;
	if ( this->heVotante->agregarRegistro(registroVotante3) == operacionOK )
			cout << "Se agrego un votante3" << endl;
		else cout << "Error agregando votante3" << endl;


	delete votante1;
	delete votante2;
	delete votante3;

	delete registroVotante1;
	delete registroVotante2;
	delete registroVotante3;
}

void SimulacionSistema::iniciarDistritosParaIntegracion(){
	this->distrito1 = new Distrito("Chaco");
	this->distrito2 = new Distrito("Misiones");
	this->distrito3 = new Distrito("Formosa");
	this->registroDistrito1 = new Registro(distrito1);
	this->registroDistrito2 = new Registro(distrito2);
	this->registroDistrito3 = new Registro(distrito3);
	delete this->distrito1;
	delete this->distrito2;
	delete this->distrito3;
	char archivoDeControl[]="archivoDeControlDistrito.txt";
	char archivoDeDatos[]="archivoDeDatosDistrito.txt";
	this->heDistrito = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos,archivoDeControl);
	if ( this->heDistrito->agregarRegistro(registroDistrito1) == operacionOK )
		cout << "Se agrego distrito1" << endl;
	else cout << "Error agregando distrito1" << endl;
	if ( this->heDistrito->agregarRegistro(registroDistrito2) == operacionOK )
		cout << "Se agrego un distrito2" << endl;
	else cout << "Error agregando distrito2" << endl;
	if ( this->heDistrito->agregarRegistro(registroDistrito3) == operacionOK )
		cout << "Se agrego un distrito3" << endl;
	else cout << "Error agregando distrito3" << endl;

}

void SimulacionSistema::iniciarEleccionesParaIntegracion(){
	cout << "***************** INICIO CARGA DE ELECCIONES *****************"<<endl;

	this->eleccion1 = new Eleccion("19970701","Presidente");
	this->eleccion1->agregarDistrito("Chaco");
	this->eleccion1->agregarDistrito("Misiones");
	this->eleccion1->agregarDistrito("Formosa");
	this->eleccion1->agregarDistrito("Corrientes");
	this->eleccion1->agregarDistrito("Chaco");
	this->eleccion1->agregarDistrito("Ciudad Autonoma de Buenos Aires");
	this->eleccion1->agregarDistrito("Buenos Aires");
	this->eleccion1->agregarDistrito("Catamarca");
	this->eleccion1->agregarDistrito("Chubut");
	this->eleccion1->agregarDistrito("Cordoba");
	this->eleccion1->agregarDistrito("Entre Rios");
	this->eleccion1->agregarDistrito("Corrientes");
	this->eleccion1->agregarDistrito("Jujuy");
	this->eleccion1->agregarDistrito("La Pampa");
	this->eleccion1->agregarDistrito("La Rioja");
	this->eleccion1->agregarDistrito("Mendoza");
	this->eleccion1->agregarDistrito("Neuquen");
	this->eleccion1->agregarDistrito("Rio Negro");
	this->eleccion1->agregarDistrito("Salta");
	this->eleccion1->agregarDistrito("San Luis");
	this->eleccion1->agregarDistrito("Santa Cruz");
	this->eleccion1->agregarDistrito("Santa Fe");
	this->eleccion1->agregarDistrito("Santiago del Estero");
	this->eleccion1->agregarDistrito("Tucuman");
	this->eleccion1->agregarDistrito("Tierra del Fuego");

	this->eleccion2 = new Eleccion("19970701","Gobernador");
	this->eleccion2->agregarDistrito("Chaco");
	this->eleccion2->agregarDistrito("Misiones");
	this->eleccion2->agregarDistrito("Formosa");
	this->eleccion2->agregarDistrito("Corrientes");
	this->eleccion2->agregarDistrito("Chaco");
	this->eleccion2->agregarDistrito("Ciudad Autonoma de Buenos Aires");
	this->eleccion2->agregarDistrito("Buenos Aires");
	this->eleccion2->agregarDistrito("Catamarca");
	this->eleccion2->agregarDistrito("Chubut");
	this->eleccion2->agregarDistrito("Cordoba");
	this->eleccion2->agregarDistrito("Entre Rios");
	this->eleccion2->agregarDistrito("Corrientes");
	this->eleccion2->agregarDistrito("Jujuy");
	this->eleccion2->agregarDistrito("La Pampa");
	this->eleccion2->agregarDistrito("La Rioja");
	this->eleccion2->agregarDistrito("Mendoza");
	this->eleccion2->agregarDistrito("Neuquen");
	this->eleccion2->agregarDistrito("Rio Negro");
	this->eleccion2->agregarDistrito("Salta");
	this->eleccion2->agregarDistrito("San Luis");
	this->eleccion2->agregarDistrito("Santa Cruz");
	this->eleccion2->agregarDistrito("Santa Fe");
	this->eleccion2->agregarDistrito("Santiago del Estero");
	this->eleccion2->agregarDistrito("Tucuman");
	this->eleccion2->agregarDistrito("Tierra del Fuego");

	this->eleccion3 = new Eleccion("19970702","Presidente");
	this->eleccion3->agregarDistrito("Chaco");
	this->eleccion3->agregarDistrito("Misiones");
	this->eleccion3->agregarDistrito("Formosa");
	this->eleccion3->agregarDistrito("Corrientes");
	this->eleccion3->agregarDistrito("Chaco");
	this->eleccion3->agregarDistrito("Ciudad Autonoma de Buenos Aires");
	this->eleccion3->agregarDistrito("Buenos Aires");
	this->eleccion3->agregarDistrito("Catamarca");
	this->eleccion3->agregarDistrito("Chubut");
	this->eleccion3->agregarDistrito("Cordoba");
	this->eleccion3->agregarDistrito("Entre Rios");
	this->eleccion3->agregarDistrito("Corrientes");
	this->eleccion3->agregarDistrito("Jujuy");
	this->eleccion3->agregarDistrito("La Pampa");
	this->eleccion3->agregarDistrito("La Rioja");
	this->eleccion3->agregarDistrito("Mendoza");
	this->eleccion3->agregarDistrito("Neuquen");
	this->eleccion3->agregarDistrito("Rio Negro");
	this->eleccion3->agregarDistrito("Salta");
	this->eleccion3->agregarDistrito("San Luis");
	this->eleccion3->agregarDistrito("Santa Cruz");
	this->eleccion3->agregarDistrito("Santa Fe");
	this->eleccion3->agregarDistrito("Santiago del Estero");
	this->eleccion3->agregarDistrito("Tucuman");
	this->eleccion3->agregarDistrito("Tierra del Fuego");
	this->registroEleccion1 = new Registro(eleccion1);
	this->registroEleccion2 = new Registro(eleccion2);
	this->registroEleccion3 = new Registro(eleccion3);
	delete this->eleccion1;
	delete this->eleccion2;
	delete this->eleccion3;
	char archivoDeControl[]="archivoDeControlEleccion.txt";
	char archivoDeDatos[]="archivoDeDatosEleccion.txt";
	this->heEleccion = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos,archivoDeControl);
	if ( this->heEleccion->agregarRegistro(registroEleccion1) == operacionOK )
		cout << "Se agrego una eleccion1" << endl;
	else cout << "Error agregando eleccion1" << endl;
	if ( this->heEleccion->agregarRegistro(registroEleccion2) == operacionOK )
		cout << "Se agrego una eleccion2" << endl;
	else cout << "Error agregando eleccion2" << endl;
	if ( this->heEleccion->agregarRegistro(registroEleccion3) == operacionOK )
		cout << "Se agrego un eleccion3" << endl;
	else cout << "Error agregando eleccion3" << endl;

	string fechasDeElecciones[] = {"20080901","20040901","20000901","19960901"};
	for (int i = 0; i < 4; i++){
		Eleccion* eleccion = new Eleccion(fechasDeElecciones[i],"Jefe De Gobierno");
		eleccion->agregarDistrito("Buenos Aires");
		Registro* registro = new Registro(eleccion);
		delete eleccion;
		heEleccion->agregarRegistro(registro);
		delete registro;
	}

	heEleccion->mostrarArchivoDeHash();

	cout << "***************** FIN CARGA DE ELECCIONES *****************"<<endl;

}

void SimulacionSistema::iniciarCandidatosParaIntegracion(){
	this->candidato1 = new Candidato("19970701","Presidente","Jaime",1);
	this->candidato2 = new Candidato("19970701","Gobernador","Cosme",2);
	this->candidato3 = new Candidato("19970702","Presidente","Juan",3);
	this->registroCandidato1 = new Registro(candidato1);
	this->registroCandidato2 = new Registro(candidato2);
	this->registroCandidato3 = new Registro(candidato3);
	delete this->candidato1;
	delete this->candidato2;
	delete this->candidato3;
	char archivoDeControl[]="archivoDeControlCandidato.txt";
	char archivoDeDatos[]="archivoDeDatosCandidato.txt";
	this->heCandidato = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos,archivoDeControl);
	if ( this->heCandidato->agregarRegistro(registroCandidato1) == operacionOK )
		cout << "Se agrego un candidato" << endl;
	else cout << "Error agregando candidato1" << endl;
	if ( this->heCandidato->agregarRegistro(registroCandidato2) == operacionOK )
		cout << "Se agrego un candidato" << endl;
	else cout << "Error agregando candidato2" << endl;
	if ( this->heCandidato->agregarRegistro(registroCandidato3) == operacionOK )
		cout << "Se agrego un candidato" << endl;
	else cout << "Error agregando candidato3" << endl;
}

string* SimulacionSistema::getString(vector<char> vect){
	string* s = new string();
	vector<char>::iterator it = vect.begin();
	while( it != vect.end() ){
		s->push_back(*it);
		it++;
	}
	return s;
}

void SimulacionSistema::verContenidoArbolListas (){
	//	se posiciona en el primer registro

	string* registroSerializado = getString( arbolB-> search("") );
	delete registroSerializado;
	pair<vector<char>,string> par = this->arbolB->getnext();
	registroSerializado = getString( par.first );

	Registro* unRegistro = new Registro();
	unRegistro->deserializar(registroSerializado);
	delete registroSerializado;

	unRegistro->verContenido();

	par=this->arbolB->getnext();
	while(par.second.size()!=0) {

		registroSerializado = getString( par.first );
		unRegistro->deserializar(registroSerializado);
		delete registroSerializado;

		unRegistro->verContenido();
		cout << endl;
		par=this->arbolB->getnext();
	}
	delete unRegistro;
}

/*
 * Agrega una lista al arbol, siendo la clave un string
 * donde primero va la fecha, luego el cargo y finalmente el nombre de la lista.
 */
void SimulacionSistema::agregarBoletaAlArbol(Registro* registro){
	string clave;

	Lista* lista = (Lista*)registro->getContenido();

	clave  = lista->getFecha();
	clave += lista->getCargo();
	clave += lista->getNombre();

	delete lista;
	string* registroSerializado = registro->serializar();
	vector<char> data(registroSerializado->begin(),registroSerializado->end());
	delete registroSerializado;

	this->arbolB->add(clave,data);
}

void SimulacionSistema::iniciarListasParaIntegracion(){
	this->lista1 = new Lista("UCR","19970701","Presidente");
	this->lista2 = new Lista("UCR","19970701","Gobernador");
	this->lista3 = new Lista("PJ","19970702","Presidente");
	this->registroLista1 = new Registro(lista1);
	this->registroLista2 = new Registro(lista2);
	this->registroLista3 = new Registro(lista3);
	delete this->lista1;
	delete this->lista2;
	delete this->lista3;

	arbolB = new bplustree();
	arbolB->newtree("arbolDeListas",LONGITUD_BLOQUE);

	this->agregarBoletaAlArbol(registroLista1);
	this->agregarBoletaAlArbol(registroLista2);
	this->agregarBoletaAlArbol(registroLista3);
}


void SimulacionSistema::iniciarCargosParaIntegracion() {
	this->cargo1 = new Cargo("Presidente");
	this->cargo1->agregarCargo("Vice Presidente");
	this->registroCargo1 = new Registro(cargo1);
	delete this->cargo1;
	char archivoDeControl[]="archivoDeControlCargo.txt";
	char archivoDeDatos[]="archivoDeDatosCargo.txt";
	this->heCargo = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos,archivoDeControl);
	if ( this->heCargo->agregarRegistro(registroCargo1) == operacionOK )
		cout << "Se agrego un cargo1" << endl;
}

void SimulacionSistema::crearArchivoDeVotantes(){
	int dimensionBucket = LONGITUD_BLOQUE;
	char nombreDeArchivo[] = "votantesAleatorios.bin";
	char archivoConfiguracion[] = "conf.bin";
	this->heVotante = new HashingExtensible(dimensionBucket,nombreDeArchivo,archivoConfiguracion);
	remove(nombreDeArchivo);
	remove(archivoConfiguracion);
	 for (int i = 0; i < 10; i++){
	        CreadorVotante * creador = new CreadorVotante(i+1);
	        Votante* votante = creador->crearVotante();
	        Registro* registro = new Registro(votante);
       		this->heVotante->agregarRegistro(registro);
//        	he->mostrarArchivoDeHash();
//	        votante->verVotante();
	        delete (registro);
	        delete (votante);
	        delete (creador);
	    }
}

void SimulacionSistema::cargarBaseDeDatos(Administrador* administrador, char modo) {
	cout << "Inicio de carga de padron electoral" << endl;
	if (modo=='a') this->crearArchivoDeVotantes();
	else {
		this->iniciarVotantesParaIntegracion();
		cout << "Se cargo el padron electoral" << endl;
		cout << "Se carga un votante nuevo" << endl;
		this->votante4 = new Votante(4,"Ignacio","i","","Corrientes");
		this->votante4->agregarEleccion ("19970701","Presidente");
		this->votante4->agregarEleccion ("19970701","Gobernador");
		this->registroVotante4 = new Registro(votante4);
		if (administrador->altaHash(this->heVotante,this->registroVotante4)==operacionOK )
			cout << "Se agrego un votante" << endl;
		else cout << "Error agregando votante4" << endl;

		delete votante4;
		delete registroVotante4;

		heVotante->mostrarArchivoDeHash();
	}

	cout << "Inicio de carga de distritos" << endl;
	this->iniciarDistritosParaIntegracion();
	this->distrito4 = new Distrito("Corrientes");
	this->registroDistrito4 = new Registro(distrito4);
	if (administrador->altaHash(this->heDistrito,this->registroDistrito4)==operacionOK )
		cout << "Se agrego un distrito4" << endl;
	else cout << "Error agregando distrito4" << endl;
	heDistrito->mostrarArchivoDeHash();

	cout << "Inicio de carga de Cargos posibles" << endl;
	this->iniciarCargosParaIntegracion();
	cout << "Fin de carga de Cargos posibles" << endl;
	this->cargo2 = new Cargo ("Gobernador");
	this->cargo2->agregarCargo("Vice Gobernador");
	this->registroCargo2 = new Registro(cargo2);
	if (administrador->altaHash(this->heCargo,this->registroCargo2)==operacionOK )
		cout << "Se agrego un cargo2" << endl;
	else cout << "Error agregando cargo2" << endl;
	heCargo->mostrarArchivoDeHash();

	cout << "Inicio de carga de Elecciones pasadas" << endl;
	this->iniciarEleccionesParaIntegracion();
	cout << "Fin de carga de Elecciones pasadas" << endl;
	this->eleccion4 = new Eleccion ("19970702","Gobernador");
	this->eleccion4->agregarDistrito("Chaco");
	this->eleccion4->agregarDistrito("Misiones");
	this->eleccion4->agregarDistrito("Formosa");
	this->eleccion4->agregarDistrito("Corrientes");
	this->eleccion4->agregarDistrito("Chaco");
	this->eleccion4->agregarDistrito("Ciudad Autonoma de Buenos Aires");
	this->eleccion4->agregarDistrito("Buenos Aires");
	this->eleccion4->agregarDistrito("Catamarca");
	this->eleccion4->agregarDistrito("Chubut");
	this->eleccion4->agregarDistrito("Cordoba");
	this->eleccion4->agregarDistrito("Entre Rios");
	this->eleccion4->agregarDistrito("Corrientes");
	this->eleccion4->agregarDistrito("Jujuy");
	this->eleccion4->agregarDistrito("La Pampa");
	this->eleccion4->agregarDistrito("La Rioja");
	this->eleccion4->agregarDistrito("Mendoza");
	this->eleccion4->agregarDistrito("Neuquen");
	this->eleccion4->agregarDistrito("Rio Negro");
	this->eleccion4->agregarDistrito("Salta");
	this->eleccion4->agregarDistrito("San Luis");
	this->eleccion4->agregarDistrito("Santa Cruz");
	this->eleccion4->agregarDistrito("Santa Fe");
	this->eleccion4->agregarDistrito("Santiago del Estero");
	this->eleccion4->agregarDistrito("Tucuman");
	this->eleccion4->agregarDistrito("Tierra del Fuego");
	this->registroEleccion4 = new Registro(eleccion4);
	if (administrador->altaHash(this->heEleccion,this->registroEleccion4)==operacionOK )
		cout << "Se agrego una eleccion4" << endl;
	else cout << "Error agregando eleccion4" << endl;
	heEleccion->mostrarArchivoDeHash();

	cout << "Inicio de carga de Candidatos pasados" << endl;
	this->iniciarCandidatosParaIntegracion();
	cout << "Fin de carga de Elecciones pasadas" << endl;
	this->candidato4 = new Candidato ("19970702","Gobernador","VodkaTonic",4);
	this->registroCandidato4 = new Registro(candidato4);
	if (administrador->altaHash(this->heCandidato,this->registroCandidato4)==operacionOK )
		cout << "Se agrego un candidato4" << endl;
	else cout << "Error agregando candidato4" << endl;
	heCandidato->mostrarArchivoDeHash();

	cout << "Inicio de carga de Listas de elecciones pasadas" << endl;
	this->iniciarListasParaIntegracion();
	cout << "Fin de carga de Listas de elecciones pasadas" << endl;

	this->lista4 = new Lista ("Socialista","19970702","Gobernador");
	this->registroLista4 = new Registro(lista4);
	if (administrador->altaArbol(this->arbolB,this->registroLista4)==0)
		cout << "Se agrego una Lista4" << endl;
	else cout << "Error agregando lista4" << endl;
	this->verContenidoArbolListas();
}




void SimulacionSistema::levantarBaseDeDatos(Administrador* administrador) {

//      NUEVO
        cout << "Inicio de Levante de padron electoral" << endl;
        char archivoDeControl1[]="archivoDeControlVotante.txt";
        char archivoDeDatos1[]="archivoDeDatosVotante.txt";
        this->heVotante = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos1,archivoDeControl1);
        heVotante->mostrarArchivoDeHash();

        cout << "Inicio de Levante de distritos" << endl;
        char archivoDeControl2[]="archivoDeControlDistrito.txt";
        char archivoDeDatos2[]="archivoDeDatosDistrito.txt";
        this->heDistrito = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos2,archivoDeControl2);
        heDistrito->mostrarArchivoDeHash();

        cout << "Inicio de Levante de Cargos posibles" << endl;
        char archivoDeControl3[]="archivoDeControlCargo.txt";
        char archivoDeDatos3[]="archivoDeDatosCargo.txt";
        this->heCargo = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos3,archivoDeControl3);
        heCargo->mostrarArchivoDeHash();

        cout << "Inicio de Levante de Elecciones pasadas" << endl;
        char archivoDeControl4[]="archivoDeControlEleccion.txt";
        char archivoDeDatos4[]="archivoDeDatosEleccion.txt";
        this->heEleccion = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos4,archivoDeControl4);
        heEleccion->mostrarArchivoDeHash();

        cout << "Inicio de Levante de Candidatos pasados" << endl;
        char archivoDeControl5[]="archivoDeControlCandidato.txt";
        char archivoDeDatos5[]="archivoDeDatosCandidato.txt";
        this->heCandidato = new HashingExtensible (LONGITUD_BLOQUE,archivoDeDatos5,archivoDeControl5);
        heCandidato->mostrarArchivoDeHash();

        cout << "Inicio de Levante de Listas de elecciones pasadas" << endl;
        arbolB = new bplustree();
        arbolB->opentree("arbolDeListas",LONGITUD_BLOQUE);
}


void SimulacionSistema::habilitarElecciones(Administrador* administrador){
	//	El administrador habilita una eleccion valida que esta en el archivo de elecciones
	//	creacion auxiliar de 3 registros para que el obtenerRegistro del bucket pueda obtener la clave del registro que busco
	Eleccion* eleccionAHabilitar1 = new Eleccion ("19970701","Presidente");
	Eleccion* eleccionAHabilitar2 = new Eleccion ("19970701","Presidente");
	Eleccion* eleccionAHabilitar3 = new Eleccion ("19970702","Gobernador");
	Registro* registroAHabilitar1 = new Registro (eleccionAHabilitar1);
	Registro* registroAHabilitar2 = new Registro (eleccionAHabilitar2);
	Registro* registroAHabilitar3 = new Registro (eleccionAHabilitar3);
	delete eleccionAHabilitar1;
	delete eleccionAHabilitar2;
	delete eleccionAHabilitar3;
	Registro* miRegistro = this->heEleccion->obtenerRegistro(registroAHabilitar1);
	Eleccion* eleccion = (Eleccion*)miRegistro->getContenido();
	administrador->habilitarEleccion(eleccion);
	delete eleccion;
	delete miRegistro;
	miRegistro = this->heEleccion->obtenerRegistro(registroAHabilitar2);
	eleccion = (Eleccion*)miRegistro->getContenido();
	administrador->habilitarEleccion(eleccion);
	delete eleccion;
	delete miRegistro;
	miRegistro = this->heEleccion->obtenerRegistro(registroAHabilitar3);
	eleccion = (Eleccion*)miRegistro->getContenido();
	administrador->habilitarEleccion(eleccion);
	delete eleccion;
	delete miRegistro;
	delete registroAHabilitar1;
	delete registroAHabilitar2;
	delete registroAHabilitar3;
}

bool SimulacionSistema::inicioDeSimulacion(Administrador* administrador,AdministradorDeVotaciones* administradorDeConteo, char modo, int cantidadDeSimulaciones){
	Log log;
	log.abrir();
	cout << endl;
	cout << "Bienvenido al sistema de voto electronico de los Gutierrez" << endl;
	cout << endl;
	srand (time(NULL));
	// Cargar archivoDeConteo con las listas que participan en la actual eleccion.
		cargarArchivoDeConteo(administrador,administradorDeConteo);

	//	ingresa el votante
	for (int k=1; k <= cantidadDeSimulaciones;k++) {
		int numeroDeEleccion;
		int dni;
		char c;
		bool ok=false;
		bool seguir = true;
		Registro* registroAuxiliar;
		Votante* votanteActual = new Votante (k,"","","","");
		if (modo=='a') {
			Registro* reg = new Registro(votanteActual);
			delete votanteActual;
			registroAuxiliar = this->heVotante->obtenerRegistro(reg);
			delete reg;
			if (!registroAuxiliar) {
				cout << "NO EXISTE EN EL PADRON" << endl;
				votanteActual = (Votante*) registroAuxiliar->getContenido();
				dni=votanteActual->getDNI();
				log.insertarMensajeConEntero(dni);
				delete votanteActual;
				delete registroAuxiliar;
				seguir=false;
			}
		}
		else{
			while (!ok) {
				cout << "Ingrese su DNI: " << endl;
				cin >> dni;
				cout << "Su dni es: " << dni << endl;
				while (!ok) {
					cout << "Presione ""S"" para confirmar, ""N"" para cancelar" << endl;
					cin >> c;
					if ((c=='s')||(c=='n')) ok=true;
					else cout << "Tecla no reconocida" << endl;
				}
				if (c=='n') ok=false;
			}
			delete votanteActual;
			votanteActual = new Votante (dni,"","","","");
			Registro* reg = new Registro(votanteActual);
			delete votanteActual;
			registroAuxiliar = this->heVotante->obtenerRegistro(reg);
			delete reg;
			if (!registroAuxiliar) {
				cout << "NO EXISTE EN EL PADRON" << endl;
				log.insertarMensajeConEntero(dni);
				seguir=false;
				delete registroAuxiliar;
			}
		}
		if (seguir) {
			votanteActual = (Votante*) registroAuxiliar->getContenido();
			delete registroAuxiliar;
			string mensaje= " Ingreso el votante: ";
			log.insertarMensajeConEntidad(votanteActual,mensaje);
			cout << "Bienvenido " << votanteActual->getNombre() << endl;
			string password;
			cout << "Ingrese su Password" << endl;
			if (modo=='a') password = votanteActual->getPassword();
			else cin >> password;
			if (password == votanteActual->getPassword()) {
				cout << "INGRESO AUTORIZADO" << endl;
				cout << endl;
				//			carga listaDeEleccionesDelVotante, de las habilitadas solo las de su distrito que no haya votado anteriormente
				if (administrador->consultarEleccionesHabilitadasParaElVotante(votanteActual)) {
					ok=false;
					while (!ok){
						cout << "Indique el numero de eleccion en la cual desea sufragar" << endl;
						int n;
						if (modo=='a') n = (rand()%((administrador->getListaDeEleccionesDelVotante()).size()))+1;
//						if (modo=='a') n=1;
						else cin >> n;
						if (((n)<=((int)((administrador->getListaDeEleccionesDelVotante()).size()))) && (n>0)) {
							while (!ok) {
								cout << "Usted eligio la eleccion " << n << endl;
								cout << "Si es correcto presione s sino n" << endl;
								numeroDeEleccion=n;
								if (modo=='a') c='s';
								else cin >> c;
								if ((c=='s')||(c=='n')) ok=true;
								else cout << "Tecla incorrecta" << endl;
							}
							if (c=='s') ok=true;
							else ok=false;
						}
						else cout << "Numero invalido" << endl;
					}
					//			me posiciono en la eleccion elegida dentro de la lista del votante
					list<Eleccion*> listaDelVotante = administrador->getListaDeEleccionesDelVotante();
					list<Eleccion*>::iterator itListaDelVotante = listaDelVotante.begin();
					for (int i=0;i<numeroDeEleccion-1;i++) itListaDelVotante++;
					//			agrego la eleccion elegida a elecciones anteriores del votante
					votanteActual->agregarEleccion((*itListaDelVotante)->getFecha(),(*itListaDelVotante)->getCargo());
					//			actualizo el registro en el hash de votante
					registroAuxiliar = new Registro (votanteActual);
					this->heVotante->modificarRegistro(registroAuxiliar);
					delete registroAuxiliar;
					mensaje = "El votante participara en la eleccion: ";
					log.insertarMensajeConEntidad(*itListaDelVotante,mensaje);
					ok=false;
					int boleta;
					//			cargo las listas que puede elegir el votante en esta eleccion
					administrador->cargarListasDeEleccion(*itListaDelVotante,this->arbolB);
					while (!ok) {
						while (!ok) {
							boleta = administrador->elegirBoleta(modo);
							if (!boleta) return 0;
							c=administrador->sufragar(boleta,modo);
							if ((c=='s')||(c=='n')) ok=true;
							else cout << "Tecla no reconocida" << endl;
						}
						if (c=='n') ok=false;
					}
					list<Lista*> listaBoletas = administrador->getListaDeBoletas();
					list<Lista*>::iterator itBoletas = listaBoletas.begin();
					int size = listaBoletas.size();
					if ( boleta==size+1 ) {
						string mensaje="El votante voto en blanco ";
						log.insertarMensaje(mensaje);
					}
					else if ( boleta==size+2 ){
						string mensaje="El votante voto impugnado, nulo, etc ";
						log.insertarMensaje(mensaje);
					}
					else {
						//	me posiciono en la lista elegida de las opciones dadas
						for (int i=0; i< boleta-1;i++) itBoletas++;
						string mensaje="El votante voto lista: ";
						log.insertarMensajeConEntidad(*itBoletas,mensaje);
					}
					//		INCREMENTAR CLASE CONTEO
					string nombreDeLista = (*itBoletas)->getNombre();
					string nombreDelDistrito = votanteActual->getDistrito();
					cout << nombreDeLista << endl;
					cout << nombreDelDistrito << endl;
					administradorDeConteo->incrementarVoto(*itListaDelVotante,&nombreDeLista,&nombreDelDistrito);
				}
			}
			else {
				cout << "PASSWORD INVALIDO" << endl;
				string mensaje="Intento de ingreso con password invalido";
				log.insertarMensaje(mensaje);
			}
			log.insertarMensajeSeparador(k);
			delete votanteActual;
			administrador->destruir();
		}
	}
	log.cerrar();
	return 1;
}

void SimulacionSistema::main (int argc,const char* argv[]) {

	Configuracion conf(argc,argv);

	string nombreDePrograma = ".//ArchivosAuxiliares//password";
	string pathArchivoConteo = ".//ArchivosAuxiliares//ArchivoDeConteo.bin";
	string pathIndiceSecundario = ".//ArchivosAuxiliares//IndiceSecundario.bin";

	Administrador* administrador = new Administrador (nombreDePrograma);

	AdministradorDeVotaciones* administradorDeConteo = new AdministradorDeVotaciones();
	administradorDeConteo->nuevoArchivoDeConteo(pathArchivoConteo,pathIndiceSecundario,LONGITUD_BLOQUE);

//	intenta acceder al sistema con usuario incorrecto pero contraseña correcta
	if ((administrador->acceder("undomiel","1")) || (administrador->acceder("1","aragorn")) || (administrador->acceder("",""))) cout << "SEGURIDAD VIOLADA" << endl;

	if (administrador->acceder("undomiel","aragorn")) {
		cout << "INGRESO APROBADO" << endl;
		cout << "Bienvenido al sistama de gestion de elecciones" << endl;
		char modo = 'm';
		this->cargarBaseDeDatos(administrador,'m');
//		this->levantarBaseDeDatos(administrador);
		//	habilita ciertas elecciones del archivo de elecciones
		this->habilitarElecciones(administrador);
		administrador->getEleccionesHabilitadas();
		this->inicioDeSimulacion(administrador,administradorDeConteo,'a',4);
	}
	else cout << "ERROR EN EL NOMBRE DE USUARIO O PASSWORD" << endl;
	delete administrador;

	administradorDeConteo->mostrarArchivoPrincipalEnFormatoTabla();
	administradorDeConteo->mostrarArchivoSecundario();

	//cout << "********* GENERO EL INFORME POR ELECCION **********" << endl;
	Eleccion* eleccion = new Eleccion("19970702","Gobernador");
	administradorDeConteo->generarInformePorEleccion(eleccion);
	delete eleccion;

	//cout << "********* GENERO EL INFORME POR LISTA **********" << endl;
	Lista* lista = new Lista("Socialista","19970702","Gobernador");
	administradorDeConteo->generarInformePorLista(lista,heCargo);
	delete lista;

	//cout << "********* GENERO EL INFORME POR DISTRITO **********" << endl;
	Distrito* distrito = new Distrito("Misiones");
	administradorDeConteo->generarInformePorDistrito(distrito);
	delete distrito;

	delete administradorDeConteo;

	remove(pathArchivoConteo.c_str());
	remove(pathIndiceSecundario.c_str());
}


