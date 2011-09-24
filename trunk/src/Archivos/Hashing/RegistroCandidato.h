#ifndef REGISTROCANDIDATO_H_
#define REGISTROCANDIDATO_H_

#include "../Registro.h"
#include "../../Entidades/Candidato.h"

using namespace std;

class RegistroCandidato : public Registro {

public:

	RegistroCandidato();

	int obtenerClave();

    Candidato* getContenido();


	string* serializar();
	void deserializar(string * source);


	virtual ~RegistroCandidato();
};

#endif /* REGISTROCANDIDATO_H_ */
