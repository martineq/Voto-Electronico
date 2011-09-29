
#ifndef REGISTRO_H_
#define REGISTRO_H_

#include "../../Entidades/Entidad.h"
#include "FabricaDeEntidades.h"

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
	 * Instancia un registro.
	 */
	Registro();

	/*
	 * Crea un registro asignándole la entidad pasada por parámetro.
	 */
	Registro(Entidad* nombreDeEntidad);

	/*
	 * Crea un registro con una instancia de una entidad particular.
	 */
	Registro(NombreDeEntidad nombreDeEntidad);

	/*
	 * Deserializa una tira de bytes sobre el actual objeto.
	 */
	void deserializar(std::string* source);

	/*
	 * Agrega o sobreescribe el contenido del registro
	 */
	void setContenido(Entidad* entidad);

	/*
	 * Instancia una de si mismo.
	 */
	Registro* duplicar();

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

	~Registro();
};

#endif /* REGISTRO_H_ */
