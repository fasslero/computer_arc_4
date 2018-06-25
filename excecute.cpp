
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
    bool write_en = (op == 'w') && write_allocation || op == 'r';
    int temp_address = NULL;

    totalCycles += l1_cycles;
    // search in l1
    if(!l1.cache_access(line, op)){
        totalCycles += l2_cycles;
        // not in l1, search in l2
        if(!l2.cache_access(line, op)){
            totalCycles += memory_cycles;
            // not in l2 - write it to l2 if needed
            if (write_en){
                // write it to l2 and get the address of l1 that need to be invalidated
                temp_address = l2.write(line, 1, op);
                if (temp_address != -1)
                    l1.invalidate(temp_address);
            }
        }
        // write to l1 if needed
        if (write_en){
            temp_address = l1.write(line, 2, op);
            if (temp_address != -1)
                l2.cache_access(temp_address, op);
        }
    }
}

void excecute::get_res(double* l1missRate, double* l2missRate, double* avg) {
    missCountL1 = l1.miss_counter;
    missCountL2 = l2.miss_counter;

	*l1missRate = ((float)missCountL1 / (float)total_lines);
	*l2missRate = ((float)missCountL2 / (float)missCountL1);
	*avg = ((float)totalCycles / (float)total_lines);
}
