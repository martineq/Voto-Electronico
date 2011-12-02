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
	this->longitud = config->darTamanioBucket();
	this->longitudNodo = config->darTamanioNodo();
	votoAutomatizado = false;
	
	administradorDeConteo = new AdministradorDeVotaciones();

	string pathArchivoConteo 	= configuracion->pathArbol() + "DeConteo.bin";
	string pathIndiceSecundario = configuracion->pathArbol() + "IndiceSecundario.bin";

	administradorDeConteo->nuevoArchivoDeConteo(pathArchivoConteo,pathIndiceSecundario,configuracion->darTamanioNodo());
	
//	Se crea el RSA para encriptar votantes
	this->rsa = new RSA(true);
	long long numero;
	ManejadorDeArchivo manejador("clavePrivada.txt");
//	cout << "ingrese el d de la clave privada de RSA: " << endl;
//	cin >> numero;
	if(!manejador.existe())
	{
		numero = this->rsa->getD();
		manejador.escribir((char*) &numero,sizeof(long long));

//		cout << "ingrese el n de la clave privada de RSA: " << endl;
//		cin >> numero;

		numero = this->rsa->getN();
		manejador.escribir((char*)&numero,sizeof(long long));

		numero = this->rsa->getE();
		manejador.escribir((char*)&numero,sizeof(long long));

		manejador.guardarBuffer();

		cout << "D: "<<this->rsa->getD()<<endl;
		cout << "N: "<<this->rsa->getN()<<endl;
		cout << "E: "<<this->rsa->getE()<<endl;
		char trulala;
		cin >> trulala;

	}
	else
	{
		long long* numeroPuntero = new long long;
		manejador.posicionarse(0);
		char* buf= new char[sizeof(long long)]; 		// Preparo un buffer de tamaño int para obtener los datos		// Voy a la posición <pos>
		manejador.leer(buf,sizeof(long long));	// Leo en archivo
		(*numeroPuntero) = *(long long*)buf;					// Guardo el valor en donde apunta <dest>
		delete[] buf;
		this->rsa->setD(*numeroPuntero);
		char* buf2= new char[sizeof(long long)]; 		// Preparo un buffer de tamaño int para obtener los datos		// Voy a la posición <pos>
		manejador.leer(buf2,sizeof(long long));	// Leo en archivo
		(*numeroPuntero) = *(long long*)buf2;					// Guardo el valor en donde apunta <dest>
		delete[] buf2;
		this->rsa->setN(*numeroPuntero);

		char* buf3= new char[sizeof(long long)]; 		// Preparo un buffer de tamaño int para obtener los datos		// Voy a la posición <pos>
		manejador.leer(buf3,sizeof(long long));	// Leo en archivo
		(*numeroPuntero) = *(long long*)buf3;					// Guardo el valor en donde apunta <dest>
		delete[] buf3;
		this->rsa->setE(*numeroPuntero);
		delete numeroPuntero;

		cout << "D en archivo: "<<this->rsa->getD()<<endl;
		cout << "N en archivo: "<<this->rsa->getN()<<endl;
		cout << "E en archivo: "<<this->rsa->getE()<<endl;


	}
}

void InterfazAdministrador::ingresoAdministrador(Administrador * administrador){
	string usuario,password;
	string tecla = "P";
	cout <<"Ingrese su nombre de usuario: ";
	cin >> usuario;
	cout <<endl<<"Ahora ingrese su contraseña: ";
	cin >> password;
	cout <<endl;
	cout << "usuario: <"<<usuario<<">"<<endl;
	cout << "password: <"<<password<<">"<<endl;

//	========================
	usuario="undomiel";
	password="aragorn";
//	========================

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
				pathABorrar = this->rutaHash+"DeDatosVotante";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeControlDistrito.txt";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeDatosDistrito";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeControlEleccion.txt";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeDatosEleccion";
				(pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeControlCandidato.txt";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeDatosCandidato";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeControlCargo.txt";
				remove (pathABorrar.c_str());
				pathABorrar = this->rutaHash+"DeDatosCargo";
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

		cout << "Adios!!"<<endl;


	}else{
		cout << "Nombre de usuario o contraseña incorrecto. Adiós!"<<endl;
	}

}



bool InterfazAdministrador::mostrarMenuAdministrador(Administrador * administrador){
	string opcion = "0";
	int i = 0;
	while ((i < 1) or (i > 13)){
		cout << "Opciones: "<<endl<<endl;
		cout << "1) Mantener Distritos"<<endl;
		cout << "2) Mantener Votantes"<<endl;
		cout << "3) Mantener Elecciones"<<endl;
		cout << "4) Mantener Cargos"<<endl;
		cout << "5) Mantener Listas"<<endl;
		cout << "6) Mantener Candidatos"<<endl;
		cout << "7) Informar Resultados"<<endl;
		cout << "8) Habilitar Elecciones"<<endl;
		cout << "9) Habilitar Votantes para elección"<<endl;
		cout << "10) salir"<<endl;
		cout << "11) Votacion automatica" << endl;
		cout << "12) Criptoanalizar informes" << endl;
		cout << "13) Atacar RSA" << endl;
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
	case 1  : mostrarMenuDistritos(administrador);break;
	case 2  : mostrarMenuVotantes(administrador);break;
	case 3  : mostrarMenuElecciones(administrador);break;
	case 4  : mostrarMenuCargos(administrador);break;
	case 5  : mostrarMenuListas(administrador);break;
	case 6  : mostrarMenuCandidatos(administrador);break;
	case 7  : mostrarMenuInformes(administrador);break;
	case 8  : habilitarElecciones(administrador);break;
	case 9  : comienzoVotacion(administrador);break;
	case 10 : return true; break;
	case 11 : mostrarMenuVotacionAutomatica(administrador);break;
	case 12 : mostrarMenuCriptoanalisis(administrador);break;
	case 13 : atacarRSA(); break;
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
			cin >> opcion;
			cout <<endl;
			if (isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}
			else{
				i = 6;
			}

		}

		if ((i != 4) and (i != 5)){
			cout << "Ingrese el nombre del distrito: "<<endl;

			char* entrada = new char[longitud];
			cin.ignore();
			cin.getline(entrada,this->longitud);
			nombreDistrito = entrada;
			delete[] entrada;

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
		case 5: {
			heDistrito->mostrarArchivoDeHash();
			break;
		}
		}
		i = 0;
		delete (registro);
		registro = NULL;
	}

}

void InterfazAdministrador::mostrarMenuVotantes(Administrador * administrador){

	string pathControl = this->rutaHash + "DeControlVotante.txt";
	string pathDatos = this->rutaHash + "DeDatosVotante";

	HashingExtensible * heVotante = new HashingExtensible (this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	pathControl = this->rutaHash + "DeControlDistrito.txt";
	pathDatos = this->rutaHash + "DeDatosDistrito";

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

				char* entrada = new char[longitud];
				cin.ignore();
				cin.getline(entrada,this->longitud);
				dom = entrada;
				delete[] entrada;

				cout << endl;
				cout << "dom: "<<dom<<endl;

				//Ingresar Distrito
				cout << "Ingrese el nombre del distrito: "<<endl;

				char* entrada2 = new char[longitud];
//				cin.ignore();
				cin.getline(entrada2,this->longitud);
				nombreDistrito = entrada2;
				delete[] entrada2;

				cout << endl;
				cout << "Distrito: "<<nombreDistrito<<endl;

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
			//	Cada votante recibe una clave RSA
			votante->setRSA(this->rsa);
			registro = new Registro(votante);
			delete (votante);
		}
		switch (i)
		{
		case 1 : {
			if (! errorCarga) {
				Resultados rta = administrador->altaHash(heVotante,registro);
				imprimirRespuesta(rta);
			} else{
				cout << "Error de carga!! distrito inválido!!"<<endl;
			}
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
			delete heDistrito;
			return;
		}break;
		case 5 : {
			int cantTotal;
			int cantIngr = 0;
			int cont = 1;
			cout << "Ingrese la cantidad de votantes a ingresar: ";
			cin >> cantTotal;
			while (cantIngr < cantTotal){
				CreadorVotante * creador = new CreadorVotante(cont);
				votante = creador->crearVotante(config,rsa);
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

		if ((i != 5) and (i != 6)) delete registro;
		registro = NULL;
		i = 0;
		dni = 0;
		errorCarga = false;
	}

}

void InterfazAdministrador::mostrarMenuElecciones(Administrador * administrador){

	string pathControl = this->rutaHash + "DeControlEleccion.txt";
	string pathDatos = this->rutaHash + "DeDatosEleccion";

	HashingExtensible * heEleccion = new HashingExtensible (this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	string pathControl2 = this->rutaHash + "DeControlDistrito.txt";
	string pathDatos2 = this->rutaHash + "DeDatosDistrito";

	HashingExtensible * heDistrito = new HashingExtensible (this->longitud,(char*)pathDatos2.c_str(),(char*)pathControl2.c_str());

	string pathControl3 = this->rutaHash + "DeControlCargo.txt";
	string pathDatos3 = this->rutaHash + "DeDatosCargo";

	HashingExtensible * heCargo = new HashingExtensible (this->longitud,(char*)pathDatos3.c_str(),(char*)pathControl3.c_str());

	pathDatos = this->rutaArbol + "arbolDeListas";
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
			cin >> opcion;
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

			bool salir=false; string tecla;
			while ((salir==false) or (tecla.compare("S") == 0)){
				cout << "Ingrese el cargo: ";
				cin >> cargo;
				Cargo* unCargo = new Cargo (cargo);
				Registro* reg1 = new Registro (unCargo);
				delete unCargo;
				Registro* reg2;
				reg2=heCargo->obtenerRegistro(reg1);
				if(reg2==NULL) {
					cout << "No existe cargo/cargo no valido" << endl;
					tecla = "S";
				}
				else {
					salir=true;
					tecla = "P";
					errorCarga=false;
				}
				delete reg2;
				delete reg1;
				if (tecla.compare("S") == 0){
					cout << "¿ Desea repetir? (S/N): ";
					cin >> tecla;
					cout <<endl;
					if (tecla.compare("N") == 0){
						salir = true;
						tecla="N";
						errorCarga = true;
						cout << "La eleccion no fue cargada" << endl;
						cargo = "";
					}
				}
			}


			eleccion = new Eleccion(fecha,cargo);

			while ((masDistritos.compare("S") == 0) and (i != 2) and (!errorCarga)){

				cout << "Ingrese el nombre del distrito: "<<endl;

				char* entrada2 = new char[longitud];
				cin.ignore();
				cin.getline(entrada2,this->longitud);
				nombreDistrito = entrada2;
				delete[] entrada2;

				cout << endl;
				Distrito* undistrito = new Distrito (nombreDistrito);
				Registro* unregistro = new Registro (undistrito);
				delete undistrito;
				Registro* reg = heDistrito->obtenerRegistro(unregistro);
				if (reg!=NULL) {
					delete unregistro;
					if (eleccion->agregarDistrito(nombreDistrito)) cout << "Distrito agregado" << endl;
				}
				else {
					delete unregistro;
					cout << "El distrito no existe" << endl;
				}
				delete reg;
				cout << endl;
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
			if (!errorCarga){
				Resultados rta = administrador->altaHash(heEleccion,registro);
				imprimirRespuesta(rta);
				if (rta == operacionOK){
					Lista * lista = new Lista("blanco",fecha,cargo);
					Registro * regLista = new Registro(lista);
					delete lista;
					administrador->altaArbol(bLista,regLista);
					delete regLista;
				}
				else cout << "La eleccion ya existe" << endl;
			} else{
				cout << "Error!! cargo inexistente!!"<<endl;
			}
		}break;
		case 2 : {
			if (!errorCarga){
				Resultados rta = administrador->bajaHash(heEleccion,registro);
				imprimirRespuesta(rta);
			}
		}break;
		case 3 : {
			if (!errorCarga){
				Resultados rta = administrador->modificaHash(heEleccion,registro);
				imprimirRespuesta(rta);
			}
		}break;
		case 4 : {
			delete heEleccion;
			delete heDistrito;
			delete heCargo;
			delete bLista;
			return;
		} break;
		case 5 : {
			heEleccion->mostrarArchivoDeHash();
			break;
		}
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

	HashingExtensible * heCargo = new HashingExtensible (this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

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
			cin >> opcion;
			cout <<endl;
			if ( isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		if ((i != 4) and (i != 5)){
			cout << "Ingrese el nombre del cargo principal: "<<endl;

			char* entrada = new char[longitud];
			cin.ignore();
			cin.getline(entrada,this->longitud);
			cargoPpal = entrada;
			delete[] entrada;

			cout << endl;
			cargo = new Cargo(cargoPpal);

			if ( i != 2){
				cout << "Desea agregar subcargos? (S/N)";
				cin >> masSubcargos;
				cout <<endl;
			}

			while ((masSubcargos.compare("S") == 0) and (i != 2)){
				cout << "Ingrese el nombre del subcargo: "<<endl;

				char* entrada = new char[longitud];
				cin.ignore();
				cin.getline(entrada,this->longitud);
				subCargo = entrada;
				delete[] entrada;

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
		case 5 : {
			heCargo->mostrarArchivoDeHash();
			break;
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

	HashingExtensible * heCandidato = new HashingExtensible (this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	pathControl = this->rutaHash + "DeControlCargo.txt";
	pathDatos = this->rutaHash + "DeDatosCargo";

	HashingExtensible * heCargo = new HashingExtensible (this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	pathControl = this->rutaHash + "DeControlVotante.txt";
	pathDatos = this->rutaHash + "DeDatosVotante";

	HashingExtensible * heVotante = new HashingExtensible (this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	pathDatos = this->rutaArbol + "arbolDeListas";
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
			cout <<endl;
			if ( isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		if ((i != 4) and (i != 3) and (i != 5)){

				while (dni == 0){
					cout << "Ingrese el numero de DNI: ";
					cin >> DNIStr;
					cout <<endl;
					if ( isANumber(DNIStr) == 1){
						dni = atoi(DNIStr.c_str());
					}
				}
				Votante * votante = new Votante(dni,"","","","");
				votante->setRSA(this->rsa);
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
				cin >> nombre;
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
				delete heCargo;
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
			cout <<endl;
			if ( isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		if ((i == 1) or (i == 2)){

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
			char* entrada = new char[longitud];
			cin.ignore();
			cin.getline(entrada,this->longitud);
			cargo = entrada;
			delete[] entrada;

			if (i == 1){
				eleccion = new Eleccion(fecha,cargo);
			}
			else {
				cout << "Ingrese la lista: ";
				char* entrada = new char[longitud];
				cin.getline(entrada,this->longitud);
				nombreLista = entrada;
				delete[] entrada;
				lista = new Lista(nombreLista,fecha,cargo);
			}


		}else if ( i == 3 ){
			cout << "Ingrese el nombre del distrito: ";

			char* entrada = new char[longitud];
			cin.ignore();
			cin.getline(entrada,this->longitud);
			nombreDelDistrito = entrada;
			delete[] entrada;

			distrito = new Distrito(nombreDelDistrito);
		}

		string enter;
		switch (i)
		{
		case 1 :
		{
			string informe = config->pathInformes()+ELECCIONES;
			administradorDeConteo->setPathInformePorEleccion(informe);

			string clave = this->config->getClaveVigenere();
			if ( clave.size() == 0 ){
				cout << "Ingrese una clave para cifrar el informe" << endl;
				string clave;
				getline(cin,clave);
			}
			administradorDeConteo->setClaveParaEleccion(clave);

			administradorDeConteo->generarInformePorEleccion(eleccion);
			cout << "Ingrese una tecla para continuar";

			cin.ignore(cin.rdbuf()->in_avail());
			cin.get();
			delete eleccion;
			eleccion = NULL;
			break;
		}
		case 2 :
		{
			string pathDatos	= this->rutaHash + "DeDatosCargo";
			string pathControl	= this->rutaHash + "DeControlCargo.txt";
			HashingExtensible* he = new HashingExtensible(longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

			string informe = config->pathInformes()+LISTAS;
			administradorDeConteo->setPathInformePorLista(informe);
			string clave = this->config->getClaveVigenere();
			if ( clave.size() == 0 ){
				cout << "Ingrese una clave para cifrar el informe" << endl;
				string clave;
				getline(cin,clave);
			}
			administradorDeConteo->setClaveParaLista(clave);

			administradorDeConteo->generarInformePorLista(lista,he);
			delete he;
			cout << "Ingrese una tecla para continuar";
			cin.ignore(cin.rdbuf()->in_avail());
			cin.get();
			delete lista;
			lista  = NULL;
			break;
		}
		case 3 :
		{

			string informe = config->pathInformes()+DISTRITOS;
			administradorDeConteo->setPathInformePorDistrito(informe);
			string clave = this->config->getClaveVigenere();
			if ( clave.size() == 0 ){
				cout << "Ingrese una clave para cifrar el informe" << endl;
				string clave;
				getline(cin,clave);
			}
			administradorDeConteo->setClaveParaDistrito(clave);


			administradorDeConteo->generarInformePorDistrito(distrito);
			cout << "Ingrese una tecla para continuar";
			cin.ignore(cin.rdbuf()->in_avail());
			cin.get();
			delete distrito;
			distrito = NULL;
			break;
		}
		case 4 :
		{
			return;
		}
		case 5:
		{
			administradorDeConteo->mostrarArchivoPrincipalEnFormatoTabla();
			cout << "Ingrese una tecla para continuar" << endl;
			cin.ignore();
			cin.get();
			break;
		}
		case 6:
		{
			administradorDeConteo->mostrarArchivoPrincipalEnFormatoTablaOrdenadoPorClaveSecundaria();
			cout << "Ingrese una tecla para continuar" << endl;
			cin.ignore();
			cin.get();
			break;
		}
		}
		i = 0;
	}

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

			cout << setw(10) << left << lista->getFecha()	<< "\t";
			cout << lista->getCargo()	<< "\t";
			cout << lista->getNombre()	<< endl;

			delete lista;

			par=arbolB->getnext();
		}
	}else
		cout << "No hay Listas cargadas" << endl;
}

void InterfazAdministrador::mostrarMenuListas(Administrador * administrador){
	string pathControl3 = this->rutaHash + "DeControlCargo.txt";
	string pathDatos3 = this->rutaHash + "DeDatosCargo";

	HashingExtensible * heCargo = new HashingExtensible (this->longitud,(char*)pathDatos3.c_str(),(char*)pathControl3.c_str());

	string pathDatos = this->rutaArbol + "arbolDeListas";
	bplustree * bLista = new bplustree();
//	bLista->opentree(archivoDeDatos,LONGITUD_BLOQUE);
	bLista->newtree((char*)pathDatos.c_str(),this->longitudNodo);
	string opcion = "0";
	string fecha,cargo,nombreLista;

	int i = 0;
	bool errorCarga = false;
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
			cin >> opcion;
			cout <<endl;
			if ( isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		if ((i != 4) and (i != 3) and (i != 5)){

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

			bool salir=false; string tecla;
			while ((salir==false) or (tecla.compare("S") == 0)){
				cout << "Ingrese el cargo: ";
				cin >> cargo;
				Cargo* unCargo = new Cargo (cargo);
				Registro* reg1 = new Registro (unCargo);
				delete unCargo;
				Registro* reg2 = heCargo->obtenerRegistro(reg1);
				if(reg2==NULL) {
					cout << "No existe cargo/cargo no valido" << endl;
					tecla = "S";
				}
				else {
					salir=true;
					tecla = "P";
					errorCarga=false;
				}
				delete reg1;
				delete reg2;
				if (tecla.compare("S") == 0){
					cout << "¿ Desea repetir? (S/N): ";
					cin >> tecla;
					cout <<endl;
					if (tecla.compare("N") == 0){
						salir = true;
						tecla="N";
						errorCarga = true;
						cout << "La eleccion no fue cargada" << endl;
						cargo = "";
					}
				}
			}

			if (!errorCarga){
				cout << "Ingrese la lista: ";

				char* entrada2 = new char[longitud];
				cin.ignore();
				cin.getline(entrada2,this->longitud);
				nombreLista = entrada2;
				delete[] entrada2;
			}

			lista = new Lista(nombreLista,fecha,cargo);

			registro = new Registro(lista);
			delete (lista);

		}
		int rta;
		switch (i)
		{
		case 1 : {
			if (!errorCarga){
				rta = administrador->altaArbol(bLista,registro);
				if (rta == 0) {
					cout << "Operación exitosa"<<endl;
				}
				else{
					cout << "Operación fallida"<<endl;
				}
			}
		}break;
		case 2 : {
			if (!errorCarga){
				rta = administrador->bajaArbol(bLista,registro);
				if (rta == 0) {
					cout << "Operación exitosa"<<endl;
				}
				else{
					cout << "Operación fallida"<<endl;
				}
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
	string archivoDeControl=this->rutaHash+"DeControlEleccion.txt";
	string archivoDeDatos = this->rutaHash+"DeDatosEleccion";
	HashingExtensible * heEleccion = new HashingExtensible (this->longitud,(char*)archivoDeDatos.c_str(),(char*)archivoDeControl.c_str());

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
			char* entrada = new char[longitud];
			cin.ignore();
			cin.getline(entrada,this->longitud);
			cargo = entrada;
			delete[] entrada;
//			cin >> cargo;

			eleccion = new Eleccion(fecha,cargo);
			registro = new Registro(eleccion);
			delete eleccion;
		}
		switch (i)
		{
		case 1 : {
			Registro * registroObtenido = heEleccion->obtenerRegistro(registro);
			if ( registroObtenido != NULL){
				eleccion = (Eleccion*) registroObtenido->getContenido();

				if ( administrador->habilitarEleccion(eleccion) ){

					string pathDatos = this->rutaArbol + "arbolDeListas";
					bplustree * arbolB = new bplustree();
					arbolB->newtree(pathDatos,this->longitudNodo);

					// Cargar archivoDeConteo con las listas que participan en la actual eleccion.
					administradorDeConteo->cargarEleccionEnArchivoDeConteo(eleccion, arbolB);
					delete arbolB;
					cout << "Elección habilitada"<<endl;

					cout << "Se habilito la eleccion: " << eleccion->getFecha() << endl;
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
			return;
		}break;
		}
//		delete eleccion;
		delete registro;
		registro = NULL;
		i = 0;
	}
}

void InterfazAdministrador::comienzoVotacion(Administrador * administrador){
	string pathControl = this->rutaHash + "DeControlVotante.txt";
	string pathDatos = this->rutaHash + "DeDatosVotante";

	HashingExtensible * heVotante = new HashingExtensible (this->longitud,(char*)pathDatos.c_str(),(char*)pathControl.c_str());

	int cantidadDeSimulaciones;
	cout << "Ingrese la cantidad de votos a realizar: ";
	cin >> cantidadDeSimulaciones;
	cout << endl;

	pathDatos = this->rutaArbol + "arbolDeListas";
	bplustree * arbolB = new bplustree();
	arbolB->newtree(pathDatos,this->longitudNodo);

	string modo = "S";

	while ((modo.compare("a") != 0) and (modo.compare("m") != 0)){
		cout << "Ingrese modo de votación: Automático (a) o Manual (m)";
		cin >> modo;
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
		votanteActual->setRSA(this->rsa);
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
			votanteActual->setRSA(this->rsa);
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
			if (modo.compare("a") == 0) password = votanteActual->getPassword();
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
						if (modo.compare("a") == 0) n = (rand()%((administrador->getListaDeEleccionesDelVotante()).size()))+1;
//						if (modo=='a') n=1;
						else cin >> n;
						if (((n)<=((int)((administrador->getListaDeEleccionesDelVotante()).size()))) && (n>0)) {
							while (!ok) {
								cout << "Usted eligio la eleccion " << n << endl;
								cout << "Si es correcto presione s sino n" << endl;
								numeroDeEleccion=n;
								if (modo.compare("a") == 0) c='s';
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
					heVotante->modificarRegistro(registroAuxiliar);
					delete registroAuxiliar;
					mensaje = "El votante participara en la eleccion: ";
					log.insertarMensajeConEntidad(*itListaDelVotante,mensaje);
					ok=false;
					int boleta;
					//			cargo las listas que puede elegir el votante en esta eleccion
					administrador->cargarListasDeEleccion(*itListaDelVotante,arbolB);
					while (!ok) {
						char modoApertura;
						while (!ok) {
							if (modo.compare("a") == 0){
								modoApertura = 'a';
							} else{
								modoApertura = 'm';
							}
							boleta = administrador->elegirBoleta(modoApertura);
//							if (!boleta) return;
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
	delete arbolB;
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

void InterfazAdministrador::cargarArchivoDeConteo(Eleccion* eleccion,Administrador* administrador){

	//Busco en la lista de elecciones habilitadas
	string pathDatos = this->rutaArbol + "arbolDeListas";
	bplustree * arbolDeListas = new bplustree();
//	arbolDeListas->opentree((char*)pathDatos.c_str(),this->longitudNodo);
	arbolDeListas->newtree((char*)pathDatos.c_str(),this->longitudNodo);


	string fecha = eleccion->getFecha();
	string cargo = eleccion->getCargo();

	string clave = fecha + cargo;
	arbolDeListas->search(clave);

	arbolDeListas->search(clave);
	pair<vector<char>,string> map = arbolDeListas->getnext();

	bool buscarSiguienteLista = true;
	while ( map.second.size() != 0 and buscarSiguienteLista == true){

		string* registroSerializado = getString(map.first);

		Registro* registro = new Registro();
		registro->deserializar(registroSerializado);
		delete registroSerializado;

		Lista* lista = (Lista*)registro->getContenido();
		delete registro;

		if ( lista != NULL ){

			if ( lista->getFecha() == fecha and lista->getCargo() == cargo ){

				// Recorro los distritos de la eleccion habilitada
				list<Distrito>::iterator itDistrito = eleccion->obtenerIterador();
				while( !eleccion->ultimo(itDistrito) ){
					Conteo* conteo = new Conteo(fecha,cargo,lista->getNombre(),(*itDistrito).getDistrito());
					administradorDeConteo->agregarConteo(conteo);
					delete conteo;

					itDistrito++;
				}
				pair<vector<char>,string> map = arbolDeListas->getnext();

			}

			else
				buscarSiguienteLista = false;

			delete lista;
		}

		else
			buscarSiguienteLista = false;
	}
}

void InterfazAdministrador::mostrarMenuVotacionAutomatica(Administrador * administrador){

	if ( votoAutomatizado == false ){

		string s = "";

		string votantes = "2\n5\n5000\n4\n";
		string cargo = "4\n1\nPresidente\nS\nVicepresidente\nN\n4\n";

		for(int a = 1983; a < 2010; a++){
			//for(int m = 1; m < 13; m++){
				stringstream stream;
				stream << a;
//				if (m < 10) stream <<"0";
//				stream << m;
				string fecha = stream.str()+"0303";
				string eleccion = "3\n1\n"+fecha+"\nPresidente\nCiudad Autonoma de Buenos Aires\nS\nBuenos Aires\nS\nEntre Rios\nS\nCorrientes\nS\nMisiones\nS\nFormosa\nS\nChaco\nS\nSanta Fe\nS\nCordoba\nS\nSantiago del Estero\nS\nTucuman\nS\nSalta\nS\nJujuy\nS\nCatamarca\nS\nLa Rioja\nS\nSan Juan\nS\nMendoza\nS\nSan Luis\nS\nLa Pampa\nS\nRio Negro\nS\nNeuquen\nS\nChubut\nS\nSanta Cruz\nS\nTierra del Fuego\nN\n4\n";
				string listas = "5\n1\n"+fecha+"\nPresidente\nVerde\n1\n"+fecha+"\nPresidente\nAzul\n1\n"+fecha+"\nPresidente\nRoja\n1\n"+fecha+"\nPresidente\nAmarilla\n1\n"+fecha+"\nPresidente\nVioleta\n1\n"+fecha+"\nPresidente\nCesleste\n1\n"+fecha+"\nPresidente\nNegra\n1\n"+fecha+"\nPresidente\nTurquesa\n1\n"+fecha+"\nPresidente\nRosa\n1\n"+fecha+"\nPresidente\nBlanca\n1\n"+fecha+"\nPresidente\nMarron\n4\n";
				string habilitarEleccion = "8\n1\n"+fecha+"\nPresidente\n3\n";
				s += eleccion + listas + habilitarEleccion;
			//}
		}
		string votacion = "9\n5000\na\n";
		string terminar = "11\n";

		string automata = votantes+cargo+s+votacion+terminar;

		stream = new stringstream(automata);
		backup = cin.rdbuf(stream->rdbuf());
		votoAutomatizado = true;
	}else{
		cin.rdbuf(backup);
		delete stream;
		votoAutomatizado = false;
	}
	return;


}

void InterfazAdministrador::mostrarMenuCriptoanalisis(Administrador * administrador){

	int i;
	string opcion = "0";

	while (true){

		i = 0;

		while ((i < 1) or (i > 5)){
			cout << "Opciones: "<<endl<<endl;
			cout << "1) Criptoanalizar informe de Elecciones"<<endl;
			cout << "2) Criptoanalizar informe de Listas"<<endl;
			cout << "3) Criptoanalizar informe de Distritos"<<endl;
			cout << "4) Volver atrás"<<endl;
			cout << "Opcion: ";
			cin >> opcion;
			cout <<endl;
			if ( isANumber(opcion) == 1){
				i = atoi(opcion.c_str());
			}

		}

		switch (i)
		{
		case 1 : {
			this->criptoanalizarInforme(config->pathInformes()+ELECCIONES);

		}break;
		case 2 : {
			this->criptoanalizarInforme(config->pathInformes()+LISTAS);
		}break;
		case 3 : {
			this->criptoanalizarInforme(config->pathInformes()+DISTRITOS);
		}break;
		case 4 :
			return;
		}

	}
}


void InterfazAdministrador::criptoanalizarInforme(string informe){

	ManejadorDeArchivo* ma = new ManejadorDeArchivo(informe);
	int size = ma->obtenerTamArchivo();

	if ( size > 0 ){

		string* criptograma;
		string* mensaje;
		char* cadena = new char[size];
		ma->leer(cadena,size);

		stringstream stream;
		stream.write(cadena,size);
		criptograma = new string(stream.str());

		Kasiski ka;
		string key;

		ka.generarPatrones(criptograma);
		ka.MCDDistancias();
		ka.analisisDeFrecuencias(*criptograma);
		key = ka.romper();

		cout << "Clave descifrada: " << key << endl<< endl;

		Vigenere* vigenere = new Vigenere(key);
		mensaje = vigenere->descifrar(criptograma);
		cout << *mensaje;

		delete mensaje;
		delete criptograma;
		delete vigenere;
		delete[] cadena;

	}else{
		cout << "Archivo del informe vacio o inexistente" << endl;
	}
	delete ma;
}

void InterfazAdministrador::atacarRSA(){
	this->rsa->atacar();
}

InterfazAdministrador::~InterfazAdministrador() {
//	delete (this->config);
	delete (this->administradorDeConteo);
	delete rsa;
}
