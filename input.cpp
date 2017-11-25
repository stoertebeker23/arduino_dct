#include "input.h"

using std::vector;
using std::string;
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;

vector<double> readFile(string filename) {
    vector<double> input;
    std::ifstream _file(filename);

    if(!_file.good()) {
        cout << "Could not read input file" << endl;
        return input;
    }

    std::string str;
    while (std::getline(_file, str)) {
        input.push_back(atof(str.c_str()));
    }
    
    return input;
}
