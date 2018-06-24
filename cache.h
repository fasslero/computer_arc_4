

//
// Created by ofer fassler on 19/06/2018.
//

#ifndef COMPUTER_ARC_4_CACHE_H
#define COMPUTER_ARC_4_CACHE_H
#include <cstdlib>
#include <vector>
#include <math.h>

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
	block() : time_counter(0), valid(false), address(0), dirty(false), tag(0) {};
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
	cache(int associative, int cache_size, int block_size, int cache_access_time, bool WA);
	bool cache_access(int address, char op);

	//void remove_lRU();
	block* get_lru(int address);
	int miss_counter;
	int hit_counter;
	int set_calc(int address);
	int tag_calc(int address);
	block* search(int address);

};

class excecute {
public:
	excecute(int memory_cycles, int block_size, int l1_size, int l1_cycles, int l2_size, int l2_cycles,
		int write_allocation, int l1_ways, int l2_ways);
	void handle_line(int line, char op);

private:
	int memory_cycles;
	int block_size;
	int l1_size;

	int l1_cycles;
	int l2_size;
	int l2_cycles;
	int write_allocation;

	//todo - create Cach objects
	cache l1;
	cache l2;

	int totalCycles;
	double missCountL1;
	double hitCountL1;
	double missCountL2;
	double hitCountL2;

public:



};


#endif //COMPUTER_ARC_4_CACHE_H
