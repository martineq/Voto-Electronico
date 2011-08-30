#include <iostream>

using namespace std;

int main(int argc,char* argv[])
{
    int i;

    cout<<"||TP 1||\n--------\n\nHola Mundo!!!\n";

    for (i=0;i<argc;i++){
        cout<<"\nParámetro ["<<i<<"]: "<<argv[i];
    }

    cout<<"\n\nBueno, chau...\n";

    return 0;
}
