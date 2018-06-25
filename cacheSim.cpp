#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "main.cpp"

using std::FILE;
using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::stringstream;

int main(int argc, char **argv){
    prog my_prog = prog(argc, argv);
    my_prog.main();
}

