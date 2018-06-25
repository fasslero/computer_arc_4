//
// Created by ofer fassler on 19/06/2018. henry
//

#include <vector>
#include <cmath>

using namespace std;

/*memory block class*/
class block {

public:
    int time_counter;
    bool valid;
    bool dirty; // probably not essential
    int address;
    int tag;
    block() : time_counter(0), valid(false), address(0), dirty(false), tag(0) {};
};

typedef vector<block*> blockVec;
typedef vector<blockVec*> vecOfBlockVec;

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
	bool write_allocate;
    int cache_access_counter; // for miss rate calc

public:
    cache(int associative, int cache_size, int block_size, int cache_access_time, bool WA);
    bool cache_access(int address, char op);

    //void remove_lRU();
    block* get_lru(int address);
    int miss_counter;
    int hit_counter;
    int set_calc(int address);
    int tag_calc(int address);
    block* search(int address);
	int write(int address, int valid_or_dirty);
	void invalidate(int address);
};


cache::cache(int associative, int cache_size, int block_size, int cache_access_time,bool _write_allocate) : cache_size(cache_size),
block_size(block_size), blocks_per_way(),
cache_access_time(cache_access_time),
time_conter(0), cache_access_counter(0),
hit_counter(0), write_allocate(_write_allocate)
{
	num_of_ways = (int)pow(2, associative);
	set_size = cache_size - block_size - associative;
	num_of_sets = (int)pow(2, set_size);
	miss_counter = 0;

	for (int i = 0; i < num_of_ways; ++i) {
		//create a vector of blocks for each way
		blockVec* way_i = new blockVec();
		for (int j = 0; j < num_of_sets; ++j) {
			// create and add a block for each set in each way
			block* block_m = new block();
			way_i->push_back(block_m);
		}
		//add the way to the cache
		ways.push_back(way_i);
	}
}

bool cache::cache_access(int address, char op) {

	//search for the address
	block* block_in_cache = search(address);

	if (block_in_cache) {
		//the block is in the cache
		//read operation
		if (op == 'r') {
			return true;
		}
		// write op
		else {
			time_conter++;
			block_in_cache->dirty = true;
			block_in_cache->time_counter = time_conter;
			return true;
		}
	}
	// the block is there
	else {
		miss_counter++;
		return false;
	}
}


int cache::set_calc(int address) {
	int address_block_size_shift = address >> block_size;
	return (address_block_size_shift - ((address_block_size_shift >> set_size) << set_size));
}

int cache::tag_calc(int address) {
	return address >> (block_size + set_size);
}

/*!
* search for the line in the cache, return block pointer if found, else return nullptr
*/
block* cache::search(int address) {

	// calc the right set and tag number for this address
	int address_set = set_calc(address);
	int address_tag = tag_calc(address);
	//add one for cache access

    block* block_i;

    //search for the address
	for (int i = 0; i < num_of_ways; i++) {// check if tag is in way i(in the set)
		block_i = ways[i]->at(address_set);
		if ((address_tag == block_i->tag) && block_i->valid) {
			// the data is in the cache!
			time_conter++;
			block_i->time_counter = time_conter;
			hit_counter++;
			return block_i;
		}
	}

    return nullptr;
}

block *cache::get_lru(int address) {
	// calc the right set and tag number for this address
	int address_set = set_calc(address);
	block* return_block = nullptr;
	block* block_i;
	int min = INT_MAX;

	// find the LRU
	for (int i = 0; i < num_of_ways; i++) {
		block_i = (*ways[i])[address_set];
		if (!block_i->valid){
			min = block_i->time_counter;
			return_block = block_i ;
			break;
		}
		else if (block_i->time_counter < min) {
			min = block_i->time_counter;
			return_block = block_i ;
		}
	}
	return return_block;
}

int cache::write(int address, int valid_or_dirty) {
    int address_to_return = -1;
	block* write_block = get_lru(address);

	// if valid in l1, we need to save it in l2
	// if dirty in l1, we need to update it in l2
	if ((write_block->valid && valid_or_dirty == 1) || (write_block->dirty && valid_or_dirty == 2))
		address_to_return = write_block->address;

	time_conter++;

    write_block->time_counter = time_conter;
    write_block->dirty = false;
    write_block->tag = tag_calc(address);
    write_block->address = address;
    write_block->valid = true;

	return address_to_return;
}

void cache::invalidate(int address){
	block* block_in_cache = search(address);
	if (block_in_cache)
		block_in_cache->valid = false;
}