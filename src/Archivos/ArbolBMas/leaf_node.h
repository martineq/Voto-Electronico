#ifndef LEAF_NODE_H
#define	LEAF_NODE_H
#include <string>
#include <utility>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "inner_node.h"

using namespace std;

  
class leaf_node {
public:
	void initialization();
	friend class inner_node;
	int getsize();
	leaf_node & operator=(const leaf_node &rhs);
	void setnext(int n);
	std::pair<std::pair<vector<char>,std::string>,int> nextelem();
    void deserialize(std::vector<char> v);
    leaf_node();
    ~leaf_node();
    std::vector<char> serialize();
    char peek(vector<char> node);
    std::vector<char> search(string str);
	std::pair<inner_node,leaf_node> split_root(int maxsize, int rightblock, int leftblock);
	int del(string elem, int maxsize);
	int add(std::pair<vector<char>,std::string> newelem, int maxsize);
	int modify(std::pair<vector<char>,std::string> newelem, int maxsize);
	std::pair<leaf_node,std::pair<int,std::string> > split(int maxsize, int leftblock);
private:
	static int compare(std::pair<vector<char>, std::string> r,std::pair<vector<char>, std::string> l);
	int next;
    int currentpos;
	std::vector<std::pair<vector<char>,std::string> > l; 
};

#endif	/* LEAF_NODE_H */
