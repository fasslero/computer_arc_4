//
// Created by ofer fassler on 19/06/2018. henry
//

#include "cache.h"
#include <math.h>

cache::cache(int ways, int size, int blocksize, int delaytime) {
	Size = size;
	Ways = ways;
	blockSize = blocksize;
	delay = delaytime;
	arrLen = pow(2, (Size - blockSize));	// 2^(size-blocksize)
	arr = new block[arrLen];

	if (Ways <= 1)			//one way: need to check only in one index of array
		blocksPerWay = arrLen;		// iterator will only read one cell		
	else
		blocksPerWay = arrLen / (pow(2, Ways));		// 2^(size-blocksize-ways)
}

void cache::write(int address){

}
