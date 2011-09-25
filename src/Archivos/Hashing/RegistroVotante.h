#ifndef REGISTROVOTANTE_H_
#define REGISTROVOTANTE_H_

#include "Registro.h"
#include "../../Entidades/Votante.h"
#include "HashingVotante.h"

using namespace std;

class RegistroVotante : public Registro {

public:

	RegistroVotante();

	int obtenerClave();

    Entidad* getContenido();


	string* serializar();
	void deserializar(string * source);


	virtual ~RegistroVotante();
};

#endif /* REGISTROVOTANTE_H_ */
