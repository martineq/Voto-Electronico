
#ifndef MANEJADORDEARCHIVOS_H_
#define MANEJADORDEARCHIVOS_H_

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class ManejadorDeArchivo{

    private:
        fstream archivo;
        string nombre;

    public:
        ManejadorDeArchivo();
        virtual ~ManejadorDeArchivo();

        void abrir(string nombre);
        void cerrar();
        void leer(char* registro, size_t cantBytes);
        void escribir(const char* registro, size_t cantBytes);
        void posicionarse(ios::pos_type posicion);
        void posicionarseEnFin();
        void sincroBuffer();
        bool fin();
        string obtenerNombreArchivo();
        string obtenerNombreArchivoTmp();
        void renombrar(string nombreNuevo);
        void borrar();

        // Ver si se van a usar
        ios::pos_type obtenerPosicionDeLectura();
        ios::pos_type obtenerTamArchivo();

};

#endif /* MANEJADORDEARCHIVOS_H_ */
