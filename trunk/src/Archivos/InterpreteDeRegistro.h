#include <string>
#include "./Hashing/Bucket.h"
#include "../Entidades/Serializable.h"


using namespace std;

#ifndef INTERPRETEDEREGISTRO_H_
#define INTERPRETEDEREGISTRO_H_

class InterpreteDeRegistro  {
private:
	string* bytes;

public:
	InterpreteDeRegistro();
	// ID es el identificador del registro del archivo
	// clave = hash(ID)
	// devuelve la clave
	virtual int obtenerClave(string* bytes) = 0;

	string* getBytes();

	void setBytes(string* bytes);


	virtual ~InterpreteDeRegistro();
};

#endif /* INTERPRETEDEREGISTRO_H_ */
