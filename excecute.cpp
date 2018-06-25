
#include "cache.cpp"

class excecute {
public:
    excecute(int memory_cycles, int block_size, int l1_size, int l1_cycles, int l2_size, int l2_cycles,
             int write_allocation, int l1_ways, int l2_ways);
    void handle_line(int line, char op);
    void get_res(double*, double*, double*);

private:
    int memory_cycles;
    int block_size;
    int l1_size;

    int l1_cycles;
    int l2_size;
    int l2_cycles;
    int write_allocation;

    cache l1;
    cache l2;

    int total_lines;
    int totalCycles;
    double missCountL1;
    double hitCountL1;
    double missCountL2;
    double hitCountL2;

};

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
			totalCycles += memory_cycles;
		}
		totalCycles += l2_cycles;
	}

	totalCycles += l1_cycles;
	
}

void excecute::get_res(double* l1missRate, double* l2missRate, double* avg) {
    missCountL1 = l1.miss_counter;
    missCountL2 = l2.miss_counter;

	*l1missRate = ((float)missCountL1 / (float)totalCycles);
	*l2missRate = ((float)missCountL2 / (float)missCountL1);
	*avg = ((float)totalCycles / (float)total_lines);
}


