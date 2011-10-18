#include "ffile.h"


ffile::ffile(void)
{
	return;
}


ffile::~ffile(void)
{
	return;
}

int ffile::newblock()
{
	int retval;
		std::vector<char> tmp;
		if(q.size()==0){
			this->v.push_back(tmp);
			return this->v.size()-1; 
		};
		retval = this->q.back();
		this->q.pop_back();
		return retval;
}

