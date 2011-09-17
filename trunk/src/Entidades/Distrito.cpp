/*
 * Distrito.cpp
 *
 *  Created on: 17/09/2011
 *      Author: martin
 */

#include <string>

using namespace std;

#ifndef DISTRITO_H_
#define DISTRITO_H_

class Distrito {

private:
	string 	distrito;

public:
	Distrito();
	Distrito(string distrito){
		this->distrito = distrito;
	}

	string getDistrito(){
		return this->distrito;
	}

	void setDistrito(string distrito){
		this->distrito = distrito;
	}

	virtual ~Distrito();

};

#endif /* DISTRITO_H_ */
