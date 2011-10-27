/*
 * InterfazVotante.cpp
 *
 *  Created on: 21/10/2011
 *      Author: lucas
 */

#include "InterfazAdministrador.h"

bool InterfazAdministrador::validarRespuesta(){
	string tecla;
	getline(cin,tecla);

	bool respuesta = false;
	bool continuar = true;
	while ( continuar ){

		continuar = false;
		if ( tecla.compare("S") == 0 )
			respuesta = true;
		else if ( tecla.compare("N") != 0 ){
			cout << endl << "Opción ingresada: " << tecla << " invalida. Reinténtelo, S/N: ";
			getline(cin,tecla);
			continuar = true;
		}

	}
	cout << endl;
	return respuesta;
}

InterfazAdministrador::InterfazAdministrador(Configuracion* configuracion) {
	this->config = configuracion;
	this->rutaArbol = config->pathArbol();
	this->rutaHash = config->pathHash();
	this->longitud = config->darTamanioBucket();
	this->longitudNodo = config->darTamanioNodo();
	dummy = new string();
}

void InterfazAdministrador::ingresoAdministrador(Administrador * administrador){
	string usuario,password;
	string tecla = "P";
	cout <<"Ingrese su nombre de usuario: ";
	getline(cin,usuario);
	cout <<endl<<"Ahora ingrese su contraseña: ";
	getline(cin,password);
	cout <<endl;
	cout << "usuario: <"<<usuario<<">"<<endl;
	cout << "password: <"<<password<<">"<<endl;

	if (administrador->acceder(usuario,password)){
		cout << "INGRESO APROBADO" << endl;
		cout << "Bienvenido al sistama de gestion de elecciones" << endl;

		while (tecla.compare("N") != 0 and tecla.compare("S") != 0){
			cout << "¿ Desea eliminar la base de datos y comenzar de 0? S/N"<<endl;
			getline(cin,tecla);
			cout << endl;
			if (tecla.compare("S") == 0) {
				string pathABorrar = this->rutaHash+HASH_VOTANTE;
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+HASH_VOTANTE_CONTROL;
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+HASH_DISTRITO;
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+HASH_DISTRITO_CONTROL;
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+HASH_ELECCION;
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+HASH_ELECCION_CONTROL;
				(pathABorrar.c_str());
				pathABorrar = this->rutaHash+HASH_CANDIDATO;
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+HASH_CANDIDATO_CONTROL;
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+HASH_CARGO;
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+HASH_CARGO_CONTROL;
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaArbol+ARBOL_DE_LISTAS;
				remove (pathABorrar.c_str());
			} else {
				if (tecla.compare("N") != 0){
					cout <<"Tecla inválida. Repita proceso.";
				}
			}
		}

		bool parar = false;
		while (! parar){
			parar = this->mostrarMenuAdministrador(administrador);
		}

		cout << "Adios!!"<<endl;


	}else{
		cout << "Nombre de usuario o contraseña incorrecto. Adiós!"<<endl;
	}

}



bool InterfazAdministrador::mostrarMenuAdministrador(Administrador * administrador){
	string opcion = "0";
	int i = 0;
	while ((i < 1) or (i > 10)){
		cout << "Opciones: "<<endl<<endl;
		cout << "1) Mantener Distritos"<<endl;
		cout << "2) Mantener Votantes"<<endl;
		cout << "3) Mantener Cargos"<<endl;
		cout << "4) Mantener Listas"<<endl;
		cout << "5) Mantener Candidatos"<<endl;
		cout << "6) Mantener Elecciones"<<endl;
		cout << "7) Habilitar Elecciones"<<endl;
		cout << "8) Habilitar Votantes para elección"<<endl;
		cout << "9) Informar Resultados"<<endl;
		cout << "10) salir"<<endl;
		cout << "Opcion: ";

		cin >> opcion;
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

		cout << endl;
		if (isANumber(opcion) == 1){
			i = atoi(opcion.c_str());
		}
		else{
			i = 0;
		}

	}

	switch (i)
	{
	case 1  : mostrarMenuDistritos(administrador);break;
	case 2  : mostrarMenuVotantes(administrador);break;
	case 3  : mostrarMenuCargos(administrador);break;
	case 4  : mostrarMenuListas(administrador);break;
	case 5  : mostrarMenuCandidatos(administrador);break;
	case 6  : mostrarMenuElecciones(administrador);break;
	case 7  : habilitarElecciones(administrador);break;
	case 8  : comienzoVotacion(administrador);break;
	case 9  : mostrarMenuInformes(administrador);break;
	case 10 : return true;
	}

	return false;

}

int InterfazAdministrador::isANumber(string &cad){
  short int largov=cad.size(),ret=0;
  bool cond=true;
  for(int i=0; (cond) && (i<largov);i++){//Valido que sea numero( ya sea int o float)
		  const char a=cad.at(i);
		  if (((a<48) || (a>57))) cond=false;
  }
  if (cond){
	  ret= 1;
  }else{
	  ret =0;
  }
   return ret;
}

void InterfazAdministrador::imprimirRespuesta(Resultados res){
	switch (res)
	{
	case bucketDisponible    : cout << "Bucket Disponible" <<endl;break;
	case bucketLibre 	     : cout << "Bucket Libre" <<endl;break;
	case bucketNoDisponible	 : cout << "Bucket no Disponible"<<endl;break;
	case bucketNULO			 : cout << "Bucket Nulo"<<endl;break;
	case operacionOK         : cout << "Operacion OK"<<endl;break;
	case operacionFALLO		 : cout << "Operacion Fallada"<<endl;break;
	case claveRepetida		 : cout << "Clave Repetida"<<endl;break;
	case registroInexistente : cout << "Registro Inexistente"<<endl;break;

	}

}

void InterfazAdministrador::mostrarMenuDistritos(Administrador * administrador){

	string pathDatos 	= rutaHash + HASH_DISTRITO;
	string pathControl 	= rutaHash + HASH_DISTRITO_CONTROL;

	HashingExtensible * heDistrito = new HashingExtensible (this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());


	string opcion = "0";
	string nombreDistrito;
	int i = 0;
	Distrito * distrito = NULL;
	Registro * registro = NULL;

	while (true){
		while ((i < 1) or (i > 5)){
			cout << "Opciones: "<<endl<<endl;
			cout << "1) Alta Distrito"<<endl;
			cout << "2) Baja Distrito"<<endl;
			cout << "3) Modificar Distrito"<<endl;
			cout << "4) Volver atrás"<<endl;
			cout << "5) Ver Distritos"<<endl;
			cout << "Opcion: ";
			getline(cin,opcion);
			cout <<endl;

			if (isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}
			else{
				i = 6;
			}

		}

		if ((i == 1) or (i == 2)){

			cout << "Ingrese el nombre del distrito: ";
			getline(cin,nombreDistrito);
			cout << endl;

			distrito = new Distrito(nombreDistrito);
			registro = new Registro(distrito);
			delete (distrito);
		}
		switch (i)
		{
		case 1 : {
			Resultados rta = administrador->altaHash(heDistrito,registro);
			imprimirRespuesta(rta);
			delete (registro);
		}break;
		case 2 : {
			Resultados rta = administrador->bajaHash(heDistrito,registro);
			delete (registro);
			imprimirRespuesta(rta);
		}break;
		case 3 : {
			cout<<"No puede modificarse un distrito!!"<<endl;
		}break;
		case 4 : {
			delete (heDistrito);
			return;
		}break;
		case 5: {
			heDistrito->mostrarArchivoDeHash();
			break;
		}
		}
		i = 0;
	}

}

void InterfazAdministrador::mostrarMenuVotantes(Administrador * administrador){

	string pathDatos 	= rutaHash + HASH_VOTANTE;
	string pathControl 	= rutaHash + HASH_VOTANTE_CONTROL;

	HashingExtensible * heVotante = new HashingExtensible (this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	pathDatos 			= rutaHash + HASH_DISTRITO;
	pathControl 		= rutaHash + HASH_DISTRITO_CONTROL;

	HashingExtensible * heDistrito = new HashingExtensible(this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	string opcion = "0";
	int dni = 0;
	string DNIString,nombre,apellido,apeNom,clave,dom,nombreDistrito;
	int i = 0;
	Votante * votante = NULL;
	Registro * registro = NULL;
	bool errorCarga = false;

	while (true){
		while ((i < 1) or (i > 6)){
			cout << "Opciones: "<<endl<<endl;
			cout << "1) Alta Votante"<<endl;
			cout << "2) Baja Votante"<<endl;
			cout << "3) Modificar Votante"<<endl;
			cout << "4) Volver atrás"<<endl;
			cout << "5) Alta Automática"<<endl;
			cout << "6) Ver votantes"<<endl;
			cout << "Opcion: ";
			cin >> opcion;
			cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
			cout <<endl;
			if (isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}
			else {
				i = 0;
			}

		}

		if ((i != 4) and (i != 5) and (i != 6)){

			//Ingresar DNI Válido
			while (dni < 1){
				cout << "Ingrese el DNI del votante: ";
				getline(cin,DNIString);
				cout <<endl;
				if (isANumber(DNIString) == 1){
					dni = atoi(DNIString.c_str());
				}
			}

			if (i != 2){

				//Ingresar apellido y nombre
				cout << "Ingrese nombre: ";
				getline(cin,nombre);
				cout<<endl;

				cout << "Ingrese apellido: ";
				getline(cin,apellido);
				cout << endl;

				apeNom = nombre+" "+apellido;

				//Ingresar Clave
				cout << "Ingrese la clave: ";
				getline(cin,clave);
				cout <<endl;
				cout << "Clave: "<<clave<<endl;;

				//Ingresar Domicilio
				cout << "Ingrese el domicilio: ";
				getline(cin,dom);
				cout << endl;
				cout << "dom: "<<dom<<endl;

				//Ingresar Distrito
				cout << "Ingrese el nombre del distrito: ";
				getline(cin,nombreDistrito);
				cout << endl;
				cout << "Distrito: "<< nombreDistrito << endl;

				Distrito * distrito = new Distrito(nombreDistrito);
				Registro * registroDistrito = new Registro(distrito);
				Registro * registroDistritoObtenido = heDistrito->obtenerRegistro(registroDistrito);
				if (registroDistritoObtenido == NULL){
					errorCarga = true;
				}
				delete (distrito);
				delete (registroDistrito);
				delete (registroDistritoObtenido);
			}else{
				apeNom = "";
				clave = "";
				dom = "";
				nombreDistrito = "";
			}
			votante = new Votante(dni,apeNom,clave,dom,nombreDistrito);
			registro = new Registro(votante);
			delete (votante);
		}
		switch (i)
		{
		case 1 : {
			if (! errorCarga) {
				Resultados rta = administrador->altaHash(heVotante,registro);
				delete (registro);
				imprimirRespuesta(rta);
			} else{
				cout << "Error de carga!! distrito inválido!!"<<endl;
			}
		}break;
		case 2 : {
			Resultados rta = administrador->bajaHash(heVotante,registro);
			delete (registro);
			imprimirRespuesta(rta);
		}break;
		case 3 : {
			if (! errorCarga){
				Resultados rta = administrador->modificaHash(heVotante,registro);
				delete (registro);
				imprimirRespuesta(rta);
			}
			else cout << "Operación FALLÓ, distrito inválido." << endl;
		}break;
		case 4: {
			delete heVotante;
			delete heDistrito;
			return;
		}break;
		case 5 : {
			int cantTotal;
			int cantIngr = 0;
			int cont = 1;
			cout << "Ingrese la cantidad de votantes a ingresar: ";
			cin >> cantTotal;
			cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
			while (cantIngr < cantTotal){
				CreadorVotante * creador = new CreadorVotante(cont);
				votante = creador->crearVotante(config);
				Distrito * distrito = new Distrito(votante->getDistrito());
				Registro * registroDistrito = new Registro(distrito);
				delete (distrito);
				Registro * registroDistritoObtenido = heDistrito->obtenerRegistro(registroDistrito);
				if (registroDistritoObtenido == NULL){
					heDistrito->agregarRegistro(registroDistrito);
				}
				delete (registroDistritoObtenido);
				delete (registroDistrito);
				registro = new Registro(votante);
				Resultados rta = administrador->altaHash(heVotante,registro);
				votante->verVotante();
				delete votante;
				delete registro;
				if (rta == operacionOK ) {
					cantIngr++;
				}
				cont++;
				delete creador;
			}
		}break;
		case 6 : {
			heVotante->mostrarArchivoDeHash();
			break;
		}
		}
		i = 0;
		dni = 0;
	}

}

void InterfazAdministrador::mostrarMenuElecciones(Administrador * administrador){

	string pathDatos	= rutaHash + HASH_DISTRITO;
	string pathControl	= rutaHash + HASH_DISTRITO_CONTROL;

	HashingExtensible * heDistrito = new HashingExtensible(longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	pathDatos			= rutaHash + HASH_ELECCION;
	pathControl			= rutaHash + HASH_ELECCION_CONTROL;

	HashingExtensible * heEleccion = new HashingExtensible (longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	pathDatos			= rutaHash + HASH_CARGO;
	pathControl			= rutaHash + HASH_CARGO_CONTROL;

	HashingExtensible * heCargo = new HashingExtensible (longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	pathDatos = rutaArbol + ARBOL_DE_LISTAS;
	bplustree * bLista = new bplustree();
//	bLista->opentree(archivoDeDatos,LONGITUD_BLOQUE);
	bLista->newtree((char*)pathDatos.c_str(),this->longitudNodo);


	string opcion = "0";
	string masDistritos = "S";
	string nombreDistrito,fecha,cargo;
	int i = 0;
	bool errorCarga = false;
	Eleccion * eleccion = NULL;
	Registro * registro = NULL;

	while (true){
		while ((i < 1) or (i > 5)){
			cout << "Opciones: "<<endl<<endl;
			cout << "1) Alta Eleccion"<<endl;
			cout << "2) Baja Eleccion"<<endl;
			cout << "3) Modificar Eleccion"<<endl;
			cout << "4) Volver atrás"<<endl;
			cout << "5) Ver elecciones"<<endl;
			cout << "Opcion: ";
			getline(cin,opcion);
			cout <<endl;
			if (isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}
			else {
				i = 0;
			}

		}

		if ((i != 4) and (i != 5)){
			bool fechaError = true;
			while (fechaError) {
				cout << "Ingrese la fecha de la elección: ";
				getline(cin,fecha);
				cout << endl;
				if (fecha.size() == 8) {
					string anioStr = fecha.substr(0,4);
					string mesStr = fecha.substr(4,2);
					string diaStr = fecha.substr(6,2);
					int dia = 0;
					int mes = 0;
					int anio = 0;
					if (isANumber(anioStr) == 1){
						anio = atoi(anioStr.c_str());
					}
					if (isANumber(mesStr) == 1){
						mes = atoi(mesStr.c_str());
					}
					if (isANumber(diaStr) == 1){
						dia = atoi(diaStr.c_str());
					}
					if ((anio >= 1980) and (anio <= 2020) and (mes > 0) and (mes <= 12)
						and (dia > 0) and (dia <= 30)){
						fechaError = false;
					}
				}
			}

			bool salir=false;
			while (salir==false){
				cout << "Ingrese el cargo: ";
				getline(cin,cargo);
				cout << endl;

				Cargo* unCargo = new Cargo (cargo);
				Registro* reg1 = new Registro (unCargo);
				delete unCargo;

				Registro* registroObtenido = heCargo->obtenerRegistro(reg1);
				delete reg1;

				if ( registroObtenido == NULL ){
					cout << "No existe cargo/cargo no valido. ";
					cout << "Desea reintentar ingresar el cargo. S/N : ";
					if ( validarRespuesta() == false ){
						salir		= true;
						errorCarga	= true;
					}
					cout << endl;
				}

				else {
					salir = true;
					delete registroObtenido;

					eleccion = new Eleccion(fecha,cargo);

					bool continuarCargaDistritos = true;
					while ( continuarCargaDistritos and  i!=2){

						cout << "Ingrese el nombre del distrito: ";
						getline(cin,nombreDistrito);
						cout << endl;

						Distrito* unDistrito = new Distrito (nombreDistrito);
						Registro* unRegistro = new Registro (unDistrito);
						delete unDistrito;

						registroObtenido = heDistrito->obtenerRegistro(unRegistro);
						delete unRegistro;

						if ( registroObtenido != NULL ) {

							delete registroObtenido;
							if ( eleccion->agregarDistrito(nombreDistrito) )
								cout << "Distrito agregado" << endl;

							cout << "¿Desea agregar más distritos? S/N: ";
							if ( validarRespuesta() == false )
								continuarCargaDistritos = false;
							cout << endl;
						}

						else {
							cout << "El distrito no existe. Desea Reintentar S/N: ";
							if ( validarRespuesta() == false )
								continuarCargaDistritos = false;
							cout << endl;
						}
					}

					registro = new Registro(eleccion);
					delete eleccion;
				}
			}
		}

		switch (i) {
			case 1 : {
					if ( errorCarga == false ){
						Resultados rta = administrador->altaHash(heEleccion,registro);
						delete registro;
						imprimirRespuesta(rta);
						if (rta == operacionOK){
							Lista * lista = new Lista("blanco",fecha,cargo);
							Registro * regLista = new Registro(lista);
							delete lista;
							administrador->altaArbol(bLista,regLista);
							delete regLista;
						}
						else cout << "La eleccion ya existe" << endl;

					}else cout << "Operacion FALLÓ. No se dio de alta el cargo: " << cargo << "."<<endl;
					break;
			}
			case 2 : {
				Resultados rta = administrador->bajaHash(heEleccion,registro);
				delete registro;
				imprimirRespuesta(rta);
				break;
			}
			case 3 : {
				Resultados rta = administrador->modificaHash(heEleccion,registro);
				delete registro;
				imprimirRespuesta(rta);
				break;
			}
			case 4 : {
				delete heEleccion;
				delete heDistrito;
				delete heCargo;
				delete bLista;
				return;
				break;
			}
			case 5 : {
				heEleccion->mostrarArchivoDeHash();
				break;
			}
		}

		i = 0;
	}
}

void InterfazAdministrador::mostrarMenuCargos(Administrador * administrador){

	string pathDatos 	= rutaHash + HASH_CARGO;
	string pathControl 	= rutaHash + HASH_CARGO_CONTROL;

	HashingExtensible * heCargo = new HashingExtensible (longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	string opcion = "0";
	string cargoPpal,subCargo;
	string masSubcargos = "S";
	int i = 0;
	Cargo * cargo = NULL;
	Registro * registro = NULL;

	while (true){
		while ((i < 1) or (i > 5)){
			cout << "Opciones: "<<endl<<endl;
			cout << "1) Alta Cargo"<<endl;
			cout << "2) Baja Cargo"<<endl;
			cout << "3) Modificar Cargo"<<endl;
			cout << "4) Volver atrás"<<endl;
			cout << "5) Ver cargos"<<endl;
			cout << "Opcion: ";
			getline(cin,opcion);
			cout <<endl;
			if ( isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		if ((i != 4) and (i != 5)){
			cout << "Ingrese el nombre del cargo principal: ";
			getline(cin,cargoPpal);
			cout << endl;
			cargo = new Cargo(cargoPpal);

			if ( i != 2){
				cout << "Desea agregar subcargos? (S/N)";
				if ( validarRespuesta() == true ){

					bool continuarAgregandoSubcargos = true;
					while ( continuarAgregandoSubcargos ){

						cout << "Ingrese el nombre del subcargo: ";
						getline(cin,subCargo);
						cout << endl;
						cargo->agregarCargo(subCargo);

						cout << "Desea agregar más subcargos? (ingrese 'S' para seguir)";
						if ( validarRespuesta() == false )
							continuarAgregandoSubcargos = false;
						cout <<endl;
					}
				}
				cout <<endl;
			}

			registro = new Registro(cargo);
			delete (cargo);
		}

		switch (i)
		{
		case 1 : {
			Resultados rta = administrador->altaHash(heCargo,registro);
			delete registro;
			imprimirRespuesta(rta);
		}break;
		case 2 : {
			Resultados rta = administrador->bajaHash(heCargo,registro);
			delete registro;
			imprimirRespuesta(rta);
		}break;
		case 3 : {
			Resultados rta = administrador->modificaHash(heCargo,registro);
			delete registro;
			imprimirRespuesta(rta);
		}break;
		case 4 : {
			delete heCargo;
			return;
		}
		case 5 : {
			heCargo->mostrarArchivoDeHash();
			break;
		}
		}
		i = 0;
	}

}



void InterfazAdministrador::mostrarMenuCandidatos(Administrador * administrador){

	string pathDatos	= rutaHash + HASH_CANDIDATO;
	string pathControl	= rutaHash + HASH_CANDIDATO_CONTROL;

	HashingExtensible * heCandidato = new HashingExtensible(longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	pathDatos			= rutaHash + HASH_VOTANTE;
	pathControl			= rutaHash + HASH_VOTANTE_CONTROL;

	HashingExtensible * heVotante = new HashingExtensible (longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	pathDatos			= rutaHash + HASH_CARGO;
	pathControl			= rutaHash + HASH_CARGO_CONTROL;

	HashingExtensible * heCargo = new HashingExtensible (longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	pathDatos = this->rutaArbol + ARBOL_DE_LISTAS;
	bplustree * bLista = new bplustree();
//	bLista->opentree(archivoDeDatos,LONGITUD_BLOQUE);
	bLista->newtree((char*)pathDatos.c_str(),this->longitudNodo);


	string opcion = "0";
	string fecha,cargo,nombre,DNIStr;
	int dni = 0;
	int i = 0;
	bool errorCarga = false;
	bool errorLista = false;
	bool errorVotante = false;
	bool errorCargo = true;
	Candidato * candidato = NULL;
	Registro * registro = NULL;

	while (true){
		while ((i < 1) or (i > 5)){
			cout << "Opciones: "<<endl<<endl;
			cout << "1) Alta Candidato"<<endl;
			cout << "2) Baja Candidato"<<endl;
			cout << "3) Modificar Candidato"<<endl;
			cout << "4) Volver atrás"<<endl;
			cout << "5) Mostrar Candidatos"<<endl;
			cout << "Opcion: ";
			cin >> opcion;
			cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

			cout <<endl;
			if ( isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		if ((i != 4) and (i != 3) and (i != 5)){

				while (dni == 0){
					cout << "Ingrese el numero de DNI: ";
					getline(cin,DNIStr);
					cout <<endl;
					if ( isANumber(DNIStr) == 1){
						dni = atoi(DNIStr.c_str());
					}
				}
				Votante * votante = new Votante(dni,"","","","");
				Registro * regVotante = new Registro(votante);

				delete votante;
				Registro * regVotanteHash = heVotante->obtenerRegistro(regVotante);

				if (regVotanteHash == NULL) {
					errorVotante = true;
				}
				delete regVotante;
				delete regVotanteHash;

			if (!errorVotante){
				bool fechaError = true;
				while (fechaError) {
					cout << "Ingrese la fecha de la elección: ";
					getline(cin,fecha);
					cout << endl;
					if (fecha.size() == 8) {
						string anioStr = fecha.substr(0,4);
						string mesStr = fecha.substr(4,2);
						string diaStr = fecha.substr(6,2);
						int anio = 0;
						int mes = 0;
						int dia = 0;
						if ( isANumber(anioStr) == 1){
							anio = atoi(anioStr.c_str());
						}
						if (isANumber(mesStr) == 1){
							mes = atoi(mesStr.c_str());
						}
						if (isANumber(diaStr) == 1){
							dia = atoi(diaStr.c_str());
						}
						if ((anio > 1980) and (anio < 2020) and (mes > 0) and (mes < 12)
							and (dia > 0) and (dia < 30)){
							fechaError = false;
						}
					}
				}

				cout << "Ingrese el cargo: ";
				getline(cin,cargo);
				cout << endl;

				Cargo * objetoCargo = new Cargo(cargo);
				Registro * registroCargo = new Registro(objetoCargo);
				Registro * registroCargoObtenido = heCargo->obtenerRegistro(registroCargo);
				if (registroCargoObtenido == NULL){
					errorCargo = true;
				}
				delete (objetoCargo);
				delete (registroCargo);
				delete (registroCargoObtenido);



				/* Agregar búsqueda si existe lista */

				cout << "Ingrese el nombre de la lista: ";
				getline(cin,nombre);
				cout << endl;

				/*----------------------------------*/
				candidato = new Candidato(fecha,cargo,nombre,dni);
				registro = new Registro(candidato);
				delete (candidato);
			}else{
				cout << "No existe el candidato!!"<<endl;
			}
		}

		if ((!errorCargo) and (!errorVotante) and (!errorLista)) {
			errorCarga = true;
		}
		switch (i)
			{
			case 1 : {
				if (!errorCarga){
					Resultados rta = administrador->altaHash(heCandidato,registro);
					imprimirRespuesta(rta);
				}
			}break;
			case 2 : {
				if (!errorCarga){
					Resultados rta = administrador->bajaHash(heCandidato,registro);
					imprimirRespuesta(rta);
				}
			}break;
			case 3 : {
				cout<<"No puede modificarse un candidato!!"<<endl;
			}break;
			case 4 : {
				delete heCandidato;
				delete heVotante;
				return;
			}
			case 5 : {
				heCandidato->mostrarArchivoDeHash();
				break;
			}
			}
			dni = 0;
			i = 0;
			if (i != 3){
				delete registro;
			};
			registro = NULL;

	}
}

void InterfazAdministrador::mostrarMenuInformes(Administrador * administrador){

	AdministradorDeVotaciones* administradorDeConteo = new AdministradorDeVotaciones();

	string pathArchivoConteo 	= rutaArbol + ARBOL_DE_CONTEO;
	string pathIndiceSecundario = rutaArbol + ARBOL_INDICE_SEC_CONTEO;

	administradorDeConteo->nuevoArchivoDeConteo(pathArchivoConteo,pathIndiceSecundario,config->darTamanioNodo());


	string opcion = "0";
	string fecha,cargo,nombreLista,nombreDelDistrito;

	int i = 0;
	Lista * lista = NULL;
	Eleccion* eleccion = NULL;
	Distrito* distrito = NULL;

	while (true){
		while ((i < 1) or (i > 6)){
			cout << "Opciones: "<<endl<<endl;
			cout << "1) Informe por elección"<<endl;
			cout << "2) Informe por lista"<<endl;
			cout << "3) Informe por distrito"<<endl;
			cout << "4) Volver atrás"<<endl;
			cout << "5) Mostrar archivo de conteo"<<endl;
			cout << "6) Mostrar archivo de conteo ordenado por distrito" << endl;
			cout << "Opcion: ";

			cin >> opcion;
			cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

			if ( isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		if ((i == 1) or (i == 2)){

			bool fechaError = true;
			while (fechaError) {
				cout << "Ingrese la fecha de la elección: ";
				getline(cin,fecha);
				cout << endl;
				if (fecha.size() == 8) {
					string anioStr = fecha.substr(0,4);
					string mesStr = fecha.substr(4,2);
					string diaStr = fecha.substr(6,2);
					int dia = 0;
					int mes = 0;
					int anio = 0;
					if (isANumber(anioStr) == 1){
						anio = atoi(anioStr.c_str());
					}
					if (isANumber(mesStr) == 1){
						mes = atoi(mesStr.c_str());
					}
					if (isANumber(diaStr) == 1){
						dia = atoi(diaStr.c_str());
					}
					if ((anio >= 1980) and (anio <= 2020) and (mes > 0) and (mes <= 12)
							and (dia > 0) and (dia <= 30)){
						fechaError = false;
					}
				}
			}

			cout << "Ingrese el cargo: ";
			getline(cin,cargo);

			if (i == 1){
				eleccion = new Eleccion(fecha,cargo);
			}
			else {

				cout << "Ingrese la lista: ";
				getline(cin,nombreLista);

				lista = new Lista(nombreLista,fecha,cargo);
			}


		}else if ( i == 3 ){

			cout << "Ingrese el nombre del distrito: ";
			getline(cin,nombreDelDistrito);

			distrito = new Distrito(nombreDelDistrito);
		}

		string enter;
		switch (i)
		{
		case 1 :
		{

			administradorDeConteo->generarInformePorEleccion(eleccion);

			cout << "Ingrese enter para continuar" << endl;
			getline(cin,*dummy);

			delete eleccion;
			eleccion = NULL;
			break;
		}
		case 2 :
		{
			string pathDatos	= this->rutaHash + HASH_CARGO;
			string pathControl	= this->rutaHash + HASH_CARGO_CONTROL;
			HashingExtensible* heCargo = new HashingExtensible(longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

			administradorDeConteo->generarInformePorLista(lista,heCargo);
			delete heCargo;

			cout << "Ingrese enter para continuar" << endl;
			getline(cin,*dummy);

			delete lista;
			lista  = NULL;
			break;
		}
		case 3 :
		{
			administradorDeConteo->generarInformePorDistrito(distrito);

			cout << "Ingrese enter para continuar" << endl;
			getline(cin,*dummy);

			delete distrito;
			distrito = NULL;
			break;
		}
		case 4 :
		{
			delete administradorDeConteo;
			return;
		}
		case 5:
		{
			administradorDeConteo->mostrarArchivoPrincipalEnFormatoTabla();

			cout << "Ingrese enter para continuar" << endl;
			getline(cin,*dummy);

			break;
		}
		case 6:
		{
			administradorDeConteo->mostrarArchivoPrincipalEnFormatoTablaOrdenadoPorClaveSecundaria();

			cout << "Ingrese enter para continuar" << endl;
			getline(cin,*dummy);

			break;
		}
		}
		i = 0;
	}
}

void InterfazAdministrador::mostrarMenuListas(Administrador * administrador){

	string pathDatos 	= rutaHash + HASH_CARGO;
	string pathControl 	= rutaHash + HASH_CARGO_CONTROL;

	HashingExtensible * heCargo = new HashingExtensible (longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	pathDatos			= rutaArbol + ARBOL_DE_LISTAS;
	bplustree * bLista	= new bplustree();
//	bLista->opentree(archivoDeDatos,LONGITUD_BLOQUE);
	bLista->newtree((char*)pathDatos.c_str(),this->longitudNodo);
	string opcion = "0";
	string fecha,cargo,nombreLista;

	int i = 0;
	Lista * lista = NULL;
	Registro * registro = NULL;

	while (true){
		while ((i < 1) or (i > 5)){
			cout << "Opciones: "<<endl<<endl;
			cout << "1) Alta Lista"<<endl;
			cout << "2) Baja Lista"<<endl;
			cout << "3) Modificar Lista"<<endl;
			cout << "4) Volver atrás"<<endl;
			cout << "5) Ver Listas" << endl;
			cout << "Opcion: ";
			getline(cin,opcion);
			cout <<endl;
			if ( isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		if ((i != 4) and (i != 3) and (i != 5)){

			bool fechaError = true;
			while (fechaError) {
				cout << "Ingrese la fecha de la elección: ";
				getline(cin,fecha);

				cout << endl;
				if (fecha.size() == 8) {
					string anioStr = fecha.substr(0,4);
					string mesStr = fecha.substr(4,2);
					string diaStr = fecha.substr(6,2);
					int dia = 0;
					int mes = 0;
					int anio = 0;
					if (isANumber(anioStr) == 1){
						anio = atoi(anioStr.c_str());
					}
					if (isANumber(mesStr) == 1){
						mes = atoi(mesStr.c_str());
					}
					if (isANumber(diaStr) == 1){
						dia = atoi(diaStr.c_str());
					}
					if ((anio >= 1980) and (anio <= 2020) and (mes > 0) and (mes <= 12)
						and (dia > 0) and (dia <= 30)){
						fechaError = false;
					}
				}
			}

			bool salir=false;
			while (salir==false){
				cout << "Ingrese el cargo: ";
				getline(cin,cargo);
				Cargo* unCargo = new Cargo (cargo);
				Registro* reg1 = new Registro (unCargo);
				delete unCargo;
				if(heCargo->obtenerRegistro(reg1)==NULL) cout << "No existe cargo/cargo no valido" << endl;
				else salir=true;
				delete reg1;
			}

			cout << "Ingrese la lista: ";
			getline(cin,nombreLista);
			lista = new Lista(nombreLista,fecha,cargo);

			registro = new Registro(lista);
			delete (lista);
		}
		int rta;
		switch (i)
		{
		case 1 : {
			 rta = administrador->altaArbol(bLista,registro);
			if (rta == 0) {
				cout << "Operación exitosa"<<endl;
			}
			else{
				cout << "Operación fallida"<<endl;
			}
		}break;
		case 2 : {
			rta = administrador->bajaArbol(bLista,registro);
			if (rta == 0) {
				cout << "Operación exitosa"<<endl;
			}
			else{
				cout << "Operación fallida"<<endl;
			}

		}break;
		case 3 : {
//			rta = administrador->modificaArbol(bLista,registro);
//			if (rta == 1) {
//				cout << "Operación exitosa"<<endl;
//			}
//			else{
//				cout << "Operación fallida"<<endl;
//			}
			cout << "No se puede modificar una lista!!"<<endl;

		}break;
		case 4 : {
			delete bLista;
			delete heCargo;
			return;
			break;
		}
		case 5 : {
			verContenidoArbolListas(bLista);
			break;
		}
		}
		i = 0;

		delete registro;
		registro = NULL;
	}

}


void InterfazAdministrador::habilitarElecciones(Administrador * administrador){

	string archivoDeDatos 	= rutaHash + HASH_ELECCION;
	string archivoDeControl	= rutaHash + HASH_ELECCION_CONTROL;

	HashingExtensible * heEleccion = new HashingExtensible (this->longitud,(char*)archivoDeDatos.c_str(),(char*)archivoDeControl.c_str());

	AdministradorDeVotaciones* administradorDeConteo = new AdministradorDeVotaciones();

	string pathArchivoConteo 	= rutaArbol + ARBOL_DE_CONTEO;
	string pathIndiceSecundario = rutaArbol + ARBOL_INDICE_SEC_CONTEO;

	administradorDeConteo->nuevoArchivoDeConteo(pathArchivoConteo,pathIndiceSecundario,config->darTamanioNodo());

	string opcion = "0";
	string fecha,cargo;
	int i = 0;
	Eleccion * eleccion = NULL;
	Registro * registro = NULL;

	while (true){
		while ((i < 1) or (i > 3)){
			cout << "Opciones: "<<endl<<endl;
			cout << "1) Habilitar Eleccion"<<endl;
			cout << "2) Ver elecciones habilitadas"<<endl;
			cout << "3) Salir"<<endl;
			cout << "Opcion: ";
			cin >> opcion;
			cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
			cout <<endl;
			if (isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		if (i == 1){
			bool fechaError = true;
			while (fechaError) {
				cout << "Ingrese la fecha de la elección: ";
				getline(cin,fecha);
				cout << endl;
				if (fecha.size() == 8) {
					string anioStr = fecha.substr(0,4);
					string mesStr = fecha.substr(4,2);
					string diaStr = fecha.substr(6,2);
					int dia = 0;
					int mes = 0;
					int anio = 0;
					if (isANumber(anioStr) == 1){
						anio = atoi(anioStr.c_str());
					}
					if (isANumber(mesStr) == 1){
						mes = atoi(mesStr.c_str());
					}
					if (isANumber(diaStr) == 1){
						dia = atoi(diaStr.c_str());
					}
					if ((anio >= 1980) and (anio <= 2020) and (mes > 0) and (mes <= 12)
							and (dia > 0) and (dia <= 30)){
						fechaError = false;
					}
				}
			}

			cout << "Ingrese el cargo: ";
			getline(cin,cargo);
			eleccion = new Eleccion(fecha,cargo);
			registro = new Registro(eleccion);
			delete eleccion;
		}
		switch (i)
		{
		case 1 : {
			Registro * registroObtenido = heEleccion->obtenerRegistro(registro);
			delete registro;
			registro = NULL;
			if ( registroObtenido != NULL){
				eleccion = (Eleccion*) registroObtenido->getContenido();

				if ( administrador->habilitarEleccion(eleccion) ){

					string pathDatos 	= rutaArbol + ARBOL_DE_LISTAS;
					bplustree * arbolB 	= new bplustree();
					arbolB->newtree(pathDatos,longitudNodo);

					// Cargar archivoDeConteo con las listas que participan en la actual eleccion.
					administradorDeConteo->cargarEleccionEnArchivoDeConteo(eleccion, arbolB);
					delete arbolB;
					cout << "Elección habilitada"<<endl;
				}


				delete eleccion;
				delete registroObtenido;
			}
			else{
				cout << "Elección inexistente!!"<<endl;
			}
		}break;
		case 2 : {
			administrador->getEleccionesHabilitadas();
		}break;
		case 3 : {
			delete (heEleccion);
			delete administradorDeConteo;
			return;
		}break;
		}
		i = 0;
	}
}

void InterfazAdministrador::comienzoVotacion(Administrador * administrador){

	string pathDatos	= rutaHash + HASH_VOTANTE;
	string pathControl	= rutaHash + HASH_VOTANTE_CONTROL;

	HashingExtensible * heVotante = new HashingExtensible (longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	AdministradorDeVotaciones* administradorDeConteo = new AdministradorDeVotaciones();

	string pathArchivoConteo 	= rutaArbol + ARBOL_DE_CONTEO;
	string pathIndiceSecundario = rutaArbol + ARBOL_INDICE_SEC_CONTEO;

	administradorDeConteo->nuevoArchivoDeConteo(pathArchivoConteo,pathIndiceSecundario,config->darTamanioNodo());

	/****/

	int cantidadDeSimulaciones;
	cout << "Ingrese la cantidad de votos a realizar: ";
	cin >> cantidadDeSimulaciones;
	cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
	cout << endl;

	pathDatos 	= rutaArbol + ARBOL_DE_LISTAS;
	bplustree * arbolDeListas = new bplustree();
	arbolDeListas->newtree(pathDatos,longitudNodo);

	string modo = "S";

	while ((modo.compare("a") != 0) and (modo.compare("m") != 0)){
		cout << "Ingrese modo de votación: Automático (a) o Manual (m)";
		getline(cin,modo);
		if ((modo.compare("a") != 0) and (modo.compare("m") != 0)){
			cout <<endl<<"Caracter erróneo, repita"<<endl;
		}
	}
	Log log;
	log.abrir(config);
	cout << endl;
	cout << "Bienvenido al sistema de voto electronico de los Gutierrez" << endl;
	cout << endl;
	srand (time(NULL));

	//	ingresa el votante
	for (int k=1; k <= cantidadDeSimulaciones;k++) {
		int numeroDeEleccion;
		int dni;
		char c;
		bool ok=false;
		bool seguir = true;
		Registro* registroAuxiliar;
		Votante* votanteActual = new Votante (k,"","","","");
		if (modo.compare("a") == 0) {
			Registro* reg = new Registro(votanteActual);
			delete votanteActual;
			registroAuxiliar = heVotante->obtenerRegistro(reg);
			delete reg;
			if (!registroAuxiliar) {
				cout << "NO EXISTE EN EL PADRON" << endl;
				log.insertarMensajeConEntero(k);
				seguir=false;
			}
		}
		else{
			while (!ok) {
				cout << "Ingrese su DNI: " << endl;
				cin >> dni;
				cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
				cout << "Su dni es: " << dni << endl;
				while (!ok) {
					cout << "Presione ""S"" para confirmar, ""N"" para cancelar" << endl;
					c = cin.get();
					cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
					if ((c=='s')||(c=='n')) ok=true;
					else cout << "Tecla no reconocida" << endl;
				}
				if (c=='n') ok=false;
			}
			delete votanteActual;
			votanteActual = new Votante (dni,"","","","");
			Registro* reg = new Registro(votanteActual);
			delete votanteActual;
			registroAuxiliar = heVotante->obtenerRegistro(reg);
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

			if (modo.compare("a") == 0)
				password = votanteActual->getPassword();
			else
				getline(cin,password);

			if (password == votanteActual->getPassword()) {
				cout << "INGRESO AUTORIZADO" << endl;
				cout << endl;
				//			carga listaDeEleccionesDelVotante, de las habilitadas solo las de su distrito que no haya votado anteriormente
				if (administrador->consultarEleccionesHabilitadasParaElVotante(votanteActual)) {
					ok=false;
					while (!ok){
						cout << "Indique el numero de eleccion en la cual desea sufragar" << endl;
						int n;
						if (modo.compare("a") == 0) n = (rand()%((administrador->getListaDeEleccionesDelVotante()).size()))+1;
//						if (modo=='a') n=1;
						else{
							n = cin.get();
							cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
						}
						if (((n)<=((int)((administrador->getListaDeEleccionesDelVotante()).size()))) && (n>0)) {
							while (!ok) {
								cout << "Usted eligio la eleccion " << n << endl;
								cout << "Si es correcto presione s sino n" << endl;
								numeroDeEleccion=n;
								if (modo.compare("a") == 0) c='s';
								else{
									c = cin.get();
									cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
								}
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
					heVotante->modificarRegistro(registroAuxiliar);
					delete registroAuxiliar;
					mensaje = "El votante participara en la eleccion: ";
					log.insertarMensajeConEntidad(*itListaDelVotante,mensaje);
					ok=false;
					int boleta;
					//			cargo las listas que puede elegir el votante en esta eleccion
					administrador->cargarListasDeEleccion(*itListaDelVotante,arbolDeListas);
					while (!ok) {
						char modoApertura;
						while (!ok) {
							if (modo.compare("a") == 0){
								modoApertura = 'a';
							} else{
								modoApertura = 'm';
							}
							boleta = administrador->elegirBoleta(modoApertura);
							if (!boleta) return;
							c=administrador->sufragar(boleta,modoApertura);
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
	delete heVotante;
	delete arbolDeListas;
	delete administradorDeConteo;
	return;
}

string* InterfazAdministrador::getString(vector<char> vect){
	string* s = new string();
	vector<char>::iterator it = vect.begin();
	while( it != vect.end() ){
		s->push_back(*it);
		it++;
	}
	return s;
}

void InterfazAdministrador::verContenidoArbolListas (bplustree* arbolB){

	arbolB->search("");

	pair<vector<char>,string> par = arbolB->getnext();

	if (par.second.size()!=0){

		while (par.second.size()!=0){
			string* registroSerializado = getString( par.first );

			Registro* unRegistro = new Registro();
			unRegistro->deserializar(registroSerializado);
			delete registroSerializado;

			Lista* lista = (Lista*)unRegistro->getContenido();
			delete unRegistro;

			cout << setw(10) << left << lista->getFecha();
			cout << setw(30) << left << lista->getCargo();
			cout << setw(40) << left << lista->getNombre() << endl;

			delete lista;

			par=arbolB->getnext();
		}
	}else
		cout << "No hay Listas cargadas" << endl;
}


InterfazAdministrador::~InterfazAdministrador() {
	delete (this->dummy);
}
