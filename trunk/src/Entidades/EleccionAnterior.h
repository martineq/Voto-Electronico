#ifndef ELECCIONANTERIOR_H_
#define ELECCIONANTERIOR_H_

#include <iterator>
#include <string>
using namespace std;

class EleccionAnterior {
private:
	string fecha;
	string cargo;
public:
	EleccionAnterior(string fecha, string cargo);
	EleccionAnterior();
	string getFecha ();
	string getCargo ();
	virtual ~EleccionAnterior();
};

#endif /* ELECCIONANTERIOR_H_ */
