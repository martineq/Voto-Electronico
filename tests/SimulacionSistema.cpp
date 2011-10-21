/*
 * SimulacionSistema.cpp
 *
 *  Created on: 20/10/2011
 *      Author: daniel
 */

#include "SimulacionSistema.h"

SimulacionSistema::SimulacionSistema(){}

SimulacionSistema::~SimulacionSistema(){
	delete votante4;
	delete distrito4;
	delete eleccion4;
	delete candidato4;
	delete lista4;
	delete cargo2;
	delete registroVotante1;
	delete registroVotante2;
	delete registroVotante3;
	delete registroVotante4;
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
	remove("arbolDeListas");
}

void SimulacionSistema::iniciarVotantesParaIntegracion() {
	this->votante1 = new Votante(1,"Martin","m","","Recoleta");
	this->votante1->agregarEleccion ("19970701","Presidente");
	this->votante1->agregarEleccion ("19970701","Gobernador");
	this->votante2 = new Votante(2,"Lucas","l","","Recoleta");
	this->votante2->agregarEleccion ("19970701","Presidente");
	this->votante2->agregarEleccion ("19970701","Gobernador");
	this->votante3 = new Votante(3,"Daniel","d","","Recoleta");
	this->votante3->agregarEleccion ("19970701","Presidente");
	this->votante3->agregarEleccion ("19970701","Gobernador");
	this->registroVotante1 = new Registro(votante1);
	this->registroVotante2 = new Registro(votante2);
	this->registroVotante3 = new Registro(votante3);
	delete this->votante1;
	delete this->votante2;
	delete this->votante3;
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
}

void SimulacionSistema::iniciarDistritosParaIntegracion(){
	this->distrito1 = new Distrito("Recoleta");
	this->distrito2 = new Distrito("Retiro");
	this->distrito3 = new Distrito("Mataderos");
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
	this->eleccion1 = new Eleccion("19970701","Presidente");
	this->eleccion1->agregarDistrito("Recoleta");
	this->eleccion1->agregarDistrito("Retiro");
	this->eleccion1->agregarDistrito("Mataderos");
	this->eleccion1->agregarDistrito("Colegiales");
	this->eleccion2 = new Eleccion("19970701","Gobernador");
	this->eleccion2->agregarDistrito("Recoleta");
	this->eleccion2->agregarDistrito("Retiro");
	this->eleccion2->agregarDistrito("Mataderos");
	this->eleccion2->agregarDistrito("Colegiales");
	this->eleccion3 = new Eleccion("19970702","Presidente");
	this->eleccion3->agregarDistrito("Recoleta");
	this->eleccion3->agregarDistrito("Retiro");
	this->eleccion3->agregarDistrito("Mataderos");
	this->eleccion3->agregarDistrito("Colegiales");
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

void SimulacionSistema::cargarBaseDeDatos(Administrador* administrador) {
	cout << "Inicio de carga de padron electoral" << endl;
	this->iniciarVotantesParaIntegracion();
	cout << "Se cargo el padron electoral" << endl;
	cout << "Se carga un votante nuevo" << endl;
	this->votante4 = new Votante(4,"Ignacio","i","","Recoleta");
	this->votante4->agregarEleccion ("19970701","Presidente");
	this->votante4->agregarEleccion ("19970701","Gobernador");
	this->registroVotante4 = new Registro(votante4);
	if (administrador->altaHash(this->heVotante,this->registroVotante4)==operacionOK )
		cout << "Se agrego un votante" << endl;
	else cout << "Error agregando votante4" << endl;
	heVotante->mostrarArchivoDeHash();

	cout << "Inicio de carga de distritos" << endl;
	this->iniciarDistritosParaIntegracion();
	this->distrito4 = new Distrito("Colegiales");
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
	this->eleccion4->agregarDistrito("Recoleta");
	this->eleccion4->agregarDistrito("Retiro");
	this->eleccion4->agregarDistrito("Mataderos");
	this->eleccion4->agregarDistrito("Colegiales");
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

//	NUEVO
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

bool SimulacionSistema::inicioDeSimulacion(Administrador* administrador){
	//	Se abre el Log
	Log log;
	log.abrir();
	//	Inicio del sistema
	this->habilitarElecciones(administrador);
	administrador->getEleccionesHabilitadas();
	//	ingresa el votante1
	int numeroDeEleccion;
	int dni;
	char c;
	cout << endl;
	cout << "Bienvenido al sistema de voto electronico de los Gutierrez" << endl;
	cout << endl;
	bool ok=false;
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
	Votante* votanteActual = new Votante(dni,"","","","");
	Registro* reg = new Registro(votanteActual);
	delete votanteActual;
	Registro* registroAuxiliar = this->heVotante->obtenerRegistro(reg);
	delete reg;
	if (!registroAuxiliar) {
		cout << "NO EXISTE EN EL PADRON" << endl;
		log.insertarMensajeConEntero(dni);
		delete registroAuxiliar;
	}
	else {
		string mensaje= " Ingreso el votante: ";
		votanteActual = (Votante*)registroAuxiliar->getContenido();
		log.insertarMensajeConEntidad(votanteActual,mensaje);
		cout << "Bienvenido " << votanteActual->getNombre() << endl;
		string password;
		cout << "Ingrese su Password" << endl; cin >> password;
		if (password.compare(votanteActual->getPassword())) {
			cout << "INGRESO AUTORIZADO" << endl;
			cout << endl;
			administrador->consultarEleccionesHabilitadasParaElVotante(votanteActual);
			ok=false;
			while (!ok){
				cout << "Indique el numero de eleccion en la cual desea sufragar" << endl;
				int n;
				cin >> n;
				if (((n)<=((int)((administrador->getListaDeEleccionesHabilitadas()).size()))) && (n>0)) {
					while (!ok) {
						cout << "Usted eligio la eleccion " << n << endl;
						cout << "Si es correcto presione s sino n" << endl;
						numeroDeEleccion=n;
						cin >> c;
						if ((c=='s')||(c=='n')) ok=true;
						else cout << "Tecla incorrecta" << endl;
					}
					if (c=='s') ok=true;
					else ok=false;
				}
				else cout << "Numero invalido" << endl;
			}
			//		hasheo la eleccion
			list<Eleccion*> listaHabilitadas= (administrador->getListaDeEleccionesHabilitadas());
			list<Eleccion*>::iterator itHabilitadas = listaHabilitadas.begin();
			for (int i=0;i<numeroDeEleccion-1;i++) itHabilitadas++;
			votanteActual->agregarEleccion((*itHabilitadas)->getFecha(),(*itHabilitadas)->getCargo());
			mensaje = "El votante participara en la eleccion: ";
			log.insertarMensajeConEntidad(*itHabilitadas,mensaje);
			ok=false;
			int boleta;
			administrador->cargarListasDeEleccion(*itHabilitadas,this->arbolB);
			while (!ok) {
				while (!ok) {
//					boleta = administrador->elegirBoleta(numeroDeEleccion,this->bucketLista);
					boleta = administrador->elegirBoleta();
					if (!boleta) return 0;
					c=administrador->sufragar(boleta);
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
			delete votanteActual;
			delete registroAuxiliar;
		}
		else {
			cout << "PASSWORD INVALIDO" << endl;
			string mensaje="Intento de ingreso con password invalido";
			log.insertarMensaje(mensaje);
		}
		log.cerrar();
	}
}

void SimulacionSistema::main () {
	string nombreDePrograma = ".//doc//password";
	Administrador* administrador = new Administrador (nombreDePrograma);

//	intenta acceder al sistema con usuario incorrecto pero contraseña correcta
	if ((administrador->acceder("undomiel","1")) || (administrador->acceder("1","aragorn")) || (administrador->acceder("",""))) cout << "SEGURIDAD VIOLADA" << endl;

	if (administrador->acceder("undomiel","aragorn")) {
		cout << "INGRESO APROBADO" << endl;
		cout << "Bienvenido al sistama de gestion de elecciones" << endl;
		this->cargarBaseDeDatos(administrador); // Esto se corre una sola vez, luego se usan los archivos bin
//		this->levantarBaseDeDatos(administrador); // Con esto se carga lo que llenó po unica vez el "cargarBaseDeDatos"
	}
	else cout << "ERROR EN EL NOMBRE DE USUARIO O PASSWORD" << endl;
	delete administrador;
}
