#pragma once
#include <vector>
#include <string>
#include "leaf_node.h"
#include "inner_node.h"
#include "ffile.h"
using namespace std;

class bplustree
{
public:
	bplustree(void);
	~bplustree(void);
	void initialize();
	void newtree(string p, int bs); //bs is the blocksize, p is the path to the data of the new tree
	void opentree(string p, int bs); //bs is the blocksize, p is the path to the data of the new tree
	int add(string key, vector<char> data);
	int modify(string key, vector<char> data);
	int del(string);
	vector<char> search(string key);
	int getrootblock(){return (this->bs); }; //i need this to be deterministic from the backend
	std::pair<vector<char>,std::string> getnext();
private:
	void clear(){leaf_node l; this->n=l; };
	ffile* f;
	vector<int> q;
	leaf_node n; //for the last search, its used in the nextnode logic
	int bs;
};

