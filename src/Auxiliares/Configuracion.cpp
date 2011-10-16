/*
 * Configuracion.cpp
 *
 *  Created on: 15/10/2011
 *      Author: mart
 */

#include "Configuracion.h"

Configuracion::Configuracion(int argc, const char** argv ){
	this->cargarArgumentos(argc,argv);
	this->cargarchivoConfig();
}

// Opciones por ahora: '-a', '-m', '-c path'
void Configuracion::cargarArgumentos(int argc, const char** argv){
	this->vAuto = false;
	this->vManual = false;
	this->rutaConfig = "";

	int index,c;
    opterr = 0;
    cout <<"optind: " << optind<<endl;
    while ((c = getopt (argc, (char* const*)argv, "amc:")) != -1)
    	switch (c){
    	case 'a':
    		this->vAuto = true;
    		break;
        case 'm':
        	this->vManual = true;
        	break;
        case 'c':
			this->rutaConfig = optarg;
			break;
        case '?':
          if (optopt == 'c')
            fprintf (stderr, "La opción -%c requiere un argumento.\n",optopt);
          else if (isprint (optopt))
            fprintf (stderr, "Opción desconocida `-%c'.\n", optopt);
          else
            fprintf (stderr,"Caracter de opción desconocida `\\x%x'.\n",optopt);
        default:
        	exit(1);
        }
    for (index = optind; index < argc; index++)
      printf ("Argumento inválido %s\n", argv[index]);
    if(this->rutaConfig == ""){
    	cerr << "Falta la ruta de archivo de configuración. Programa terminado."<<endl;
    	exit(1);
    }
}


void Configuracion::cargarchivoConfig(){
	char chr1='\0';
	char chr2='\0';
	vector<string> v;
	ManejadorDeArchivo man(this->rutaConfig);

	// Salteo el texto hasta llegar a detectar una doble barra "//" o llegar al EOF
	while ( (chr1!='/') && (chr2!='/') && (man.fin()!= true) ){
		man.leer(&chr1,1);
		man.leer(&chr2,1);
	}

	// Si no se acabó el archivo comienzo el parseo
	while(man.fin()!= true){
		man.leer(&chr1,1);
		if ( (chr1 == '-') || (chr1 == '+') ){ // El '-' indica que viene un argumento, el '+' indica un valor
			string cad("");
			if (chr1 == '-') cad += "-";
			man.leer(&chr1,1);
			while( (chr1 != ' ') && (man.fin()!= true) ){
				cad += chr1;
				man.leer(&chr1,1);
			}
			v.push_back(cad);
		}
	}
	// Acá ya tengo lleno el vector de strings, ahora lo paso al argc y argv
	int argc = v.size();
	int i;
	char** argv = new char*[argc+1];// El "+1" es para no usar el [0]
	argv[0] = new char[(this->rutaConfig).size()+1]();
	strcpy (argv[0], (this->rutaConfig).c_str() );
	for(i=0; i<argc ; i++ ){
		string dato (v[i]);
		int size = dato.size();
		argv[i+1] = new char[size+1](); // El "+1" es por el caracter de fin de string al hacer strcpy
		strcpy (argv[i+1], dato.c_str());
	}
	cout << "argc: " <<argc << endl;
	for(i=0; i<=argc ; i++ ){ cout<<"|" << argv[i]<<"|" << endl; }
	cout << "argc: " <<argc << endl;

	// Ahora cargo los parámetros que se obtuvieron del archivo de configuración
	this->rutaArbol = "";
	this->rutaHash = "";
	int index,c;
    opterr = 0;
    optind = 1; // Inicalo la variable para poder usar el getopt otra vez
    while ((c = getopt (argc, (char* const*)argv, "T:H:")) != -1)
    	switch (c){
    	case 'H':
    		this->rutaHash = optarg;
    		break;
        case 'T':
        	this->rutaArbol = optarg;
        	break;
        case '?':
          if (optopt == 'c')fprintf (stderr, "La opción -%c requiere un argumento.\n",optopt);
          else if (isprint (optopt))
            fprintf (stderr, "Opción desconocida `-%c'.\n", optopt);
          else
            fprintf (stderr,"Caracter de opción desconocida `\\x%x'.\n",optopt);
        default:
        	cerr << "El archivo de cofiguración tiene opciones inválidas"<<endl;
        }

    cout << "Rutas: "<<(this->rutaArbol)<<", " << (this->rutaHash) <<endl;

    for (index = optind; index < argc; index++)
      printf ("Opción de configuración inválida %s\n", argv[index]);

    if( (this->rutaArbol == "") || (this->rutaHash == "") ){
    	cerr << "Falta la ruta de archivo de Árbol y/o Hash. Programa terminado."<<endl;
    	exit(1);
    }



	// Libero la memoria que yo instancié
	for(i=0; i<=(int)v.size() ; i++ ){ delete[] argv[i]; }
	delete[] argv;
}


string Configuracion::pathArbol(){
	return this->rutaArbol;
}

string Configuracion::pathHash(){
	return this->rutaHash;
}

bool Configuracion::isAuto(){
	return this->vAuto;
}

bool Configuracion::isManual(){
	return this->vManual;
}

Configuracion::~Configuracion() {

}
