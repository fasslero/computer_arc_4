#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "cache.cpp"

using std::FILE;
using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::stringstream;

class excecute {

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





