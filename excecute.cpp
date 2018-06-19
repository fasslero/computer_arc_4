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

class excecute {
public:
    excecute(int memory_cycles, int block_size, int l1_size, int l1_cycles, int l2_size, int l2_cycles,
             int write_allocation, const stringstream &input_lines);

private:
    int memory_cycles;
    int block_size;
    int l1_size;

    int l1_cycles;
    int l2_size;
    int l2_cycles;
    int write_allocation;

    stringstream input_lines;
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

excecute::excecute(int memory_cycles, int block_size, int l1_size, int l1_cycles, int l2_size, int l2_cycles,
                   int write_allocation, const stringstream &input_lines,int l1_ways, int l2_ways
) :
                                                                            memory_cycles(memory_cycles),
                                                                            block_size(block_size), l1_size(l1_size),
                                                                            l1_cycles(l1_cycles), l2_size(l2_size),
                                                                            l2_cycles(l2_cycles),
                                                                            write_allocation(write_allocation),
                                                                            input_lines(input_lines) {
    l1 = cache::cache(l1_ways,)

}




