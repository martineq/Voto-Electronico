#ifndef VIGENERE_H_
#define VIGENERE_H_

#include <string>

using std::string;

class Vigenere{

private:
	// Almacena internamente la clave empleada para la encriptación y desencriptación.
	string		clave;

	// Contiene el tamaño del alfabeto empleado.
	int			cardinalAlfabeto;

	// Mantiene la última posición empleada de la clave por el cifrador.
	int			posicionCifrador;

	// Mantiene la última posición traducida de la clave por el descifrador.
	int			posicionDescifrador;

public:

	/*
	 * Instancia un objeto cifrador, el tamaño del alfabeto está implícito
	 * y se asume resulta ser de 256.
	 */
	Vigenere(string clave);

	/*
	 * Intancia un objeto cifrador, el tamaño del alfabeto se define mediante
	 * cardinalAlfabeto.
	 */
	Vigenere(string clave,int cardinalAlfabeto);

	/*
	 * Cifra un mensaje obteniendo y devuelve un criptograma.
	 *
	 * Si no se está haciendo un cifrado en bloques entonces hay que invocar
	 * al método reiniciarCifrador previamente, excepto en el primer uso.
	 *
	 * El método reserva un string en memoria por lo que debe ser liberado luego
	 * de ser empleado.
	 */
	string* cifrar(string* mensaje);

	/*
	 * Descifra un criptograma, devolviendo el mensaje original.
	 *
	 * Si no se está haciendo un descifrado en bloques entonces hay que invocar
	 * al método reiniciarDescifrador previamente, excepto en el primer uso.
	 *
	 * El método reserva un string en memoria por lo que debe ser liberado luego
	 * de ser empleado.
	 */
	string* descifrar(string* criptograma);

	/*
	 * Para el manejo en bloques el método tiene un contador interno de la
	 * última posición leída, si se quiere encriptar un nuevo mensaje debe
	 * reiniciarse dicho contador.
	 */
	void reiniciarCifrador();

	/*
	 * Para el manejo en bloques el método tiene un contador interno de la
	 * última posición leída, si se quiere desencriptar un nuevo mensaje debe
	 * reiniciarse dicho contador.
	 */
	void reiniciarDescifrador();

	~Vigenere();

};

#endif /* VIGENERE_H_*/
