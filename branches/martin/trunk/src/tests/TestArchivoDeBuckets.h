#include <iostream>
#include "../logica/Archivos/Hashing/Bucket.h"
#include "../logica/Archivos/Hashing/ArchivoDeBuckets.h"

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
	void testAgregarDistrito(Bucket* bucket,string lugar);
public:
	TestArchivoDeBuckets();
	void testLecturaEscrituraDeBuckets();
	void testAgotamiento();
	void testObtenerBucketFallas();
	void testAccesoADisco();
	void testAltaBajaDeBucketsEnArchivoDeBuckets();
	~TestArchivoDeBuckets();
};

#endif /* TESTARCHIVODEBUCKETS_H_ */
