#ifndef REGISTRODEPRUEBA_H_
#define REGISTRODEPRUEBA_H_

#include "../Archivos/Hashing/Registro.h"
#include "../Entidades/Distrito.h"

class RegistroDePrueba: public Registro {
public:

	RegistroDePrueba(Entidad* entidad);

	int obtenerClave();

	Entidad* getContenido();

	std::string* serializar();

	void deserializar(std::string* source);

	~RegistroDePrueba();

};

#endif /* REGISTRODEPRUEBA_H_ */
