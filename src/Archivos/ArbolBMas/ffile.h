#pragma once
#include <vector>
#include <string>

using namespace std;

class ffile
{
public:
	ffile();
	~ffile();
	int newblock();

	void openfile(string p);
	int getblocksize();
	void newfile(string p, int bs);
	std::vector<char> getblock(int bn);
	void setblock(std::vector<char> b,int bn);
	void delblock(int bn);

private:
	string path;
	int blocksize;
	std::vector<std::vector<char> > v;
	std::vector<int> q;

};

