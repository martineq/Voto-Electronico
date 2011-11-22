#ifndef KASISKI_H
#define	KASISKI_H

#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

class Kasiski {
public:
    Kasiski();
    Kasiski(const Kasiski& orig);
    virtual ~Kasiski();
    int getkeylen(std::string c);
    std::vector<std::vector<char> > ngram(std::string c, unsigned int keylen);
    std::vector<std::vector<std::pair<char,int> > > buildhisto(std::string c, unsigned int keylen);
    std::string getkey(std::string c);
private:
    static int compare(std::pair<char, int> l, std::pair<char, int> r);
	static int mcd(int a, int b);
};

#endif /* KASISKI_H_ */
