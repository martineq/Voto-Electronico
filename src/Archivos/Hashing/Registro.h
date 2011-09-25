
#ifndef REGISTRO_H_
#define REGISTRO_H_

#include "../../Entidades/Entidad.h"

class Registro : public Serializable {

protected:

	int			clave;
	Entidad* 	contenido;

	/*
	 * Realiza el cálculo para obtener la clave a partir del ID de la Entidad.
	 */
	void determinarClave();

public:

	/*
	 * Deserializa una tira de bytes sobre el actual objeto.
	 */
	virtual void deserializar(std::string* source) = 0;

	/*
	 * Agrega o sobreescribe el contenido del registro
	 */
	virtual void setContenido(Entidad* entidad) = 0;

	/*
	 * Obtiene el tamanio del registro luego de ser serializado.
	 */
	int getTamanio();

	/*
	 * Devuelve una clave obtenida tras aplicar una función de Hash al ID de la Entidad
	 */
	int obtenerClave();

	/*
	 * Devuelve el objeto serializado como un string
	 */
	std::string* serializar();

	/*
	 * Devuelve el contenido del registro, NULL si no lo tiene.
	 */
	Entidad* getContenido();

	virtual ~Registro();
};

#endif /* REGISTRO_H_ */
