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
	conteo->verEntidad();

	string* conteoSerializado = conteo->serializar();

	string clave = obtenerClavePrincipal(conteo);
	vector<char> resultado = archivoDeConteo.search(clave);
	if ( resultado.size() == 0 ){
		cout << "size: " << conteoSerializado->size() << endl;

		vector<char> data(conteoSerializado->begin(),conteoSerializado->end());
		delete conteoSerializado;

		archivoDeConteo.add(clave,data);

		// agrego el contenido al indice secundario distrito
		agregarConteoAlIndicePorDistrito(conteo);

		return 0;
	}else{
		return 1;
	}
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
	string* conteoSerializado = getString( indiceSecundario.search("") );

	pair<vector<char>,string> par=indiceSecundario.getnext();
	while( par.second.size() != 0 ) {

		conteoSerializado = getString( par.first );

		cout << *conteoSerializado << endl;
		par=indiceSecundario.getnext();
	}
}

void AdministradorDeVotaciones::generarInformePorEleccion(Eleccion *eleccion)
{
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
}

void AdministradorDeVotaciones::generarInformePorLista(Lista *lista,HashingExtensible* heCargo)
{
	string clave = lista->getFecha();
	clave += lista->getCargo();
	clave += lista->getNombre();

	vector<char> resultadoBusqueda = archivoDeConteo.search(clave);

	if ( resultadoBusqueda.size() != 0 )
	{
		string* contenidoSerializado = getString( resultadoBusqueda );
		Conteo* conteo = new Conteo();
		conteo->deserializar(contenidoSerializado);
		delete contenidoSerializado;

		cout << "Fecha de eleccion \tLista \t\tCantidad de votos" << endl;

		int cantidadDeVotos = 0;

		while( conteo->getFechaEleccion() == lista->getFecha() && conteo->getCargoEleccion() == lista->getCargo() && conteo->getLista() == lista->getNombre()){

			cantidadDeVotos += conteo->getCantidadVotos();

			pair<vector<char>,string> resultado = archivoDeConteo.getnext();
			string* conteoSerializado = getString( resultado.first );

			delete conteo;

			conteo = new Conteo();
			conteo->deserializar(conteoSerializado);
			delete conteoSerializado;
		}

		cout << lista->getFecha() << "\t\t" << "\t" << lista->getNombre() << "\t\t" << cantidadDeVotos << endl;

		cout << "Cargo principal:\t" << lista->getCargo() << endl;

		Cargo* cargo 		= new Cargo(lista->getCargo());
		Registro* registro	= new Registro(cargo);
		delete cargo;

		Registro* registroEncontrado = heCargo->obtenerRegistro(registro);

		if ( registroEncontrado != NULL ){
			Cargo* cargo = (Cargo*)registroEncontrado->getContenido();

			list<string> listaCargos = cargo->devolverSubCargos();
			int cantidadSubcargos = listaCargos.size();
			list<string>::iterator it = listaCargos.begin();
			for(int i=0; i < cantidadSubcargos ; i++){
				cout << "Subcargo:\t" << *it << endl;
				it++;
			}
		}

		delete cargo;
		delete registroEncontrado;
		delete conteo;
	}
}

void AdministradorDeVotaciones::generarInformePorDistrito(Distrito *distrio)
{
}

AdministradorDeVotaciones::~AdministradorDeVotaciones() {
}

