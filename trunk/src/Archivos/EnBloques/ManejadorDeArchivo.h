
#ifndef MANEJADORDEARCHIVO_H_
#define MANEJADORDEARCHIVO_H_

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
        void posicionarse(ios::pos_type pos);
        void posicionarseEnFin();
        void guardarBuffer();
        bool fin();
        ios::pos_type obtenerPosicionDeLectura();
        ios::pos_type obtenerTamArchivo();
        string obtenerNombreArchivo();
        string obtenerNombreArchivoTmp();
        void renombrar(string nombreNuevo);
        void borrar();


};

#endif /* MANEJADORDEARCHIVO_H_ */
