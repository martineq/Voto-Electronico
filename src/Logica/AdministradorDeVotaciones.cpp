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

//	archivoDeConteo.opentree(pathArchivo);
//	indiceSecundario.opentree(pathIndiceSecundario);
}

int AdministradorDeVotaciones::agregarConteo(Conteo *conteo)
{
	int resultadoFuncion = 1;

	conteo->verEntidad();

	string* conteoSerializado = conteo->serializar();

	string clave = obtenerClavePrincipal(conteo);
	vector<char> resultado = archivoDeConteo.search(clave);
	if ( resultado.size() == 0 ){
		cout << "size: " << conteoSerializado->size() << endl;

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

		conteo->verEntidad();

		conteo->incrementarVotos();
		delete conteoSerializado;

		conteoSerializado = conteo->serializar();

		vector<char> vectorSerializado(conteoSerializado->begin(),conteoSerializado->end());
		archivoDeConteo.modify(clave,vectorSerializado);

		delete conteo;
		delete conteoSerializado;
	}else
		cout << "size==0" << endl;
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

	archivoDeConteo.search("");

	pair<vector<char>,string> par=archivoDeConteo.getnext();
	while( par.second.size() != 0 ) {

		conteoSerializado = getString( par.first );
		Conteo* conteo = new Conteo("","","","");
		conteo->deserializar(conteoSerializado);
		delete conteoSerializado;

		cout << conteo->getFechaEleccion() << "\t\t";
		cout << conteo->getCargoEleccion() << "\t\t";
		cout << conteo->getLista() << "\t\t";
		cout << conteo->getDistrito() << "\t\t";
		cout << conteo->getCantidadVotos() << endl;


		delete conteo;
		cout << endl;
		par=archivoDeConteo.getnext();
	}

}

void AdministradorDeVotaciones::generarInformePorEleccion(Eleccion *eleccion)
{
	cout << "********* GENERO EL INFORME POR ELECCION **********" << endl;

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

		cout << "Fecha de eleccion \tCargo \t\tLista \t\tCantidad de votos" << endl;

		while( conteo->getFechaEleccion() == eleccion->getFecha() && conteo->getCargoEleccion() == eleccion->getCargo() ){

			int cantidadDeVotos = 0;

			string nombreDeListaActual = conteo->getLista();

			while ( conteo->getLista() == nombreDeListaActual ){

				cantidadDeVotos += conteo->getCantidadVotos();

				pair<vector<char>,string> resultado = archivoDeConteo.getnext();
				string* conteoSerializado = getString( resultado.first );

				delete conteo;

				conteo = new Conteo();
				conteo->deserializar(conteoSerializado);
				delete conteoSerializado;
			}
			cout << eleccion->getFecha() << "\t\t" << eleccion->getCargo() << "\t" << nombreDeListaActual << "\t\t" << cantidadDeVotos << endl;

		}
		delete conteo;
	}

	cout << endl;
}

void AdministradorDeVotaciones::generarInformePorLista(Lista *lista,HashingExtensible* heCargo)
{
	cout << "********* GENERO EL INFORME POR LISTA **********" << endl;

	string fecha = lista->getFecha();
	string cargoPrincipal = lista->getCargo();
	string nombreLista = lista->getNombre();

	cout << endl << "Lista a informar: "<< nombreLista << endl << endl;
	string clave = fecha + cargoPrincipal + nombreLista;

	archivoDeConteo.search(clave);

	pair<vector<char>,string> resultadoBusqueda = archivoDeConteo.getnext();

	if ( resultadoBusqueda.second.size() != 0 )
	{
		string* contenidoSerializado = getString( resultadoBusqueda.first );
		Conteo* conteo = new Conteo();
		conteo->deserializar(contenidoSerializado);
		delete contenidoSerializado;

		cout << "Fecha de eleccion \tLista \t\tCantidad de votos" << endl;

		int cantidadDeVotos = 0;

		while( conteo->getFechaEleccion() == fecha && conteo->getCargoEleccion() == cargoPrincipal && conteo->getLista() == nombreLista ){

			cantidadDeVotos += conteo->getCantidadVotos();

			pair<vector<char>,string> resultado = archivoDeConteo.getnext();

			string* conteoSerializado = getString( resultado.first );

			delete conteo;

			conteo = new Conteo();
			conteo->deserializar(conteoSerializado);
			delete conteoSerializado;
		}

		delete conteo;

		cout << fecha << "\t\t" << nombreLista << "\t\t" << cantidadDeVotos << endl;

		cout << "Cargo principal\t" << cargoPrincipal << endl;

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
				it++;
			}

			delete cargo;
		}
		cout << endl;
	}
}

void AdministradorDeVotaciones::generarInformePorDistrito(Distrito *distrito)
{
	cout << "********* GENERO EL INFORME POR DISTRITO **********" << endl;

	cout << endl << "Distrito a informar: " << distrito->getDistrito() << endl<<endl;

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

			cout << "Fecha de eleccion \tCargo \t\tLista ganadora \t\tCantidad de votos" << endl;

			string distritoAinformar = distrito->getDistrito();

			while( distritoAinformar == conteo->getDistrito() )
			{

				string fechaEleccion = conteo->getFechaEleccion();

				string cargoEleccion = conteo->getCargoEleccion();

				unsigned int maximo = conteo->getCantidadVotos();
				bool primero = true;

				string nombreDelGanador = conteo->getLista();

				while( conteo->getDistrito() == distritoAinformar && conteo->getFechaEleccion() == fechaEleccion && conteo->getCargoEleccion() == cargoEleccion)
				{

					if ( conteo->getCantidadVotos() > maximo ){
						maximo = conteo->getCantidadVotos();
						nombreDelGanador = conteo->getLista();
						primero = false;
					}
					else if ( conteo->getCantidadVotos() == maximo && primero == false)
						nombreDelGanador = "empate";

					resultadoBusquedaSecundario = indiceSecundario.getnext();

					clavePrincipal = getString( resultadoBusquedaSecundario.first );
					resultadoBusquedaPrimario = archivoDeConteo.search( *clavePrincipal );
					delete clavePrincipal;

					delete conteo;

					contenidoSerializado = getString( resultadoBusquedaPrimario );
					conteo = new Conteo();
					conteo->deserializar(contenidoSerializado);
					delete contenidoSerializado;
				}

				cout << fechaEleccion << "\t\t" << cargoEleccion << "\t" << nombreDelGanador << "\t\t\t" << maximo << endl;

			}
			delete conteo;
		}
	}
	cout << endl;
}

AdministradorDeVotaciones::~AdministradorDeVotaciones() {
}

