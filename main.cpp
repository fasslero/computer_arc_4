#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

using std::FILE;
using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::stringstream;


class prog{

    int memory_cycles_arg;
    int block_size_arg;
    int l1_size_arg;
    int l1_ways_arg;
    int l1_cycles_arg;
    int l2_size_arg;
    int l2_ways_arg;
    int l2_cycles_arg;
    int write_allocation_arg;
    string fileString;
public:
    bool read_args(char **argv);
    void prog(int argc, char **argv);
    int main();

};

// Get input arguments
bool prog::read_args(char **argv) {
    // Assuming file name is the first argument
    fileString = argv[1];
    //read all the other arguments
    for (int i = 2; i < 19; i += 2) {
        string s(argv[i]);
        if (s == "--mem-cyc") {
            memory_cycles_arg = atoi(argv[i + 1]);
        } else if (s == "--bsize") {
            block_size_arg = atoi(argv[i + 1]);
        } else if (s == "--l1-size") {
            l1_size_arg = atoi(argv[i + 1]);
        } else if (s == "--l2-size") {
            l2_size_arg = atoi(argv[i + 1]);
        } else if (s == "--l1-cyc") {
            l1_cycles_arg = atoi(argv[i + 1]);
        } else if (s == "--l2-cyc") {
            l2_cycles_arg = atoi(argv[i + 1]);
        } else if (s == "--l1-assoc") {
            l1_ways_arg = atoi(argv[i + 1]);
        } else if (s == "--l2-assoc") {
            l2_ways_arg = atoi(argv[i + 1]);
        } else if (s == "--wr-alloc") {
            write_allocation_arg = atoi(argv[i + 1]);
        } else {
            printf("Error in arguments");
            return false;
        }
    }
    // every thing is OK
    return true;
}

prog::prog(int argc, char **argv) {
    if (argc < 19){
        printf("Not enough arguments ");
        exit(1);
    }
    //read the args
    read_args(argv);

}


int prog::main(){
    //read the file and analays the program

    ifstream file(fileString); //input file stream
    string line;
    if (!file || !file.good()) {
        // File doesn't exist or some other error
        cerr << "File not found" << endl;
        return 0;
    }

	//creating the caches todo : need to put all the arg
	excecute exe();

    while (getline(file, line)) {

        stringstream ss(line);
        string address;
        char operation = 0; // read (R) or write (W)
        if (!(ss >> operation >> address)) {
            // Operation appears in an Invalid format
            cout << "Command Format error" << endl;
            return 0;
        }
      
    

        string cutAddress = address.substr(2); // Removing the "0x" part of the address

        unsigned long int address = 0;
        address = strtoul(cutAddress.c_str(), NULL, 16);
		exe.handle_line(address, operation);
        
    }
    
    
    //print

    double L1MissRate;
    double L2MissRate;
    double avgAccTime;
    
    exe.get_results();

    printf("L1miss=%.03f ", L1MissRate);
    printf("L2miss=%.03f ", L2MissRate);
    printf("AccTimeAvg=%.03f\n", avgAccTime);

}
