/*
 * RSA.cpp
 *
 *  Created on: 10/11/2011
 *      Author: daniel
 */

#include "RSA.h"

RSA::RSA(bool inicializar) {

	if (inicializar) {
//		cout << "CONSTRUCTOR RSA" << endl;
		for (int i=0; i<6; i++) {
			this->fila1.push_back(0);
			this->fila2.push_back(0);
		}
		this->generarPyQ();
		this->calcularN();
		this->calcularPhi();
		this->calcularE();
	}
}

RSA::RSA(long z, long n, bool encriptar) {
	this->n = n;
	if (encriptar){
		this->e = z;
	}
	else{
		this->d = z;
	}
}


RSA::~RSA() {
//	cout << "destructor rsa" << endl;
	// TODO Auto-generated destructor stub
}

RSA* RSA::duplicar(){
	RSA* unRSA = new RSA();
	unRSA->d = this->d;
	unRSA->e = this->e;
	unRSA->p = this->p;
	unRSA->q = this->q;
	unRSA->phi = this->phi;
	unRSA->n = this->n;

	for (int i=0; i<6; i++) {
		unRSA->fila1.push_back(0);
		unRSA->fila2.push_back(0);
	}
	return unRSA;
}

void RSA::generarListaDePrimos(){
	int indice = 2;
	primos.push_back(indice);

	for(int j = ++indice; j < 100; j=j+2){

		list<int>::iterator it = primos.begin();
		bool primo = true;

		while ( (it != primos.end()) && primo){
			if ( (j % (*it)) == 0 )
				primo = false;
			it++;
		}

		if ( primo )
			primos.push_back(j);

	}


	//	list<int>::iterator it = primos.begin();
	//	while ( it != primos.end()){
	//		cout << *it << " ";
	//		it++;
	//	}
}


long long RSA::aBinario (long long num){
	if (num < 2){
		return num;
	}
	else {
		return num%2 + ( 10 * aBinario (num/2));
	}
}

bool RSA::esPrimo(long long numero){
	long long resto;
	int nc=0;
	for(int c=1;c<=(int) numero;c++)	{
		resto=numero%c;
		if(resto==0) nc++;
		if(nc>2) break;
	}
	if (nc==2) return true;
	else return false;
}

void RSA::setN (long long n){
	this->n=n;
}
void RSA::setE (long long e){
	this->e=e;
}
void RSA::setD (long long d){
	this->d=d;
}

void RSA::generarPyQ() {
	cout << "Se van a generar p y q" << endl;
	srand (time(NULL));
	bool salir = false;
	int k = 1;
	while (!salir) {
		long long numero = rand () % 100;
		if (numero>3){
			if (esPrimo(numero)){
				if (k==1) {
					this->p=numero;
					k++;
				}
				else {
					if (p!=numero) {
						this->q=numero;
						salir = true;
					}
				}
			}
		}
	}
	//	PARA PRUEBA
	//	this->p=19;
	//	this->q=7;
	//	============
	cout << "P= " << this->p << endl;
	cout << "Q= " << this->q << endl;
}

void RSA::calcularN(){
	cout << "Se va a calcular n" << endl;
	this->n=p*q;
	cout << "n= " << this->n << endl;
}

void RSA::calcularPhi(){
	cout << "Se va a calcular phi" << endl;
	this->phi=(p-1)*(q-1);
	cout << "PHI= " << this->phi << endl;
}

void RSA::elegirD(){
	cout << "Se va a calcular d" << endl;
	bool fin = false;
	while (!fin){
		long long  numero = rand () % 100;
		if (numero>3){
			if (esPrimo(numero)){
				if ((numero!=this->p) && (numero!=this->q) && (numero<this->phi)) {
					this->d=numero;
					fin = true;
				}
			}
		}
	}
	//	PARA PRUEBA
	//	this->d=73;
	//	===========
	this->fila1[0]=1;
	this->fila1[1]=0;
	this->fila1[2]=this->phi;
	this->fila1[3]=0;
	this->fila1[4]=1;
	this->fila1[5]=this->d;
	cout << "d= " << this->d << endl;
}

void RSA::calcularE() {
	cout << "Se va a calcular e " << endl;
	bool fin = false;
	while (!fin){
		this->elegirD();
		while (!fin){
			long long Q = this->fila1[2]/this->fila1[5];
			this->fila2[0]=this->fila1[3];
			this->fila2[1]=this->fila1[4];
			this->fila2[2]=this->fila1[5];
			this->fila2[3]=this->fila1[0]-Q*this->fila1[3];
			this->fila2[4]=this->fila1[1]-Q*this->fila1[4];
			this->fila2[5]=this->fila1[2]-Q*this->fila1[5];
			if (this->fila2[5]==1) {
				this->e=this->fila2[4];
				fin = true;
			}
			else {
				if (this->fila2[5]==0) {
					fin=true;
					this->e=0;
				}
				else {
					for (int i=0;i<(int)this->fila2.size();i++)
						this->fila1[i]=this->fila2[i];
				}
			}
		}
		if (this->e<=0) fin = false;
	}
	cout << "e = " << this->e << endl;
}

long long RSA::encriptar(int dato){
//	cout << "Se va a encriptar " << dato << endl;
//	cout << "this->e= " << this->e << endl;
	long long eEnBinario = this->aBinario(this->e);
//	cout << this->e << " en binario= " << eEnBinario << endl;
	stringstream ss;
	ss << eEnBinario;
	string eEnString = ss.str();
	long long eEnEntero = atol(&eEnString[0]);
	vector<long long> numero;
	long long fin = 0;
	while (fin < (long long)eEnString.size()){
		numero.push_back(eEnEntero%10);
		eEnEntero/=10;
		fin++;
	}
	long long cantidadDeIteraciones = numero.size();
	long long anterior = dato % this->n;
	long long suma=1;
	long long j=0;
	if (numero[j]) suma=anterior%this->n;
	int i=1;
	j++;
	while (i < (long long)cantidadDeIteraciones) {
		anterior = (anterior*anterior) % this->n;
		if (numero[j]) suma=(suma*anterior)%this->n;
		i++;
		j++;
	}
//	cout << "Resultado de la encriptacion: " << suma << endl;
	return suma;
}

string RSA::encriptar(string mensaje){
	int size = mensaje.size();
	stringstream textoCifrado;

	textoCifrado.write((char*)&size,sizeof(int));
	for(int i = 0 ; i < size ; i++){
		int numero = (int) mensaje.at(i);
		long long resultado = this->encriptar( numero );
		textoCifrado.write((char*)&resultado,sizeof(long long));
	}
	return textoCifrado.str();
}


long long RSA::getN(){
	return this->n;
}

long long RSA::getE(){
	return this->e;
}

long long RSA::getD(){
	return this->d;
}

void RSA::setP (long long p) {
	this->p=p;
}

void RSA::setQ (long long q) {
	this->q=q;
}

string RSA::desencriptar(string mensajeCifrado){
	stringstream criptograma;
	criptograma << mensajeCifrado;
	string mensajeDesencriptado;
	int sizeDesencriptado;
	criptograma.read((char*)&sizeDesencriptado,sizeof(int));
	for (int j = 0; j < sizeDesencriptado; j++){
		long long dato;
		criptograma.read((char*)&dato,sizeof(long long));
		mensajeDesencriptado.push_back( this->desencriptar(dato) );
	}
	return mensajeDesencriptado;
}

int RSA::desencriptar(long long dato){
//	cout << "Se va a desencriptar " << dato << endl;
	long dEnBinario = this->aBinario(this->d);
	stringstream ss;
	ss << dEnBinario;
	string dEnString = ss.str();
	long long dEnEntero = atol(&dEnString[0]);
	vector<long long> numero;
	long long fin = 0;
	while (fin < (long long)dEnString.size()){
		numero.push_back(dEnEntero%10);
		dEnEntero/=10;
		fin++;
	}
	long long cantidadDeIteraciones = numero.size();
	long long anterior = dato % this->n;
	long long suma=1;
	long long j=0;
	if (numero[j]) suma=anterior%this->n;
	int i=1;
	j++;
	while (i < (int)cantidadDeIteraciones) {
		anterior = (anterior*anterior) % this->n;
		if (numero[j]) suma=(suma*anterior)%this->n;
		i++;
		j++;
	}
//	cout << "Resultado de la desencriptacion: " << suma << endl;
	return suma;
}

void RSA::atacar(){
	long long pAtacado, qAtacado;
	this->generarListaDePrimos();
	list<int>::iterator it1 = primos.begin();
	list<int>::iterator it2 = primos.begin();
	it2++;
	bool fin = false;
	while ((!fin) && (it1!= primos.end())){
		while (it2!= primos.end() && (!fin)){
			long long supuestoN= *it1*(*it2);
			if (supuestoN==this->n){
				pAtacado=*it1;
				qAtacado=*it2;
				fin=true;
			}
			else it2++;
		}
		if (!fin) {
			it1++;
			it2=it1;
			it2++;
		}
	}
	cout << "ATACADO" << endl;
	cout << "El p es= " << pAtacado << endl;
	cout << "El q es= " << qAtacado << endl;
	RSA* unRSA = new RSA(true);
	unRSA->setP(pAtacado);
	unRSA->setQ(qAtacado);
	unRSA->calcularN();
	unRSA->calcularPhi();
	unRSA->calcularE();
	delete unRSA;
	cout << "Con estos datos puede crearse el archivo clavePrivada.txt y vulnerarse la seguridad" << endl;
}
