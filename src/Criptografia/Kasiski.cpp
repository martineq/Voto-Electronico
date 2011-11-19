
#include "Kasiski.h"

using namespace std;

Kasiski::Kasiski() {
}

Kasiski::Kasiski(const Kasiski& orig) {
}

Kasiski::~Kasiski() {
}



int Kasiski::getkeylen(std::string c)
{
    /*how it works:
     *basically, this will add an empty char at the begining of each pass to
     * the aux string, and traverse through the original string comparing it
     * to the same position of the aux string, if the number of coincidences
     * spikes, then we have the length of the key
     */
    std::vector<int> vcoin; //store the coincidences of each pass
    unsigned int coin; //store current coincicences
    cout << "getkeylen"<<endl;
    string aux=c;
//    cout << "c.size(): " << c.size()<<endl;
//    cout << "vcoin.size(): " << vcoin.size()<<endl;
//    cout << "AUX: " << aux<<endl;
    while(vcoin.size() < c.size()/2)
    {
    	const char empty = '\0';
       aux.insert(aux.begin(),empty);
//       cout << "vcoin.size(): " << vcoin.size()<<endl;
       coin=0;

       for(unsigned int i=vcoin.size();i<c.size();i++)
       {
            if(c[i]==aux[i])
                coin++;
       }
       vcoin.push_back(coin);
    }
    cout << "sort"<<endl;
    sort(vcoin.begin(),vcoin.end());
    cout << "*vcoin.end(): "<<*vcoin.end()<<endl;
    cout << "*vcoin.begin(): "<<*vcoin.begin()<<endl;
    return *vcoin.begin();
}


int Kasiski::compare(std::pair<char, int> l, std::pair<char, int> r)
{
        return l.first < r.first;
}


std::vector<std::vector<char> > Kasiski::ngram(std::string c, unsigned int keylen)
{
    /*how it works:
     *I need my ngrams to analyze, so i basically create a vector of char vectors
     * i initialize keylen of those and then i traverse c putting in each vector
     * the char that fits
     */
   std::vector<std::vector<char> > r;
   vector<char> v;

   for(unsigned int i=0;i<keylen;i++)
       r.push_back(v);


   for(unsigned int j=0;j<c.size();j++)
       r[j%keylen].push_back(c[j]);

   return r;
}

std::vector<std::vector<std::pair<char,int> > > Kasiski::buildhisto(std::string c, unsigned int keylen)
{
    /*how it works:
     *i basically take the ngrams, sort, count them and then add that a
     *vector of pairs, i sort the vector of pairs with occurrence as a key
     * and add them to my vector of vectors
     */
     std::vector<std::vector<char> > ngrm = this->ngram(c,keylen);
     std::vector<std::vector<std::pair<char,int> > > r;
     std::vector<std::pair<char,int> > tmphist;
     std::pair<char,int> tmppair;

     for(unsigned int i=0;i<keylen;i++)
     {
         tmphist.empty();

         for(int j=0;j<255;j++)
         {
             tmppair.first=j;
             tmppair.second=std::count(ngrm[i].begin(),ngrm[i].end(),j);
             tmphist.push_back(tmppair);
         }
         r.push_back(tmphist);
     }
     cout << "END of buildhisto"<<endl;
     return r;
}


std::string Kasiski::getkey(std::string c)
{
    int keylen=this->getkeylen(c);

    std::vector<std::vector<std::pair<char,int> > > histo = buildhisto(c,keylen);
    std::vector<std::vector<std::pair<char,int> > > tmphisto=histo;
    string r;

    for(unsigned int i=0;i<tmphisto.size();i++)
        sort(tmphisto[i].begin(),tmphisto[i].end(), this->compare);

    for(unsigned int j=0;j<tmphisto.size();j++)
    {
        int found=0;
        while(!found)
        {
            if (tmphisto[j].empty())
            {
				r.clear();
                return r;
            }
            char fplace=tmphisto[j].at(1).first;
            char splace=tmphisto[j].at(2).first;
            char tplace=tmphisto[j].at(3).first;
            cout <<"Primero: "<<(short int)fplace<<endl;
            cout <<"Segundo: "<<(short int)splace<<endl;
            cout <<"Tercero: "<<(short int)tplace<<endl;

            if((fplace+4)%27==splace ||(fplace+4)%27==tplace)
            {
                if((fplace+15)%27==splace ||(fplace+15)%27==tplace)
                {
                    r.push_back(fplace);
                    found=1;
                }
            }

            tmphisto.erase(tmphisto.begin());
        }

        //here i have to make each frequency analysis
        found=0;
    }
    return r;
}





///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
/*

Kasiski::Kasiski(string textoARomper) {
	this->textoCifrado = textoARomper;
	this->maximaLongitudPatron = 0;
}

int Kasiski::MCDDistancias(){
	list<Patron>::iterator it = this->listaPatrones.begin();
	int mcd = (*(it->devolverDistancias()));

	while (it != this->listaPatrones.end()){
		list<int>::iterator itInts = it->devolverDistancias();
		while (! it->esUltimo(itInts)){
			mcd = gcd(mcd,(*itInts));
			itInts++;
		}
		it++;
	}
	return mcd;
}

int Kasiski::gcd(int a, int b){
	if (b == 0) return a;
	return gcd(b, a%b);
}

bool Kasiski::noExiste(Patron patron){
	bool encontrado = false;
	list<Patron>::iterator it = this->listaPatrones.begin();
	while ((it != this->listaPatrones.end()) and (!encontrado)){
		if (patron.getPalabra() != it->getPalabra()){
			encontrado = true;
		}
	}
	return encontrado;
}

void Kasiski::listarPatrones(){
	int cantidadCharsComun = 3;
	unsigned int posicion = 0;
	unsigned int posicionUltimaOcurrencia = posicion;
	unsigned int posicionDesde = 3;
	string textoABuscar;
	string textoRestante;

	while (posicion < (this->textoCifrado.length() - 2)) {
		posicionUltimaOcurrencia = posicion;
		textoABuscar = this->textoCifrado.substr(posicion,cantidadCharsComun);
		Patron patron(textoABuscar);
		if (noExiste(patron)) {
			posicionDesde = posicion+cantidadCharsComun;
			while (posicionDesde < this->textoCifrado.length()){
				posicionDesde = this->textoCifrado.find(textoABuscar,posicionDesde);
				if (posicionDesde != string::npos){
					int diferencia = posicionDesde - posicionUltimaOcurrencia;
					posicionUltimaOcurrencia = posicionDesde;
					posicionDesde += cantidadCharsComun;
					patron.agregarDistancia(diferencia);
				}
			}
			if (posicionUltimaOcurrencia != posicion){
				this->listaPatrones.push_back(patron);
			}
		}
		posicion++;
	}
}

string Kasiski::romper(){
	this->listarPatrones();
	int mcd = this->MCDDistancias();
}
Kasiski::~Kasiski() {

}

*/
