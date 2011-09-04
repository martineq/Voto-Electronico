#include <iostream>

using namespace std;

int main(int argc,char* argv[])
{
    int i;

    cout<<"||TP 1||\n--------\n\nHola Mundo!!!\n";

    cout<<"Si les llegó este commit al mail es porque lo configuré bien.\n";

    cout << "Daniel Shlufman padron 88040 - Saludos!" << endl;

    cout << "Martín Eduardo Quiroz padron 86012 - Saludos!" << endl;


    for (i=0;i<argc;i++){
        cout<<"\nParámetro ["<<i<<"]: "<<argv[i];
    }

    cout<<"\n\nBueno, chau...\n";

    return 0;
}
