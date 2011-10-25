/*
 * TestVotanteAleatorio.cpp
 *
 *  Created on: 17/10/2011
 *      Author: lÑ#$dsa44
 */

#include "TestVotanteAleatorio.h"

TestVotanteAleatorio::TestVotanteAleatorio() {

}
void TestVotanteAleatorio::pruebaBusquedaEnArchivoDeVotantes(){
	int dimensionBucket = 2048;
	char nombreDeArchivo[] = "votantesAleatorios.bin";
	char archivoConfiguracion[] = "conf.bin";
	HashingExtensible* he = new HashingExtensible(dimensionBucket,nombreDeArchivo,archivoConfiguracion);

	he->mostrarArchivoDeHash();

    Votante* votante = new Votante(28601463,"","","","");
    Registro* registro = new Registro(votante);
   	Registro* regObtenido = he->obtenerRegistro(registro);
   	if (regObtenido != NULL )
   		regObtenido->verContenido();

   	delete regObtenido;
   	delete registro;
   	delete votante;

	delete he;

}

void TestVotanteAleatorio::crearArchivoDeVotantes()
{
	int dimensionBucket = 2048;
	char nombreDeArchivo[] = "votantesAleatorios.bin";
	char archivoConfiguracion[] = "conf.bin";
	remove(nombreDeArchivo);
	remove(archivoConfiguracion);
	HashingExtensible* he = new HashingExtensible(dimensionBucket,nombreDeArchivo,archivoConfiguracion);

	 for (int i = 0; i < 1000; i++){
	        /*CreadorVotante * creador = new CreadorVotante(time(NULL) * (i+1));
	        Votante* votante = creador->crearVotante();
	        Registro* registro = new Registro(votante);
       		he->agregarRegistro(registro);
//        	he->mostrarArchivoDeHash();
	        votante->verVotante();
	        delete (registro);
	        delete (votante);
	        delete (creador);
*/	    }

	delete he;
}

TestVotanteAleatorio::~TestVotanteAleatorio() {
	// TODO Auto-generated destructor stub
}

