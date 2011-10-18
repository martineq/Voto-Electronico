#pragma once
#include <list>
#include <string.h>
#include <utility>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "leaf_node.h"


using namespace std;


class inner_node {
public:
	void initialization();
	int getsize();
	friend class leaf_node;
	inner_node & operator=(const inner_node &rhs);
    void deserialize(std::vector<char> v);
    inner_node();
    ~inner_node();
    std::vector<char> serialize();
    char peek(vector<char> node);
    std::pair<inner_node, inner_node> split_root(int maxsize, int rightblock, int leftblock);
	std::pair<inner_node, std::pair<int, std::string> > split(int block);
    int search(string str);
	int add(std::pair<int, std::string> newelem, int maxsize);
	int del(string elem, int maxsize);
	std::pair<inner_node,std::pair<int,std::string> > split(int maxsize, int leftblock);
private:
    static int compare(std::pair<int, std::string> l, std::pair<int, std::string> r);
    int prev;    
    std::vector<std::pair<int,std::string> > l;
   
};


