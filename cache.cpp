//
// Created by ofer fassler on 19/06/2018. henry
//

#include "cache.h"
#include <vector>
#include <math.h>

using namespace std;
typedef vector<block> blockVec;
typedef vector<blockVec> vecOfBlockVec;

/*memory block class*/
class block {

public:
    int time_counter;
    bool valid;
    bool dirty; // probably not essential
    int address;
    int tag;
    block() :  time_counter(0), valid(false), address(0), dirty(false), tag(0) {};
};

class cache {
    int num_of_ways;
    int cache_size;			// sizes are in log2()
    int block_size;
    int blocks_per_way;
    int set_size;
    int num_of_sets;
    int cache_access_time;
    vecOfBlockVec ways;
    int time_conter;
    int cache_access_counter; // for miss rate calc

public:
    cache(int associative, int cache_size, int block_size, int cache_access_time);
    void cache_access(int address, char op);

    void remove_lRU();
    int miss_counter;
    int set_calc(int address);
    int tag_calc(int address);
};

/*

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

*/


cache::cache(int associative, int cache_size, int block_size, int cache_access_time): cache_size(cache_size),
                                                                        block_size(block_size), blocks_per_way(),
                                                                        cache_access_time(cache_access_time),
                                                                        time_conter(0), cache_access_counter(0)
{
    num_of_ways = (int)pow(2,associative);
    set_size = cache_size - block_size - associative;
    num_of_sets = (int)pow(2,num_of_sets);
    miss_counter = 0;

    for (int i = 0; i < num_of_ways; ++i) {
        //create a vector of blocks for each way
        blockVec way_i;
        for (int j = 0; j < num_of_sets ; ++j) {
            // create and add a block for each set in each way
            block block;
            way_i.push_back(block);
        }
        //add the way to the cache
        ways.push_back(way_i);
    }
}

void cache::cache_access(int address, char op) {
    // calc the right set and tag number for this address
    // todo - write tag and set number functions
    int address_set = set_calc(address);
    int address_tag = tag_calc(address);
    //add one for cache access
    cache_access_counter++;
    //search for the address

    for (int i = 0; i < num_of_ways; i++) {// check if tag is in way i(in the set)
        if (address_tag == ways[i][address_set].tag && ways[i][address_set].valid) {
        // the data is in the cache!
            //read operation
            if (op == 'r'){
                time_conter++;
                ways[i][address_set].time_counter = time_conter;
                return;
            }

                //write operation
            else{
                // todo - who to take out?
            }
        }
        //the data is not in the cache for read op, todo - but what about write?
        miss_counter++;
    }

}

int cache::set_calc(int address) {
    int address_block_size_shift = address >> block_size;
    return (address_block_size_shift - ((address_block_size_shift >> set_size) << set_size));
}

int cache::tag_calc(int address) {
    return address >> (block_size + set_size);
}

