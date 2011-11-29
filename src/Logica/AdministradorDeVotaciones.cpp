#include "AdministradorDeVotaciones.h"

AdministradorDeVotaciones::AdministradorDeVotaciones() {

}

string AdministradorDeVotaciones::obtenerClavePrincipal(Conteo *conteo)
{
	string clave = "";

	clave  = conteo->getFechaEleccion();
	clave += conteo->getCargoEleccion();
	clave += conteo->getLista();
	clave += conteo->getDistrito();

	return clave;
}

string AdministradorDeVotaciones::obtenerClaveSecundaria(Conteo *conteo)
{
	string clave = "";

	clave += conteo->getDistrito();
	clave += conteo->getFechaEleccion();
	clave += conteo->getCargoEleccion();
	clave += conteo->getLista();

	return clave;
}

string* AdministradorDeVotaciones::getString(vector<char> vect){
	string* s = new string();
	vector<char>::iterator it = vect.begin();

	while( it != vect.end() ){
		s->push_back(*it);
		it++;
	}
	return s;
}

int AdministradorDeVotaciones::agregarConteoAlIndicePorDistrito(Conteo* conteo){

	string clave = obtenerClaveSecundaria(conteo);
	vector<char> resultado = indiceSecundario.search(clave);

	if ( resultado.size() == 0 ){

		string clavePrincipal = obtenerClavePrincipal(conteo);
		vector<char> data(clavePrincipal.begin(),clavePrincipal.end());

		indiceSecundario.add(clave,data);

		return 0;
	}else{
		return 1;
	}

}

/* METODOS PUBLICOS **********************************************************/

void AdministradorDeVotaciones::nuevoArchivoDeConteo(string pathArchivo, string pathIndiceSecundario,int dimensionBloque)
{
	archivoDeConteo.newtree(pathArchivo,dimensionBloque);
	indiceSecundario.newtree(pathIndiceSecundario,dimensionBloque);
}

void AdministradorDeVotaciones::abrirArchivoDeConteo(string pathArchivo,string pathIndiceSecundario,int dimensionBloque){

	archivoDeConteo.opentree(pathArchivo,dimensionBloque);
	indiceSecundario.opentree(pathIndiceSecundario,dimensionBloque);
}

int AdministradorDeVotaciones::agregarConteo(Conteo *conteo)
{
	int resultadoFuncion = 1;
	string* conteoSerializado = conteo->serializar();

	string clave = obtenerClavePrincipal(conteo);
	vector<char> resultado = archivoDeConteo.search(clave);
	if ( resultado.size() == 0 ){

		vector<char> data(conteoSerializado->begin(),conteoSerializado->end());

		archivoDeConteo.add(clave,data);

		// agrego el contenido al indice secundario distrito
		agregarConteoAlIndicePorDistrito(conteo);

		resultadoFuncion = 0;
	}
	delete conteoSerializado;

	return resultadoFuncion;
}

void AdministradorDeVotaciones::incrementarVoto(Eleccion *eleccion, string *nombreLista, string *distrito)
{
	Conteo* conteo = new Conteo(eleccion->getFecha(),eleccion->getCargo(),*nombreLista,*distrito);
	string clave = obtenerClavePrincipal(conteo);
	delete conteo;

	vector<char> result = archivoDeConteo.search(clave);

	if (result.size() != 0){

		string* conteoSerializado = getString(result);

		conteo = new Conteo("","","","");
		conteo->deserializar(conteoSerializado);

		conteo->incrementarVotos();
		delete conteoSerializado;

		conteoSerializado = conteo->serializar();

		vector<char> vectorSerializado(conteoSerializado->begin(),conteoSerializado->end());
		archivoDeConteo.modify(clave,vectorSerializado);

		delete conteo;
		delete conteoSerializado;
	}
}

void AdministradorDeVotaciones::mostrarArchivoPrincipal(){
	string* conteoSerializado = getString( archivoDeConteo.search("") );

	pair<vector<char>,string> par=archivoDeConteo.getnext();
	while( par.second.size() != 0 ) {

		conteoSerializado = getString( par.first );
		Conteo* conteo = new Conteo("","","","");
		conteo->deserializar(conteoSerializado);
		delete conteoSerializado;

		conteo->verEntidad();
		delete conteo;
		cout << endl;
		par=archivoDeConteo.getnext();
	}
}

void AdministradorDeVotaciones::mostrarArchivoSecundario(){
	indiceSecundario.search("");

	pair<vector<char>,string> par=indiceSecundario.getnext();
	while( par.second.size() != 0 ) {

		string* conteoSerializado = getString( par.first );

		cout << *conteoSerializado << endl;
		par=indiceSecundario.getnext();
		delete conteoSerializado;
	}
}
void AdministradorDeVotaciones::mostrarArchivoPrincipalEnFormatoTabla(){
	string* conteoSerializado;

	int contarVotos = 0;

	archivoDeConteo.search("");

	pair<vector<char>,string> par=archivoDeConteo.getnext();
	while( par.second.size() != 0 ) {

		conteoSerializado = getString( par.first );
		Conteo* conteo = new Conteo("","","","");
		conteo->deserializar(conteoSerializado);
		delete conteoSerializado;

		cout << setw(10) << left << conteo->getFechaEleccion();
		cout << setw(20) << left << conteo->getCargoEleccion();
		cout << setw(30) << left << conteo->getLista();
		cout << setw(30) << left << conteo->getDistrito();
		cout << setw(15) << conteo->getCantidadVotos();
		cout << endl;

		contarVotos += conteo->getCantidadVotos();

		delete conteo;

		par=archivoDeConteo.getnext();
	}

	cout << endl << "Cantidad de votos en total: " << contarVotos << endl;
}


void AdministradorDeVotaciones::mostrarArchivoPrincipalEnFormatoTablaOrdenadoPorClaveSecundaria(){
	string* conteoSerializado;

	int contarVotos = 0;

	indiceSecundario.search("");

	pair<vector<char>,string> par=indiceSecundario.getnext();
	while( par.second.size() != 0 ) {

		string* clavePrimaria = getString(par.first);
		conteoSerializado = getString( archivoDeConteo.search(*clavePrimaria) );
		delete clavePrimaria;

		Conteo* conteo = new Conteo("","","","");
		conteo->deserializar(conteoSerializado);
		delete conteoSerializado;

		cout << setw(40) << left << conteo->getDistrito();
		cout << setw(10) << left << conteo->getFechaEleccion();
		cout << setw(30) << left << conteo->getCargoEleccion();
		cout << setw(40) << left << conteo->getLista();
		cout << setw(15) << conteo->getCantidadVotos();
		cout << endl;

		contarVotos += conteo->getCantidadVotos();

		delete conteo;
		par=indiceSecundario.getnext();
	}

	cout << endl << "Cantidad de votos en total: " << contarVotos << endl;
}

void AdministradorDeVotaciones::generarInformePorEleccion(Eleccion *eleccion)
{
	bool busquedaOK = false;

	bool mismaEleccion;
	bool mismoDistrito;

	Vigenere* vigenere = new Vigenere(claveParaEleccion);
	ManejadorDeArchivo* archivo = new ManejadorDeArchivo(pathInformePorEleccion);
	stringstream informe;
	string* mensaje = new string();

	cout << "********* GENERO EL INFORME POR ELECCION **********" << endl;
	informe << "********* GENERO EL INFORME POR ELECCION **********" << endl;

	cout << endl;
	string clave = eleccion->getFecha();
	clave += eleccion->getCargo();

	archivoDeConteo.search(clave);

	pair<vector<char>,string> resultado = archivoDeConteo.getnext();

	if ( resultado.second.size() != 0 ){

		string* conteoSerializado = getString( resultado.first );

		Conteo* conteo = new Conteo();
		conteo->deserializar(conteoSerializado);
		delete conteoSerializado;

		if( conteo->getFechaEleccion() == eleccion->getFecha() && conteo->getCargoEleccion() == eleccion->getCargo() ){

			cout << setw(10) << left << "Fecha";
			cout << setw(30) << left << "Cargo";
			cout << setw(40) << left << "Lista";
			cout << setw(15) << left << "Cantidad de votos";
			cout << endl;

			informe << setw(10) << left << "Fecha";
			informe << setw(30) << left << "Cargo";
			informe << setw(40) << left << "Lista";
			informe << setw(15) << left << "Cantidad de votos";
			informe << endl;

			mismaEleccion = true;
			while( mismaEleccion ){

				if  ( conteo->getFechaEleccion() == eleccion->getFecha() && conteo->getCargoEleccion() == eleccion->getCargo() ){

					int cantidadDeVotos = 0;
					string nombreDeListaActual = conteo->getLista();

					mismoDistrito = true;
					while ( mismoDistrito ){

						if ( conteo->getLista() == nombreDeListaActual ){
							cantidadDeVotos += conteo->getCantidadVotos();

							pair<vector<char>,string> resultado = archivoDeConteo.getnext();

							if ( resultado.second.size() != 0 ){
								string* conteoSerializado = getString( resultado.first );
								delete conteo;

								conteo = new Conteo();
								conteo->deserializar(conteoSerializado);
								delete conteoSerializado;

							}else{
								mismoDistrito = false;
								mismaEleccion = false;
							}

						}else mismoDistrito = false;
					}

					cout << setw(10) << left << eleccion->getFecha();
					cout << setw(30) << left << eleccion->getCargo();
					cout << setw(40) << left << nombreDeListaActual;
					cout << setw(15) << cantidadDeVotos;
					cout << endl;

					informe << setw(10) << left << eleccion->getFecha();
					informe << setw(30) << left << eleccion->getCargo();
					informe << setw(40) << left << nombreDeListaActual;
					informe << setw(15) << cantidadDeVotos;
					informe << endl;

					busquedaOK = true;

					mensaje->assign(informe.str());
					string* criptograma = vigenere->cifrar(mensaje);
					archivo->escribir(criptograma->c_str(),criptograma->size()+1);

					delete criptograma;

				}else mismaEleccion = false;
			}
		}

		delete conteo;
	}

	delete mensaje;
	delete archivo;
	delete vigenere;

	if ( !busquedaOK )
		cout << "No se encontraron registros previos." << endl;

	cout << endl;
}

void AdministradorDeVotaciones::generarInformePorLista(Lista *lista,HashingExtensible* heCargo)
{
	bool busquedaOK = false;
	bool mismaEleccion;


	Vigenere* vigenere = new Vigenere(claveParaLista);
	ManejadorDeArchivo* archivo = new ManejadorDeArchivo(pathInformePorLista);
	stringstream informe;
	string* mensaje = new string();


	cout << "********* GENERO EL INFORME POR LISTA **********" << endl;
	informe << "********* GENERO EL INFORME POR LISTA **********" << endl;

	string fecha = lista->getFecha();
	string cargoPrincipal = lista->getCargo();
	string nombreLista = lista->getNombre();

	cout << endl << "Lista a informar: "<< nombreLista << endl << endl;
	informe << endl << "Lista a informar: "<< nombreLista << endl << endl;
	string clave = fecha + cargoPrincipal + nombreLista;

	archivoDeConteo.search(clave);

	pair<vector<char>,string> resultadoBusqueda = archivoDeConteo.getnext();

	if ( resultadoBusqueda.second.size() != 0 )
	{
		string* contenidoSerializado = getString( resultadoBusqueda.first );
		Conteo* conteo = new Conteo();
		conteo->deserializar(contenidoSerializado);
		delete contenidoSerializado;

		if( conteo->getFechaEleccion() == fecha && conteo->getCargoEleccion() == cargoPrincipal && conteo->getLista() == nombreLista ){

			busquedaOK = true;

			cout << setw(10) << left << "Fecha";
			cout << setw(40) << left << "Nombre de lista";
			cout << setw(15) << "Cantidad de votos";
			cout << endl;

			informe << setw(10) << left << "Fecha";
			informe << setw(40) << left << "Nombre de lista";
			informe << setw(15) << "Cantidad de votos";
			informe << endl;

			int cantidadDeVotos = 0;

			mismaEleccion = true;
			while( mismaEleccion ){

				if (conteo->getFechaEleccion() == fecha && conteo->getCargoEleccion() == cargoPrincipal && conteo->getLista() == nombreLista){
					cantidadDeVotos += conteo->getCantidadVotos();

					pair<vector<char>,string> resultado = archivoDeConteo.getnext();

					if ( resultado.second.size() != 0){
						string* conteoSerializado = getString( resultado.first );
						delete conteo;

						conteo = new Conteo();
						conteo->deserializar(conteoSerializado);
						delete conteoSerializado;

					}else mismaEleccion = false;

				}else mismaEleccion = false;
			}

			cout << setw(10) << left << fecha;
			cout << setw(40) << left << nombreLista;
			cout << setw(15) << cantidadDeVotos;
			cout << endl;

			cout << "Cargo principal\t" << cargoPrincipal << endl;

			informe << setw(10) << left << fecha;
			informe << setw(40) << left << nombreLista;
			informe << setw(15) << cantidadDeVotos;
			informe << endl;

			informe << "Cargo principal\t" << cargoPrincipal << endl;

			Cargo* cargo 		= new Cargo(cargoPrincipal);
			Registro* registro	= new Registro(cargo);
			delete cargo;

			Registro* registroEncontrado = heCargo->obtenerRegistro(registro);
			delete registro;

			if ( registroEncontrado != NULL ){
				cargo = (Cargo*)registroEncontrado->getContenido();
				delete registroEncontrado;

				list<string> listaCargos = cargo->devolverSubCargos();
				int cantidadSubcargos = listaCargos.size();
				list<string>::iterator it = listaCargos.begin();
				for(int i=0; i < cantidadSubcargos ; i++){
					cout << "Subcargo " << i+1 << "\t" << *it << endl;
					informe << "Subcargo " << i+1 << "\t" << *it << endl;
					it++;
				}

				delete cargo;
			}

		}
		delete conteo;

		cout << endl;
		informe << endl;
	}

	mensaje->assign(informe.str());
	string* criptograma = vigenere->cifrar(mensaje);
	archivo->escribir(criptograma->c_str(),criptograma->size()+1);

	cout << "se escribieron " << criptograma->size() << endl;

	delete mensaje;
	delete archivo;
	delete vigenere;


	if ( !busquedaOK )
		cout << "No se encontraron registros previos." << endl;
}

void AdministradorDeVotaciones::generarInformePorDistrito(Distrito *distrito)
{
	bool busquedaOK = false;
	bool mismoDistrito;
	bool mismaEleccion;

	Vigenere* vigenere = new Vigenere(claveParaDistrito);
	ManejadorDeArchivo* archivo = new ManejadorDeArchivo(pathInformePorDistrito);
	stringstream informe;
	string* mensaje = new string();

	cout << "********* GENERO EL INFORME POR DISTRITO **********" << endl;
	informe << "********* GENERO EL INFORME POR DISTRITO **********" << endl;

	cout << endl << "Distrito a informar: " << distrito->getDistrito() << endl<<endl;
	informe << endl << "Distrito a informar: " << distrito->getDistrito() << endl<<endl;

	string clave = distrito->getDistrito();

	indiceSecundario.search(clave);

	pair<vector<char>,string> resultadoBusquedaSecundario = indiceSecundario.getnext();

	if ( resultadoBusquedaSecundario.first.size() != 0 )
	{

		// Obtengo el contenido del indice secundario, que es la clave del primario.
		string* clavePrincipal = getString( resultadoBusquedaSecundario.first );
		vector<char> resultadoBusquedaPrimario = archivoDeConteo.search( *clavePrincipal );
		delete clavePrincipal;

		if ( resultadoBusquedaPrimario.size() != 0 )
		{
			string* contenidoSerializado = getString( resultadoBusquedaPrimario );
			Conteo* conteo = new Conteo();
			conteo->deserializar(contenidoSerializado);
			delete contenidoSerializado;

			string distritoAinformar = distrito->getDistrito();

			if ( distritoAinformar == conteo->getDistrito() ){

				cout << setw(10) << left << "Fecha";
				cout << setw(30) << left << "Cargo";
				cout << setw(40) << left << "Lista ganadora";
				cout << setw(15) << "Cantidad de votos obtenidos";
				cout << endl;

				informe << setw(10) << left << "Fecha";
				informe << setw(30) << left << "Cargo";
				informe << setw(40) << left << "Lista ganadora";
				informe << setw(15) << "Cantidad de votos obtenidos";
				informe << endl;

				mismoDistrito = true;
				while( mismoDistrito )
				{
					if ( distritoAinformar == conteo->getDistrito() ){

						string fechaEleccion = conteo->getFechaEleccion();

						string cargoEleccion = conteo->getCargoEleccion();

						unsigned int maximo = conteo->getCantidadVotos();
						bool primero = true;

						string nombreDelGanador = conteo->getLista();

						mismaEleccion = true;
						while( mismaEleccion){

							if ( conteo->getDistrito() == distritoAinformar && conteo->getFechaEleccion() == fechaEleccion && conteo->getCargoEleccion() == cargoEleccion ){
								if ( conteo->getCantidadVotos() > maximo ){
									maximo = conteo->getCantidadVotos();
									nombreDelGanador = conteo->getLista();
								}
								else if ( conteo->getCantidadVotos() == maximo && primero == false)
									nombreDelGanador = "empate";
								primero = false;

								resultadoBusquedaSecundario = indiceSecundario.getnext();

								if ( resultadoBusquedaSecundario.second.size() != 0 ){
									clavePrincipal = getString( resultadoBusquedaSecundario.first );
									resultadoBusquedaPrimario = archivoDeConteo.search( *clavePrincipal );
									delete clavePrincipal;

									delete conteo;

									contenidoSerializado = getString( resultadoBusquedaPrimario );
									conteo = new Conteo();
									conteo->deserializar(contenidoSerializado);
									delete contenidoSerializado;
								}
								else{
									mismaEleccion = false;
									mismoDistrito = false;
								}
							}else mismaEleccion = false;
						}

						cout << setw(10) << left << fechaEleccion;
						cout << setw(30) << left << cargoEleccion;
						cout << setw(40) << left << nombreDelGanador;
						cout << setw(15) << maximo;
						cout << endl;

						informe << setw(10) << left << fechaEleccion;
						informe << setw(30) << left << cargoEleccion;
						informe << setw(40) << left << nombreDelGanador;
						informe << setw(15) << maximo;
						informe << endl;

					}else mismoDistrito = false;
				}

				busquedaOK = true;
			}
			delete conteo;
		}
	}

	mensaje->assign(informe.str());
	string* criptograma = vigenere->cifrar(mensaje);
	archivo->escribir(criptograma->c_str(),criptograma->size()+1);

	delete mensaje;
	delete archivo;
	delete vigenere;

	if ( !busquedaOK )
		cout << "No se encontraron registros previos."<<endl;

	cout << endl;
}

bplustree AdministradorDeVotaciones::getArchivoDeConteo() const
{
    return archivoDeConteo;
}

bplustree AdministradorDeVotaciones::getIndiceSecundario() const
{
    return indiceSecundario;
}

string AdministradorDeVotaciones::getPathInformePorDistrito() const
{
    return pathInformePorDistrito;
}

string AdministradorDeVotaciones::getPathInformePorEleccion() const
{
    return pathInformePorEleccion;
}

string AdministradorDeVotaciones::getPathInformePorLista() const
{
    return pathInformePorLista;
}

void AdministradorDeVotaciones::setArchivoDeConteo(bplustree archivoDeConteo)
{
    this->archivoDeConteo = archivoDeConteo;
}

void AdministradorDeVotaciones::setIndiceSecundario(bplustree indiceSecundario)
{
    this->indiceSecundario = indiceSecundario;
}

void AdministradorDeVotaciones::setPathInformePorDistrito(string pathInformePorDistrito)
{
    this->pathInformePorDistrito = pathInformePorDistrito;
}

void AdministradorDeVotaciones::setPathInformePorEleccion(string pathInformePorEleccion)
{
    this->pathInformePorEleccion = pathInformePorEleccion;
}

void AdministradorDeVotaciones::setClaveParaDistrito(string claveParaDistrito)
{
    this->claveParaDistrito = claveParaDistrito;
}

void AdministradorDeVotaciones::setClaveParaEleccion(string claveParaEleccion)
{
    this->claveParaEleccion = claveParaEleccion;
}

void AdministradorDeVotaciones::setClaveParaLista(string claveParaLista)
{
    this->claveParaLista = claveParaLista;
}

void AdministradorDeVotaciones::setPathInformePorLista(string pathInformePorLista)
{
    this->pathInformePorLista = pathInformePorLista;
}

AdministradorDeVotaciones::~AdministradorDeVotaciones() {
}

bool AdministradorDeVotaciones::cargarEleccionEnArchivoDeConteo(Eleccion* eleccion, bplustree * arbolB)
{

	bool cargado = false;

	Conteo* conteo;

	string clave;
	clave  = eleccion->getFecha();
	clave += eleccion->getCargo();

	vector<char> result = arbolB->search(clave);

	bool buscarSiguienteLista = true;
	while ( buscarSiguienteLista == true ){

		buscarSiguienteLista = false;

		pair<vector<char>,string> map = arbolB->getnext();

		if ( map.first.size() != 0 ){

			string* registroSerializado = getString(map.first);

			Registro* registro = new Registro();
			registro->deserializar(registroSerializado);
			delete registroSerializado;

			Lista* lista = (Lista*)registro->getContenido();
			delete registro;

			if ( lista != NULL ){

				if ( lista->getFecha() == eleccion->getFecha() and lista->getCargo() == eleccion->getCargo() ){

					// Recorro los distritos de la eleccion habilitada
					list<Distrito>::iterator itDistrito = eleccion->obtenerIterador();
					while( !eleccion->ultimo(itDistrito) ){
						conteo = new Conteo(lista->getFecha(),lista->getCargo(),lista->getNombre(),(*itDistrito).getDistrito());
						if ( agregarConteo(conteo) == 0)
							cargado = true;

						delete conteo;

						itDistrito++;
					}

					buscarSiguienteLista = true;

				}
				delete lista;
			}
		}
	}
	return cargado;

}
