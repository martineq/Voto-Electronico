/*
 * TestCriptografia.cpp
 *
 *  Created on: 12/11/2011
 *      Author: tincho
 */

#include "TestVigenere.h"
#include "../src/Criptografia/Kasiski.h"


TestVigenere::TestVigenere() {
	// TODO Auto-generated constructor stub

}

int TestVigenere::testCifrado(){

	string clave = "ABCD";

	Vigenere* vigenere = new Vigenere(clave);

	string mensaje = "Estoy haciendo una prueba de vigenere a ver que tal se comporta, saludos!";

	string* criptograma = vigenere->cifrar(&mensaje);

	string* mensajeDescifrado = vigenere->descifrar(criptograma);

	int resultado = mensajeDescifrado->compare(mensaje);

	if (resultado != 0)
		cout << "testVigenere.testCifrado: FALLO" << endl;

	delete criptograma;
	delete mensajeDescifrado;
	delete vigenere;

	return resultado;
}

int TestVigenere::testEnBloques(){

	string clave = "HZDIOP";

	Vigenere* vigenere = new Vigenere(clave);

	string m1 = "mensaje1 ";
	string m2 = "mensaje2 ";
	string m3 = "mensaje3 ";
	string m4 = "mensaje4";

	string* criptograma = new string();
	string* temp;

	temp = vigenere->cifrar(&m1);
	criptograma->append(*temp);
	delete temp;

	temp = vigenere->cifrar(&m2);
	criptograma->append(*temp);
	delete temp;

	temp = vigenere->cifrar(&m3);
	criptograma->append(*temp);
	delete temp;

	temp = vigenere->cifrar(&m4);
	criptograma->append(*temp);
	delete temp;

	string mensaje;
	mensaje.append(m1);
	mensaje.append(m2);
	mensaje.append(m3);
	mensaje.append(m4);

	string* mensajeDescifrado = vigenere->descifrar(criptograma);


	int resultado = mensajeDescifrado->compare(mensaje);

	if (resultado != 0)
		cout << "testVigenere.testEnBloques: FALLO" << endl;

	delete criptograma;
	delete mensajeDescifrado;
	delete vigenere;

	return resultado;
}


int TestVigenere::testCifradoCadenaLarga(){

	string clave = "ABCD";
	ManejadorDeArchivo* archivo = new ManejadorDeArchivo("SalidaCripto(Clave ABCD).txt");

	Vigenere* vigenere = new Vigenere(clave,256);

	string mensaje = "Primera Parte Capítulo Primero  Declaraciones derechos y garantías Art 1 La Nación Argentina adopta para su gobierno la forma representativa republicana federal según la establece la presente Constitución Art 2 El Gobierno federal sostiene el culto católico apostólico romano Art 3 Las autoridades que ejercen el Gobierno federal residen en la ciudad que se declare Capital de la República por una ley especial del Congreso previa cesión hecha por una o más legislaturas provinciales del territorio que haya de federalizarse Art 4 El Gobierno federal provee a los gastos de la Nación con los fondos del Tesoro nacional formado del producto de derechos deimportación y exportación del de la venta o locación de tierras de propiedad nacional de la renta de Correos de las demás contribuciones que equitativa y proporcionalmente a la población imponga el Congreso General y de los empréstitos y operaciones de crédito que decrete el mismo Congreso para urgencias de la Nación o para empresas de utilidad nacional Art 5 Cada provincia dictará para sí una Constitución bajo el sistema representativo republicano de acuerdo con los principios declaraciones y garantías de la Constitución Nacional y que asegure su administración de justicia su régimen municipal y la educación primaria Bajo de estas condiciones el Gobierno federal garante a cada provincia el goce y ejercicio de sus instituciones Art 6 El Gobierno federal interviene en el territorio de las provincias para garantir la forma republicana de gobierno o repeler invasiones exteriores y a requisición de sus autoridades constituidas para sostenerlas o restablecerlas si hubiesen sido depuestas por la sedición o por invasión de otra provincia Art 7 Los actos públicos y procedimientos judiciales de una provincia gozan de entera fe en las demás y el Congreso puede por leyes generales determinar cuál será la forma probatoria de estos actos y procedimientos y los efectos legales que producirán Art 8 Los ciudadanos de cada provincia gozan de todos los derechos privilegios e inmunidades inherentes al título de ciudadano en las demás La extradición de los criminales es de obligación recíproca entre todas las provincias Art 9 En todo el territorio de la Nación no habrá más aduanas que las nacionales en las cuales regirán las tarifas que sancione el Congreso Art 10 En el interior de la República es libre de derechos la circulación de los efectos de producción o fabricación nacional así como la de los géneros y mercancías de todas clases despachadas en las aduanas exteriores Art 11 Los artículos de producción o fabricación nacional o extranjera así como los ganados de toda especie que pasen por territorio de una provincia a otra serán libres de los derechos llamados de tránsito siéndolo también los carruajes buques o bestias en que se transporten y ningún otro derecho podrá imponérseles en adelante cualquiera que sea su denominación por el hecho de transitar el territorio Art 12 Los buques destinados de una provincia a otra no serán obligados a entrar anclar y pagar derechos por causa de tránsito sin que en ningún caso puedan concederse preferencias a un puerto respecto de otro por medio de leyes o reglamentos de comercio Art 13 Podrán admitirse nuevas provincias en la Nación pero no podrá erigirse una provincia en el territorio de otra u otras ni de varias formarse una sola sin el consentimiento de la Legislatura de las provincias interesadas y del Congreso Art 14 Todos los habitantes de la Nación gozan de los siguientes derechos conforme a las leyes que reglamenten su ejercicio a saber de trabajar y ejercer toda industria lícita de navegar y comerciar de peticionar a las autoridades de entrar permanecer transitar y salir del territorio argentino de publicar sus ideas por la prensa sin censura previa de usar y disponer de su propiedad de asociarse con fines útiles de profesar libremente su culto de enseñar y aprender Art 14 bis El trabajo en sus diversas formas gozará de la protección de las leyes las que asegurarán al trabajador condiciones dignas y equitativas de labor jornada limitada descanso y vacaciones pagados retribución justa salario mínimo vital móvil igual remuneración por igual tarea participación en las ganancias de las empresas con control de la producción y colaboración en la dirección protección contra el despido arbitrario estabilidad del empleado público organización sindical libre y democrática reconocida por la simple inscripción en un registro especial Queda garantizado a los gremios concertar convenios colectivos de trabajo recurrir a la conciliación y al arbitraje el derecho de huelga Los representantes gremiales gozarán de las garantías necesarias para el cumplimiento de su gestión sindical y las relacionadas con la estabilidad de su empleo El Estado otorgará los beneficios de la seguridad social que tendrá carácter de integral e irrenunciable En especial la ley establecerá el seguro social obligatorio que estará a cargo de entidades nacionales o provinciales con autonomía financiera y económica administradas por los interesados con participación del Estado sin que pueda existir superposición de aportes jubilaciones y pensiones móviles la protección integral de la familia la defensa del bien de familia la compensación económica familiar y el acceso a una vivienda digna Art 15 En la Nación Argentina no hay esclavos los pocos que hoy existen quedan libres desde la jura de esta Constitución y una ley especial reglará las indemnizaciones a que dé lugar esta declaración Todo contrato de compra";

//	cout << "Mensaje plano: "<< mensaje<<endl;
	string* criptograma = vigenere->cifrar(&mensaje);

	// Salida a archivo
	char* buf = new char[criptograma->size()];
	strcpy(buf,criptograma->c_str());
	archivo->escribir(buf,criptograma->size());
	delete[] buf;
	archivo->guardarBuffer();
	delete archivo;

	Kasiski ka;
	string key;
	key = ka.getkey(*criptograma);
	cout <<"Key: "<<key<<endl;

//	cout <<"Encriptado: "<< *criptograma<<endl;
	string* mensajeDescifrado = vigenere->descifrar(criptograma);
//	cout <<"DESEncriptado: "<< * mensajeDescifrado<<endl;
	int resultado = mensajeDescifrado->compare(mensaje);

	if (resultado != 0)
		cout << "testVigenere.testCifrado: FALLO" << endl;

	delete criptograma;
	delete mensajeDescifrado;
	delete vigenere;

	return resultado;
}



TestVigenere::~TestVigenere() {
	// TODO Auto-generated destructor stub
}

