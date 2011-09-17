/*
 * Distrito.h
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
	string distrito;

public:
	Distrito();
	Distrito(string distrito);

	string getDistrito();

	void setDistrito(string distrito);

	~Distrito();

};

#endif /* DISTRITO_H_ */

