#ifndef REGISTROVOTANTE_H_
#define REGISTROVOTANTE_H_

#include "../Registro.h"
#include "../../../Entidades/Votante.h"

using namespace std;

class RegistroVotante : public Registro {

public:

	RegistroVotante();

	RegistroVotante(Entidad*);

	void setContenido(Entidad*);

    Entidad* getContenido();


	void deserializar(string * source);

	Registro* hidratar(std::string*);

	Registro* duplicar();

	virtual ~RegistroVotante();
};

#endif /* REGISTROVOTANTE_H_ */
