#include <iostream>

using namespace std;

int main(int argc,char* argv[])
{
    int i;

    cout<<"Hola Mundo!!!\n";

    for (i=0;i<argc;i++){  // El argv[0] es la ruta del binario.
        cout<<"\nParámetro ["<<i<<"]: "<<argv[i];
    }

    cout<<"\n\nBueno, chau...\n";

    return 0;
}
