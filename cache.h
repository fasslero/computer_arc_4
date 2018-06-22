//
// Created by ofer fassler on 19/06/2018.
//

#ifndef COMPUTER_ARC_4_CACHE_H
#define COMPUTER_ARC_4_CACHE_H
#include <cstdlib>


/*memory block class*/
class block {

public:
	int timeCounter;
	bool valid;			// probably not essential
	int address;
	block() :  timeCounter(INT_MAX), valid(false), address(0) {};

};



class cache {
	int Ways;
	int Size;			// sizes are in log2()
	int blockSize;
	int blocksPerWay;
	block* arr;
	int arrLen;
	int delay;
	

public:
	cache(int ways, int size, int blocksize, int delaytime);
	void write(int address);
	bool read(int address);
	void removeLRU();
	int numOfMiss;


};




#endif //COMPUTER_ARC_4_CACHE_H
