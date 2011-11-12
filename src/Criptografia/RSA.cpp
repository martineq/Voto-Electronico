/*
 * RSA.cpp
 *
 *  Created on: 10/11/2011
 *      Author: daniel
 */

#include "RSA.h"

RSA::RSA() {
	for (int i=0; i<6; i++) {
		this->fila1.push_back(0);
		this->fila2.push_back(0);
	}
}

RSA::~RSA() {
	// TODO Auto-generated destructor stub
}

long RSA::aBinario (long num){
	if (num < 2){
		return num;
	}
	else {
		return num%2 + ( 10 * aBinario (num/2));
	}
}

bool RSA::esPrimo(int numero){
	int resto;
	int nc=0;
	for(int c=1;c<=numero;c++)	{
		resto=numero%c;
		if(resto==0) nc++;
		if(nc>2) break;
	}
	if (nc==2) return true;
	else return false;
}

void RSA::generarPyQ() {
	cout << "Se van a generar p y q" << endl;
	srand (time(NULL));
	bool salir = false;
	int k = 1;
	while (!salir) {
		int numero = rand () % 50;
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
		int numero = rand () % 50;
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
			int Q = this->fila1[2]/this->fila1[5];
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
				for (int i=0;i<(int)this->fila2.size();i++)
					this->fila1[i]=this->fila2[i];
			}
		}
		if (this->e<=0) fin = false;
	}
	cout << "e = " << this->e << endl;
}

long RSA::encriptar(int dato){
	cout << "Se va a encriptar " << dato << endl;
	long eEnBinario = this->aBinario(this->e);
	stringstream ss;
	ss << eEnBinario;
	string eEnString = ss.str();
	int eEnEntero = atoi(&eEnString[0]);
	vector<int> numero;
	int fin = 0;
	while (fin < (int)eEnString.size()){
		numero.push_back(eEnEntero%10);
		eEnEntero/=10;
		fin++;
	}
	unsigned int cantidadDeIteraciones = numero.size();
	long anterior = dato % this->n;
	long suma=1;
	int j=0;
	if (numero[j]) suma=anterior%this->n;
	int i=1;
	j++;
	while (i < (int)cantidadDeIteraciones) {
		anterior = (anterior*anterior) % this->n;
		if (numero[j]) suma=(suma*anterior)%this->n;
		i++;
		j++;
	}
	cout << "Resultado de la encriptacion: " << suma << endl;
	return suma;
}

int RSA::desencriptar(long dato){
	cout << "Se va a desencriptar " << dato << endl;
	long dEnBinario = this->aBinario(this->d);
	stringstream ss;
	ss << dEnBinario;
	string dEnString = ss.str();
	int dEnEntero = atoi(&dEnString[0]);
	vector<int> numero;
	int fin = 0;
	while (fin < (int)dEnString.size()){
		numero.push_back(dEnEntero%10);
		dEnEntero/=10;
		fin++;
	}
	unsigned int cantidadDeIteraciones = numero.size();
	long anterior = dato % this->n;
	long suma=1;
	int j=0;
	if (numero[j]) suma=anterior%this->n;
	int i=1;
	j++;
	while (i < (int)cantidadDeIteraciones) {
		anterior = (anterior*anterior) % this->n;
		if (numero[j]) suma=(suma*anterior)%this->n;
		i++;
		j++;
	}
	cout << "Resultado de la desencriptacion: " << suma << endl;
	return suma;
}

void RSA::atacar(){

}
