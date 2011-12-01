#include "Kasiski.h"

Kasiski::~Kasiski() {}

Kasiski::Kasiski() {}

int Kasiski::MCDDistancias(){
	list<Patron>::iterator it = this->listaPatrones.begin();
	mcd = (*(it->devolverDistancias()));

	while (it != this->listaPatrones.end()){
		list<int>::iterator itInts = it->devolverDistancias();
		while ( it->noEsUltimo(itInts)){
			mcd = gcd(mcd,(*itInts));
			itInts++;
		}
		it++;
	}
	return mcd;
}

int Kasiski::gcd(int a, int b){
	if (b == 0) return a;
	return gcd(b, a%b);
}

bool Kasiski::noExiste(Patron patron){

	bool noEncontrado = true;
	list<Patron>::iterator it = this->listaPatrones.begin();
	while ((it != this->listaPatrones.end()) and noEncontrado ){
		if ( patron.getPalabra() == it->getPalabra() )
			noEncontrado = false;
		it++;
	}
	return noEncontrado;
}

void Kasiski::listarPatrones(){

	cout << endl << "Lista de patrones encontrados: " << endl;

	list<Patron>::iterator patron = listaPatrones.begin();
	list<Patron>::iterator ultimoPatron = listaPatrones.end();

	while ( patron != ultimoPatron ){

		cout << patron->getPalabra() << " :";
		list<int>:: iterator it = patron->devolverDistancias();
		while ( patron->noEsUltimo(it) ){
			cout << " " << *it;
			it++;
		}
		cout << endl;

		patron++;
	}

	cout << endl;
}

void Kasiski::generarPatrones(string* textoCifrado){
	int cantidadCharsComun = 4;
	unsigned int posicion = 0;
	unsigned int posicionUltimaOcurrencia = posicion;
	unsigned int posicionDesde = cantidadCharsComun;
	string textoABuscar = "";
	string textoRestante = "";

	while ( posicion < (textoCifrado->length() - 2) ) {

//		cout << posicion << " de " << textoCifrado.length()-2 <<endl;

		posicionUltimaOcurrencia = posicion;
		textoABuscar = textoCifrado->substr(posicion,cantidadCharsComun);
		Patron patron(textoABuscar);

		if ( noExiste(patron) ) {
			posicionDesde = posicion+cantidadCharsComun;
			while (posicionDesde < textoCifrado->length()){
				posicionDesde = textoCifrado->find(textoABuscar,posicionDesde);
				if (posicionDesde != string::npos){

//					cout << "Se encontro coincidencia en posicion: " << posicionUltimaOcurrencia << endl;
//					cout << "ultima ocurrencia: " << posicionDesde << endl;
					int diferencia = posicionDesde - posicionUltimaOcurrencia;
					posicionUltimaOcurrencia = posicionDesde;
					posicionDesde += cantidadCharsComun;
					patron.agregarDistancia(diferencia);
				}
			}
			if (posicionUltimaOcurrencia != posicion){

//				cout << "se agrega un nuevo patron: " << patron.getPalabra() << endl;
				this->listaPatrones.push_back(patron);
			}
		}
		posicion++;

	}

}

void Kasiski::analisisDeFrecuencias(string textoCifrado){

	vector<AnalizadorDeFrecuencias*>	listaDeAnalizadores;

	for(int i = 0; i < mcd ; i++){
		AnalizadorDeFrecuencias* analizador = new AnalizadorDeFrecuencias(256);
		listaDeAnalizadores.push_back(analizador);
	}

	int size = textoCifrado.size();
	int j = 0;

	for(int i=0; i< size; i++){

		AnalizadorDeFrecuencias* analizador = listaDeAnalizadores.at(j);

		int posicion = (unsigned char) textoCifrado.at(i);
		analizador->incrementarFrecuencia( posicion );

		(j < (mcd-1) ) ? j++: j=0;
	}

	claveEncontrada ="";

	for( int i = 0; i < mcd ; i++ ){
		AnalizadorDeFrecuencias* analizador = listaDeAnalizadores.at(i);

//		analizador->mostrarListaDeFrecuencias();

		if ( analizador->existeSupremo() )
			claveEncontrada.push_back( (unsigned char) analizador->posicionMaximaFrecuencia() -32 );
	}

	for(int i = 0; i < mcd; i++)
		delete listaDeAnalizadores.at(i);

}

string Kasiski::romper(){
	return claveEncontrada;
}
