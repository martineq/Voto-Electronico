#ifndef BUCKET_H_
#define BUCKET_H_

#include <list>
#include "../../Entidades/Serializable.h"
#include "Registro.h"


using namespace std;

class Bucket : public Serializable {

private:
	int espacioLibre;
	int tamanioDispersion;
	list<Registro*> listaRegistros;
	Registro* registro;


public:
	Bucket();
	Bucket(int dispersion, Registro* registro);
//devuelve el resultado de la operacion
	bool agregarRegistro(Registro* registro);
	int eliminarRegistro(int clave);
	int reemplazarRegistro(Registro* registro);
	Registro* getRegistro(int);
	int getEspacioLibre ();
	int getTamanioDeDispersion ();
	Registro* getInterprete();
	void  setTamanioDeDispersion (int clave);
	void setInterprete(Registro* interprete);
	string* ubicarPrimero();
	bool siguiente();
	Registro* getActual();
	string* serializar();
	void deserializar(string* source);

~Bucket();
};

#endif /* BUCKET_H_ */
