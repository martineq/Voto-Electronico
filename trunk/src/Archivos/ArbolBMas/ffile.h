#pragma once
#include <vector>
#include <string>

using namespace std;

class ffile
{
public:
	ffile(void);
	~ffile(void);
	void openfile(string p){ this->path = p; return; };
	int getblocksize(){return this->blocksize; };
	void newfile(string p, int bs){this->path = p; this->blocksize=bs; };
	std::vector<char> getblock(int bn){ return this->v[bn]; };
	void setblock(std::vector<char> b,int bn){ this->v[bn]=b;};
	int newblock();
	void delblock(int bn){this->q.push_back(bn); return;};
private:
	std::vector<std::vector<char> > v;
	std::vector<int> q;
	string path;
	int blocksize;
};

