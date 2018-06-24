#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "cache.h"

using std::FILE;
using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::stringstream;


excecute::excecute(int memory_cycles, int block_size, int l1_size, int l1_cycles, int l2_size, int l2_cycles,
	int write_allocation, int l1_ways, int l2_ways
) :
	memory_cycles(memory_cycles),
	block_size(block_size), l1_size(l1_size),
	l1_cycles(l1_cycles), l2_size(l2_size),
	l2_cycles(l2_cycles),
	write_allocation(write_allocation),
	totalCycles(0), total_lines(0),missCountL1(0),missCountL2(0),

	l1(l1_ways, l1_size, block_size, l1_cycles, write_allocation),
	l2(l2_ways, l2_size, block_size, l2_cycles, write_allocation) {};


void excecute::handle_line(int line, char op) {
	total_lines++;
	if (!(l1.cache_access(line, op))) {		//not in L1
		if (!l2.cache_access(line, op)) {	//not in L2
			totalCycles += (l1_cycles + l2_cycles + memory_cycles);
		}
		totalCycles += (l1_cycles + l2_cycles);
	}

	totalCycles += l1_cycles;
	
}

void excecute::get_res(double* l1missRate, double* l2missRate, double* avg) {

	*l1missRate = ((float)missCountL1 / (float)totalCycles);
	*l2missRate = ((float)missCountL2 / (float)missCountL1);
	*avg = ((float)totalCycles / (float)total_lines);


}


