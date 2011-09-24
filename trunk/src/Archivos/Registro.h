#include <string>
#include "./Hashing/Bucket.h"
#include "../Entidades/Serializable.h"


using namespace std;

#ifndef REGISTRO_H_
#define REGISTRO_H_

class Registro : public Serializable {
private:
	string* bytes;

public:
	Registro();
	// ID es el identificador del registro del archivo
	// clave = hash(ID)
	// devuelve la clave
	virtual int obtenerClave(string* bytes) = 0;

	string* getBytes();

	void setBytes(string* bytes);

	virtual ~Registro();
};

#endif /* REGISTRO_H_ */
