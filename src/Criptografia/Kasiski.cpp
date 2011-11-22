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
	std::vector<int> tmpvcoin; //store the coincidences of each pass
    unsigned int coin; //store current coincicences
	vector<int>::iterator pos;

//    cout << "getkeylen"<<endl;
	int len = 0;
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

	tmpvcoin=vcoin;
	pos=max_element(tmpvcoin.begin(),tmpvcoin.end());
	coin = *pos;

	int mpos=0;
	int ampos=0;

	for(unsigned int i=0;i<vcoin.size();i++)
		if(vcoin[i]==coin)
			mpos=i;

	tmpvcoin.erase(pos);
	pos=max_element(tmpvcoin.begin(),tmpvcoin.end());

	for(unsigned int i=0;i<vcoin.size();i++)
		if(vcoin[i]==coin)
			ampos=i;

	return mcd(mpos,ampos);

    //cout << "*vcoin.end(): "<<*vcoin.end()<<endl;
    //cout << "*vcoin.begin(): "<<*vcoin.begin()<<endl;

	/*int index=2;
	int retval = mcd(vcoin[vcoin.size()-1],vcoin[vcoin.size()-index]);
	while(retval==1)
	{
		retval=mcd(vcoin[vcoin.size()-1],vcoin[vcoin.size()-index]);
		index++;
		if(index == vcoin.size()-1)
			return 0;
	}
	return retval;*/
}


int Kasiski::compare(std::pair<char, int> l, std::pair<char, int> r)
{
        return l.second < r.second;
}

int Kasiski::mcd(int a, int b)
{
        if (a <= 0 || b <= 0)
            return -1;
        while (a != b)
            if (a < b)
                b-= a;
            else
                a=a - b;
        return a;
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
         tmphist.clear();

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
	{
        sort(tmphisto[i].begin(),tmphisto[i].end(), this->compare);
		reverse(tmphisto[i].begin(),tmphisto[i].end());
	}

    for(unsigned int j=0;j<tmphisto.size();j++)
    {
        int found=0;
        while(!found)
        {
            if (tmphisto[j].size()==245) // more than this guesses is pointless
            {
                                r.clear();
                return r;
            }
            char fplace=tmphisto[j].at(1).first;
            char splace=tmphisto[j].at(2).first;
            char tplace=tmphisto[j].at(3).first;
            //cout <<"Primero: "<<(short int)fplace<<endl;
            //cout <<"Segundo: "<<(short int)splace<<endl;
            //cout <<"Tercero: "<<(short int)tplace<<endl;

            if((fplace+4)%27==splace ||(fplace+4)%27==tplace)
            {
                if((fplace+15)%27==splace ||(fplace+15)%27==tplace)
                {
                    r.push_back(fplace);
                    found=1;
                }
            }

            tmphisto[j].erase(tmphisto[j].begin());
        }

        //here i have to make each frequency analysis
        found=0;
    }
    return r;
}
