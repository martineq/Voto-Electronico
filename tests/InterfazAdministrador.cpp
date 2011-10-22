/*
 * InterfazVotante.cpp
 *
 *  Created on: 21/10/2011
 *      Author: lucas
 */

#include "InterfazAdministrador.h"

InterfazAdministrador::InterfazAdministrador(int argc, const char** argv ) {
	this->config = new Configuracion(argc,argv);
	this->rutaArbol = config->pathArbol();
	this->rutaHash = config->pathHash();
	this->longitud = config->darTamanioBucket();
}

void InterfazAdministrador::ingresoAdministrador(){
	string nombreDePrograma = ".//doc//password";
	Administrador administrador(nombreDePrograma);
	string usuario,password;
	string tecla = "P";
	cout <<"Ingrese su nombre de usuario: ";
	cin >> usuario;
	cout <<endl<<"Ahora ingrese su contraseña: ";
	cin >> password;
	cout <<endl;

	if (administrador.acceder(usuario,password)){
		cout << "INGRESO APROBADO" << endl;
		cout << "Bienvenido al sistama de gestion de elecciones" << endl;

		while (tecla.compare("N") != 0 and tecla.compare("S") != 0){
			cout << "¿ Desea eliminar la base de datos y comenzar de 0? S/N"<<endl;
			cin >> tecla;
			cout << endl;
			if (tecla.compare("S") == 0) {
				remove ("archivoDeControlVotante.txt");
				remove ("archivoDeDatosVotante.txt");
				remove ("archivoDeControlDistrito.txt");
				remove ("archivoDeDatosDistrito.txt");
				remove ("archivoDeControlEleccion.txt");
				remove ("archivoDeDatosEleccion.txt");
				remove ("archivoDeControlCandidato.txt");
				remove ("archivoDeDatosCandidato.txt");
				remove ("archivoDeControlCargo.txt");
				remove ("archivoDeDatosCargo.txt");
				remove("arbolDeListas");
			} else {
				if (tecla.compare("N") != 0){
					cout <<"Tecla inválida. Repita proceso.";
				}
			}
		}

		bool parar = false;
		while (! parar){
			parar = this->mostrarMenuAdministrador(&administrador);
		}

		cout << "Adios!!"<<endl;

	}

}



bool InterfazAdministrador::mostrarMenuAdministrador(Administrador * administrador){
	string opcion = "0";
	int i = 0;
	cout << "i: "<<i<<endl;
	while ((i < 1) or (i > 8)){
		cout << "Opciones: "<<endl<<endl;
		cout << "1) Mantener Distritos"<<endl;
		cout << "2) Mantener Votantes"<<endl;
		cout << "3) Mantener Elecciones"<<endl;
		cout << "4) Mantener Cargos"<<endl;
		cout << "5) Mantener Listas"<<endl;
		cout << "6) Mantener Candidatos"<<endl;
		cout << "7) Informar Resultados"<<endl;
		cout << "8) salir"<<endl;
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
	case 8 : return true;
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

	HashingExtensible * heDistrito = new HashingExtensible (this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	string opcion = "0";
	string nombreDistrito;
	int i = 0;
	Distrito * distrito;
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
			delete (registro);
			delete (heDistrito);
			return;
		}break;
		}
		i = 0;
	}

}

void InterfazAdministrador::mostrarMenuVotantes(Administrador * administrador){

	string pathControl = this->rutaHash + "DeControlVotante.txt";
	string pathDatos = this->rutaHash + "DeDatosVotante";

	HashingExtensible * heVotante = new HashingExtensible (this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	string opcion = "0";
	int dni = 0;
	string DNIString,nombre,apellido,apeNom,clave,dom,nombreDistrito;
	int i = 0;
	Votante * votante = NULL;
	Registro * registro;

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
				delete votante;
				delete registro;
				if (rta == operacionOK ) {
					cantIngr++;
				}
				cont++;
			}
		}break;
		}

		i = 0;
		dni = 0;
	}

}

void InterfazAdministrador::mostrarMenuElecciones(Administrador * administrador){

	string pathControl = this->rutaHash + "DeControlEleccion.txt";
	string pathDatos = this->rutaHash + "DeDatosEleccion";

	HashingExtensible * heEleccion = new HashingExtensible (this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	string opcion = "0";
	string masDistritos = "S";
	string nombreDistrito,fecha,cargo;
	int i = 0;
	Eleccion * eleccion;
	Registro * registro;

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
					cout << "anioStr: "<<anioStr<<endl;
					string mesStr = fecha.substr(4,2);
					cout << "mesStr: "<<mesStr<<endl;
					string diaStr = fecha.substr(6,2);
					cout << "diaStr: "<<diaStr<<endl;
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
			delete registro;
			delete heEleccion;
			return;
		} break;
		}
		i = 0;
		masDistritos = "S";
	}
}

void InterfazAdministrador::mostrarMenuCargos(Administrador * administrador){

	string pathControl = this->rutaHash + "DeControlCargo.txt";
	string pathDatos = this->rutaHash + "DeDatosCargo";

	HashingExtensible * heCargo = new HashingExtensible (this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

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
			delete registro;
			delete heCargo;
			return;
		}
		}
		masSubcargos = "S";
		i = 0;

	}

}

void InterfazAdministrador::mostrarMenuListas(Administrador * administrador){

}

void InterfazAdministrador::mostrarMenuCandidatos(Administrador * administrador){

	string pathControl = this->rutaHash + "DeControlCandidato.txt";
	string pathDatos = this->rutaHash + "DeDatosCandidato";

	HashingExtensible * heCandidato = new HashingExtensible (this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());


	pathControl = this->rutaHash + "DeControlVotante.txt";
	pathDatos = this->rutaHash + "DeDatosVotante";

	HashingExtensible * heVotante = new HashingExtensible (this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());


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

		bool existe = false;
		if (true){

				while (dni == 0){
					cout << "Ingrese el numero de DNI: ";
					cin >> DNIStr;
					cout <<endl;
					if ( isANumber(DNIStr) == 1){
						dni = atoi(DNIStr.c_str());
					}
				}
				cout << "1"<<endl;
				Votante * votante = new Votante(dni,"","","","");
				cout << "2"<<endl;
				Registro * regVotante = new Registro(votante);
				cout <<"3"<<endl;

				delete votante;
				cout <<"4"<<endl;
				Registro * regVotanteHash = heVotante->obtenerRegistro(regVotante);

				cout <<"5"<<endl;

				if (regVotanteHash != NULL) {
					cout <<"6"<<endl;
					existe = true;
				}
				cout << "7"<<endl;
				delete regVotante;
				cout <<"8"<<endl;
				delete regVotanteHash;
				cout <<"9"<<endl;

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
		}
		switch (i)
		{
		case 1 : {
			Resultados rta = administrador->altaHash(heCandidato,registro);
			imprimirRespuesta(rta);
		}break;
		case 2 : {
			Resultados rta = administrador->bajaHash(heCandidato,registro);
			imprimirRespuesta(rta);
		}break;
		case 3 : {
			cout<<"No puede modificarse un candidato!!"<<endl;
		}break;
		case 4 : {
			delete registro;
			delete heCandidato;
			delete heVotante;
			return;
		}
		}
		dni = 0;
		i = 0;
	}
}

void InterfazAdministrador::mostrarMenuInformes(Administrador * administrador){

}


InterfazAdministrador::~InterfazAdministrador() {
	delete (this->config);
}
