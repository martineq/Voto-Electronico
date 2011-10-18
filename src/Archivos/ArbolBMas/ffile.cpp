#include "ffile.h"


ffile::ffile(){

}


ffile::~ffile(){

}

int ffile::newblock(){
	int retval;
	std::vector<char> tmp;
	if(q.size()==0){
		this->v.push_back(tmp);
		return this->v.size()-1;
	}
	retval = this->q.back();
	this->q.pop_back();
	return retval;
}

int ffile::getblocksize(){
	return this->blocksize;
}


void ffile::setblock(std::vector<char> b, int bn){
	this->v[bn]=b;
}


void ffile::newfile(string p, int bs){
	this->path = p; this->blocksize=bs;
}


void ffile::delblock(int bn){
	this->q.push_back(bn);
}


std::vector<char> ffile::getblock(int bn){
	return this->v[bn];
}


void ffile::openfile(string p){
	this->path = p;
}
