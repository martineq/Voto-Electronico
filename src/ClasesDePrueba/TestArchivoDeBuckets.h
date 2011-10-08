#include <iostream>
#include "../Archivos/Hashing/Bucket.h"
#include "../Archivos/Hashing/ArchivoDeBuckets.h"

#ifndef TESTARCHIVODEBUCKETS_H_
#define TESTARCHIVODEBUCKETS_H_

class TestArchivoDeBuckets {
private:
	Bucket* crearBucket1();
	Bucket* crearBucket2();
	Bucket* crearBucket3();
	Bucket* crearBucket4();
	Bucket* crearBucket5();
	void mostrarBucket(ArchivoDeBuckets* archivo,int numeroDeBucket);
public:
	TestArchivoDeBuckets();
	void testAltaBajaDeBucketsEnArchivoDeBuckets();
	~TestArchivoDeBuckets();
};

#endif /* TESTARCHIVODEBUCKETS_H_ */
