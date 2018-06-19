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
    while (getline(file, line)) {

        stringstream ss(line);
        string address;
        char operation = 0; // read (R) or write (W)
        if (!(ss >> operation >> address)) {
            // Operation appears in an Invalid format
            cout << "Command Format error" << endl;
            return 0;
        }
        // todo - calc the arguments (2**block_size etc)
        // todo - do algorithm

        // DEBUG - remove this line
        cout << "operation: " << operation;

        string cutAddress = address.substr(2); // Removing the "0x" part of the address

        // DEBUG - remove this line
        cout << ", address (hex)" << cutAddress;

        unsigned long int num = 0;
        num = strtoul(cutAddress.c_str(), NULL, 16);

        // DEBUG - remove this line
        cout << " (dec) " << num << endl;
    }
}