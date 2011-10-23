/*
 * InterfazVotante.cpp
 *
 *  Created on: 21/10/2011
 *      Author: lucas
 */

#include "InterfazAdministrador.h"

InterfazAdministrador::InterfazAdministrador(Configuracion* configuracion) {
	this->config = configuracion;
	this->rutaArbol = config->pathArbol();
	this->rutaHash = config->pathHash();
	this->longitudBucket = config->darTamanioBucket();
	this->longitudNodo = config->darTamanioNodo();

	administradorDeConteo = new AdministradorDeVotaciones();

	string pathArchivoConteo 	= configuracion->pathArbol() + "DeConteo.bin";
	string pathIndiceSecundario = configuracion->pathArbol() + "IndiceSecundario.bin";

	administradorDeConteo->nuevoArchivoDeConteo(pathArchivoConteo,pathIndiceSecundario,configuracion->darTamanioNodo());
}

void InterfazAdministrador::ingresoAdministrador(Administrador * administrador){
//	string nombreDePrograma = ".//doc//password";
//	Administrador * administrador = new Administrador(nombreDePrograma);
	string usuario,password;
	string tecla = "P";
	cout <<"Ingrese su nombre de usuario: ";
	cin >> usuario;
	cout <<endl<<"Ahora ingrese su contraseña: ";
	cin >> password;
	cout <<endl;
	cout << "usuario: <"<<usuario<<">"<<endl;
	cout << "password: <"<<password<<">"<<endl;

	if (administrador->acceder(usuario,password)){
		cout << "INGRESO APROBADO" << endl;
		cout << "Bienvenido al sistama de gestion de elecciones" << endl;

		while (tecla.compare("N") != 0 and tecla.compare("S") != 0){
			cout << "¿ Desea eliminar la base de datos y comenzar de 0? S/N"<<endl;
			cin >> tecla;
			cout << endl;
			if (tecla.compare("S") == 0) {
				string pathABorrar = this->rutaHash+"DeControlVotante.txt";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeDatosVotante.txt";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeControlDistrito.txt";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeDatosDistrito.txt";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeControlEleccion.txt";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeDatosEleccion.txt";
				(pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeControlCandidato.txt";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeDatosCandidato.txt";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeControlCargo.txt";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeDatosCargo.txt";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaArbol+"arbolDeListas";
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

		delete (administrador);
		cout << "Adios!!"<<endl;

	}else{
		cout << "Nombre de usuario o contraseña incorrecto. Adiós!"<<endl;
	}

}



bool InterfazAdministrador::mostrarMenuAdministrador(Administrador * administrador){
	string opcion = "0";
	int i = 0;
	cout << "i: "<<i<<endl;
	while ((i < 1) or (i > 9)){
		cout << "Opciones: "<<endl<<endl;
		cout << "1) Mantener Distritos"<<endl;
		cout << "2) Mantener Votantes"<<endl;
		cout << "3) Mantener Elecciones"<<endl;
		cout << "4) Mantener Cargos"<<endl;
		cout << "5) Mantener Listas"<<endl;
		cout << "6) Mantener Candidatos"<<endl;
		cout << "7) Informar Resultados"<<endl;
		cout << "8) Habilitar Elecciones"<<endl;
		cout << "9) salir"<<endl;
		cout << "Opcion: ";
		cin >> opcion;
		cout <<endl;
		if (isANumber(opcion) == 1){
			i = atoi(opcion.c_str());
		}
		else{
			i = 0;
		}

	}



	switch (i)
	{
	case 1 : mostrarMenuDistritos(administrador);break;
	case 2 : mostrarMenuVotantes(administrador);break;
	case 3 : mostrarMenuElecciones(administrador);break;
	case 4 : mostrarMenuCargos(administrador);break;
	case 5 : mostrarMenuListas(administrador);break;
	case 6 : mostrarMenuCandidatos(administrador);break;
	case 7 : mostrarMenuInformes(administrador);break;
	case 8 : habilitarElecciones(administrador);break;
	case 9 : return true;
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

	string pathControl = this->rutaHash + "DeControlDistrito.txt";
	string pathDatos = this->rutaHash + "DeDatosDistrito";

	HashingExtensible * heDistrito = new HashingExtensible (this->longitudBucket,(char*)pathDatos.c_str(),(char*)pathControl.c_str());


	string opcion = "0";
	string nombreDistrito;
	int i = 0;
	Distrito * distrito = NULL;
	Registro * registro = NULL;

	while (true){
		while ((i < 1) or (i > 4)){
			cout << "Opciones: "<<endl<<endl;
			cout << "1) Alta Distrito"<<endl;
			cout << "2) Baja Distrito"<<endl;
			cout << "3) Modificar Distrito"<<endl;
			cout << "4) Volver atrás"<<endl;
			cout << "Opcion: ";
			cin >> opcion;
			cout <<endl;
			if (isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}
			else{
				i = 5;
			}

		}

		if (i != 4){
			cout << "Ingrese el nombre del distrito: "<<endl;
			cin >> nombreDistrito;
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
		}break;
		case 2 : {
			Resultados rta = administrador->bajaHash(heDistrito,registro);
			imprimirRespuesta(rta);
		}break;
		case 3 : {
			cout<<"No puede modificarse un distrito!!"<<endl;
		}break;
		case 4 : {
			delete (heDistrito);
			return;
		}break;
		}
		i = 0;
		delete (registro);
		registro = NULL;
	}

}

void InterfazAdministrador::mostrarMenuVotantes(Administrador * administrador){

	string pathControl = this->rutaHash + "DeControlVotante.txt";
	string pathDatos = this->rutaHash + "DeDatosVotante";

	HashingExtensible * heVotante = new HashingExtensible (this->longitudBucket,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	string opcion = "0";
	int dni = 0;
	string DNIString,nombre,apellido,apeNom,clave,dom,nombreDistrito;
	int i = 0;
	Votante * votante = NULL;
	Registro * registro = NULL;

	while (true){
		while ((i < 1) or (i > 5)){
			cout << "Opciones: "<<endl<<endl;
			cout << "1) Alta Votante"<<endl;
			cout << "2) Baja Votante"<<endl;
			cout << "3) Modificar Votante"<<endl;
			cout << "4) Volver atrás"<<endl;
			cout << "5) Alta Automática"<<endl;
			cout << "Opcion: ";
			cin >> opcion;
			cout <<endl;
			if (isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		if ((i != 4) and (i != 5)){

			//Ingresar DNI Válido
			while (dni < 1){
				cout << "Ingrese el DNI del votante: ";
				cin >> DNIString;
				cout <<endl;
				if (isANumber(DNIString) == 1){
					dni = atoi(DNIString.c_str());
				}
			}

			if (i != 2){

				//Ingresar apellido y nombre
				cout << "Ingrese nombre: ";
				cin >> nombre;
//				getline(apeNom,cin);
				cout<<endl;

				cout << "Ingrese apellido: ";
				cin >> apellido;
				cout << endl;

				apeNom = nombre+" "+apellido;

				//Ingresar Clave
				cout << "Ingrese la clave: ";
				cin >> clave;
				cout <<endl;
				cout << "Clave: "<<clave<<endl;;

				//Ingresar Domicilio
				cout << "Ingrese el domicilio: ";
				cin  >> dom;
				cout << endl;
				cout << "dom: "<<dom<<endl;

				//Ingresar Distrito
				cout << "Ingrese el nombre del distrito: "<<endl;
				cin >> nombreDistrito;
				cout << endl;
				cout << "Distrito: "<<nombreDistrito<<endl;
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
			Resultados rta = administrador->altaHash(heVotante,registro);
			imprimirRespuesta(rta);
		}break;
		case 2 : {
			Resultados rta = administrador->bajaHash(heVotante,registro);
			imprimirRespuesta(rta);
		}break;
		case 3 : {
			Resultados rta = administrador->modificaHash(heVotante,registro);
			imprimirRespuesta(rta);
		}break;
		case 4: {
			delete heVotante;
			return;
		}break;
		case 5 : {
			int cantTotal;
			int cantIngr = 0;
			int cont = 1;
			cout << "Ingrese la cantidad de votantes a ingresar: ";
			cin >> cantTotal;
			while (cantIngr < cantTotal){
				CreadorVotante * creador = new CreadorVotante(time(NULL) * cont);
				votante = creador->crearVotante();
				registro = new Registro(votante);
				Resultados rta = administrador->altaHash(heVotante,registro);
				votante->verVotante();
				delete votante;
				delete registro;
				if (rta == operacionOK ) {
					cantIngr++;
				}
				cont++;
			}
		}break;
		}

		if (i != 5) delete registro;
		registro = NULL;
		i = 0;
		dni = 0;
	}

}

void InterfazAdministrador::mostrarMenuElecciones(Administrador * administrador){

	string pathControl = this->rutaHash + "DeControlEleccion.txt";
	string pathDatos = this->rutaHash + "DeDatosEleccion";

	HashingExtensible * heEleccion = new HashingExtensible (this->longitudBucket,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	string opcion = "0";
	string masDistritos = "S";
	string nombreDistrito,fecha,cargo;
	int i = 0;
	Eleccion * eleccion = NULL;
	Registro * registro = NULL;

	while (true){
		while ((i < 1) or (i > 4)){
			cout << "Opciones: "<<endl<<endl;
			cout << "1) Alta Eleccion"<<endl;
			cout << "2) Baja Eleccion"<<endl;
			cout << "3) Modificar Eleccion"<<endl;
			cout << "4) Volver atrás"<<endl;
			cout << "Opcion: ";
			cin >> opcion;
			cout <<endl;
			if (isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		if (i != 4){
			bool fechaError = true;
			while (fechaError) {
				cout << "Ingrese la fecha de la elección: ";
				cin >> fecha;
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
			cin >> cargo;

			eleccion = new Eleccion(fecha,cargo);

			while ((masDistritos.compare("S") == 0) and (i != 2)){
				cout << "Ingrese el nombre del distrito: "<<endl;
				cin >> nombreDistrito;
				cout << endl;
				eleccion->agregarDistrito(nombreDistrito);
				cout << "Desea agregar más distritos? (ingrese 'S' para seguir)";
				cin >> masDistritos;
				cout <<endl;
			}

			registro = new Registro(eleccion);
			delete eleccion;
		}
		switch (i)
		{
		case 1 : {
			Resultados rta = administrador->altaHash(heEleccion,registro);
			imprimirRespuesta(rta);
		}break;
		case 2 : {
			Resultados rta = administrador->bajaHash(heEleccion,registro);
			imprimirRespuesta(rta);
		}break;
		case 3 : {
			Resultados rta = administrador->modificaHash(heEleccion,registro);
			imprimirRespuesta(rta);
		}break;
		case 4 : {
			delete heEleccion;
			return;
		} break;
		}
		delete registro;
		registro = NULL;
		i = 0;
		masDistritos = "S";
	}
}

void InterfazAdministrador::mostrarMenuCargos(Administrador * administrador){

	string pathControl = this->rutaHash + "DeControlCargo.txt";
	string pathDatos = this->rutaHash + "DeDatosCargo";

	HashingExtensible * heCargo = new HashingExtensible (this->longitudBucket,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	string opcion = "0";
	string cargoPpal,subCargo;
	string masSubcargos = "S";
	int i = 0;
	Cargo * cargo = NULL;
	Registro * registro = NULL;

	while (true){
		while ((i < 1) or (i > 4)){
			cout << "Opciones: "<<endl<<endl;
			cout << "1) Alta Cargo"<<endl;
			cout << "2) Baja Cargo"<<endl;
			cout << "3) Modificar Cargo"<<endl;
			cout << "4) Volver atrás"<<endl;
			cout << "Opcion: ";
			cin >> opcion;
			cout <<endl;
			if ( isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		if (i != 4){
			cout << "Ingrese el nombre del cargo principal: "<<endl;
			cin >> cargoPpal;
			cout << endl;
			cargo = new Cargo(cargoPpal);

			if ( i != 2){
				cout << "Desea agregar subcargos? (S/N)";
				cin >> masSubcargos;
				cout <<endl;
			}

			while ((masSubcargos.compare("S") == 0) and (i != 2)){
				cout << "Ingrese el nombre del subcargo: "<<endl;
				cin >> subCargo;
				cout << endl;
				cargo->agregarCargo(subCargo);
				cout << "Desea agregar más subcargos? (ingrese 'S' para seguir)";
				cin >> masSubcargos;
				cout <<endl;
			}


			registro = new Registro(cargo);
			delete (cargo);
		}
		switch (i)
		{
		case 1 : {
			Resultados rta = administrador->altaHash(heCargo,registro);
			imprimirRespuesta(rta);
		}break;
		case 2 : {
			Resultados rta = administrador->bajaHash(heCargo,registro);
			imprimirRespuesta(rta);
		}break;
		case 3 : {
			Resultados rta = administrador->modificaHash(heCargo,registro);
			imprimirRespuesta(rta);
		}break;
		case 4 : {
			delete heCargo;
			return;
		}
		}
		masSubcargos = "S";
		i = 0;
		delete registro;
		registro = NULL;

	}

}



void InterfazAdministrador::mostrarMenuCandidatos(Administrador * administrador){

	string pathControl = this->rutaHash + "DeControlCandidato.txt";
	string pathDatos = this->rutaHash + "DeDatosCandidato";

	HashingExtensible * heCandidato = new HashingExtensible (this->longitudBucket,(char*)pathDatos.c_str(),(char*)pathControl.c_str());


	pathControl = this->rutaHash+"DeControlVotante.txt";
	pathDatos = this->rutaHash+"DeDatosVotante.txt";

	HashingExtensible * heVotante = new HashingExtensible (this->longitudBucket,(char*)pathDatos.c_str(),(char*)pathControl.c_str());


	string opcion = "0";
	string fecha,cargo,nombre,DNIStr;
	int dni = 0;
	int i = 0;
	Candidato * candidato = NULL;
	Registro * registro = NULL;

	while (true){
		while ((i < 1) or (i > 4)){
			cout << "Opciones: "<<endl<<endl;
			cout << "1) Alta Candidato"<<endl;
			cout << "2) Baja Candidato"<<endl;
			cout << "3) Modificar Candidato"<<endl;
			cout << "4) Volver atrás"<<endl;
			cout << "Opcion: ";
			cin >> opcion;
			cout <<endl;
			if ( isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		bool existe = true;
		if ((i != 4) and (i != 3)){

				while (dni == 0){
					cout << "Ingrese el numero de DNI: ";
					cin >> DNIStr;
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
					existe = false;
				}
				delete regVotante;
				delete regVotanteHash;

			if (existe){
				bool fechaError = true;
				while (fechaError) {
					cout << "Ingrese la fecha de la elección: ";
					cin >> fecha;
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
				cin >> cargo;
				cout << endl;

				cout << "Ingrese el nombre de la lista: ";
				cin >> cargo;
				cout << endl;

				candidato = new Candidato(fecha,cargo,nombre,dni);
				registro = new Registro(candidato);
				delete (candidato);
			}else{
				cout << "No existe el candidato!!"<<endl;
			}
		}
		switch (i)
			{
			case 1 : {
				if (existe){
					Resultados rta = administrador->altaHash(heCandidato,registro);
					imprimirRespuesta(rta);
				}
			}break;
			case 2 : {
				if (existe){
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

}

void InterfazAdministrador::mostrarMenuListas(Administrador * administrador){
	string pathDatos = this->rutaArbol + "arbolDeListas";
	bplustree * bLista = new bplustree();
//	bLista->opentree(archivoDeDatos,this->longitudNodo);
	bLista->newtree((char*)pathDatos.c_str(),this->longitudNodo);
	string opcion = "0";
	string fecha,cargo,nombreLista;

	int i = 0;
	Lista * lista = NULL;
	Registro * registro = NULL;

	while (true){
		while ((i < 1) or (i > 4)){
			cout << "Opciones: "<<endl<<endl;
			cout << "1) Alta Lista"<<endl;
			cout << "2) Baja Lista"<<endl;
			cout << "3) Modificar Lista"<<endl;
			cout << "4) Volver atrás"<<endl;
			cout << "Opcion: ";
			cin >> opcion;
			cout <<endl;
			if ( isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		if ((i != 4) and (i != 3)){

			bool fechaError = true;
			while (fechaError) {
				cout << "Ingrese la fecha de la elección: ";
				cin >> fecha;
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
			cin >> cargo;

			cout << "Ingrese la lista: ";
			cin >> nombreLista;


			lista = new Lista(nombreLista,fecha,cargo);

			registro = new Registro(lista);
			delete (lista);
		}
		int rta;
		switch (i)
		{
		case 1 : {
			 rta = administrador->altaArbol(bLista,registro);
			if (rta == 1) {
				cout << "Operación exitosa"<<endl;
			}
			else{
				cout << "Operación fallida"<<endl;
			}
		}break;
		case 2 : {
			rta = administrador->bajaArbol(bLista,registro);
			if (rta == 1) {
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
			return;
		}
		}
		i = 0;

		delete registro;
		registro = NULL;
	}

}


void InterfazAdministrador::habilitarElecciones(Administrador * administrador){
	string archivoDeControl=this->rutaHash+"DeControlEleccion.txt";
	string archivoDeDatos = this->rutaHash+"DeDatosEleccion.txt";
	HashingExtensible * heEleccion = new HashingExtensible (this->longitudBucket,(char*)archivoDeDatos.c_str(),(char*)archivoDeControl.c_str());

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
			cout <<endl;
			if (isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		if (i == 1){
			bool fechaError = true;
			while (fechaError) {
				cout << "Ingrese la fecha de la elección: ";
				cin >> fecha;
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
			cin >> cargo;

			eleccion = new Eleccion(fecha,cargo);

			registro = new Registro(eleccion);
		}
		switch (i)
		{
		case 1 : {
			Registro * registroObtenido = heEleccion->obtenerRegistro(registro);
			if ( registroObtenido != NULL){
				administrador->habilitarEleccion(eleccion);
				cout << "Elección habilitada"<<endl;
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
			return;
		}break;
		}
		delete eleccion;
		delete registro;
		registro = NULL;
		i = 0;
	}

}


InterfazAdministrador::~InterfazAdministrador() {
	delete (this->config);
	delete (this->administradorDeConteo);
}
